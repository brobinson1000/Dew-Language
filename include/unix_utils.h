#ifndef UNIX_UTILS_H
#define UNIX_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


/* Suspends execution for a given number of seconds.
    @param cmd A C string representing the number of seconds to sleep (integer or float).
    @behavior Parses the string and blocks the current thread for the specified duration.
    @sideeffects Blocks the current thread; execution resumes after sleep.  */
    
void sleepCommand(const char* cmd);

/* Retrieves the current wall clock time.
    @param cmd Unused parameter (included for consistency with command interface).
    @behavior Can be adapted to print or return the current time with microsecond precision.
    @sideeffects May write output to stdout or store time in a language-specific structure. */

void timeofdayCommand(const char* cmd);


void systemCommand(const char* cmd);
  


#ifdef __cplusplus
}
#endif

#endif

