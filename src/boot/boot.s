;; global
global start
;; external
extern main

;;; Definitions
;; Header of boot loader
	MAGIC_NUMBER equ 0x1BADB002    ; magic number
	FLAGS        equ 0x0           ; multiboot
	CHECKSUM     equ -MAGIC_NUMBER ; MAGIC + CHECK + FLAG = 0
;; Stack
	KERNEL_STACK_SIZE equ 0x1000 ; stack size

;;; text section
section .text
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
bits 32

;;; Entry point
start:
	mov esp, kstack + KERNEL_STACK_SIZE
	push eax		; magic number
	push ebx		; multiboot information
	; 32bit protected mode
	cli			; disable interruption
	mov eax, gdt_toc
	lgdt [eax]
	; set protected mode bit to 1
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp dword 08h:.pmode
bits 32
.pmode:
	mov ax, 0x10
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ds, ax
	pop ebx			; mb_info
	pop eax			; magic
	mov esp, 0x90000
	sti			; enable interruption
	push eax		; magic
	push ebx		; mb_info
	call main
	cli
.hlt:
	hlt
	jmp .hlt

;;; data section
section .data
align 4
;; GDT Table
gdt_data:
	; null descriptor
	dd 0
	dd 0
	; code descriptor
	dw 0FFFFh
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
	; data descriptor
	dw 0FFFFh
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
;; GDT structure
gdt_toc:
	dw 8*3
	dd gdt_data
	
;;; bss section
section .bss
align 4
;; Stack
kstack:
	resb KERNEL_STACK_SIZE
