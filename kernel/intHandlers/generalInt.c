#include "generalInt.h"

static intHandler intHandlers[IDT_ENTRIES];

//these messages use 2 pages in space (about 0x2000 bytes)
static char exceptionMessage[16][28] =
{
	"Division by zero",
	"Single step",
	"Non maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Bounds check",
	"Undefined OP Code!",
	"No coprocessor",
	"Double fault!",
	"Coprocessor segment overrun",
	"Invalid TSS!",
	"Segment not present.",
	"Task segment overrun",
	"General protection fault!",
	"Page fault!",
	"Unassigned"
};

void generalIntHandler(registers_t *regs)
{
	//auto EOI is active -> no need to send EOI here :)
	
	if(intHandlers[regs->intNo])
	{
		intHandlers[regs->intNo](regs);
	}
	else
	{
		if(regs->intNo <= 16)
		{
			fatalErr("Unhandled exception (%x). Message: %s",
				regs->intNo, exceptionMessage[regs->intNo]);
		}
		printErr("Unhandled interrupt (%x)!\n", regs->intNo);
	}
}

extern inline void registerIntHandler(uint16_t id, intHandler func)
{
	if(id >= IDT_ENTRIES)
	{
		fatalErr("Unable to register interrupt handler!");
	}
	intHandlers[id] = func;
}