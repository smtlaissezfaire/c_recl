#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "repl.h"

int main() {
  print_intro();

  for (;;) {
    eval(repl_read());
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

char * compile(char *str) {
  char * src_filename = strcat(tmpnam(NULL), ".c");
  char * bin = strcat(src_filename, ".o");
  char * cmd = mk_command(src_filename, bin);
  FILE * fp;
  int success = 0;

  if (fp = fopen(src_filename, "w")) {
    fprintf(fp, str);
    fclose(fp);

    if (!system(cmd)) {
      success = 1;
    }
  } else {
    fprintf(stderr, "Could not open file with filename %s", src_filename);
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
  strcat(str, " -o ");
  strcat(str, bin);

  return str;
}