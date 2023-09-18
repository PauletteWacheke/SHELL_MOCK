#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024

int main()
{
	char input[MAX_INPUT_SIZE];
	
	while (1)
       {
	       printf("Iluvshell$ ");
	       
	       if (fgets(input, sizeof(input), stdin) == NULL)
	       {
		       printf("\n");
		       break;
	       }
	       
	       input[strcspn(input, "\n")] = '\0';
	       
	       if (strlen(input) == 0)
	       {
		       continue;
	       }
	       
	       char *command = strtok(input, " ");
	       char *args[MAX_INPUT_SIZE];
	       int arg_count = 0;

	       args[arg_count++] = command;

	       while ((args[arg_count++] = strtok(NULL," ")));

	       pid_t pid = fork();

	       if (pid == -1)
	       {
		       perror("fork");
		       exit(EXIT_FAILURE);
	       }
	       else if (pid == 0)
	       {
		       char *args[2];
		       args[0] = input;
		       args[1] = NULL;
		       
		       if (execve(input, args, NULL) == -1)
		       {
			       perror("execve");
			       _exit(EXIT_FAILURE);
		       }
	       }
	       else
	       {
		       int status;
		       if (waitpid(pid, &status, 0) == -1)
		       {
			       perror("waitpid");
			       exit(EXIT_FAILURE);
		       }
	       }
       }

	return (0);
}


