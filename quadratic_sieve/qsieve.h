#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

#ifndef POLLARD_RHO

#include "pollard_rho.c"
#define POLLARD_RHO

#endif

#ifndef LINEAR_SOLVE

#include "linalg.c"
#define LINEAR_SOLVE

#endif


// defs
typedef long long ll;


