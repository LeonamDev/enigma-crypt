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
