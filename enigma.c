/*
The MIT License (MIT)

Copyright (c) 2015 Leonardo de Oliveira Lourenço

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "enigma.h"

#include <ctype.h>
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

void init_enigma(Enigma *enigma)
{
    enigma->rotor_size = ROTOR_SIZE;
    init_rotors(enigma);
}

Enigma* create_enigma(void)
{
    Enigma *new_enigma;

    new_enigma = (Enigma *) malloc(sizeof(Enigma));

    if(new_enigma != NULL)
    {
        init_enigma(new_enigma);
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

void reset_rotor(char *rotor)
{
    while(rotor[0] != '#')
    {
        spin_rotor(rotor);
    }
}

void reset_rotors(Enigma *enigma)
{
    reset_rotor(enigma->rotors[INNER]);
    reset_rotor(enigma->rotors[MIDDLE]);
}

void standardize_character(char *character)
{
    *character = toupper(*character);

    if((*character) == ' ')
    {
        *character = '#';
    }
}

void standardize_text(char *text)
{
    while(*text)
    {
        standardize_character(text);

        ++text;
    }
}

int find_on_rotor(char *rotor,char character)
{
    int position;

    for(position = 0; position < ROTOR_SIZE; ++position)
    {
        if(rotor[position] == character)
        {
            return position;
        }
    }

    return -1;
}

void encode_character(Enigma *enigma,char *character)
{
    int position;

    standardize_character(character);

    position = find_on_rotor(enigma->rotors[INNER],*character);
    if(position >= 0)
    {
        position = find_on_rotor(enigma->rotors[MIDDLE],enigma->rotors[OUTER][position]);

        *character = enigma->rotors[OUTER][position];

        spin_rotors(enigma);
    }
}

void encode_message(Enigma *enigma,char *message,char *encoded_message)
{
    strcpy(encoded_message,message);
    standardize_text(encoded_message);

    while(*encoded_message)
    {
        encode_character(enigma,encoded_message);

        ++encoded_message;
    }
}

void decode_character(Enigma *enigma,char *character)
{
    int position;

    standardize_character(character);

    position = find_on_rotor(enigma->rotors[OUTER],*character);
    if(position >= 0)
    {
        position = find_on_rotor(enigma->rotors[OUTER],enigma->rotors[MIDDLE][position]);

        *character = enigma->rotors[INNER][position];

        spin_rotors(enigma);
    }
}

void decode_message(Enigma *enigma,char *message,char *decoded_message)
{
    strcpy(decoded_message,message);
    standardize_text(decoded_message);

    while(*decoded_message)
    {
        decode_character(enigma,decoded_message);
        ++decoded_message;
    }
}

char* generate_output_filename(char *original,char *suffix)
{
    char *outfilename;
    size_t original_size;
    size_t name_end;
    char *file_extension_point;

    original_size = strlen(original);

    outfilename = (char *) malloc(sizeof(char) * (original_size + strlen(suffix) + 1) );

    if(outfilename != NULL)
    {
        file_extension_point = strrchr(original,'.');
        if(file_extension_point != NULL)
        {
            name_end = (file_extension_point - original);

            strncpy(outfilename, original, name_end );
            strcpy(outfilename + name_end, suffix);
            strcat(outfilename,file_extension_point);
        }
    }

    return outfilename;
}

void encode_file(Enigma *enigma,char *filename)
{
    FILE *input;
    FILE *output;
    char *outfilename;
    char character;

    input = fopen(filename,"r");

    if(input == NULL)
    {
        fprintf(stderr, "\nCouldn't open input file [%s]\n",filename);
        return;
    }

    outfilename = generate_output_filename(filename,"_encoded");
    if(outfilename == NULL)
    {
        fprintf(stderr, "\nCouldn't open output file [%s]\n",filename);
        fclose(input);
        return;
    }

    output = fopen(outfilename,"w");
    if(output == NULL)
    {
        fprintf(stderr, "\nCouldn't open output file [%s]\n",filename);
        free(outfilename);
        fclose(input);
        return;
    }

    while( (character = fgetc(input)) != EOF )
    {
        encode_character(enigma,&character);
        fputc(character,output);
    }

    free(outfilename);
    fclose(output);
    fclose(input);
}
void decode_file(Enigma *enigma,char *filename)
{
    FILE *input;
    FILE *output;
    char *outfilename;
    char character;

    input = fopen(filename,"r");

    if(input == NULL)
    {
        fprintf(stderr, "\nCouldn't open input file [%s]\n",filename);
        return;
    }

    outfilename = generate_output_filename(filename,"_decoded");
    if(outfilename == NULL)
    {
        fprintf(stderr, "\nCouldn't open output file [%s]\n",filename);
        fclose(input);
        return;
    }

    output = fopen(outfilename,"w");
    if(output == NULL)
    {
        fprintf(stderr, "\nCouldn't open output file [%s]\n",filename);
        free(outfilename);
        fclose(input);
        return;
    }

    while( (character = fgetc(input)) != EOF )
    {
        decode_character(enigma,&character);
        fputc(character,output);
    }

    free(outfilename);
    fclose(output);
    fclose(input);
}
