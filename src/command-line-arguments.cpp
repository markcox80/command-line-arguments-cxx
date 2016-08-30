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

/* get_argument
 *
 */

string
get_argument(int *i, int argc, char **argv)
{
  if ((*i + 1) >= argc) 
    throw runtime_error(string("Not enough arguments to process argument: ") + argv[*i]);

  *i = (*i + 1);
  return argv[*i];
}


/* Coercions
 *
 */

template <>
double
coerce_command_line_argument(const std::string &value)
{
  size_t index;  
  double result = stod(value, &index);
  if (index != value.size())
    throw runtime_error(string("Unable to convert ") + value + " to a double.");
  return result;
}