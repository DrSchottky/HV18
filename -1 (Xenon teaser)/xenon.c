#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xenos/xenos.h>
#include <console/console.h>
#include <xenon_smc/xenon_smc.h>
#include <xenon_soc/xenon_secotp.h>
#include <crypt/rc4.h>

int main(){
	//Trap #1
	xenon_smc_power_shutdown();

	xenos_init(VIDEO_MODE_AUTO);
	console_set_colors(0, -1);
	console_init();
	console_clrscr();

	printf("\nHackVent 2018");
	printf("\n\nDrSchottky wishes you happy Holy(0)days\n\n");

	uint64_t fuseline_0 = xenon_secotp_read_line(0);
	uint64_t fuseline_1 = xenon_secotp_read_line(1);
	volatile char hint[] = "I wish I was a Devkit :(";

	unsigned char ciphertext []  = {0xdf,0x66,0x58,0xc0,0x5e,0x93,0xc8,0xd4,0xc4,0xe9,0x5e,0x36,0xb1,0x55,0x14,0x4a,0xbe,0x83,0xc9,0x0a,0xdc,0x2b,0xc5,0xf0,0x8f,0xab,0xbb,0xac,0x49,0xdd,0x0f,0x01,0x97,0xf6,0x66,0x8b,0x07,0xa0,0xb4,0x43};
	int ciphertext_size = sizeof(ciphertext)/sizeof(unsigned char);
	unsigned char rc4_key[0x10];
	int i;
	for(i = 0; i < 16; i+=2){
		rc4_key[i] = ((fuseline_0>>(8*(7 - (i/2)))) & 0x00000000000000FF);
		rc4_key[i + 1] = ((fuseline_1>>(8*(7 - (i/2)))) & 0x00000000000000FF);
	}
	
	/*
	There's a 1-byte difference in the fuseline between a Retail console and a Devkit one
	https://github.com/Free60Project/wiki/blob/master/Fusesets.md
	As hinted the flag was encypted with a Devkit fuseset
	*/ 
	//rc4_key[15]=0xf;

	unsigned char rc4_state[0x100];
	memset(rc4_state, 0, 0x100);
	rc4_init(rc4_state, rc4_key, 0x10);
	rc4_crypt(rc4_state, ciphertext, ciphertext_size);

	//Trap #2
	console_set_colors(0, 0);

	for(i = 0; i < ciphertext_size; i++)
		printf("%c", ciphertext[i]);


	
	while(1) {
	printf("\r");
	}
	return 0;
}
