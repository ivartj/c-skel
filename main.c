#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "args.h"
#include "log.h"

#define PROGRAM_NAME "prog"

const char *main_name = PROGRAM_NAME;

int main(int argc, char *argv[])
{
	main_name = args_get_cmd(argv[0]);
	args_process(argc, argv);
	exit(EXIT_SUCCESS);
}

