#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <sys/wait.h>

#define oops(m) {perror(m); exit(EXIT_FAILURE);}

int main() {
    pid_t pid;

        // fork a child process
    pid = fork();

    if (pid < 0) // error occurred
        oops("Fork Failed!");

    if (pid == 0) // child 1.1
    {
        pid_t pid_foo;
        printf("I am the child %d\n", getpid());

            // fork a child process
        pid_foo = fork();

        if (pid_foo < 0) // error occurred
            oops("Fork Failed!");

            if (pid_foo == 0) // child 1.1.1
            {
                pid_t pid_bar;
                printf("I am the child %d\n", getpid());
            
                // fork a child process
                pid_bar = fork();    
                if (pid_bar < 0) // error occurred
                    oops("Fork Failed!");

                if (pid_bar == 0) // child 1.1.2
                {
                    printf("I am the child %d\n", getpid());
                    if (execlp("./iam", "iam", "Hello Parent! 1.1.2 Please do not kill me!", NULL) < 0) 
                        oops("Execlp Failed!");
                }
                if (execlp("./iam", "iam", "Hello Parent! 1.1.1 Please do not kill me!", NULL) < 0) 
                        oops("Execlp Failed!");
                
                }
                        if (execlp("./iam", "iam", "Hello Parent! 1.1 Please do not kill me!", NULL) < 0) 
                oops("Execlp Failed!");
        }
        // fork a child process
    pid = fork();

    if (pid == 0) // child 1.2
    {
        pid_t pid_foo;
        printf("I am the child %d\n", getpid());

            // fork a child process
        pid_foo = fork();

        if (pid_foo < 0) // error occurred
            oops("Fork Failed!");

            if (pid_foo == 0) // child 1.2.1
            {
                pid_t pid_bar;
                printf("I am the child %d\n", getpid());
            
                // fork a child process
                pid_bar = fork();    
                if (pid_bar < 0) // error occurred
                    oops("Fork Failed!");

                if (pid_bar == 0) // child 1.2.2
                {
                    printf("I am the child %d\n", getpid());
                    if (execlp("./iam", "iam", "Hello Parent! 1.1.2 Please do not kill me!", NULL) < 0) 
                        oops("Execlp Failed!");
                }
                if (execlp("./iam", "iam", "Hello Parent! 1.1.1 Please do not kill me!", NULL) < 0) 
                        oops("Execlp Failed!");
                
                }
                        if (execlp("./iam", "iam", "Hello Parent! 1.1 Please do not kill me!", NULL) < 0) 
                oops("Execlp Failed!");
        }

    // pid > 0 ==> must be parent
    printf("I am the parent %d\n", getpid());
    /* parent will wait for the child to complete */
    if (waitpid(-1, NULL, 0) < 0)
        printf("-1 from wait() with errno = %d\n", errno);

    printf("Child terminated; parent exiting\n");
    exit(EXIT_SUCCESS);
}
