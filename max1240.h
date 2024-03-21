// @File		MAX1240.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		19/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MAX1240_H
#define MAX1240_H

#define MAX1240_CS          PORTCbits.RC3
#define MAX1240_SDI         PORTCbits.RC1
#define MAX1240_SD0         PORTCbits.RC2
#define MAX1240_SCK         PORTCbits.RC0

#define MAX1240_CS_TRIS     TRISCbits.RC3
#define MAX1240_SDI_TRIS    TRISCbits.RC1
#define MAX1240_SDO_TRIS    TRISCbits.RC2
#define MAX1240_SCK_TRIS    TRISCbits.RC0

unsigned int MAX1240_read(void)
{
    unsigned int data = 0x00;
    
    MAX1240_SCK = 0;
    
    MAX1240_CS = 0;
       
    while(MAX1240_SD0 == 0);
    
    for(unsigned int bits = 0; bits < 12; bits++)
    {        
       data <<= 1;
        if(MAX1240_SD0) data |= 0x01;
        
       __asm__ __volatile__("nop");
        MAX1240_SCK = 1;
        __asm__ __volatile__("nop");
        MAX1240_SCK = 0;
        __asm__ __volatile__("nop");
    }
    
    MAX1240_CS = 1;
    
    return ((unsigned int) data);
}

void MAX1240_Init(void)
{
    MAX1240_SCK_TRIS = 0;
    MAX1240_SDI_TRIS = 0;
    MAX1240_SDO_TRIS = 1;
    MAX1240_CS_TRIS = 0;
    
    MAX1240_CS = 1;
}

#endif
