/*
    FreeRTOS V4.0.1 - Copyright (C) 2003-2006 Richard Barry.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FreeRTOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FreeRTOS; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes FreeRTOS, without being obliged to provide
    the source code for any proprietary components.  See the licensing section 
    of http://www.FreeRTOS.org for full details of how and when the exception
    can be applied.

    ***************************************************************************
    See http://www.FreeRTOS.org for documentation, latest information, license 
    and contact details.  Please ensure to read the configuration and relevant 
    port sections of the online documentation.
    ***************************************************************************
*/

#ifndef PORTMACRO_H
#define PORTMACRO_H

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */


/* Type definitions. */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      long
#define portLONG        long
#define portSHORT       int
#define portSTACK_TYPE  unsigned portSHORT
#define portBASE_TYPE	portSHORT

#if( configUSE_16_BIT_TICKS == 1 )
        typedef unsigned portSHORT portTickType;
        #define portMAX_DELAY ( portTickType ) 0xffff
#else
        typedef unsigned portLONG portTickType;
        #define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
void portENTER_CRITICAL( void );
#pragma aux portENTER_CRITICAL = "pushf" \
                                 "cli";

void portEXIT_CRITICAL( void );
#pragma aux portEXIT_CRITICAL   = "popf";

void portDISABLE_INTERRUPTS( void );
#pragma aux portDISABLE_INTERRUPTS = "cli";

void portENABLE_INTERRUPTS( void );
#pragma aux portENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define portSTACK_GROWTH        ( -1 )
#define portSWITCH_INT_NUMBER   0x80
#define portYIELD()             __asm{ int portSWITCH_INT_NUMBER } 
#define portTICK_RATE_MS        ( ( portTickType ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT      2
#define portINITIAL_SW          ( ( portSTACK_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portNOP()				__asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define portINPUT_BYTE( xAddr )                 inp( xAddr )
#define portOUTPUT_BYTE( xAddr, ucValue )       outp( xAddr, ucValue )
#define portINPUT_WORD( xAddr )                 inpw( xAddr )
#define portOUTPUT_WORD( xAddr, usValue )       outpw( xAddr, usValue )
#define inline
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )


#endif /* PORTMACRO_H */

