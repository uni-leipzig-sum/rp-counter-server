#ifndef COMMAND_H
#define COMMAND_H

typedef int (*cmd_handler_t)(int argc, const char **argv, char **res, size_t *resLen);

typedef struct {
  const char *cmd;
  cmd_handler_t handler;
} command_map_t;

typedef struct {
  const command_map_t *cmdlist;
} counter_context_t;

extern counter_context_t counter_context;

#endif /*COMMAND_H*/
