#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void usage(FILE *out)
{
	fprintf(out, "usage: prog\n");
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

int main(int argc, char *argv[])
{
	parseargs(argc, argv);
	exit(EXIT_SUCCESS);
}
