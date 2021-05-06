#pragma once
// im insane combining pragma once and header guards LOL
// mostly the reason is bc i didn't know how to use pragma once HAHAHAHAHAH
#ifndef QSIEVE_H
#define QSIEVE_H
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <time.h>


#include "prho.c"


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
