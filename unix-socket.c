#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "unix-socket.h"

#define ERRLEN 1024
#define LISTEN_BACKLOG 30

#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX (sizeof(((struct sockaddr_un *)0)->sun_path))
#endif

static char errmsg[ERRLEN] = { 0 };

const char *unix_strerror(void)
{
	return errmsg;
}


int is_socket(const char *filename)
{
	struct stat statbuf;
	int err;
	int ok;

	err = stat(filename, &statbuf);
	if(err) {
		snprintf(errmsg, ERRLEN, "Failed to inspect socket pathname '%s'", filename);
		return -1;
	}

	ok = S_ISSOCK(statbuf.st_mode);
	if(ok)
		return 1;

	return 0;
}

static int unlink_if_socket(const char *filename)
{
	int err;

	switch(is_socket(filename)) {
	case -1: /* error specified by is_socket */
		return -1;
	case 0:
		snprintf(errmsg, ERRLEN, "Non-socket file on '%s'", filename);
		return -2;
	case 1:
		err = unlink(filename);
		if(err) {
			snprintf(errmsg, ERRLEN, "Failed to unlink '%s': %s", filename, strerror(errno));
			return -3;
		}
		return 0;
	default:
		snprintf(errmsg, ERRLEN, "Unrecognized return value from is_socket");
		return -4;
	}
}

int unix_listen(const char *filename)
{
	int s;
	int err;
	struct sockaddr_un addr = { 0 };

	if(strlen(filename) >= UNIX_PATH_MAX) {
		snprintf(errmsg, ERRLEN, "The socket file name '%s' exceeds the maximum filename size for unix sockets (%llu)", filename, UNIX_PATH_MAX);
		return -1;
	}

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, filename, UNIX_PATH_MAX);

	err = unlink_if_socket(filename);
	if(err)
		return -2;

	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if(s == -1) {
		snprintf(errmsg, ERRLEN, "Error on initiating socket: %s", strerror(errno));
		return -3;
	}

	err = bind(s, (struct sockaddr *)(&addr), sizeof(addr));
	if(err) {
		snprintf(errmsg, ERRLEN, "Binding socket to '%s' failed: %s", filename, strerror(errno));
		close(s);
		return -4;
	}

	err = listen(s, LISTEN_BACKLOG);
	if(err) {
		snprintf(errmsg, ERRLEN, "Listening on '%s' failed: %s", filename, strerror(errno));
		close(s);
		return -5;
	}

	return s;
}
