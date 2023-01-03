/*
   This code is an example to show how we can measure the CPU time
   used for some specific procedures. The idea is to call the function
   mytimer() before and after excuting the procedure (in this example,
   I use a for loop), the difference of the float numbers returned
   represents the time spent for the procedures between these 2 calls
   of mytimer().

   to compile:
               g++ -o check_time check_time.c
   to run:
               check_time
	       input k= 10000000
	       k=10000000, totally takes time= 1156.000 (this number
               may differ depending on your CPU/OS..etc)
  !note: this code can compile/run under cygwin or SunOS using g++ or
         gcc. Whether it works in VC6.0 or not is unknown.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/times.h>

float mytimer()
{ struct tms hold;

 times(&hold);
 /*return  (float)(hold.tms_utime) / 60.0;*/
 return  (float)(hold.tms_utime);
}
