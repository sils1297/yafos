#include "pic.h"

//TODO parameters
void remapIrqs(void)
{
	//ICW1
	PIC_MASTER_CMD(PIC_INIT | PIC_ICW4_FOLLOWS);
	PIC_SLAVE_CMD (PIC_INIT | PIC_ICW4_FOLLOWS);
	
	//ICW2 - send new offsets
	PIC_MASTER_DAT(PIC_MASTER_OFFS);
	PIC_SLAVE_DAT (PIC_SLAVE_OFFS);
	
	//ICW3 - send where the other is ;)
	PIC_MASTER_DAT(PIC_MASTER_IRQ);
	PIC_SLAVE_DAT (PIC_SLAVE_IRQ);
	
	//ICW4 - send flags
	PIC_MASTER_DAT(PIC_PC | PIC_AUTO_EOI);
	PIC_SLAVE_DAT (PIC_PC | PIC_AUTO_EOI);
}

extern inline void maskIrqs(uint16_t mask)
{
	PIC_MASTER_DAT((uint8_t)(mask));
	PIC_SLAVE_DAT((uint8_t)(mask >> 8));
}