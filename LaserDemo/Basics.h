#ifndef BASICS_H
#define BASICS_H

// typedef for fix point numbers
typedef long FIXPT;
#define PSHIFT           14
#define PRES             (1 << PSHIFT)
#define PROUNDBIT        (1 << (PSHIFT-1))
#define FROM_FLOAT(a) (long(a*PRES))
#define FROM_INT(a) (a << PSHIFT)
//#define TO_INT(a) ((a + PROUNDBIT)>> PSHIFT) 
#define TO_INT(a) (a >> PSHIFT)
#define FPMASK (0xfff << PSHIFT)

#endif

