#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "main.h"

void args_process(int argc, char *argv[])
{
	int c;
	static struct option longopts[] = {
		{ "help", no_argument, NULL, 'h' },
		{ 0, 0, 0, 0 },
	};

	while((c = getopt_long(argc, argv, "h", longopts, NULL)) != -1)
	switch(c) {
	case 'h':
		main_usage(stdout);
		exit(EXIT_SUCCESS);
	case ':':
	case '?':
		main_usage(stderr);
		exit(EXIT_FAILURE);
	}

	switch(argc - optind) {
	case 0:
		break;
	default:
		main_usage(stderr);
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
