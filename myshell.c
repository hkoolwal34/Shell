#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#define STRTOK_DELIMETER " \t\n\r"

void run_shell();
char *read_line();
int tokenize (char *line,char *tokens[],int size);
void prompt()
{
	printf("\nKool Shell --> ");
}


int main()
{
	
	run_shell();

	return 0;
}

void run_shell()
{
	int status=1;
	char *line;
	char *arguements[100];
	int token_count=0;
	char path[100] = "/bin/";
	char clear[100] = "/usr";

	pid_t j;
		
	do
	{


		prompt();
		line = read_line();

		token_count=tokenize (line,arguements,100);	

		if(!strcmp(arguements[0],"exit"))
			exit(0);	
		
		else if(!strcmp(arguements[0],"clear"))
		{
			strcat(clear,path);
			strcpy(path,clear);
			strcpy(clear,"/usr");
		}	
		
		strcat(path,arguements[0]);
		j = fork();

		
		if(j==0)	
		{
//			int error = execl(path,"",NULL);						
			int error = execv(path,arguements);

			if(error==-1)
				printf("ERROR:Command Not Found\n");	
		}
		else
		{
			 while (wait(&status) != j); 
		}	
		
		strcpy(path,"/bin/");
	}while(1);
	
}

//reads line from command prompt
char *read_line()
{
	char *line = NULL;
	ssize_t buffer_size = 0;
	
	getline(&line,&buffer_size,stdin);
	
	return line;		
}

int tokenize (char *line,char *tokens[],int size)
{
	char *token;
	int token_count;

	token = strtok(line,STRTOK_DELIMETER);

	token_count=0;
	while(token!=NULL)
	{
		tokens[token_count]=token;
		token=strtok(NULL,STRTOK_DELIMETER);
		token_count++;
	}
	
	return token_count;
}
