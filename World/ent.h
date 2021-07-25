#ifndef ENT_H_
#define ENT_H_

#include "../Common/cmdlib.h"
#include "../Common/mathlib.h"

#define MAX_ENTITIES 1024

typedef struct epair_s
{
   struct epair_s *next = nullptr;
   char  *key = nullptr;
   char  *value = nullptr;
} epair_t;

typedef struct
{
   vec3_t      origin;
   int         firstbrush;
   int         numbrushes;
   epair_t     *epairs = nullptr;
} entity_t;

#endif /*ENT_H_*/
