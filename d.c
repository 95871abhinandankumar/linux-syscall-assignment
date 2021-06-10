#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>


#define STDIN_FD 0
#define STDOUT_FD 1
//perror write erroe message on stderr
//NOTE : always use read first from pipe
//the write otherwise it will not work

int main(int argc, char *argv[])
{
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
       
      //Creating  pipe for child process to 
      //communicate
      int pipe_end[2];
      int p = pipe(pipe_end);

      //check the pipe created 
      //or not
      if(p < 0)
      {
	      perror("");
	      exit(3);
      }

      //check current process
      if(fork() != 0)
      {
	      //check for main process
	      if(fork() != 0)
	      {
		      //close both end 
		      //of pipe
		      close(pipe_end[0]);
		      close(pipe_end[1]);
		      
		      //wait till both
		      //the child complete
		      //the process

		      wait(NULL);
		      wait(NULL);
	      }
	      else
	      {
		      //close the writing end
		      close(pipe_end[0]);

		      //change default writing file
		      //descriptor
		      close(STDOUT_FD);
		      dup(pipe_end[1]);

		      close(pipe_end[1]);
		      execl("c", "c", (char*)0);

	      }

      }
      else
      {
	      //close the wrting end
	      close(pipe_end[1]);
	      
	      //change default file descriptor
	      close(STDIN_FD);
	      dup(pipe_end[0]);
	      close(pipe_end[0]);

	      execl("b", "b", (char *)0);

      }



}
