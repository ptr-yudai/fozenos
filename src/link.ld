/*
 * Kernel linker script
 *  reference: stevej/osdev
 */
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
phys = 0x00100000;

SECTIONS
{
	. = 0x00100000;
	_KERNEL_TOP = .;

	/*
	 * text
	 */
	.text phys : AT(phys) {
	      code = .;
	      *(.text)
	      *(.rodata)
	      . = ALIGN(4096);
	}
	/*
	 * data
	 */
	.data : AT(phys + (data - code)) {
	      data = .;
	      *(.data)
	      . = ALIGN(4096);
	}
	/*
	 * bss
	 */
	.bss : AT(phys + (bss - code)) {
	     bss = .;
	     *(.bss)
	     . = ALIGN(4096);
	}
	/* End of kernel */
	terminal = .;
	/*
	 * Get rid of unnecessary GCC bits
	 */
	/DISCARD/ :
	{
		*(.comment)
		*(.eh_frame)
		*(.note.gnu.build-id)
	}
	
	_KERNEL_BOTTOM = .;
}
