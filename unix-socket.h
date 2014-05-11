#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

int unix_is_socket(const char *path);
const char *unix_strerror(void);
int unix_listen(const char *path);

#endif
