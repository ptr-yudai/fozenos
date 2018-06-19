#include "idt.h"

/* グローバル変数 */
IDT_DESC idt[IDT_MAX_INTERRUPTS];
IDTR idtr;

/**
 * IDTを初期化する
 */
void idt_init()
{
  int i;

  // IDTRを設定
  idtr.size = IDT_MAX_INTERRUPTS * sizeof(IDT_DESC);
  idtr.base = (IDT_DESC*)&idt[0];
  memset((void*)&idt[0], 0, IDT_MAX_INTERRUPTS * sizeof(IDT_DESC));
  // デフォルトハンドラを設定
  for(i = 0; i < IDT_MAX_INTERRUPTS; i++) {
    idt_setup_ir(i, idt_default_handler);
  }
  // IDTRにIDTをロード
  idt_load();
}

/**
 * 割り込みベクタにハンドラを設定する
 *
 * @param i       割り込みベクタテーブルの何番目か
 * @param handler ハンドラのアドレス
 */
void idt_setup_ir(uint32_t i, void* handler)
{
  // ベクタテーブルの範囲外
  if (i > IDT_MAX_INTERRUPTS) return;
  // ハンドラがNULLポインタ
  if (!handler) return;
  // idtディスクリプタを設定
  uint32_t uiBase = (uint32_t)handler;
  idt[i].baseLo   = (uint16_t)(uiBase & 0xFFFF);
  idt[i].sel      = IDT_INT_SELECTOR;
  idt[i].reserved = 0;
  idt[i].flags    = (uint8_t)(IDT_FLAGS_PRESENT | IDT_FLAGS_INTGATE_32BIT);
  idt[i].baseHi   = (uint16_t)((uiBase >> 16) & 0xFFFF);
}

/**
 * IDTRにIDTをロードする
 */
void idt_load()
{
  __asm__ __volatile__ ("lidt idtr");
}

/**
 * デフォルトハンドラ
 */
void idt_default_handler()
{
  kernel_panic("Unhandled Exception");
}

/**
 * 割り込みを発生する
 *
 * @param sys 割り込み番号
 */
void idt_genint(uint8_t sys)
{
  asm volatile
    (
     "movb %0, genint+1\n"
     "genint:\n"
     "int $0\n"
     : /* output */ : "r"(sys) /* input */ : /* clobbered */
     );
}
