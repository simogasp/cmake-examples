#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C"
{
  char *pDest2;

  void foo2(char *p)
  {
    if (p)
    {
      memcmp(pDest2, p, 10);
    }
  }

  void bar()
  {
    foo2(NULL);
  }
}
