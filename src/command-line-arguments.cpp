#include "command-line-arguments.hpp"
#include <stdexcept>

using namespace std;

/* Not enough arguments error */

not_enough_arguments_error::not_enough_arguments_error()
  : runtime_error("The program is missing command line arguments.")
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

/* Coercions
 *
 */

template <>
void
get_command_line_argument(string *rv, int *i, int argc, const char **argv)
{
  if ((*i + 1) >= argc)
    throw runtime_error(string("Not enough arguments to process argument: ") + argv[*i]);

  *i = (*i + 1);
  *rv = argv[*i];
}
