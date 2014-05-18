#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "log.h"
#include "main.h"

void log_warn_psv(const char *fmt, const char *prefix, const char *suffix, va_list ap)
{
	char msg[512];
	size_t off = 0;

	off += snprintf(msg + off, sizeof(msg) - off, "%s: ", main_name);
	if(prefix != NULL)
		off += snprintf(msg + off, sizeof(msg) - off, "%s: ", prefix);
	off += vsnprintf(msg + off, sizeof(msg) - off, fmt, ap);
	if(suffix != NULL)
		off += snprintf(msg + off, sizeof(msg) - off, ": %s", suffix);
	off += snprintf(msg + off, sizeof(msg) - off, ".\n", ap);

	fputs(msg, stderr);
}

void log_warn_v(const char *fmt, va_list ap)
{
	log_warn_psv(fmt, NULL, NULL, ap);
}

void log_warn(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_warn_v(fmt, ap);
	va_end(ap);
}

void log_errno(const char *fmt, ...)
{
	va_list ap;
	int errcode;
	char buf[256];

	errcode = errno;
	va_start(ap, fmt);
	strerror_r(errcode, buf, sizeof(buf));
	log_warn_psv(fmt, NULL, buf, ap);
	va_end(ap);
}
