#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#define PROGRAM_NAME "prog"

static const char *program_name = PROGRAM_NAME;
static void usage(FILE *out);
static void parseargs(int argc, char *argv[]);
static const char *get_program_name(const char *argv0);

void usage(FILE *out)
{
	fprintf(out, "usage: %s\n", program_name);
}

void parseargs(int argc, char *argv[])
{
	int c;
	static struct option longopts[] = {
		{ "help", no_argument, NULL, 'h' },
		{ 0, 0, 0, 0 },
	};

	while((c = getopt_long(argc, argv, "h", longopts, NULL)) != -1)
	switch(c) {
	case 'h':
		usage(stdout);
		exit(EXIT_SUCCESS);
	case ':':
	case '?':
		usage(stderr);
		exit(EXIT_FAILURE);
	}

	switch(argc - optind) {
	case 0:
		break;
	default:
		usage(stderr);
		exit(EXIT_FAILURE);
	}
}

void error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "%s: ", program_name);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, ".\n");
	va_end(ap);
	exit(EXIT_FAILURE);
}

void xerror(const char *fmt, ...)
{
	va_list ap;
	int errcode;

	va_start(ap, fmt);
	errcode = errno;
	fprintf(stderr, "%s: ", program_name);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, ": %s.\n", strerror(errno));
	va_end(ap);
	exit(EXIT_FAILURE);
}

const char *get_program_name(const char *argv0)
{
	const char *sepcheck = NULL;

	if(argv0 == NULL)
		return PROGRAM_NAME;

	for(sepcheck = argv0; *sepcheck != '\0'; sepcheck++)
		if(*sepcheck == '/')
			argv0 = sepcheck + 1;

	return argv0;
}

int main(int argc, char *argv[])
{
	program_name = get_program_name(argv[0]);
	parseargs(argc, argv);
	exit(EXIT_SUCCESS);
}
