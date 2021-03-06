/* x86_idt.c
 * 
 * Provides function headers for manipulating the interrupt descriptor table.
 * Architecture specific file for x86 architecture.
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#include "idt.h"

#ifdef _X86_IDT_H

#include <stdint.h>
#include <sys/io.h>
#include <string.h>
#include <PIC/pic.h>
#include <stdMacro.h>

STRUCT
{
	uint16_t entryLow;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  attr;
	uint16_t entryHigh;
} PACKED idtEntry_t;

STRUCT
{
	uint16_t  limit;
	void     *base;
} PACKED idtPtr_t;

// interrupt handler routines
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define I_PRESENT	1<<7
#define I_DPL(dpl)	((dpl)<<5)
#define I_STORAGE	1<<4
#define I_TASK_GATE	0x5
#define I_TRAP_GATE	0xF
#define I_INT_GATE	0xE

#define CALC_SEL(param) (param)*8

static idtEntry_t idt[IDT_ENTRIES];
static idtPtr_t   tidtPtr;

static void idtSetGate(const uint8_t index, const uint32_t entry, const uint16_t selector, const uint16_t attr)
{
	idt[index].zero = 0x00;
	idt[index].attr = attr;
	idt[index].selector  = selector;
	idt[index].entryLow	 = 0xFFFF & entry;
	idt[index].entryHigh = (entry>>16) & 0xFFFF;
}

void installIdt(void)
{
	tidtPtr.limit = (sizeof(idtEntry_t) * IDT_ENTRIES)-1;
	tidtPtr.base  = idt;
	
	memset((void *)idt, 0, sizeof(idtEntry_t) *IDT_ENTRIES);
	
	//set gates for all exceptions
	idtSetGate(0 , (uint32_t)isr0 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(1 , (uint32_t)isr1 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(2 , (uint32_t)isr2 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(3 , (uint32_t)isr3 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(4 , (uint32_t)isr4 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(5 , (uint32_t)isr5 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(6 , (uint32_t)isr6 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(7 , (uint32_t)isr7 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(8 , (uint32_t)isr8 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(9 , (uint32_t)isr9 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(10, (uint32_t)isr10, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(11, (uint32_t)isr11, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(12, (uint32_t)isr12, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(13, (uint32_t)isr13, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(14, (uint32_t)isr14, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(15, (uint32_t)isr15, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(16, (uint32_t)isr16, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(17, (uint32_t)isr17, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(18, (uint32_t)isr18, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(19, (uint32_t)isr19, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(20, (uint32_t)isr20, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(21, (uint32_t)isr21, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(22, (uint32_t)isr22, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(23, (uint32_t)isr23, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(24, (uint32_t)isr24, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(25, (uint32_t)isr25, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(26, (uint32_t)isr26, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(27, (uint32_t)isr27, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(28, (uint32_t)isr28, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(29, (uint32_t)isr29, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(30, (uint32_t)isr30, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(31, (uint32_t)isr31, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	
	//set gates for all hardware IRQs (with one master and slave its 16 IRQs)
	idtSetGate(32, (uint32_t)irq0 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(33, (uint32_t)irq1 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(34, (uint32_t)irq2 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(35, (uint32_t)irq3 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(36, (uint32_t)irq4 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(37, (uint32_t)irq5 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(38, (uint32_t)irq6 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(39, (uint32_t)irq7 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(40, (uint32_t)irq8 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(41, (uint32_t)irq9 , CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(42, (uint32_t)irq10, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(43, (uint32_t)irq11, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(44, (uint32_t)irq12, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(45, (uint32_t)irq13, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(46, (uint32_t)irq14, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	idtSetGate(47, (uint32_t)irq15, CALC_SEL(1), I_PRESENT|I_DPL(0)|I_INT_GATE);
	
	//flush :)
	cli();
	remapIrqs();
	lidt(tidtPtr);
}

#endif /* _X86_IDT_H */
