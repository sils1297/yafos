/* include/sys/io.h
 * 
 * Provides functions for general input and output. (Writing to registers ...)
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _SYS_IO_H
#define _SYS_IO_H

#include <stdint.h>

#define cli() __asm__ __volatile__ ("cli")
#define sti() __asm__ __volatile__ ("sti")
#define hlt() __asm__ __volatile__ ("hlt")

void outb(uint8_t value, uint16_t port);

#endif /* _SYS_IO_H */