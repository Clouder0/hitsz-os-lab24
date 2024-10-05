#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[]) {
	if(argc != 2) {
    printf("Sleep needs one argument.");
    exit(-1);
  }
  int ticks = atoi(argv[1]);
  sleep(ticks);
  printf("(nothing happens for a while");
  exit(0);
}
