#include "spritz.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    uint8_t m[] = "shuffle*whip$crush%squeeze";
    uint8_t enc [] = {0xf4, 0x2d, 0xf9, 0x2b, 0x38, 0x9f, 0xff, 0xca, 0x59, 0x59, 0x84, 0x65, 0xc7, 0xa5, 0x1d, 0x36, 0x08, 0x2e, 0xcf, 0xea, 0x56, 0x7a, 0x90, 0x0e, 0x5e, 0xac, 0x9e, 0x5e, 0x9f, 0xb1};
    spritz_encrypt(m,27,enc,30);
    int i = 0;
    for (i=0;i<30;i++)
    	printf("%c", enc[i]);
    return 0;
}
