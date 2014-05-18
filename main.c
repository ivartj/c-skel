#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "args.h"

#define PROGRAM_NAME "prog"

const char *main_name = PROGRAM_NAME;
const char *main_usage_string = \
	"usage: " PROGRAM_NAME " %s\n";

void main_usage(FILE *out)
{
	fputs(main_usage_string, stderr);
}

int main(int argc, char *argv[])
{
	main_name = args_get_cmd(argv[0]);
	args_process(argc, argv);
	exit(EXIT_SUCCESS);
}

