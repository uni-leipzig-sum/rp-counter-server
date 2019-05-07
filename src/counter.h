
#ifndef COUNTER_H
#define COUNTER_H

#include "common.h"

int Counter_GetCountingTime(int argc, char **argv, char **res, size_t *resLen);
int Counter_SetCountingTime(int argc, char **argv, char **res, size_t *resLen);
int Counter_Count(int argc, char **argv, char **res, size_t *resLen);
int Counter_WaitAndReadAndStartCounting(int argc, char **argv, char **res, size_t *resLen);

#endif /* COUNTER_H */
