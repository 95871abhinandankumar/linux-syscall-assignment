#include<stdio.h>
int main(int argc, char* argv[])
{
    
	int count = 0;
	for(int i = 1 ; i < argc ; i++)
	{

             if(argv[i][0] != '-')
	     {
		     printf("%s ", argv[i]);
		     count++;
	     }

	}
        if(count > 0)
		 printf("\n");


}

