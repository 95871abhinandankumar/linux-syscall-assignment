#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

int main(int argc, char *argv)
{
    char ch;

    while(2)
    {
        ch = getchar();

	//If EOF came program will terminate
	if(ch == EOF)
	{
	   fprintf(stderr, "\nEnd of file!\n\n");
           exit(0);
	}

	if(islower(ch))
	{
            //If character is lower case
            ch = toupper(ch);
	    putchar(ch);

	}	
	else if(isupper(ch))
	{
	    //If character is upper case
	    ch = tolower(ch);
	    putchar(ch);
	}
	else
	{
             //If character is non-alpahabetic
	     putchar(ch);
	}


    }

}
