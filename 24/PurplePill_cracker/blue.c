#include <stdio.h>
#include <inttypes.h>
#include "rabbit.h"
#define EPOCH_DIFF 11644473600LL
#define LAST_MODIFIED 1540734118LL /*2018-10-28 14:41:58*/

uint8_t key[16]= {0x87, 0x05, 0x89, 0xCD, 0xA8, 0x75, 0x62, 0xEF, 0x38, 0x45, 0xFF, 0xD1, 0x41, 0x37, 0x54, 0xD5};
uint8_t valid_header [4] = {0x85, 0x44, 0x00, 0x10};


uint64_t getfiletime(unsigned long unix_epoch) {
  
  unsigned long long result = EPOCH_DIFF;
  result += unix_epoch;
  result *= 10000000LL;
  return result;
}


int main(void) {
  RABBIT_ctx c;
  uint64_t i;
  for(i = getfiletime(LAST_MODIFIED); i > 0; i -= 10000)
  {
    uint8_t in[4] = {0x1E, 0xD5, 0x3B, 0xF4};
    uint8_t* iv = (uint8_t*) &i;
    RABBIT_setkey(&c, key);
    RABBIT_setiv (&c, iv);
    RABBIT_crypt (&c, in, 4);
    
    if (memcmp((void *)valid_header, (void *)in, 4) == 0)
    {
      printf("Found: %" PRIu64 " (", i);
      size_t j;
      for(j = 0; j < 8; j++)
        printf("%02X", iv[j]);
      printf(")\n");
      return 0;
    }
  }

  printf("Not found!\n");
  return 1;
}
