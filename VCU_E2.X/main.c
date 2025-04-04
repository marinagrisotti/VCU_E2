/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  dsPIC33CH256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"
#include "user_can.h"
#include <libpic30.h> // para __delay_ms
#define FCY 800000L

/*
                         Main application
 */
void INT_Timer(void);

CAN_MSG_OBJ msgRx;          //Objetos de mensagem CAN para recebimento
uint8_t tx_data[8] = {0};     //Vetor de mensagem para envio CAN1
uint8_t log_data[8] = {0};    //Vetor de mensagens de log - para testes com RTU

CAN_BMS_Rx CAN_INFOS;
CAN_BMS_TX status;

// Vari¡veis globais
int timer = 0;
int teste = 3900; // Definindo a variavel 'teste'


int main(void)
{
    // Inicializa o dispositivo
    SYSTEM_Initialize();
    TMR1_SetInterruptHandler(INT_Timer);
    TMR1_Start();
    
    // Inicializa variáveis e saídas
    DO1_BRM_SetLow();
    DO2_PRECARGA_SetLow();
    DO3_DESCARGA_SetLow();
    
    
    while(1)
    {
        //desativa sistema em caso de erro
        if (CAN_INFOS.hw_failure || CAN_INFOS.charger_overtemp || ...) {
            // Desliga tudo
            DO1_BRM_SetLow();
            DO2_PRECARGA_SetLow();
            DO3_DESCARGA_SetLow();

            // Envia pro BMS que tudo está desligado
            status.charging_mos = 0x00;
            status.discharging_mos = 0x00;
            SendCAN_StatusMOS(status);

        }
        
        // Se DO1 está ativo e DI2 (12V carregador) está DESATIVADO ? DESCARGA
        if (DO1_BRM_GetValue() && !DI2_12CARREGADOR_GetValue())
        {
            // Envia para o BMS: iniciar descarregamento
            status.charging_mos = 0x00;
            status.discharging_mos = 0x01;
            SendCAN_StatusMOS(status);
        }

        // Se DI2 ATIVADO ? CARREGAMENTO
        if (DI2_12CARREGADOR_GetValue())
        {
            // Passo 1: BRM ON
            DO1_BRM_SetHigh();

            // Passo 2: Pré-carga
            DO2_PRECARGA_SetHigh();
            __delay_ms(1000); // Espera 1 segundo

            // Passo 3: Contator de descarga
            DO3_DESCARGA_SetHigh();

            // Passo 4: Desliga pré-carga
            DO2_PRECARGA_SetLow();

            // Envia para o BMS: iniciar carregamento
            status.charging_mos = 0x01;
            status.discharging_mos = 0x00;
            SendCAN_StatusMOS(status);
        }


        /* CAN Rx ------------------------------------------------------- */
        // CAN1 - CAN geral
        if (CAN1_ReceivedMessageCountGet() > 0) { // Verifica recebimento de mensagem
            if (true == CAN1_Receive(&msgRx)) {   // Leitura da mensagem

                // Seleção da conversão dos dados a partir do ID da mensagem
                switch (msgRx.msgId) 
                {
                    case BMS_SOC:
                        Conv_BMS_SOC(msgRx.data);
                        break;

                    case BMS_CHARGE:
                        Conv_BMS_CHARGE(msgRx.data);
                        break;

                    case CHARGER_RX:
                        Conv_CHARGER_RX(msgRx.data);
                        break;

                    default:
                        // Apenas para testes
                        break;
                }
            }
        }
    }

    return 1;
}

/**
 End of File
*/

void INT_Timer(void)
{
    LED_Toggle();
    
    if(timer >= 10) {
        if(teste == 3900) {
            teste = 0;
        } else {
            teste = 3900;
        }
        timer = 0;
    } else {
        timer = timer + 1;
    }
}