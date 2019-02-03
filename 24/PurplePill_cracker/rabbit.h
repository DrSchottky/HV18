/**
  Copyright © 2016 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#ifndef RABBIT_H
#define RABBIT_H

#include "macros.h"

typedef struct {
   uint32_t x[8];
   uint32_t c[8];
   uint32_t carry;
} RABBIT_state;

typedef struct {
   RABBIT_state m;
   RABBIT_state w;
} RABBIT_ctx;

#ifdef __cplusplus
extern "C" {
#endif

  void RABBIT_setkey(RABBIT_ctx*, const void*);
  void RABBIT_setkeyx(RABBIT_ctx*, const void*);

  void RABBIT_setiv(RABBIT_ctx*, const void*);
  void RABBIT_setivx(RABBIT_ctx*, const void*);

  void RABBIT_crypt(RABBIT_ctx*, void*, uint32_t);
  void RABBIT_cryptx(RABBIT_ctx*, void*, uint32_t);

#ifdef __cplusplus
}
#endif

#endif
