#include "enigma.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_rotors(Enigma *enigma)
{
    char outer[ROTOR_SIZE]  = {'#','B','D','F','H','J','L','N','P','R','T','V','X','Z','A','C','E','G','I','K','M','O','Q','S','U','W','Y'};
    char middle[ROTOR_SIZE] = {'#','E','J','O','T','Y','C','H','M','R','W','A','F','K','P','U','Z','D','I','N','S','X','B','G','L','Q','V'};
    char inner[ROTOR_SIZE]  = {'#','G','N','U','A','H','O','V','B','I','P','W','C','J','Q','X','D','K','R','Y','E','L','S','Z','F','M','T'};
    int i;

    for(i = 0; i < ROTOR_SIZE; ++i)
    {
        enigma->rotors[OUTER][i]  = outer[i];
        enigma->rotors[MIDDLE][i] = middle[i];
        enigma->rotors[INNER][i]  = inner[i];
    }
}

Enigma* create_enigma(void)
{
    Enigma *new_enigma;

    new_enigma = (Enigma *) malloc(sizeof(Enigma));

    if(new_enigma != NULL)
    {
        new_enigma->rotor_size = ROTOR_SIZE;

        memset(new_enigma->rotors[OUTER]    , '\0', ROTOR_SIZE);
        memset(new_enigma->rotors[MIDDLE]   , '\0', ROTOR_SIZE);
        memset(new_enigma->rotors[INNER]    , '\0', ROTOR_SIZE);

        init_rotors(new_enigma);
    }

    return new_enigma;
}

void destroy_enigma(Enigma *enigma)
{
    free(enigma);
}

void print_rotor(char *rotor,char *label)
{
    int i;

    printf("%s:\t",label);
    for(i = 0; i < ROTOR_SIZE; ++i)
    {
        putchar(rotor[i]);
    }
    putchar('\n');
}

void print_rotors(Enigma *enigma)
{
    printf("\nEnigma rotors:\n");

    print_rotor(enigma->rotors[OUTER]   ," Outer");
    print_rotor(enigma->rotors[MIDDLE]  ,"Middle");
    print_rotor(enigma->rotors[INNER]   ," Inner");
    putchar('\n');
    fflush(stdout);
}

char spin_rotor(char *rotor)
{
    int i;
    char last_value, next_value;

    last_value = rotor[0];
    for(i = 0; i < (ROTOR_SIZE-1); ++i)
    {
        next_value = rotor[i+1];
        rotor[i+1] = last_value;
        last_value = next_value;
    }
    rotor[0] = last_value;

    return rotor[0];
}

void spin_rotors(Enigma *enigma)
{
    char first_after_spin;

    first_after_spin = spin_rotor(enigma->rotors[INNER]);

    if(first_after_spin == '#')
    {
        spin_rotor(enigma->rotors[MIDDLE]);
    }
}

void standardize_text(char *text)
{
    while(*text)
    {
        *text = toupper(*text);
        if((*text) == ' ')
        {
            *text = '#';
        }
        ++text;
    }
}
