#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

FILE *log_file;
enum e_log_output log_output_mode;

void init_log(enum e_log_output mode) {

    if (mode == LOGFILE)
    {
        log_file = fopen("log.txt", "a");
        if(!log_file)
        {
            printf("Error opening log file\n");
            exit(1);
        }
    }
    else
    {
        log_file = stdout;
    }

}

void _log(const char *type, char *msg) {
    time_t ts;
    time(&ts);
    fprintf(log_file,"%d [%s] %s\n", ts, type, msg);
}

void log_info(char * msg)
{
    _log("INFO", msg);
}


void log_err(char * msg)
{
    _log("ERRO", msg);
}

void log_debug(char * msg)
{
    _log("DEBG", msg);
}


void close_log()
{
    fclose(log_file);
}
