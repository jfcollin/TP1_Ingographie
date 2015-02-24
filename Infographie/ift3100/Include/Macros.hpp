#ifndef  MACROS_HPP
#define  MACROS_HPP

#include <stdlib.h>
#include <math.h>

#ifndef PI
#define PI (float)3.14159265359
#endif

#ifndef GLSL
#define GLSL(version, A) "#version " #version "\n" #A
#endif  

#ifndef RAND
#define RAND (1.0 * rand() / (RAND_MAX))
#endif

#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n,id) glGenVertexArrays(n,id)
#endif

#ifndef BINDVERTEXARRAY
#define BINDVERTEXARRAY(id) glBindVertexArray(id)
#endif


#endif	// !MACROS_HPP