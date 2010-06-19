#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "repl.h"

#define MAX_BUF_LENGTH 10000

char buffer[MAX_BUF_LENGTH];
char line[MAX_BUF_LENGTH];

#define CLEAR_LINE(x) (strcpy((x), ""))

int main() {
  int run = 1;

  print_intro();

  do {
    repl_read();
    run = eval();
  } while(run);

  return 0;
}

void print_intro() {
  puts("Welcome to the C repl");
  puts("type .break to restart the repl,");
  puts("     .      to compile");
  puts("     .list  to list the current source code");
  puts("     .exit  to quit");
}

void repl_read() {
  CLEAR_LINE(line);
  printf("> ");
  fgets(line, MAX_BUF_LENGTH, stdin);
}

int eval() {
  if (!strcmp(line, ".exit\n")) {
    return 0;
  }

  if (!strcmp(line, ".list\n")) {
    puts(buffer);
  } else if (!strcmp(line, ".break\n")) {
    CLEAR_LINE(buffer);
  } else if (!strcmp(line, ".\n")) {
    compile(buffer);
  } else {
    strcat(buffer, line);
  }

  return 1;
}

void compile(char *str) {
  char * src_filename = build_source_name();
  char * bin = build_bin_name(src_filename);
  char * cmd = mk_command(src_filename, bin);
  FILE * fp;

  if ((fp = fopen(src_filename, "w"))) {
    fprintf(fp, "%s", str);
    fclose(fp);

    if (!system(cmd)) {
      system(bin);
    }
  } else {
    fprintf(stderr, "Could not open file with filename %s", src_filename);
  }
}

char * build_source_name() {
  char *name = tmpnam(NULL);
  char *src = malloc(sizeof(char) * (strlen(name) + 3));
  strcpy(src, name);
  strcat(src, ".c");
  return src;
}

char * build_bin_name(char *src) {
  char *str = malloc(sizeof(char) * (strlen(src) + 3));
  strcpy(str, src);
  strcat(str, ".o");
  return str;
}

char * mk_command(char *src, char *bin) {
  char *cmd;
  char gcc_command[] = "gcc ";
  char flags[] = " -o ";

  // int strlenth = sizeof(char) * (strlen(gcc_command) + strlen(src) + strlen(flags) + strlen(bin) + 1);
  int strlenth = 1000;

  cmd = malloc(strlenth);
  strcpy(cmd, gcc_command);
  strcat(cmd, src);
  strcat(cmd, flags);
  strcat(cmd, bin);
  puts(cmd);
  return cmd;
}