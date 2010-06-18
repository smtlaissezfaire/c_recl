#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repl.h"

int main() {
  print_intro();

  for (;;) {
    print(eval(read()));
  }
  return 0;
}

void print_intro() {
  puts("Welcome to the C repl");
  puts("type .break to restart the repl, Ctrl-C to quit");
}

char * read() {
  char *str = malloc(100);
  printf("> ");
  scanf("%s", str);
  return str;
}

char * eval(char *str) {
  return str;
}

void print(char *str) {
  puts(compile(str));
}

char * compile(char *str) {
  char * src_filename = tmpnam(NULL);
  char * bin = tmpnam(NULL);
  FILE *fp = fopen(src_filename, "w");
  char * cmd = mk_command(src_filename, bin);

  if (fp) {
    if (system(cmd)) {
      printf("executed command: %s", cmd);
    } else {
      return NULL;
    }
    fclose(fp);
  } else {
    fprintf(stderr, "Could not open file with filename %s", src_filename);
  }
  return str;
}

char * mk_command(char *src, char *bin) {
  char * str = malloc(1000);

  strcat(str, "gcc ");
  strcat(str, src);
  strcat(str, " -o ");
  strcat(str, bin);

  return str;
}