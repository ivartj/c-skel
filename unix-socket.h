#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

const char *unix_strerror(void);
int unix_listen(const char *filename);

#endif
