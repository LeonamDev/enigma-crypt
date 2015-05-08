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

Enigma* create_enigma(void);

void destroy_enigma(Enigma *enigma);
void print_rotors(Enigma *enigma);

void standardize_text(char *text);

#endif
