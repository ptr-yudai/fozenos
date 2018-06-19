#include "stdlib.h"

/**
 * memcpy - メモリにデータをコピーする
 *
 * @param to   コピー先のメモリブロック
 * @param from コピー元のメモリブロック
 * @param n    コピーバイト数
 * @return コピー先アドレス
 */
void *memcpy(void *to, const void *from, uint32_t n)
{
  uint32_t i;
  uint8_t* dest = (uint8_t*)to;
  uint8_t* src = (uint8_t*)from;
  // コピー実行
  for(i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  return to;
}

/**
 * memset - メモリにバイトを連続コピーする
 *
 * @param to セット先のメモリブロック
 * @param ch セットする文字
 * @param n  セットバイト数
 * @return セット先アドレス
 */
void *memset(void *to, uint8_t ch, uint32_t n)
{
  uint32_t i;
  uint8_t* desc = (uint8_t*)to;
  for(i = 0; i < n; i++) {
    desc[i] = ch;
  }
  return to;
}
