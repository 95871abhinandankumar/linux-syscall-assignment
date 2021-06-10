#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char *argv[])
{
    char ch ;
    int count = 0;

    while(2)
    {
         ch = getchar();
	// printf("%c", ch);
             
	 //If end of file came
	 if(ch == EOF)
	 {
             fprintf(stderr , "\nTotal non-alphbetic is %d\n", count);
	     exit(0);
	 }

	 putchar(ch);
         
	 //if character is not alphabetic
	 if(!isalpha(ch))
	 {
             count++;
	 }


    }
    
    return 0;

}
