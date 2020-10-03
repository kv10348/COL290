                                                                          COL 290
                                                                        Assignment 2
                                                                    Name = Kapil Verma
                                                                    Entry No =2018CS10348
In this assignment we have to make a Simple terminal which can execute simple commands which are mentioned in Assignment.
What are function of built-in commands, mostly i have mentioned in commnents in the code. Elevorated details is given here about each Function.
firsty main function will run and a WELCOME window will pop up and clear the terminal. Now a while loop will run for infinite time till there is not exit commands.
In while loop first it will wait for input and read it that is done by:
int taken_input(char* str){
************
char* buf= readline("\n>> ");

if(strlen(buf)!=0){
	add_history(buf);
	strcpy(str, buf);
	return 0;

}else{
	return 1;

}
}
***********
here buf is the commands which it will read form console and add to the history. It copy the readline to str for further process.
After this it will execute check what to do for given commands. This is done by processing function.

*******************
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
********************
Here it will first check if there is piping or not by cheking_pipe, then check commands contains "<" or not , then parserediretouput check contains ">" or not.
if b==1 means there is need of piping otherwise similiar it will execute the function according to what input contains. If the input does not contains "<", ">" and "|" then ot parse
the input according to " " and execute the commands which are define by us.
Parding is done by parseinput(char* str, char *cmd[]) fucntion which store the parsed string to *cmd[].
***************
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
**************
In above functio for loop goes from 0 to MAXLIST which is maximum number of word can a commands have, it is parsing by " ". Simulatneoulsy we are checking that any parse
string is NULL or not it's NULL means we have at the end of input string. ALso we are checking that if there is any string which has length 0 means there is more than
onw space between two word so we have to ignore that one.
So if the input have "|" we firstly spilt the string according to "|" and then parsing them by " ". And same concept we are usign for "<" and ">".
After parsing the input commands, we will take appropiate step to execute them.
First if commnands line contains "|", then we will use piping to execute them. During piping we will first check can we create piping if yes then create fork() and
now we will copy the discriptor to stdout as first file will only write the file. Simulatneoulsy we will close the pipe as there is no more need for writing. Now the
execution of first file will done by "execvp" it will exit fork child and immediately start executing whatever file name we will give to execvp.
After executing first fork() we will create another fork() child which will execute other file. In second fork() firstly we will copy the discriptor to stdin and will close
the pipe. After that we will use "execvp" to execute other file which will take the input form stdin. After comign form childs fork we will close the pipe, will wait for
child to finish it, as there is two child that is why i am using two wait() call.
piping executing is done by exe_pipe() function;

If we have to use redirection then we will use execvp with fork():
1--> first we will see "<", if we have to read the input file :
this is done by inputredirect() function..
first we will creat the fork() if the fork is created successfully then we will read the input file that .txt file and that discriptor we will copy to stdin so that
executing file can take it as it input. after copy discriptor, we will close the file and run the executable file by "execvp" function, we will wait for the child in
the parent by wait() function.

2--> first we will see ">", if we have to read the input file :
this is done by outputredirect() function..
first we will creat the fork() if the fork is created successfully then we will creat the file that .txt file which can be only write and we will copy that stdout to this discriptor
which is created by this open() function, after copy stdout, we will close the discriptor and run the executable file by "execvp" function, we will wait for the child in
the parent by wait() function.

defined commands are cd .. , cd, mkdir , rmdir, ls , quit.
When the commnands are of which are we have defined manually, for that wwe are using exe_args() function. It will first check the the given input is of what we have defined
then we will call that function using switching.If given commands is cd .. then it call the CHDIR(), in which we have used built in function chdir() which is will the
dirctory if it can. similiarly for mkdir commands we have use MKDIR() function which use built in function mkdir() which creat the dirctory.

Other commands which are not form defined commands or "|" or ">" or "<", it will show a erro message because it will recognize that commands as we have not defined anything about
it.
