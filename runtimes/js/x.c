#include <stdio.h>
#include <stddef.h>

// struct X { char a; int b; };


// struct T { long long a; long long b; long long c; long long d; };
struct T { long long a; };

struct X { char a[11]; struct T b; };

int main() {
  printf("Size = %lu\n", sizeof(struct X));
  printf("OffsetOf(a) = %lu\n", offsetof(struct X, a));
  printf("OffsetOf(b) = %lu\n", offsetof(struct X, b));
}

