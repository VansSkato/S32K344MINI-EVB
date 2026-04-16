/* Copyright 2020, 2022-2023, 2025 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/
/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K344.h"

#include <stdio.h>
#include <stdint.h>

#define SIUL2_BASE  	0x40290000UL 	//es la base
#define SIUL2_MSCR29_B 	(*(volatile uint32_t*)(SIUL2_BASE + 0x2B4UL)) //la base + el ofset del 29 //Pag.309
#define SIUL2_MSCR30_B  (*(volatile uint32_t*)(SIUL2_BASE + 0x2B8UL)) //la base + el ofset del 30 //Pag.309
#define SIUL2_MSCR31_B  (*(volatile uint32_t*)(SIUL2_BASE + 0x2BCUL)) //la base + el ofset del 31 //Pag.309


 // Leer la parte de abajo para entender
/*
 *
 * - (volatile uint32_t*):
 *   Se hace un cast a un puntero a entero de 32 bits sin signo y "volatile":
 *     • uint32_t → el registro es de 32 bits.
 *     • volatile → indica al compilador que este valor puede cambiar por hardware
 *       en cualquier momento, evitando optimizaciones peligrosas.
 *
 * - *(...):
 *   Se desreferencia el puntero para acceder directamente al contenido del registro.
 *
 * Resultado:
 *   Permite leer o escribir directamente en el registro MSCR29 como si fuera
 *   una variable, por ejemplo:
 *
 *       SIUL2_MSCR29 = 0x00000001;   // escritura
 *       uint32_t val = SIUL2_MSCR29; // lectura
 *
 * Uso típico:
 *   Configuración de un pin específico (modo GPIO, función alternativa, pull-up/down, etc.).
 */

#define GPDO29		(*(volatile uint8_t*)(SIUL2_BASE + 0x131EUL))// formula 1300h + (n + 3 - 2 × (n mod 4))
#define GPDO30		(*(volatile uint8_t*)(SIUL2_BASE + 0x131DUL))// formula 1300h + (n + 3 - 2 × (n mod 4))
#define GPDO31		(*(volatile uint8_t*)(SIUL2_BASE + 0x131CUL))// formula 1300h + (n + 3 - 2 × (n mod 4))


int main(void)
{
	SIUL2_MSCR29_B = (1U<< 21); // OBE y SSS = 0000 -> GPIO PAG 425
	SIUL2_MSCR30_B = (1U<<21); // OBE y SSS = 0000 -> GPIO
	SIUL2_MSCR31_B = (1U<<21); // OBE y SSS = 0000 -> GPIO

	while(1)
	{	//LED ON REd
		GPDO29 = 1U;
		for(uint32_t  i = 0 ; i < 700000 ; i++);
		//Led OFF
		GPDO29 = 0U;
		for(uint32_t  i = 0 ; i < 700000 ; i++);

		//LED ON
		GPDO30 = 1U;
		for(uint32_t  i = 0 ; i < 800000 ; i++);
		//Led OFF
		GPDO30 = 0U;
		for(uint32_t  i = 0 ; i < 800000 ; i++);

		//LED ON
		GPDO31 = 1U;
		for(uint32_t  i = 0 ; i < 900000 ; i++);
		//Led OFF
		GPDO31 = 0U;
		for(uint32_t  i = 0 ; i < 900000 ; i++);

	}


}

//Paginas importantes
/*
 * PAG 308
 * PAG 41
 * PAG 424
 * PAG 425
 * PAG 439
 * PAG 440
 * PAG 309
 * */



