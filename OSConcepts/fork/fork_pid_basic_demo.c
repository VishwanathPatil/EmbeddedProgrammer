#include <stdio.h>
#include <unistd.h>
int main(void)
{
    int pid;
    pid = fork();
    printf("pid: %d ppid: %d\n", pid, getppid());
    return 0;
}
