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

#ifndef ENIGMA_H
#define ENIGMA_H

typedef enum
{
    OUTER = 0,
    MIDDLE,
    INNER,
    ROTOR_SIZE = 27
} _enigma_constants;

typedef struct
{
    char rotors[3][ROTOR_SIZE];
    int rotor_size;
} Enigma;

void init_enigma(Enigma *enigma);
Enigma* create_enigma(void);
void destroy_enigma(Enigma *enigma);
void print_rotors(Enigma *enigma);
void reset_rotors(Enigma *enigma);

void encode_character(Enigma *enigma,char *character);
void encode_message(Enigma *enigma,char *message,char *encoded_message);
void decode_character(Enigma *enigma,char *character);
void decode_message(Enigma *enigma,char *message,char *decoded_message);

void encode_file(Enigma *enigma,char *filename);
void decode_file(Enigma *enigma,char *filename);

#endif
