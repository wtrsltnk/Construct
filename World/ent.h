#ifndef ENT_H_
#define ENT_H_

#include "../Common/cmdlib.h"
#include "../Common/mathlib.h"

#define MAX_ENTITIES 1024

typedef struct epair_s
{
   struct epair_s *next;
   char  *key;
   char  *value;
} epair_t;

typedef struct
{
   vec3_t      origin;
   int         firstbrush;
   int         numbrushes;
   epair_t     *epairs;
} entity_t;

#endif /*ENT_H_*/
