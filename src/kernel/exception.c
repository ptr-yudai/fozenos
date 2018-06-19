#include "exception.h"

/**
 * カーネルパニック画面
 *
 * @param msg 表示するエラー原因
 */
void kernel_panic(const char* msg)
{
  msg = msg;
  asm volatile
    (
     ".loop:\n"
     "cli\n"
     "hlt\n"
     "jmp .loop\n"
     );
}
