#include "logger.h"

void logger_reset() {
  logger.num_steps = 0;
}

void logger_add() {
  logger.num_steps +=1;
}
