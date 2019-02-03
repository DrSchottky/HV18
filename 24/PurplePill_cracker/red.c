#include <stdio.h>
#include <inttypes.h>
#include <pthread.h>
#include "rabbit.h"
#define THREAD_NUM 20

uint8_t valid_header [4] = {0x90, 0xE7, 0xDA, 0xAA};
uint8_t run_threads = 1;

void decrypt(size_t *index) {

  uint64_t start = (*index) * (100000000 / THREAD_NUM), stop = start + (100000000 / THREAD_NUM);
  RABBIT_ctx c;
  uint64_t i;
  for(i = start; i < stop && run_threads; i += 1)
  {
    uint8_t in[64] = {0x59, 0xC5, 0xB2, 0xAB};
    uint8_t key[16];
    uint8_t iv[9];
    sprintf((char *)iv, "%" PRIu64 "", i);
    memcpy(key, iv, 8);
    memcpy(key + 8, iv, 8);  
    RABBIT_setkey(&c, key);
    RABBIT_setiv (&c, iv);
    RABBIT_crypt (&c, in, 4);
    
    if (memcmp((void *)valid_header, (void *)in, 4) == 0)
    {
      printf("Found: %" PRIu64 "\n", i);
      run_threads = 0;
      return;
    }

  }
}

int main(void) {
  pthread_t threads [THREAD_NUM];
  size_t start_values [THREAD_NUM];
  size_t i;

  for(i = 0; i < THREAD_NUM; i++) {
    start_values[i] = i;
    pthread_create(&threads[i], NULL, (void*)decrypt, &start_values[i]);
  }

  for(i = 0; i < THREAD_NUM; i++)
    pthread_join(threads[i], NULL);

    
  return 0;
}
