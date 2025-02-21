#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define SYS_pidchecker 467

int main() {
    char *filename = "pid_file";
    pid_t pid = getpid(); 

    long result = syscall(SYS_pidchecker, filename, pid);
    if (result < 0) {
        perror("syscall failed");
        return 1;
    }
    printf("pid checker1 returned PID: %ld\n", result);

//Syscall will run twice to ensure code doesn't save duplicate PIDs

    result = syscall(SYS_pidchecker, filename, pid);
    if (result < 0) {
        perror("syscall failed");
        return 1;
    }
    printf("pidchecker2 returned PID: %ld\n", result);
    return 0;
}
