#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#define STIN 0
#define STOP 1
int main(int argc, char* argv[])
{
     if(argc != 3)
     {
          fprintf(stderr, "Invalid input!\n");
	  exit(1);

     }
     
     //For write and read through pipe
     int pipe_fd[2];
     int fr, fw;
     //For child process
    

     //if unable to open file
     if((fr = open(argv[1], O_RDONLY)) == -1)
     {
            perror("Error : ");
	    exit(1);
     }
    
     //If not able to create file
     if((fw = creat(argv[2], 0644)) == -1)
     {
            perror("Error : ");
	    exit(1);
     }
     
     close(0);
     dup(fr);

      close(1);
      dup(fw);   
      
     if(pipe(pipe_fd)== -1)
     {
              perror("Error : ");
	      exit(1);
     }
     
     if(fork() != 0)
     {
	     if(fork() != 0) 
	     {
		     close(pipe_fd[0]);
		     close(pipe_fd[1]);
		     wait(NULL);
		     wait(NULL);
	     }else{
		     close(0);
		     //close(pipe_fd[1]);
		    
		     dup(fw);
		    // close(0);
		    // dup(pipe_fd[0]);
		     //close(pipe_fd[1]);
		     execl("q2", "q2", (char *)NULL);
	     }
     }else{
	    close(0);
	    dup(fr);

	    //close(pipe_fd[0]);
	     
	    close(1);
	    dup(fw);

	    // close(pipe_fd[0] );
	     execl("q3", "q3", (char *)NULL);
     }
     
     return 0;

}
