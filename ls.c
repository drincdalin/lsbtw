/*
	This is basically the ls/ls -a function from linux. REWRITTEN IN C
	I just tried to follow a tutorial to see how it will go, but it went too fast and i kinda lost it.
	I m going to try to document everything from start now so i can understand what everything does brb
	Ok umm idk man idk.....
	I tried but it s like 3AM and i don t really get it. Will look into it in another day i guess. #peaceout
*/
#include <stdio.h> //standard io.h header file
#include <dirent.h> //for DIR type
#include <unistd.h>// apparently for getopt
#include <sys/stat.h>

int show_all = 0; //boolean for -a

int main (int argc, char *argv[]){ //argc = argument count-how many words the user typed when they ran the prog
								   //*argv = pointer to a pointer of a char/array of strings

	int opt; //define the opt

	while((opt = getopt(argc,argv,"a")) != -1){ //a loop on the opt to read all arguments
		switch(opt){ //switch case for opt variable
			case 'a': //if the argument is -a then the show_all var turns into TRUE
				show_all = 1;
				break;
			default:
				fprintf(stderr, "usage: %s [-a] [path]\n", argv[0]);//if the user doesn t input a valid arg it just outputs a standard error message, telling the user what is the usage (that means arguments)
				return 1;
		}

	}

	const char *path = (optind<argc) ? argv[optind]:"."; //pointer to a character -> if optind<argc then the path is 
														 //going to be argv[optind], otherwise it will js be a dot.

	DIR *dir = opendir(path); //pointer to DIR type -- a pointer that you don t need to open but you can hand to 
							  //other functions. and it runs opendir on the path so we can open the path and hand 
							  //it out going further
	if(!dir){
		perror("opendir"); //the error generates a nr that perror checks and outputs a human-readable msg and
						   //print it to std error prefixed with wtv you pass
		return 1;//early exit -- code for error
	}

	struct dirent *entry; //pointer to a dirent struct
	while((entry = readdir(dir)) != NULL){//if the entry of readdir is not null
		if(!show_all && entry->d_name[0] == '.') continue; //if the 1st char is a dot, we just skip it and continue
		printf("%s \n", entry->d_name); // %s because it s going to be a string,| -> basically is for (*entry).d_name
	}

	closedir(dir); //this is to close the current directory after the execution of the program
	return 0;
}
