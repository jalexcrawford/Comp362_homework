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

    if (pid == 0) // child
    {
        // this is 1.1
        pid = fork();
        if(pid < 0)
        {
            oops("Fork Failed!");
        }
        if(pid == 0)
        {
            //this is 1.1.1
            if (execlp("./iam", "iam", "1.1.1", NULL) < 0)
                oops("Fork Failed (1.1.1)");
        }
        else
        {
            //this is still 1.1
            pid = fork();
            if(pid < 0)
            {
                oops("Fork Failed!");
            }
            if(pid == 0)
            {
                //this is 1.1.2
                if (execlp("./iam", "iam", "1.1.2", NULL) < 0) oops("Fork Failed (1.1.2)");
            }
            else
            {
                //this is still 1.1
                if(execlp("./iam", "iam", "1.1", NULL) < 0)
                    oops("Fork Failed (1.1)");
            }
        }

        printf("I am the child, pid = %d\n", getpid());
        if (execlp("./iam", "iam", "Hello Parent! Please do not kill me!", NULL) < 0) 
            oops("Execlp Failed!");

    }
    else
    {
        // This is 1
        // create 1.2 and it's children
        pid = fork();
        if (pid < 0)
        {
            oops("fork failed");
        }
        if(pid == 0)
        {
            //this is still 1.2
            pid = fork();
            if(pid < 0)
            {
                oops("Fork Failed!");
            }
            if(pid == 0){
            //this is 1.2.1
                if(execlp("./iam", "iam", "1.2.1", NULL) < 0)
                    oops("ForkFailed (1.2.1");
            }
        }
        
    else{
        //this is still 1
        pid = fork();
        if(pid < 0)
        {
            oops("Fork Failed!");
        }
        if (pid == 0)
        {
            //this is 1.2.2
            if(execlp("./iam", "iam", "1.2.2", NULL) < 0)
            oops("ForkFailed (1.2.2");
        }
        else
        {
            //this is still 1
            if(execlp("./iam", "iam", "1", NULL) < 0)
            oops("ForkFailed (1)");
        }
    }
        //this is 1.2
        if(execlp("./iam", "iam", "1.2", NULL) < 0)
        oops("ForkFailed (1.2)");
    }

    // pid > 0 ==> must be parent
    printf("I am the parent, pid = %d\n", getpid());
    /* parent will wait for the child to complete */
    if (waitpid(-1, NULL, 0) < 0)
        printf("-1 from wait() with errno = %d\n", errno);

    printf("Child terminated; parent exiting\n");
    exit(EXIT_SUCCESS);
}