
#include "defs.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#define PREFIX ";"

typedef struct {
  char *name;
  char *alias;
  char *description;
  int (*callback)(const char *);
} Command;

typedef struct {
  Command *commands;
  size_t count;
  size_t capacity;
} CommandList;

CommandList cmd_list = {NULL, 0, 0};

void init_command_list(size_t inittial_capacity) {
  cmd_list.commands = malloc(inittial_capacity * sizeof(Command));
  cmd_list.capacity = inittial_capacity;
  cmd_list.count = 0;
}

void free_command_list(void) {
  for (size_t i = 0; i < cmd_list.count; i++) {
    free(cmd_list.commands[i].name);
    free(cmd_list.commands[i].alias);
    free(cmd_list.commands[i].description);
  }
  free(cmd_list.commands);
}

void register_command(const char *name, const char *alias,
                      const char *description, int (*callback)(const char *)) {
  if (cmd_list.count >= cmd_list.capacity) {
    cmd_list.capacity = cmd_list.capacity ? cmd_list.capacity * 2 : 4;
    cmd_list.commands =
        realloc(cmd_list.commands, cmd_list.capacity * sizeof(Command));
  }

  Command cmd = {.name = strdup(name),
                 .alias = alias ? strdup(alias) : NULL,
                 .description = strdup(description),
                 .callback = callback};

  cmd_list.commands[cmd_list.count++] = cmd;
}

int command_quit(const char *args) {
  // Quit command
  if (args && strlen(args) > 0)
    printf("Warning: 'quit' ignores all arguments %s\n", args);

  printf("Goodbye. :(\n");
  return REPL_EXIT;
}

int command_ping(const char *args) {
  // Ping command
  printf("Pong :)\n");
  return REPL_CONTINUE;
}

int command_set(const char *args) {
  if (!args || strlen(args) == 0) {
    printf("Error: 'set' requires key and value (e.g., ;set key value)\n");
    return REPL_CONTINUE;
  }
  char key[64], value[64];
  if (sscanf(args, "%63s %63s", key, value) != 2) {
    printf("Error: Invalid format. Use: ;set key value\n");
    return REPL_CONTINUE;
  }
  printf("Set %s = %s\n", key, value);
  return REPL_CONTINUE;
}

int command_help(const char *args) {
  if (!args || strlen(args) == 0) {
    printf("Available commands:\n");
    for (size_t i = 0; i < cmd_list.count; i++) {
      Command *cmd = &cmd_list.commands[i];
      printf("%s%s [%s]: %s\n", PREFIX, cmd->name, cmd->alias,
             cmd->description);
    }
    return REPL_CONTINUE;
  } else {
    char h_arg[64];
    if (sscanf(args, "%63s", h_arg) != 2) {
      for (size_t i = 0; i < cmd_list.count; i++) {
        Command *cmd = &cmd_list.commands[i];
        if (strncmp(cmd->name, h_arg, strlen(cmd->name)) == 0) {
          printf("%s%s [%s]: %s\n", PREFIX, cmd->name,
                 cmd->alias ? cmd->alias : "", cmd->description);
          // printf("  %s%s %s %s: %s %s\n", PREFIX, cmd->name,
          //        cmd->alias ? " (" : "", cmd->alias ? cmd->alias : "",
          //        cmd->alias ? ")" : "", cmd->description);
          return REPL_CONTINUE;
        }
      }
      printf("Command not found: %s\n", h_arg);
      return REPL_CONTINUE;
    }
  }
  return REPL_CONTINUE;
}

int execute_command(const char *input) {
  if (input[0] != ';' && input[0] != ':')
    return REPL_NCMD;

  char cmd_name[64] = {0};
  const char *args = NULL;
  size_t i = 1;
  while (i < strlen(input) && input[i] != ' ' && i < sizeof(cmd_name) - 1) {
    cmd_name[i - 1] = input[i];
    i++;
  }
  if (i < strlen(input) && input[i] == ' ') {
    args = input + i + 1;
    while (*args == ' ')
      args++;
    if (strlen(args) == 0)
      args = NULL;
  }

  // Lookup command
  for (size_t j = 0; j < cmd_list.count; j++) {
    Command *cmd = &cmd_list.commands[j];
    if (strcmp(cmd_name, cmd->name) == 0 ||
        (cmd->alias && strcmp(input, cmd->alias) == 0)) {
      return cmd->callback(args); // Execute callback with args
    }
  }

  printf("Unknown command: %s\n", input);
  return REPL_CONTINUE;
}

void register_commands(void) {
  init_command_list(4);
  register_command("quit", ":q", "Exit the program", command_quit);
  register_command("ping", ":p", "Ping the system", command_ping);
  register_command("set", NULL, "Set a key-value pair", command_set);
  register_command("help", ":h", "Show help for commands", command_help);
  printf("System Loaded\n");
}

void init_repl(void) {
  char input[64];

  // Register Commands
  register_commands();

  // Starting Program
  printf("%s Program by Sophos %s (type :q or ;quit for terminating, :h or "
         ";help for help)\n",
         APP_NAME, APP_VERSION);
  printf("> ");
  while (fgets(input, sizeof(input), stdin)) {
    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
      printf("> ");
      continue;
    }

    int status = execute_command(input);
    if (status == 0)
      break;
    if (status == -1) {
      printf("You typed %s\n", input);
    }

    printf("> ");
  }
  free_command_list();
}

void quit_repl(void) {}
