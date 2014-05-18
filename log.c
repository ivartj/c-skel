#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "log.h"
#include "main.h"

void log_warn(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "%s: ", main_name);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, ".\n");
	va_end(ap);
}

void log_errno(const char *fmt, ...)
{
	va_list ap;
	int errcode;

	errcode = errno;
	va_start(ap, fmt);
	fprintf(stderr, "%s: ", main_name);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, ": %s.\n", strerror(errno));
	va_end(ap);
}
