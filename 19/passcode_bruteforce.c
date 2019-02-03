#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t enc_flag[] = {0xC1,0xF2,0x74,0x68,0xF3,0x51,0xBC,0xF0,0x00,0x87,0xAB,0x8A,0xA0,0xD1,0x57, 0xE3,0xDE,0x71,0x12,0xF3,0x72,0x85,0xEB,0x2F,0x87,0xA7,0xAB,0xAB,0xFF,0x74};
uint8_t xor_mask[] = {0x89,0xA4,0x45,0x50,0xDE,0x00,0x00,0x00,0x00,0xAA,0x00,0x00,0x00,0x00,0x7A};
uint8_t code [] = {'W','3','b','4','5','m',0,0,0,0,0,0,0,0,0};
char * letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
int r44 = 0;

int valid_ascii(char i, int index) 
{
	if((( i >= 48 && i<= 57 ) || ( i>= 65 && i <= 90) || ( i >= 97 && i <= 122 ) || i == 45) || ( i == 0x0e && index == 14 ))
		return 1;
	return 0;
}

void generate_mask(char * str, int n) {
	r44 = 0;
	uint8_t r55 = 165;
	uint8_t i;
	for (i = 0; i <= n; i++) { 
		int r60 = str[i] * r55 + 1337;
		r44 += r60 + str[i];
		uint8_t r61 = (uint8_t)(r60 % 255);
		xor_mask[i] = r61;
		r55 = r61;
	}
	
}

int is_valid(char * code, int index) {
	generate_mask(code, index);
	if (index == 9 && xor_mask[9] != 0xAA)
		return 0;
	if (index == 14 && xor_mask[14] != 0x7a)
		return 0;
	if (valid_ascii(xor_mask[index] ^ enc_flag[index], index) && valid_ascii(xor_mask[index] ^ enc_flag[index + 15], index))
		return 1;
	return 0;
}


int main()
{
	for (char * a = letters; *a != 0; ++a) {
		char tmp[1] = {*a};
		memcpy((void*)code + 6, (void*) tmp, 1);
		if (!is_valid(code,6))
			continue;
		for (char * b = letters; *b != 0; ++b) {
			char tmp[2] = {*a, *b};
			memcpy((void*)code + 6, (void*) tmp, 2);
			if (!is_valid(code,7))
				continue;
			for (char * c = letters; *c != 0; ++c) {
				char tmp[3] = {*a, *b, *c};
				memcpy((void*)code + 6, (void*) tmp, 3);
				if (!is_valid(code,8))
					continue;
				for (char * d = letters; *d != 0; ++d) {
					char tmp[4] = {*a, *b, *c, *d};
					memcpy((void*)code + 6, (void*) tmp, 4);
					if (!is_valid(code,9))
						continue;
					for (char * e = letters; *e != 0; ++e) {
						char tmp[5] = {*a, *b, *c, *d, *e};
						memcpy((void*)code + 6, (void*) tmp, 5);
						if (!is_valid(code,10))
							continue;
						for (char * f = letters; *f != 0; ++f) {
							char tmp[6] = {*a, *b, *c, *d, *e, *f};
							memcpy((void*)code + 6, (void*) tmp, 6);
							if (!is_valid(code,11))
								continue;
								for (char * g = letters; *g != 0; ++g) {
								char tmp[7] = {*a, *b, *c, *d, *e, *f ,*g};
								memcpy((void*)code + 6, (void*) tmp, 7);
								if (!is_valid(code,12))
									continue;
								for (char * h = letters; *h != 0; ++h) {
									char tmp[8] = {*a, *b, *c, *d, *e, *f ,*g, *h};
									memcpy((void*)code + 6, (void*) tmp, 8);
									if (!is_valid(code,13))
										continue;
									for (char * i = letters; *i != 0; ++i) {
										char tmp[9] = {*a, *b, *c, *d, *e, *f ,*g, *h, *i};
										memcpy((void*)code + 6, (void*) tmp, 9);
										if (!is_valid(code,14) || r44 != 217675)
											continue;
										else
											for(int z = 0;z < 15;z++)
												printf("%c", code[z]);
											printf("\n");
									}
								}
							}
						}
					}
				}				
			}
		}
	}
}