#include "command-line-arguments.hpp"
#include <stdexcept>

using namespace std;

/* Not enough arguments error */

not_enough_arguments_error::not_enough_arguments_error(const string &argument)
  : runtime_error(string("The command line option ") + argument + " requires an argument.")
{

}

static
not_enough_arguments_error
not_enough_arguments(const char *arg)
{
  return not_enough_arguments_error(arg);
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
