#ifndef _COMMAND_LINE_ARGUMENTS_HPP_
#define _COMMAND_LINE_ARGUMENTS_HPP_

extern "C" {
#include <inttypes.h>
};

#include <string>
#include <stdexcept>
#include <sstream>


/* Exceptions
 *
 */

struct not_enough_arguments_error : public std::runtime_error
{
  not_enough_arguments_error();
};

struct excess_argument_error : public std::runtime_error
{
  excess_argument_error(const std::string &value);
};

struct missing_argument_value_error : public std::runtime_error
{
  missing_argument_value_error(const std::string &argument);
};

/* String to value conversion functions.
 *
 */
template <typename T> void coerce_command_line_argument(T *arg, const std::string &value);

/* Get arguments
 *
 */

template <typename T>
void get_command_line_argument(T *arg, int*i, int argc, const char **argv);

template <>
void get_command_line_argument(std::string *arg, int *i, int argc, const char **argv);

template <typename T>
void
get_command_line_argument(T *arg, int *i, int argc, const char **argv)
{
  std::string string_value;
  int previous_value = *i;
  try {
    get_command_line_argument(&string_value, i, argc, argv);
    coerce_command_line_argument(arg, string_value);
  } catch (...) {
    *i = previous_value;
    throw;
  }
}

/* Command Line Argument for general values.
 *
 */
template <class T>
class CommandLineArgument
{
public:
  CommandLineArgument() : is_assigned(false) {}

  CommandLineArgument &operator=(const T &argument) {
    is_assigned = true;
    value = argument;
    return *this;
  }

  CommandLineArgument &operator=(const std::string &string) {
    coerce_command_line_argument(&value, string);
    is_assigned = true;
    return *this;
  }

  T &operator*() {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain reference to value of expected command line argument as no value has been assigned.");

    return value;
  }

  T *operator->() {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain pointer to value of expected command line argument as no value has been assigned.");

    return &value;
  }

  bool isAssigned() const {
    return is_assigned;
  }

private:
  bool is_assigned;
  T value;
};


/* Command Line Argument for strings.
 *
 */

template <>
class CommandLineArgument<std::string>
{
public:
  CommandLineArgument() : is_assigned(false) {}
  CommandLineArgument &operator=(const std::string &argument) {
    is_assigned = true;
    value = argument;

    return *this;
  }

  std::string &operator*() {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain reference to value of expected command line argument as no value has been assigned.");

    return value;
  }

  const std::string &operator*() const {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain reference to value of expected command line argument as no value has been assigned.");

    return value;
  }

  std::string *operator->() {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain pointer to value of expected command line argument as no value has been assigned.");

    return &value;
  }

  const std::string *operator->() const {
    if (!isAssigned())
      throw std::runtime_error("Cannot obtain pointer to value of expected command line argument as no value has been assigned.");

    return &value;
  }

  bool isAssigned() const {
    return is_assigned;
  }

private:
  bool is_assigned;
  std::string value;
};


/**
 ** HAVE_ARGUMENT_P and HAVE_ARGUMENTS_P.
 **/

template <typename T>
bool have_argument_p(const CommandLineArgument<T> &argument)
{
  return argument.isAssigned();
}

template <typename T>
bool have_arguments_p(const CommandLineArgument<T> &argument)
{
  return have_argument_p(argument);
}

template <typename T, typename... Rest>
bool have_arguments_p(const CommandLineArgument<T> &argument, Rest... others)
{
  return true
    && have_argument_p(argument)
    && have_arguments_p(others...);
}

/**
 ** ASSIGN_ARGUMENT
 **/

template <typename V, typename T>
bool assign_argument(const V &value, CommandLineArgument<T> &argument)
{
  if (have_argument_p(argument))
    return false;
  else {
    argument = value;
    return true;
  }
}

template <typename V, typename T1, typename... Rest>
bool assign_argument(const V &value, CommandLineArgument<T1> &argument1, CommandLineArgument<Rest> & ... others)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, others...);
}

/* Number conversions. */

template <typename T>
struct CoerceToNumberFunctor;

template <>
struct CoerceToNumberFunctor<intmax_t> : public std::binary_function<const char *, char **, intmax_t>
{
  CoerceToNumberFunctor() : base(10) {}
  CoerceToNumberFunctor(int _base) : base(_base) {}

  result_type operator()(const char *string, char **endptr) const {
    return strtoimax(string, endptr, base);
  }

  int base;
};

template <>
struct CoerceToNumberFunctor<uintmax_t> : public std::binary_function<const char *, char **, uintmax_t>
{
  CoerceToNumberFunctor() : base(10) {}
  CoerceToNumberFunctor(int _base) : base(_base) {}

  result_type operator()(const char *string, char **endptr) const {
    return strtoumax(string, endptr, base);
  }

  int base;
};

template <>
struct CoerceToNumberFunctor<double> : public std::binary_function<const char *, char **, double>
{
  result_type operator()(const char *string, char **endptr) const {
    return strtod(string, endptr);
  }
};

template <typename T, bool IsEnum, bool IsInteger, bool IsSigned>
struct CoerceToNumberFunctorSelector;

template <typename T>
struct CoerceToNumberFunctorSelector<T, false, true, true>
{
  typedef CoerceToNumberFunctor<intmax_t> functor_type;
};

template <typename T>
struct CoerceToNumberFunctorSelector<T, false, true, false>
{
  typedef CoerceToNumberFunctor<uintmax_t> functor_type;
};

template <typename T>
struct CoerceToNumberFunctorSelector<T, false, false, true>
{
  typedef CoerceToNumberFunctor<double> functor_type;
};

template <typename T, bool V>
struct CoerceToNumberFunctorSelector<T, true, false, V>
{
  typedef typename std::underlying_type<T>::type underlying_type;

  static const bool is_enum = std::is_enum<T>::value;
  static const bool is_integer = std::is_integral<T>::value;
  static const bool is_signed = std::is_signed<T>::value;

  typedef
  typename CoerceToNumberFunctorSelector<underlying_type, is_enum, is_integer, is_signed>::functor_type
  functor_type;
};

template <typename T>
void
coerce_command_line_argument(T *arg, const std::string &string_value)
{
  static const bool is_enum = std::is_enum<T>::value;
  static const bool is_integer = std::is_integral<T>::value;
  static const bool is_signed = std::is_signed<T>::value;

  typedef typename CoerceToNumberFunctorSelector<T, is_enum, is_integer, is_signed>::functor_type functor_type;

  functor_type functor;

  const char *data = string_value.c_str();
  const char *data_end = data + string_value.size();
  char *end;

  typename functor_type::result_type value = functor(data, &end);

  std::numeric_limits<T> limits;

  if ((end == data_end) && (limits.lowest() <= value) && (value <= limits.max()))
    *arg = static_cast<T>(value);
  else
    throw std::runtime_error(std::string("Unable to convert value ") + string_value + " to the specified number type.");
}

#endif
