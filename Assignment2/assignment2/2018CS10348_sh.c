#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include <readline/readline.h>
#include<readline/history.h>
#include <dirent.h>
#include <signal.h>
//#include <curses.h>
#include <math.h>
#define PIPE_RD 0
#define PIPE_WR 1
#define MAXCOM 1000 // maximum number of letter to be supported
#define MAXLIST 100 // max number of commands to be  supported

//clearing the space using escape sequences
#define clear() system("clear")
//WELCOME Screen
void init_shell()
{
	clear();
	printf("\n\n\n\n ********************************");
	printf("\n\n\n\t  ************MY SHELL**************");
	printf("\n\n\n ****************************");

	char* username = getenv("USER");					// getting the user name of operating system
	printf("\n\n\n USER IS: @%s", username);
	printf("\n");
	sleep(1);
	clear();

}

// first we will make sure that we have taken the input and we will store it in histor file
int taken_input(char* str){
char* buf= readline("\n>> ");

if(strlen(buf)!=0){
	add_history(buf);
	strcpy(str, buf);
	return 0;

}else{
	return 1;

}
}

// printing the current working directory...
void dir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("Dir: %s ", cwd);
}

// here we will execute our programm
void exe_arg(char**  parsed){
	pid_t pid = fork();					//creating fork child
	    if (pid == -1) {
	        printf("\nFailed forking child..");
	        return;
	    } else if (pid == 0) {
				//we are in child fork
	        if (execvp(parsed[0], parsed) < 0) { 		// executing the command using execv
	            printf("\nCould not execute command..");
	        }
	        exit(0);
	    } else {
	        // waiting for child to terminate
	        wait(NULL);
	        return;
	    }
}


// Function where the piped system commands is executed
void exepipe(char **cmd1, char **cmd2) {
  int fds[2]; // file descriptors
  pipe(fds);		// initialising the pipe

  // child process #1
  if (fork() == 0) {
    // Reassign stdin to fds[0] end of pipe.
    dup2(fds[1], 1);			// copy the stdout to fds[1]
    close(fds[0]);				// close fds[0] as no need to read input
    close(fds[1]);
		char  *cmd[] = { cmd1[0], NULL };
		execvp(cmd[0],cmd);				// executing the commands

	}
    // Execute the second command.
    // child process #2
    if (fork() == 0) {
        // Reassign stdout to fds[1] end of pipe.
        dup2(fds[0], 0);
        close(fds[0]);
        close(fds[1]);
				char  *cmd[] = { cmd2[0], NULL };
        // Execute the first command.
        execvp(cmd[0], cmd);
    }
		// we are in parent
    close(fds[1]);
    close(fds[0]);
    wait(NULL);			//wating for one child
		wait(NULL);			//waitng for another child
}
// function for help call
void help(){

	printf(
			"\n\t****************WELCOME TO MY SHELL***************\n"
			"\t Use it according to supported commands only\n"
			"\t Supported commands for this shell are: \n"
			"\t cd\n"
			"\t cd ..\n"
			"\t ls\n"
			"\t mkdir\n"
			"\t rmdir\n"
			"\t quit \n"

			"##########all other commands you find in your Linux provided shell##########\n"

	);
}
// removing the dir or folder
int removing(char* str){
	int ret;
	if(remove(str)==0){				// removing the directory name as str
		printf("Directory is successfully deleted...\n");
		ret= 1;
	}else{
		printf("Directory could not be deleted...\n");
		ret= 0;
	}
	return ret;
}

// printing the whole contents in a current directory
int con_dir(){
	DIR *dir;
	struct dirent *sd;
	dir= opendir(".");				// opne current directory
	if(dir==NULL){
		printf("\nError! we can't have access to this directory..");
		exit(1);
	}


	while( (sd=readdir(dir))!=NULL ){			// printing the directory name..
		printf(">> %s\n", sd->d_name);

	}
	closedir(dir);												// close the present directory
	return 0;

}
// creating the directory
int MKDIR(char* str){
	int a;
	a= mkdir(str,0700);										// creating the directory of name str
	if (!a){
		printf("Directory created successfully ...\n");

	}else{
		printf("Directory could not be created successfully ...\n");
		exit(1);
	}
	//getch();
}
// changing the directory of working directory
int CHDIR(char *path){

	if(chdir(path)==0){

	}else{
		printf("Can't change to entered directory!!\n");
	}
	return 0;

}


