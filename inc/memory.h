#pragma once

#include "stdint.h"
#include "stdlib.h"
#include "linker.h"

/*----- 定数 -----*/
#define MEMORY_KERNEL_START 0x00100000
#define MEMORY_BLOCK_SIZE   4096

/*----- 構造体 -----*/
// ビットマップ情報
typedef struct {
  uint32_t mem_size;
  uint32_t blocks_max;
  uint32_t blocks_used;
  uint32_t blocks_free;
  uint32_t *mem_map;
  uint32_t mem_map_size;
} PHYSICAL_MEMORY_INFO;

/*----- 関数定義 -----*/
void mem_init(uint32_t memsize);
uint32_t mem_find_blocks(uint32_t size);
void* mem_alloc_blocks(uint32_t size);
void mem_free_blocks(void* addr, uint32_t size);
void mem_enable_bit(uint32_t num);
void mem_disable_bit(uint32_t num);
uint8_t mem_test_bit(uint32_t num);
inline uint32_t sizeof_kernel(void);

/*----- 変数 -----*/
extern PHYSICAL_MEMORY_INFO pm_info;
