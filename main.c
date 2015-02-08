#include <stdlib.h>
#include "args.h"
#include "log.h"
#include "config.h"

const char *main_name = PROJECT_NAME;

int main(int argc, char *argv[])
{
	main_name = args_get_cmd(argv[0]);
	args_process(argc, argv);
	exit(EXIT_SUCCESS);
}

