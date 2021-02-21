#ifndef LOG_H
#define LOG_H

enum e_log_output
{
    STDOUT,
    LOGFILE
};

void init_log();
void log_info(char *);
void log_err(char *);
void log_debug(char *);
void close_log();
#endif
