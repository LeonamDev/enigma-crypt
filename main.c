#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enigma.h"

typedef enum
{
    ENCODE,
    DECODE
} file_mode_t;

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
        fprintf(stderr, "\n\tERROR\nUses:\n");
        fprintf(stderr, "\t%s\t\t   * user mode *\n",argv[0]);
        fprintf(stderr, "\t%s -enc <filename>   * encodes contents of file *\n",argv[0]);
        fprintf(stderr, "\t%s -dec <filename>   * decodes contents of file *\n",argv[0]);
        fflush(stderr);
        return 1;
    }

    return 0;
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
