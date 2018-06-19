#pragma once

#include "stdint.h"
#include "multiboot.h"
#include "idt.h"
#include "pic.h"
#include "memory.h"

/*----- 関数定義 -----*/
void hal_init(multiboot_info_t* mbd);
void __attribute__((__cdecl__)) interrupt_done(uint32_t inter_n);
void __attribute__((__cdecl__)) enable_interrupt(void);
void __attribute__((__cdecl__)) disable_interrupt(void);
void enter_interrupt(void);
void exit_interrupt(void);
