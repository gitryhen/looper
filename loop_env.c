#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <termios.h>

int main(int argc, char* argv[]){
    char *p;

    int seconds_wait = 0;
    if (argc>1){
        errno = 0;
        long s = strtol(argv[1], &p, 10);
        if (errno != 0 || *p !='\0' || s > INT_MAX || s < INT_MIN) {
            printf("Argument does not compute, please enter integer.\n");
        } else {
            seconds_wait = s;
            printf("%d\n", s);
        }
    }
    while (1){
        int id = fork();
        pid_t cpid;
        char* arr[] = {
            "../out/example_service_envelope",
            NULL
        };
        if (id==0){
            printf("child process\n");
            execvp( arr[0], arr);
        } else if (id==-1){
            printf("process creation failed\n");
            return 1;
        } else {
            cpid = wait(NULL);
            printf("Sleep for %d seconds\n", seconds_wait);
            sleep(seconds_wait);
        }
    }
    return 0;
}

