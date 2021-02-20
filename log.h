#ifndef LOG_H
#define LOG_H
void init_log();
void log_info(char *);
void log_err(char *);
void log_debug(char *);
void close_log();
#endif
