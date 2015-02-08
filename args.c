#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "main.h"
#include "config.h"

void args_usage(FILE *out)
{
	fprintf(out, "usage: %s\n", main_name);
}


void args_version(FILE *out)
{
	fprintf(out, "%s version %s\n", main_name, PROJECT_VERSION);
}

void args_process(int argc, char *argv[])
{
	int c;
	static struct option longopts[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "version", no_argument, NULL, 256 },
		{ 0, 0, 0, 0 },
	};

	while((c = getopt_long(argc, argv, "h", longopts, NULL)) != -1)
	switch(c) {
	case 'h':
		args_usage(stdout);
		exit(EXIT_SUCCESS);
	case 256:
		args_version(stdout);
		exit(EXIT_SUCCESS);
	case ':':
	case '?':
		args_usage(stderr);
		exit(EXIT_FAILURE);
	}

	switch(argc - optind) {
	case 0:
		break;
	default:
		args_usage(stderr);
		exit(EXIT_FAILURE);
	}
}

const char *args_get_cmd(const char *argv0)
{
	const char *sepcheck = NULL;

	if(argv0 == NULL)
		return main_name;

	for(sepcheck = argv0; *sepcheck != '\0'; sepcheck++)
		if(*sepcheck == '/')
			argv0 = sepcheck + 1;

	return argv0;
}
