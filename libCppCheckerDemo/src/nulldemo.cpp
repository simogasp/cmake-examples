#include <cstdio>
#include <cstdlib>
#include <cstring>

int fn()
{
    return 1;
}

int forward_null_example1(int *p) {
    int x;
    if ( p == NULL ) {
        x = 0;
    } else {
        x = *p;
    }
    x += fn();
    *p = x;   // Defect: p is potentially NULL
    return 0;
}

char *pDest;

void test1() {
  memcpy(pDest, NULL, 10);
}

// char *pDest;

void foo2(char *p) {
  memcmp(pDest, p, 10);
}

void bar2() {
  foo2(NULL);
}