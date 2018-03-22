#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *f;
    char c;
    char lexeme[20]="\0";
    int lexeme_pos = 0;
    int state = 0;
    int error = 0;
    int semi=0; /*semicolon checker.There can't be a semicolon after '=' or the operators */
    int lineNo=1; /*to count the new line character(line no)*/

    printf("Lineno 1 :");

    f=fopen("C:\\Text\\input.txt","r");
    while((!error) && ((c=fgetc(f))!=EOF)){

        lexeme[lexeme_pos++] = c;

        switch(state)
        {
            case 0 :
                if(isalpha(c)){state = 1;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    printf("Error Detected %c,Firstly there should a variable ",c);
                    error = 1;
                }
                break;

            case 1 :
                if(isalpha(c) || isdigit(c) || c=='_' ){state = 1;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    if(c == ' ')
                    {
                        lexeme[--lexeme_pos]='\0'; //remove space
                        printf("<%s,%s>","variable",lexeme);
                        state = 2;
                        lexeme_pos = 0;
                    }else
                    {
                        printf(" Error Detected %c,,There should be a space character after the variable",c);
                        error = 1;
                    }
                }
                break;

            case 2 :

                if(c=='='){state=3;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    printf(" Error Detected %c,,There should be a = sign ",c);
                    error = 1;
                }
                break;

            case 3 :

                if(c==' ')
                {
                    lexeme[--lexeme_pos]='\0'; //remove space
                    printf("<%s,%s>","Equal",lexeme);
                    state = 4;
                    lexeme_pos = 0;
                    semi=0;
                }
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    printf(" Error Detected %c,,There should a space character after the = ",c);
                    error = 1;
                }
                break;

            case 4 :

                if(isdigit(c)){state = 5;}
                else if(c=='*' || c=='+' || c=='-'){state=10;}
                else if(isalpha(c)){state=12;}
                else if(c==';')
                {
                    state=15;
                }
                else if(c!=' ')
                {
                    printf(" Error Detected_%c_, Undefined character",c);
                    error = 1;
                }
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                break;

            case 5 :
                if(isdigit(c)){state = 5;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    if(c == ' ')
                    {
                        lexeme[--lexeme_pos]='\0';
                        printf("<%s,%s>","Integer",lexeme);
                        state = 4;
                        lexeme_pos = 0;
                        semi=1;
                    }
                    else
                    {
                        if(c == '.'){state = 7;}
                        else
                        {
                            printf("Error Detected %c,,There should a space character after the integer",c);
                            error = 1;
                        }

                    }
                }
                break;

            case 7 :

                if(isdigit(c)){state = 8;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    printf(" Error Detected %c,,There should be at least a number ",c);
                    error = 1;
                }
                break;

            case 8 :

                if(isdigit(c)){state = 8;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    if(c == ' ')
                    {
                        lexeme[--lexeme_pos]='\0';
                        printf("<%s,%s>","Float",lexeme);
                        state = 4;
                        lexeme_pos = 0;
                        semi=1;
                    }
                    else
                    {
                        printf("Error Detected %c,,There should a space character after the float",c);
                        error = 1;
                    }
                }
                break;

            case 10 :

                if(c==' ')
                {
                    lexeme[--lexeme_pos]='\0'; //remove space
                    printf("<%s,%s>","Operator",lexeme);
                    state = 4;
                    lexeme_pos = 0;
                    semi=0;
                }
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    printf(" Error Detected %c,,There should a space character after the Operator ",c);
                    error = 1;
                }

                break;

            case 12 :

                if(isalpha(c) || isdigit(c) || c=='_' ){state = 12;}
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else
                {
                    if(c == ' ')
                    {
                        lexeme[--lexeme_pos]='\0'; //remove space
                        printf("<%s,%s>","variable",lexeme);
                        state = 4;
                        lexeme_pos = 0;
                        semi=1;
                    }else
                    {
                        printf(" Error Detected %c,,There should be a space character after the variable",c);
                        error = 1;
                    }
                }
                break;

            case 15 :

                if(semi==0)
                {
                    printf(" Error Detected..There should not be semicolon");
                    error = 1;
                }
                else if(c=='\n')
                {
                    lineNo++;
                    printf("\nLineno %d :",lineNo);
                }
                else if(c==' ')
                {
                    lexeme[--lexeme_pos]='\0'; //remove space
                    printf("<%s,%s>","endOfAssignment",lexeme);
                    state = 0;
                    lexeme_pos = 0;
                }
                else
                {
                    printf(" Error Detected %c,,There should a space character after the Semicolon ",c);
                    error = 1;
                }

                break;
        }
    }

    if(error!=1){

        if(lexeme[0]==';' && state==15){printf("There should be a space character after the semicolon");}

        if(state==4){printf(" Statement should be finish with a semicolon and a space character");}

        if(state==5){printf(" Statement can't be finish with a integer");}

        if(state==8){printf(" Statement can't be finish with a float");}

        if(state==12){printf(" Statement can't be finish with a variable");}

        if(state==10){printf(" Statement can't be finish with a operator");}

    }

    fclose(f);

    return 0;
}
