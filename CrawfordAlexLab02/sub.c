#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void printHelp();
void replaceChar(char *del, char *ins);

void main(int argc, char *argv[]){
	char* removeChar = "";
	char* addChar = "";
	char* outputFile = "";
	char* inputFile = "";
	
	if(argc == 1){
		printHelp();
	}
	else{

		for(int i = 1; i < argc; i++){
			switch (argv[i][1]){
				case '-':
					removeChar = argv[i];
					break;
				case '+':
					addChar = argv[i];
					break;
				case 'o':
					outputFile = argv[++i];
					freopen(outputFile, "w+", stdout);
					break;
				case 'i':
					inputFile = argv[++i];
					freopen(inputFile, "r", stdin);
					break;
				case 'h':
					printHelp();
					break;
				default :
					printHelp();				
			}

		}

	replaceChar(removeChar, addChar);
	//printf("removeChar %s %d, addChar %s, output %s, input %s", removeChar,strlen(removeChar), addChar, outputFile, inputFile);
	}
}

void replaceChar(char *del, char *ins){
	char c = ' ';
	while(c != EOF){
		c = getc(stdin);
		//printf("read input");
		for(int i = 0; i<strlen(ins); i++){
			if(c == del[i]){
				c = ins[i];
			}
		}
		putc(c, stdout);
		
		
	}
	
}

void printHelp(){
	printf("USAGE:\n");
	printf("\t sub [ -h | --fromChars -+toChars [-i inputFile] [-o outputFile] ]\n");

	printf("DESCRIPTION:\n");
	printf("\tThis utility copies text from an input stream to an output stream replacing every\n");
	printf("\tinstance of a specific character in fromChars with a corresponding (position-wise)\n");
	printf("\tcharacter from toChars. Any characters in fromChars and in toChars that do not\n");
	printf("\thave corresponding counterparts in the other one are ignored. If an input file is\n");
	printf("\tprovided, the content is read from that file; otherwise, the standard input is used.\n");
	printf("\tIf an output file is provided, then the modified content is written to that file;\n");
	printf("\totherwise, the standard output is used.\n\n");

	printf("OPTIONS:\n");
	printf("\t-- (followed by a string without separating space)\n");
	printf("\t\tindicates all characters that will be replaced in the processed text\n");
	printf("\t-+ (followed by a string without separating space)\n");
	printf("\t\tindicates the characters that will be used to replace corresponding\n");
	printf("\t\t(position-wise) characters from fromChars in the processed text\n");
	printf("\t-i (followed by input file name)\n");
	printf("\t\tuse the provided file as an input stream instead of standard input\n");
	printf("\t-o (followed by output file name)\n");
	printf("\t\tuse the provided file as an output stream instead of standard output\n");
	printf("\t-h prints this help message; it is also a default if no command line\n");
	printf("\t\targuments are provided\n");
}

