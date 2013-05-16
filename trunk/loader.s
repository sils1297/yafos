; init.s
;
; Contains the nessecary instructions to load the C kernel. Therefore it is the
; bridge from an arbitrary multiboot compliant bootloader to the C kernel.
; That includes specificly the following tasks:
; 		build up a stack
; 		TODO read multiboot structure and pass it to the kernel
; 		Call the kernel
; 		Halt the system if the kernel returns
;
; Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
; Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
;
; This program is free software: you can redistribute it and/or modify it under
; the terms of the GNU General Public License as published by the Free Software
; Foundation, either version 3 of the License, or (at your option) any later
; version.

; Declarations
global loader
global hltLoop
extern init

; Definition macros
%define STACKSIZE 0x2000 ; 8kiB Stack

section .multiboot 
; setting up the Multiboot header - see GRUB docs for details
; a multiboot compliant bootloader will read the parameters from here
%define MODULEALIGN  1<<0
%define MEMINFO      1<<1
MAGIC       equ  0x1BADB002
FLAGS       equ  MODULEALIGN | MEMINFO
CHECKSUM    equ -(MAGIC + FLAGS)

align 4 ; these are 4 bytes in length for meeting multiboot requirements
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
; more information
; http://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf

section .text

loader:
	mov  esp, stack
	; TODO pass multiboot structure to the stack
	cli ; clear interrupts before enabled controlled by the kernel
	; init function is defined in init.c
	call init
	; If the kernel returns halt the system
	jmp hltLoop

hltLoop:
	hlt
	jmp hltLoop

; All the code needed by the C kernel
%include "loader/include.inc"

section .bss
align 4
stackend: resb STACKSIZE
stack: