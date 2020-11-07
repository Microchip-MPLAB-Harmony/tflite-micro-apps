/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

// Used by TFLite error_reporter
void DebugLog(const char *s)
{
	fprintf(stderr, "%s", s);
	// NOTE: fprintf uses _write(), which is defined in syscall.c
	//       _write() uses __io_putchar(), which is a weak function
	//       and needs to be implemented by user.
}

