#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

FILE *log_file;

void init_log() {

    log_file = fopen("log.txt", "a");
    if(!log_file) {
	printf("Error opening log file\n");
	exit(1);
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


void close_log()
{
    fclose(log_file);
}
