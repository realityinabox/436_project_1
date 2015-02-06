/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : ENC_SW_2.h
**     Project     : Lab04
**     Processor   : MK64FN1M0VLQ12
**     Component   : ExtInt
**     Version     : Component 02.105, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-02, 13:47, # CodeGen: 0
**     Abstract    :
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**         Interrupt name              : INT_PORTB
**         User handling procedure     : ENC_SW_2_OnInterrupt
**
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       92            |  ADC1_SE15/PTB11/SPI1_SCK/UART3_TX/FB_AD18/FTM0_FLT2
**             ----------------------------------------------------
**
**         Port name                   : PTB
**
**         Bit number (in port)        : 11
**         Bit mask of the port        : 0x0800
**
**         Signal edge/level           : both
**         Priority                    : 112
**         Pull option                 : off
**         Initial state               : Enabled
**
**
**         Port data register          : GPIOB_PDOR [0x400FF040]
**         Port control register       : GPIOB_PDDR [0x400FF054]
**     Contents    :
**         GetVal - bool ENC_SW_2_GetVal(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ENC_SW_2.h
** @version 01.00
** @brief
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup ENC_SW_2_module ENC_SW_2 module documentation
**  @{
*/         

#ifndef __ENC_SW_2_H
#define __ENC_SW_2_H

/* MODULE ENC_SW_2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "ExtIntLdd2.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 




/*
** ===================================================================
**     Method      :  ENC_SW_2_GetVal (component ExtInt)
**     Description :
**         Returns the actual value of the input pin of the component.
**     Parameters  : None
**     Returns     :
**         ---             - Returned input value. Possible values:
**                           <false> - logical "0" (Low level) <true> -
**                           logical "1" (High level)
** ===================================================================
*/
#define ENC_SW_2_GetVal() (ExtIntLdd2_GetVal(ExtIntLdd2_DeviceData))

void ExtIntLdd2_OnInterrupt(LDD_TUserData *UserDataPtr);

/* END ENC_SW_2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __ENC_SW_2_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
