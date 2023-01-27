/***************************************************************************
  @file         MyShell.c
  @author       Andrew Dibble

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char input[255];

/**
  @brief Fork a child to execute the command using execvp. The parent should wait for the child to terminate
  @param args Null terminated list of arguments (including program).
  @return returns 1, to continue execution and 0 to terminate the MyShell prompt.
 */
int execute(char **args){
	int rc = fork();
	
	if(rc < 0){ //fork failed, exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){ //child process
		int isSuccessful = execvp(args[0], args);
		if(isSuccessful == -1){
			printf("error executing command: No such file or directory\n");
			exit(0);
		}
	}else{ //parent process
		int wc = wait(NULL); //making sure child is finished
	}
		
	return 1;
}


/**
  @brief gets the input from the prompt and splits it into tokens. Prepares the arguments for execvp
  @return returns char** args to be used by execvp
 */
char** parse(void){
	char* tokenArr[255]; //storing the arguments
	tokenArr[0] = strtok(input, " "); //getting the first word
	
	//getting the other words if there are any 
	int num = 0;
	while(tokenArr[num] != NULL){
		num++;
		tokenArr[num] = strtok(NULL," ");
	}
	
	char** args = &tokenArr;
	return args;
}


/**
   @brief Main function should run infinitely until terminated manually using CTRL+C or typing in the exit command
   It should call the parse() and execute() functions
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv){
	do{
	printf("MyShell> ");
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")]=0; //removing the new line character from the input
	if(strcmp(input, "exit") != 0)
		execute(parse());
	}while(strcmp(input, "exit") != 0); //stop when the user types 'exit'

  	return EXIT_SUCCESS;
}
