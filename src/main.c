#include "video.h"
#include "hal.h"

/*
 * KERNEL MAIN
 */
int kmain(multiboot_info_t* mbd, uint32_t magic)
{
  magic = magic;
  hal_init(mbd);
  video_setmode();
  
  *(unsigned short*)(0xB8000) = 0x4141;

  return 0;
}
