#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
	FILE *f;
	char c;
	char lexeme[20] = "\0";
	char token[20]="\0";
	int lexeme_pos = 0;
	int state = 0;
	int error = 0;
	
	f = fopen("input.txt","r");
	while ( (!error) && ( (c =fgetc(f)) != EOF)){
		lexeme[lexeme_pos++] = c;
		
		switch(state) {
			
			case 0:
				if (c == ' '){
					state = 0;
					lexeme_pos--;
				} else {
					if (isalpha(c)) {
						state = 1;
						strcpy(token,"id");
						token[2]='\0';
					} else {
						if (isdigit(c)) {
							state = 3;
							strcpy(token,"int");
							token[3]='\0';
						} else { 
							printf("Error Detected -%c-",c);
							lexeme_pos--;
							error = 1;
						}
					}
				}
				break; 
				
			case 1:
			    c = fgetc(f);
			    while(isalpha(c) || isdigit(c)) {
					lexeme[lexeme_pos++] = c;
					c = fgetc(f);
				} 
				ungetc(c,f);
				state = 5;
				break;
				
			case 3:
				while(isdigit(c =fgetc(f))) {
					lexeme[lexeme_pos++] = c;
				}  
				state = 5;
				break;
				
			case 2:
			case 5:
				ungetc(c,f);
				lexeme[--lexeme_pos] = '\0';
				printf("<%s,%s>",token,lexeme);
				state = 0;
				lexeme_pos = 0;
				break;
			
			
		}
	}
	// print the last token detected
	if(lexeme_pos > 0){
		printf("<%s,%s>",token,lexeme);
	}
	fclose(f);
	return 0;
}