#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>




void signal_handler1(int sig)
{
    fprintf(stderr, "child process killed!\n");
    exit(1);
}
int main(int argc, char *argv[])
{
    signal(SIGTERM, signal_handler1);

    char ch = '\0' ;
//    char c[];
    int count = 0, n= 0;

    if(argc > 1)
    {
        n = atoi(argv[1]);
    }
        
        if(n == 0)
        {
   
            count = 0;
            while(2)
            {
		    int k =0 ;
                 //   count = 0;
                    ch = getchar();
               //    printf("%c", ch);
		    
         
                     //If end of file came
                     if(ch == EOF)
                    {
                        fprintf(stderr , "\nTotal non-alphbetic is %d\n", count);
                        exit(0);
                    }
                    
		     printf("%c", ch);
                    //if character is not alphabetic
                    if(!isalpha(ch))
                    {
                        count++;
                    }


            }
	    return 0 ;
        }else{
		count = 0;
		while(1){
                   ch = getchar();
                  //  printf("%c", ch);
         
                     //If end of file came
                     if(ch == EOF || n <= 0)
                    {
                        fprintf(stderr , "\nTotal non-alphbetic is %d\n", count);
                        exit(0);
                    }
                    printf("%c", ch);

                    //if character is not alphabetic
                    if(!isalpha(ch))
                    {
                        count++;
                    }
                    n--;
		}
		return 0;
        }    

    return 0;

}

