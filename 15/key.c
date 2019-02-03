#include <stdio.h>
#include <string.h>


int main()
{
	char v14 [] = {0x75, 0x51, 0x41, 0x5C, 0x2D, 0x6E, 0x4D, 0x40, 0x3D, 0x31, 0x77, 0x6C, 0x1E, 0x62, 0x4E, 0x21, 0x00};
	printf("%s\n", v14);
	int v3;
	if (strlen((const char *)v14)){
		*v14 = 120;
		if (strlen((const char *)v14) >= 2){
			v3 = 1;
			do
				*(v14 + v3++) += 3;
			while (strlen((const char *)v14) > v3);
		}
	}

	printf("%s\n", v14);

	return 0;
}
