#include <stdio.h>
#include <string.h>

void printhelp();
void printArgsError();

int processFile(char *src, char *dest, char *elim, char *replace);


int main(int argc, char *argv[]){
 	char *src = "";
	char *dest = "";
	char *elim = "";
	char *replace = "";
	switch (argc){
	//If no arguements are present or if -h or --help is present print out help
	//message.
	case 1: //no arguements given argc[0] is the name of the running program.
		printhelp();
		break;
	case 2: //one arguement given, check to see if it's -h or --help and print the help doc
		//otherwise print error message and then the help doc
		if (strcmp(argv[1],  "-h") == 0)
			printhelp();
		else if (strcmp(argv[1], "--help") == 0)
			printhelp();
		else{
			printArgsError();
		}
		break;
	default:
		for(int i = 1; i < argc; i++){
			//first check to see if the first char is a dash, print help if it is not.
			if(argv[i][0] != '-'){
				printhelp();
			}
			//Check to see if the seccond char is a dash, copy the string into elim
			//for later processing.
			else if(argv[i][1] == '-'){
				elim = argv[i];
			}
			//check to see if the second char is a plus, copy the string into replace 
			//for further processing.
			else if(argv[i][1] == '+'){
				replace = argv[i];
			}
			//if the second char is i, increment i, and then copy the next arg to src.
			else if(argv[i][1] == 'i'){
				i++;
				src = argv[i]; 
			}
			//same if the arg is o
			else if(argv[i][1] == 'o'){
				i++;
				dest = argv[i];
			}
		}
		processFile(src, dest, elim, replace);
	}
	return 0;
}

int processFile(char *src, char *dest, char *elim, char *replace){
	int toReplace;
	if (strlen(replace) <= 0){
		//Not allowed, thow an error and exit.
		printf("Error: must specify char to replace\n");
		return -1;
	}
	if (strlen(src) <= 0){
		/*TODO: since src is the name of the source file, open it
		 * and have the file stream ready for processing.
		 */
	}
	else {
		/* TODO: add code to read user input and pass it on for
		 * further processing.
		 */
	}
	if (strlen(dest) <= 0){
		/*TODO: open the destination file and prepare it to recieve
		 * output from the processed src file.
		 */
	}
	else {
		/* TODO: add code to print processed src input to console out.
		 */
	}

	if (strlen(elim) >= 0){
		//set replace equal to the lenght of the replacement string.
		//There will always be more in the to replace string, but not the other way around.
		toReplace = strlen(replace);
		if (strlen(replace) > strlen(elim)){
			printf("Error - missing replacement character./n");
		}
		else if (strlen(elim) > strlen(replace)){
			printf("Warning: more replacement letters given than letters to replace, ignoring extra replacement letters\n");
		}
		/* TODO: process the input and pass to the output. 
		 * General idea would be to have a loop that reads in a line from src.
		 * Then loop over that line to copy it to the output.
		 * While copying to the output, check to see if the char currently being looked at is 
		 * one of the members of elim. Do this by looping over elim from position 2 and increasing.
		 * Since replacements are indexed the same, looping over replace will use the same loop to
		 * copy over. Once the entire line is processed, get the next line, unless it's the EOF.
		 * Close both src and dest and inform user that program is complete.
		 */
	}
	printf("Hello world!");
	return 0;
}

//function that prints out how to use the program when fully implemented.
void printhelp(){
	printf("USAGE:\n"
		"\tsubc [ -h | --fromChars -+toChars [-i inputFile] [-o outputFile] ]\n\n"
		"DESCRIPTION:\n"
		"\tThis utility copies text from an input stream to an output stream replacing every\n"
		"\tinstance of a specific character in fromChars with a corresponding (position-wise)\n"
		"\tcharacter from toChars. Any characters in fromChars and in toChars that do not \n"
		"\thave corresponding counterparts in the other one are ignored. If an input file is\n"
		"\tprovided, the content is read from that file; otherwise, the standard input is used.\n"
		"\tIf an output file is provided, then the modified content is written to that file;\n"
		"\totherwise, the standard output is used.\n\n"
		"OPTIONS:\n"
		"\t--(followed by a string without separating space)\n"
		"\t\tindicates all characters that will be replaced in the processed text\n"
		"\t-+(followed by a string without separating space) \n"
		"\t\tindicates the characters that will be used to replace corresponding\n"
		"\t\t(position-wise) characters from fromChars in the processed text\n"
		"\t-i (followed by input file name) \n"
		"\t\tuse the provided file as an input stream instead of standard input\n"
		"\t-o (followed by output file name) \n"
		"\t\tuse the provided file as an output stream instead of standard output\n"
		"\t-h prints this help message; it is also a default if no command line\n"
		"\t\targuments are provided\n"
		);
}

//Informs user that input arguements were not valid and prints the help menu.
void printArgsError(){
	printf("ERROR: Invalid arguments, please check your input and try again!/n");
	printhelp();
}
