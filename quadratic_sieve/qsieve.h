#ifndef QSIEVE_H
#define QSIEVE_H
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

#ifndef POLLARD_RHO

#include "pollardrho.c"
#define POLLARD_RHO

#endif

#ifndef LINEAR_SOLVE

//#include "linalg.c"
#define LINEAR_SOLVE

#endif

#ifndef VECTOR_32
#define VECTOR_32
#include "vector.c"
#endif


#ifndef LONG_LONG_AS_LL
// defs
#define LONG_LONG_AS_LL
typedef long long ll;
#endif

#endif
