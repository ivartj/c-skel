#ifndef MAIN_H
#define MAIN_H

void error(const char *fmt, ...);
void xerror(const char *fmt, ...);
void main_usage(FILE *out);

extern char *main_name;
extern char *main_usage_string;

#endif
