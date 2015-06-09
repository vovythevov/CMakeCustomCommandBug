
#include <foo.h>

foo::foo() : QObject()
{
}

void foo::foo_something()
{
  std::cout << "Plop" << std::endl;
}