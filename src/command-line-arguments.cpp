#include "command-line-arguments.hpp"
#include <stdexcept>

using namespace std;

string
get_argument(int *i, int argc, char **argv)
{
  if ((*i + 1) >= argc) 
    throw runtime_error(string("Not enough arguments to process argument: ") + argv[*i]);

  *i = (*i + 1);
  return argv[*i];
}
