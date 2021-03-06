#include <sys/io.h>

//definition has to be extern inline to be visible for other files since inline
//in gcc C99 standard contains an implicit static if not mentioned else
//TODO understand this fully
extern inline void outb (uint16_t port, uint8_t value)
{
	ASM("outb %b0,%w1": :"a" (value), "Nd" (port));
}

extern inline uint8_t inb (uint16_t port)
{
	uint8_t result;
	ASM("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}
