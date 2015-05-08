#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enigma.h"

typedef enum
{
    ENCODE,
    DECODE
} file_mode_t;

char* help_message(char *program_name);
void print_help(char *program_name);
void user_mode(void);
void file_mode(char *filename,file_mode_t type);

int main(int argc, char *argv[])
{
    int error = 0;

    switch(argc)
    {
        case 1:
            user_mode();
            break;
        case 2:
            if(strcmp(argv[1],"-penc") == 0)
            {
                ;
            }
            else if(strcmp(argv[1],"-pdec") == 0)
            {
                ;
            }
            else if(strcmp(argv[1],"--help") == 0)
            {
                print_help(argv[0]);
                return 0;
            }
            else
            {
                error = 1;
            }
            break;
        case 3:
            if(strcmp(argv[1],"-enc") == 0)
            {
                file_mode(argv[2],ENCODE);
            }
            else if(strcmp(argv[1],"-dec") == 0)
            {
                file_mode(argv[2],DECODE);
            }
            else
            {
                error = 1;
            }
            break;
        default:
            error = 1;
    }

    if(error)
    {
        fprintf(stderr, "\n\tERROR");
        fprintf(stderr, "%s\n", help_message(argv[0]));
        fflush(stderr);
        return 1;
    }

    return 0;
}

char* help_message(char *program_name)
{
    static char message[2048];

    sprintf(message, "\nUses:\n");
    sprintf(message+strlen(message), "\t%s\t\t   * user mode *\n",program_name);
    sprintf(message+strlen(message), "\t%s -penc             * encodes characters received by piping *\n",program_name);
    sprintf(message+strlen(message), "\t%s -pdec             * decodes characters received by piping *\n",program_name);
    sprintf(message+strlen(message), "\t%s -enc <filename>   * encodes contents of file *\n",program_name);
    sprintf(message+strlen(message), "\t%s -dec <filename>   * decodes contents of file *\n",program_name);
    sprintf(message+strlen(message), "\t%s --help            * prints this help message *\n",program_name);

    return message;
}

void print_help(char *program_name)
{
    printf("%s",help_message(program_name));
}

void user_mode(void)
{
    Enigma enigma;
    int option;
    char character;
    void (*operation)(Enigma *,char *);

    init_enigma(&enigma);

    printf( "\nWould you like to encode or decode?"
            "\n\t1 - encode"
            "\n\t2 - decode"
            "\n\n(defaults to encode on invalid input)"
            "\n\t\t> ");
    scanf("%d",&option);
    printf("Type in the message: ");
    scanf(" "); /* holds execution until user types something */

    switch(option)
    {
        case 2:
            operation = decode_character;
            break;
        default:
            operation = encode_character;
    }

    printf("\nEncoded: ");
    character = getchar();
    while( (character != EOF) && (character != '\n') )
    {
        operation(&enigma,&character);
        putchar(character);

        character = getchar();
    }
}

void file_mode(char *filename,file_mode_t type)
{
    Enigma enigma;

    init_enigma(&enigma);

    if(type == ENCODE)
    {
        printf("Encoding\n");
        encode_file(&enigma,filename);
    }
    else if(type == DECODE)
    {
        printf("Decoding\n");
        decode_file(&enigma,filename);
    }
}
