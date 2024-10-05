#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2];
  int p2[2];
  if (pipe(p) < 0) {
    printf("pipe error");
    exit(-1);
  }
  if (pipe(p2) < 0) {
    printf("pipe error");
    exit(-1);
   }
  int fret = fork();
  if (fret == 0) {
    // sub process
    // read from ping
    close(p[1]);
    close(p2[0]);
    int self_pid = getpid();
    int another_pid;
    read(p[0], &another_pid, sizeof(int));
    close(p[0]);
    printf("%d: received ping from pid %d\n", self_pid, another_pid);
    write(p2[1], &self_pid, sizeof(int));
    close(p2[1]);
  } else if (fret > 0) {
    // parent process
    close(p2[1]);
    close(p[0]);
    int self_pid = getpid();
    write(p[1], &self_pid, sizeof(int));  // write to ping
    close(p[1]);
    int another_pid;
    read(p2[0], &another_pid, sizeof(int));   // read from pong
    close(p2[0]);
    printf("%d: received pong from pid %d\n", self_pid, another_pid);
  } else {
    printf("fork error");
    exit(-1);
  }
  // pipes will be automatically closed when process exits
  exit(0);
}
