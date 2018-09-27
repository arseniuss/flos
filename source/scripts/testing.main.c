#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor(0)))
void init(void) {
  printf("%-20s:%4s %-80s ... %3s\n", "Function", "line", "condition", "result");
}

void
assert_log (const char * file, int line, const char* cond)
{
  printf ("%s:%i %s ... ", file, line, cond);
}

void
assert_fail ()
{

  printf ("FAIL\n");

  exit (1);
}

void
assert_info (const char * fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  vprintf (fmt, args);

  va_end (args);
}

int
main (void)
{
  printf ("All tests passed!\n");

  return 0;
}
