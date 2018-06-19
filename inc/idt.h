#pragma once

#include "stdint.h"
#include "stdlib.h"
#include "exception.h"

/*----- 定数定義 -----*/
#define IDT_MAX_INTERRUPTS 256
/* フラグ定義 */
#define	IDT_FLAGS_INTGATE_16BIT 0x06
#define	IDT_FLAGS_TSKGATE       0x05
#define	IDT_FLAGS_CALL_GATE     0x0C
#define	IDT_FLAGS_INTGATE_32BIT 0x0E
#define	IDT_FLAGS_TRPGATE       0x0F
#define	IDT_FLAGS_DPL_LV0       0x00
#define	IDT_FLAGS_DPL_LV1       0x20
#define IDT_FLAGS_DPL_LV2       0x40
#define	IDT_FLAGS_DPL_LV3       0x60
#define	IDT_FLAGS_PRESENT       0x80
#define	IDT_INT_SELECTOR 0x08

/*----- 構造体定義 -----*/
/* IDTディスクリプタ */
typedef struct {
  uint16_t baseLo;
  uint16_t sel;
  uint8_t reserved;
  uint8_t flags;
  uint16_t baseHi;
}__attribute__((packed)) IDT_DESC;
/* IDTレジスタ */
typedef struct {
  uint16_t size;
  IDT_DESC* base;
}__attribute__((packed)) IDTR;

/*----- 関数定義 -----*/
void idt_init();
void idt_load();
void idt_setup_ir(uint32_t, void*);
void idt_default_handler();
void idt_genint(uint8_t);
void idt_sethandler();

/*----- グローバル変数 -----*/
extern IDT_DESC idt[IDT_MAX_INTERRUPTS];
extern IDTR idtr;
