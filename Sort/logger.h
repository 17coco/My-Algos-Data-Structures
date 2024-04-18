#ifndef __LOGGER_H__
#define __LOGGER_H__

//the structure describing the logger. This logger is extremely simple and only counts "steps" of work. See its usage in slist.c
typedef struct log {
  long int num_steps;
} log_t;

//this variable is a global variable, accessible everywhere in this program
log_t logger;

//two functions that operate on this, for convenience. Look at logger.c for their implementation.
void logger_reset();
void logger_add();




#endif