//cd, pwd, mkdir, rmdir, exit, help,
//provided commands which will be supported in this shell
int mycommands(char** str){
	int totalcommands=6;
	int a, b=0;
	char* lomcommands[totalcommands];
	lomcommands[0]="exit";
	lomcommands[1]="ls";
	lomcommands[2]="cd";
	lomcommands[3]="mkdir";
	lomcommands[4]="rmdir";
	lomcommands[5]="help";
	//	lomcommands[6]="touch";
	for (int i=0; i<6;i++){
		if(strcmp(str[0], lomcommands[i])==0){
			b=i+1;
			break;
		}
	}
	switch(b){
		case 1:
			printf("Goodbye\n");
			exit(0);

		case 2:
			con_dir();
			return 1;

		case 3:
			CHDIR(str[1]);
			return 1;

		case 4:
			MKDIR((char*)str[1]);
			return 1;

		case 5:
			removing((char*)str[1]);
			return 1;

		case 6:
			help();
			return 1;
		default:
		//	printf("\nCommand not found!! \n");
			break;
		//	return 1;
	}

	return 0;
}
// checking if the given commands have pipe or not..
int checking_pipe(char* str, char* parse_str[]){

	int k=0;
	char* found;
	while ((found=strsep(&str, "|"))!=NULL) {							// checking if there is need of pipe or need.
		parse_str[k]=found;
	//	printf("%s\n", found);
		k++;
	}
	//printf("%s\n",parse_str[1] );

	if(parse_str[1]==NULL || parse_str[0]==NULL){
		return 0;
	}
	return 1;									// 1 if there is need of piping

}

//paresing the input by strsep()
void parseinput(char *str, char* parse_str[]){
	int k=0;
	char* found;

    int i;

    for (i = 0; i < MAXLIST; i++) {
        parse_str[i] = strsep(&str, " ");							// splitting the string from " "

        if (parse_str[i] == NULL)
            break;
        if (strlen(parse_str[i]) == 0)
            i--;
    }

}
// checking redirection of reading input
int parserediretinput(char* str, char* parse_str[]){
//	printf("%s\n","parserediretinput" );
	int k=0;


	char * token = strtok(str, "<");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      //printf( " %s\n", token );
			parse_str[k]=token;
			k++; //printing each token
      token = strtok(NULL, "<");

   }

//	printf("%s\n",parse_str[1] );

	if(parse_str[1]==NULL || parse_str[0]==NULL){
		return 0;
	}
	return 3;

}
// checking redirection of writng the output..
int parserediretouput(char* str, char* parse_str[]){
//	printf("%s\n", "parserediretouput");
	int k=0;
	//char* found;
	char * token = strtok(str, ">");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
    //  printf( " %s\n", token );
			parse_str[k]=token;
			k++; //printing each token
      token = strtok(NULL, ">");

   }

	// printf("%s\n",parse_str[1] );

	if(parse_str[1]==NULL || parse_str[0]==NULL){
		return 0;
	}
	return 4;

}


//processing the input
int processing(char* str, char** parsed, char** parsedpipe){
	char* a[2];
	char* c[2];
	char* d[2];
	c[1]=NULL;
	d[1]=NULL;
	int b=checking_pipe(str, a);
	int f=parserediretinput(str , c);					// < 3
	int g=parserediretouput(str, d);   				//> 4


	if(b){

		parseinput(a[0], parsed);
		parseinput(a[1], parsedpipe);
	}else if (g==4){

		parseinput(d[0], parsed);
		parseinput(d[1], parsedpipe);
		return 4;
	}else if(f==3){
		parseinput(c[0], parsed);
		parseinput(c[1], parsedpipe);
		return 3;
	}else{
		parseinput(str,parsed);
	}

	if(mycommands(parsed)){
		return 0;

	}else{
		return 1+b;

	}
}
// writign the file using redirection concept
int outputredirect(char **parsed, char **parsedinput){
	int fd;
	int ret;
	pid_t pd;
	pd = fork();

	if(pd==0){
		fd=open(parsedinput[0], O_CREAT| O_APPEND | O_WRONLY,0600);				// open the fie wgere we have to write the ouput
	ret = dup2(fd, 1);
		close(fd);
	char *cmd[]={parsed[0], NULL};

		execvp(cmd[0], cmd);
		exit(0);
	}

wait(0);
}
int inputredirect(char **parsed, char **parsedinput){
	int fd;
	int ret;
	pid_t pd;
	pd = fork();
	if(pd==0){
		fd=open(parsedinput[0], O_RDONLY,0600);								// open the file to read the data
		ret = dup2(fd, 0);																		// copying the discriptor to stdinput
		close(fd);
	char *cmd[]={parsed[0], NULL};

		execvp(cmd[0], cmd);																														// executing the commands (runnign the file which gives ouput)
		exit(0);
	}

wait(0);
}





// function for  main
int main(){
	char input[MAXCOM];
		char* input_parsed[MAXLIST];
	char* parsed_input[MAXLIST];
	char** parsing[MAXLIST] ;
	int flag=0;
	init_shell();
	//system("gnome-terminal");
	while(1){									// running the main process till there is no exit commands
		dir();
		if(taken_input(input)){				// read the input
			continue;

		}
		flag=processing(input, input_parsed, parsed_input);						// processing the input to check what to do
		if(flag==2){
			exepipe(input_parsed, parsed_input);									// now execute the input by piping
			//exepipe();
		}
		if(flag==4){																						// redirection the output to txt file
			outputredirect(input_parsed, parsed_input);
			//fileIO(input_parsed, parsed_input,1);
		}
		if(flag==3){																							/// reading the input by txt file
				inputredirect(input_parsed, parsed_input);
		}
		if (flag==1){																						// executing the other commands ..
			exe_arg(input_parsed);
		}

	}
	return 0;


}
