#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<setjmp.h>

#define STDIN_FD 0
#define STDOUT_FD 1
//perror write erroe message on stderr
//NOTE : always use read first from pipe
//the write otherwise it will not work

static jmp_buf buf;

void sig_handler(int sig)
{
      longjmp(buf, 1);
      fprintf(stderr, "Killing both children!\n");
      
}

int main(int argc, char *argv[])
{
      signal(SIGALRM, sig_handler);
      
      int child_process1, child_process2;
      
      if(setjmp(buf))
      {
            kill(child_process1, SIGTERM);
            kill(child_process2, SIGTERM);

            exit(0);

      }

      char arr[20];
      int arg_count = 1, i = 0;


      if(argc > 1 && argv[arg_count][0] == '-')
      {
             for(i = 0 ; argv[arg_count][i+1] != '\0' ; i++)
             {
                 arr[i] = argv[arg_count][i+1];
             }

             argc--;
             arg_count += 1;

      }
       arr[i] = '\0';
       
      if(argc > 1)
      {
              int file_de_in = open(argv[arg_count], O_RDONLY);

               //If unable to open the file
              if(file_de_in < 0)
             {
                  perror("ERROR");
                  exit(0);
             }

             //Change default input as file
             close(STDIN_FD);
             int in = dup(file_de_in);
             if(in < 0)
             {
                  perror("ERROR");
                  exit(0);
             }
             close(file_de_in);

             argc -= 1;
             arg_count += 1;
      }

      if(argc > 1)
      {
             int file_de_out = creat(argv[arg_count], 0644);

             //If unable to create file
             if(file_de_out < 0)
             {
                 perror("ERROR");
                 exit(0);
             }

             //change default output as file
             close(STDOUT_FD);
             int out = dup(file_de_out);
             if(out < 0)
             {
                 perror("ERROR");
                 exit(0);
             }

             close(file_de_out);
      }


      /*
      if(argc != 3)
      {
              fprintf(stderr, "Please input a valid argument !\n");
              exit(0);
      }


      int file_de_in = open(argv[1], O_RDONLY);
      int file_de_out = creat(argv[2], 0644);

      //If unable to open the file
      if(file_de_in < 0)
      {
              perror("ERROR");
              exit(0);
      }

      //If unable to create file
      if(file_de_out < 0)
      {
              perror("ERROR");
              exit(1);
      }

      //Change default input as file
      close(STDIN_FD);
      int in = dup(file_de_in);
      if(in < 0)
      {
              perror("ERROR");
              exit(2);
      }
      close(file_de_in);

      //change default output as file
      close(STDOUT_FD);
      int out = dup(file_de_out);
      if(out < 0)
      {
              perror("ERROR");
              exit(3);
      }
      close(file_de_out);
*/
      //Creating  pipe for child process to
      //communicate
      int pipe_end[2];
      int p = pipe(pipe_end);

      //check the pipe created
      //or not
      if(p < 0)
      {
              perror("");
              exit(0);
      }

      //check current process
      if(( fork()) != 0)
      {
              //check for main process
              if((fork()) != 0)
              {
                      //close both end
                      //of pipe
                      close(pipe_end[0]);
                      close(pipe_end[1]);

                      //wait till both
                      //the child complete
                      //the process

                      alarm(15);

                      wait(NULL);
                       // fprintf(stderr, "Child-process end with process-id : %d\n", getpid());

                      wait(NULL);
                       // fprintf(stderr, "Child-process end with process-id : %d\n", getpid());

                      alarm(0);
                      fprintf(stderr, "\n\nEnd of program!\n");

                      exit(0);

              }
              else
              {
		      child_process2 = getpid();
                       //close the writing end
                       close(pipe_end[0]);

                      //change default writing file
                      //descriptor
                      close(STDOUT_FD);
                      dup(pipe_end[1]);

                      close(pipe_end[1]);
                      fprintf(stderr, "child process with process-id : %d\n", getpid());
                      execl("convert", "convert", (char*)0);

              }

      }
      else
      {
	      child_process1 = getpid();
              //close the wrting end
              close(pipe_end[1]);

              //change default file descriptor
              close(STDIN_FD);
              dup(pipe_end[0]);
              close(pipe_end[0]);     
              fprintf(stderr, "child process with process-id : %d\n", getpid());

              if(arr[0] == '\0')
                 execl("count", "count", (char *)0);
              else
                 execl("count", "count", arr, (char *)0);

      }



}

