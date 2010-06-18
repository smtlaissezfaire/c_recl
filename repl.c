#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "repl.h"

int main() {
  print_intro();

  for (;;) {
    print(eval(repl_read()));
  }
  return 0;
}

void print_intro() {
  puts("Welcome to the C repl");
  puts("type .break to restart the repl, Ctrl-C to quit");
}

char * repl_read() {
  char *str = malloc(1000);

  printf("> ");
  fgets(str, 1000, stdin);

  return str;
}

char * eval(char *str) {
  if (!strcmp(str, ".break")) {
    return NULL;
  } else {
    return compile(str);
  }
}

void print(char *str) {
  if (str) {
    puts(str);
  }
}

char * compile(char *str) {
  printf("about to compile str: %s\n", str);

  char * src_filename = tmpnam(NULL);
  FILE * fp = fopen(src_filename, "w");
  char bin[strlen(src_filename) + 4];
  int success = 0;
  char * cmd;

  strcpy(bin, src_filename);
  strcat(bin, ".out");
  cmd = mk_command(src_filename, bin);

  if (fp) {
    printf("executing command: %s\n", cmd);

    if (!system(cmd)) {
      success = 1;
    }
  } else {
    fprintf(stderr, "Could not open file with filename %s", src_filename);
    fclose(fp);
  }

  if (success) {
    return str;
  } else {
    return NULL;
  }
}

char * mk_command(char *src, char *bin) {
  char * str = malloc(1000);

  strcat(str, "gcc ");
  strcat(str, src);
  // strcat(str, " -o ");
  // strcat(str, bin);

  return str;
}