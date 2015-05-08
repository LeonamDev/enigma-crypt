#include <stdio.h>
#include <stdlib.h>

#include "enigma.h"

int main(int argc, char *argv[])
{
    Enigma *enigma;

    enigma = create_enigma();

    if(enigma != NULL)
    {
        printf("Enigma encoder/decoder!\n");
        print_rotors(enigma);

        destroy_enigma(enigma);
    }

    return 0;
}
