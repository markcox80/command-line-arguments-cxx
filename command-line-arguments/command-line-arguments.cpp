#include "command-line-arguments.hpp"
#include <stdexcept>

using namespace std;

/* Not enough arguments error */

not_enough_arguments_error::not_enough_arguments_error()
  : runtime_error("Not enough command line arguments provided.")
{
}


/* Missing argument value error */

missing_argument_value_error::missing_argument_value_error(const std::string &argument)
  : runtime_error(string("The command line argument ") + argument + " requires an argument.")
{
}


/* Excess argument error */

excess_argument_error::excess_argument_error(const std::string &argument)
  : runtime_error(string("Do not know how to process argument ") + argument)
{
}


/* Unsupported option error */

unsupported_option_error::unsupported_option_error(const std::string &option)
  : runtime_error(string("The option ") + option + " is not recognised by this program.")
{
}

/* Coercions
 *
 */

template <>
void
get_command_line_argument(string *rv, int *i, int argc, const char **argv)
{
  if ((*i + 1) >= argc)
    throw missing_argument_value_error(argv[*i]);

  *i = (*i + 1);
  *rv = argv[*i];
}


/* Command line option test. */

bool
command_line_option_p(const std::string &value)
{
  switch (value.size()) {
  case 0:
  case 1:
    return false;
  case 2:
    if (value == "--")
      return false;
    else
      return (value[0] == '-');
  default:
    return (value[0] == '-') && (value[1] == '-');
  }
}
