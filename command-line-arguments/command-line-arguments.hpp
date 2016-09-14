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
 ** HAVE_ARGUMENT_P boiler plate.
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

template <typename T1, typename T2>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2);
}

template <typename T1, typename T2, typename T3>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3);
}

template <typename T1, typename T2, typename T3, typename T4>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3,
                      const CommandLineArgument<T4> &argument4)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3)
    && have_argument_p(argument4);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3,
                      const CommandLineArgument<T4> &argument4,
                      const CommandLineArgument<T5> &argument5)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3)
    && have_argument_p(argument4)
    && have_argument_p(argument5);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3,
                      const CommandLineArgument<T4> &argument4,
                      const CommandLineArgument<T5> &argument5,
                      const CommandLineArgument<T6> &argument6)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3)
    && have_argument_p(argument4)
    && have_argument_p(argument5)
    && have_argument_p(argument6);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3,
                      const CommandLineArgument<T4> &argument4,
                      const CommandLineArgument<T5> &argument5,
                      const CommandLineArgument<T6> &argument6,
                      const CommandLineArgument<T7> &argument7)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3)
    && have_argument_p(argument4)
    && have_argument_p(argument5)
    && have_argument_p(argument6)
    && have_argument_p(argument7);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
bool have_arguments_p(const CommandLineArgument<T1> &argument1,
                      const CommandLineArgument<T2> &argument2,
                      const CommandLineArgument<T3> &argument3,
                      const CommandLineArgument<T4> &argument4,
                      const CommandLineArgument<T5> &argument5,
                      const CommandLineArgument<T6> &argument6,
                      const CommandLineArgument<T7> &argument7,
                      const CommandLineArgument<T8> &argument8)
{
  return true
    && have_argument_p(argument1)
    && have_argument_p(argument2)
    && have_argument_p(argument3)
    && have_argument_p(argument4)
    && have_argument_p(argument5)
    && have_argument_p(argument6)
    && have_argument_p(argument7)
    && have_argument_p(argument8);
}


/**
 ** ASSIGN_ARGUMENT boiler plate.
 **/

template <typename T>
bool assign_argument(const std::string &value, CommandLineArgument<T> &argument)
{
  if (have_argument_p(argument))
    return false;
  else {
    argument = value;
    return true;
  }
}

template <typename T1, typename T2>
bool assign_argument(const std::string &value, CommandLineArgument<T1> &argument1, CommandLineArgument<T2> &argument2)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2);
}

template <typename T1, typename T2, typename T3>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3);
}

template <typename T1, typename T2, typename T3, typename T4>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3,
                     CommandLineArgument<T4> &argument4)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3)
    || assign_argument(value, argument4);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3,
                     CommandLineArgument<T4> &argument4,
                     CommandLineArgument<T5> &argument5)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3)
    || assign_argument(value, argument4)
    || assign_argument(value, argument5);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3,
                     CommandLineArgument<T4> &argument4,
                     CommandLineArgument<T5> &argument5,
                     CommandLineArgument<T6> &argument6)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3)
    || assign_argument(value, argument4)
    || assign_argument(value, argument5)
    || assign_argument(value, argument6);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3,
                     CommandLineArgument<T4> &argument4,
                     CommandLineArgument<T5> &argument5,
                     CommandLineArgument<T6> &argument6,
                     CommandLineArgument<T7> &argument7)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3)
    || assign_argument(value, argument4)
    || assign_argument(value, argument5)
    || assign_argument(value, argument6)
    || assign_argument(value, argument7);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
bool assign_argument(const std::string &value,
                     CommandLineArgument<T1> &argument1,
                     CommandLineArgument<T2> &argument2,
                     CommandLineArgument<T3> &argument3,
                     CommandLineArgument<T4> &argument4,
                     CommandLineArgument<T5> &argument5,
                     CommandLineArgument<T6> &argument6,
                     CommandLineArgument<T7> &argument7,
                     CommandLineArgument<T8> &argument8)
{
  return false
    || assign_argument(value, argument1)
    || assign_argument(value, argument2)
    || assign_argument(value, argument3)
    || assign_argument(value, argument4)
    || assign_argument(value, argument5)
    || assign_argument(value, argument6)
    || assign_argument(value, argument7)
    || assign_argument(value, argument8);
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

template <typename T, bool U, bool V>
struct CoerceToNumberFunctorSelector<T, true, U, V>
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
  if ((end == data_end) && (limits.min() <= value) && (value <= limits.max()))
    *arg = static_cast<T>(value);
  else
    throw std::runtime_error(std::string("Unable to convert value ") + string_value + " to the specified number type.");
}

#endif