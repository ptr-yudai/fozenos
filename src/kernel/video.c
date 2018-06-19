#include "video.h"

void video_setmode(void)
{
  asm volatile
    (
     "movb $0x00, %ah\n"
     "movb $0x13, %al\n"
     "int $0x10\n"
     );
}

uint8_t video_getmode(void)
{
  asm volatile
    (
     "movb $0x0f, %ah\n"
     );
  return 1;
}
