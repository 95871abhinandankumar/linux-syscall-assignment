#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>

#define fd_r 0
#define fd_w 1

void signal_handler2(int sig)
{
    fprintf(stderr, "child process killed!\n");
    exit(1);
}

void signal_handler3(int sig)
{
    fprintf(stderr, "KILLED DUE TO PIPE READER DIED!\n");
    exit(2);
}

int main(int argc, char *argv)
{
    
    signal(SIGTERM, signal_handler2);
    signal(SIGPIPE, signal_handler3);

    char c[BUFSIZ];
    int n = read(fd_r, c, BUFSIZ);


    
    int i = 0;
    while(i < n)
    {

    

        if(islower(c[i]))
        {
            //If character is lower case
            c[i] = toupper(c[i]);
            //putchar(c[i]);

        }
        else if(isupper(c[i]))
        {
            //If character is upper case
            c[i] = tolower(c[i]);
            //putchar(c[i]);
        }
        else
        {
             //If character is non-alpahabetic
             //putchar(c[i]);
        }
        i++;

    }

    write(1, c, n);

    exit(0);

}

