#include "memory.h"

/*----- グローバル変数 -----*/
PHYSICAL_MEMORY_INFO pm_info;

/**
 * メモリ管理を初期化する
 *
 * @param memsize メモリサイズ(バイト)
 */
void mem_init(uint32_t memsize)
{
  // 単位はキロバイト
  pm_info.mem_size     = memsize;
  pm_info.blocks_max   = memsize * 1024 / MEMORY_BLOCK_SIZE;
  pm_info.blocks_used  = 0;
  pm_info.blocks_free  = pm_info.blocks_max;
  pm_info.mem_map      = (uint32_t*)(__KERNEL_TOP + sizeof_kernel());
  pm_info.mem_map_size = pm_info.blocks_max / 32;
  memset(pm_info.mem_map, 0x00, pm_info.mem_map_size);
  // 0番目は使わせない
  mem_enable_bit(0);
}

/**
 * メモリ上にブロックを確保する
 *
 * @param size 確保するサイズ
 * @return 確保したブロックのアドレス
 */
void* mem_alloc_blocks(uint32_t size)
{
  uint32_t i;
  // ブロックを確保
  uint32_t frame = mem_find_blocks(size);
  if (frame == 0) return 0;
  // 使用済みフラグを立てる
  for(i = 0; i < size; i++) mem_enable_bit(frame + i);
  // アドレスとして返す
  //uint32_t addr = frame * MEMORY_BLOCK_SIZE;
  // [TODO]この確保方法は一時的なものです
  //
  uint32_t addr = (uint32_t)pm_info.mem_map + pm_info.mem_map_size;
  addr += frame * MEMORY_BLOCK_SIZE;
  //
  return (void*)addr;
}

/**
 * メモリ上のブロックを解放する
 *
 * @param addr mallocしたアドレス
 * @param size mallocしたサイズ
 */
void mem_free_blocks(void* addr, uint32_t size)
{
  uint32_t i;
  //uint32_t frame = (uint32_t)addr / MEMORY_BLOCK_SIZE;
  //
  uint32_t frame = (uint32_t)addr - (uint32_t)pm_info.mem_map - pm_info.mem_map_size;
  frame /= MEMORY_BLOCK_SIZE;
  //
  // 使用済みフラグを下げる
  for(i = 0; i < size; i++) mem_disable_bit(frame + i);
  // [TODO] これで大丈夫かを確認
  addr = NULL;
}

/**
 * 使用可能な連続したメモリブロックを探索する
 *
 * @param size 必要な連続ブロック数
 * @return 確保したブロック番号
 */
uint32_t mem_find_blocks(uint32_t size)
{
  uint32_t i, j, k, ofs;
  if (size == 0) return 0;
  for(i = 0; i < pm_info.mem_map_size; i++) {
    // 1つでも空き(0)がある
    if (pm_info.mem_map[i] != 0xFFFFFFFF) {
      // ビットごとに調べる
      for(j = 0; j < 32; j++) {
	ofs = i * 32 + j;
	if (!mem_test_bit(ofs)) {
	  for(k = 0; k <= size; k++) {
	    // 使用不可
	    if (mem_test_bit(ofs + k)) break;
	    // 必要分を確保可能
	    if (k == size) return ofs;
	  }
	}
      }
    }
  }
  return 0;
}

/**
 * ビットを立てる
 *
 * @param num 何番目のビットを扱うか
 */
void mem_enable_bit(uint32_t num)
{
  pm_info.blocks_used++;
  pm_info.blocks_free = pm_info.blocks_max - pm_info.blocks_used;
  pm_info.mem_map[num / 32] |= (1 << num);
}

/**
 * ビットを下げる
 *
 * @param num 何番目のビットを扱うか
 */
void mem_disable_bit(uint32_t num)
{
  pm_info.blocks_used--;
  pm_info.blocks_free = pm_info.blocks_max - pm_info.blocks_used;
  pm_info.mem_map[num / 32] &= ~(1 << num);
}

/**
 * ビットを調べる
 *
 * @param num 何番目のビットを調べるか
 * @return セットされていれば1
 */
uint8_t mem_test_bit(uint32_t num)
{
  return (pm_info.mem_map[num / 32] & (1 << num)) > 0;
}

/**
 * カーネル本体のサイズを取得する
 *
 * @return カーネルのサイズ(バイト)
 */
inline uint32_t sizeof_kernel(void)
{
  return (__KERNEL_BOTTOM - __KERNEL_TOP);
}
