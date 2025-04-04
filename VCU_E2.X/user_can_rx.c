/*
 * File:   user_can_rx.c
 * Author: Gustavo Peres - Trackli
 * Version: 1.0
 *
 * Created on 29/02/2024
 * 
 * Programa para recebimento de mensagens CAN (Rx)
 */
/* Include Files */
#include "xc.h"
#include "mcc_generated_files/can1.h"
//#include "mcc_generated_files/mcc.h"    //header com todas as configurações do mcc

#include "user_can.h"

/* Global and Static Variables */

/* External Variables */
//---------Comando de testes-------------
extern CAN_BMS_Rx CAN_INFOS;

/* Functions prototypes */
//void Conv_BRM_Act(uint8_t data[]);
//void Conv_BRM_Status(uint8_t data[]);

//-----------Fun��es Rx----------------------------
/** @fn void Conv_BRM_Act(uint8_t data[])
*   @brief Conversão de dados CAN vindos do ID 0x0A3 - Drive Actual values
*   @param[in] Ponteiro de dados para os dados CAN recebidos
*
*   infos: 
*/
void Conv_BMS_SOC(uint8_t data[]) // chamar essa fun��o no main  junto com id
{
    uint16_t tempData16;
    //uint16_t partData1, partData2, fullData;

  
    tempData16 = (uint16_t)data[0]; 
    tempData16 = (tempData16<<8) | data[1];
    CAN_INFOS.totalvoltage = 0,1*((float)tempData16); //0,1V 
   
    tempData16 = (uint16_t)data[2]; 
    tempData16 = (tempData16<<8) | data[3];
    CAN_INFOS.totalvoltage2 = 0,1*((float)tempData16); //0,1V 
    
 
    CAN_INFOS.soc_percent   = data[4];
    
}

void Conv_BMS_CHARGE (uint8_t data[]) // chamar essa fun��o no main  junto com id
{ 
    uint32_t tempData32;

    CAN_INFOS.charge_state     = data[0]; // 0: parado, 1: carregando, 2: descarregando
    CAN_INFOS.charge_state2    = data[1]; // estado do MOS de carga
    CAN_INFOS.discharge_state  = data[2]; // estado do MOS de descarga
    CAN_INFOS.bms_life         = data[3]; // vida �til do BMS (ciclos)

    // Capacidade restante em mAh (BYTE4~7)
    tempData32  = (uint32_t)data[4];
    tempData32  = (tempData32 << 8) | data[5];
    tempData32  = (tempData32 << 8) | data[6];
    tempData32  = (tempData32 << 8) | data[7];
    CAN_INFOS.remaining_capacity = tempData32;
    

}

void Conv_CHARGER_RX (uint8_t data[]) // chamar essa fun��o no main  junto com id
{ 
    uint16_t tempData16;
    
    tempData16 = (uint16_t)data[1];
    tempData16 = (tempData16 << 8) | data[2];
    CAN_INFOS.output_voltage = 0.1f * ((float)tempData16); // 0.1V por bit
    
    tempData16 = (uint16_t)(data[3] & 0x7F); // limpa o bit de sinal
    tempData16 = (tempData16 << 8) | data[4];
    CAN_INFOS.output_current = 0.1f * ((float)tempData16); // 0.1A por bit
    
    CAN_INFOS.is_discharging = (data[3] & 0x80) ? 1 : 0;
    
    uint8_t statusByte = data[5];

    // Manipula��o dos bits do statusByte
    CAN_INFOS.hw_failure         = (statusByte & (1 << 0)) ? 1 : 0; // Bit 0
    CAN_INFOS.charger_overtemp   = (statusByte & (1 << 1)) ? 1 : 0; // Bit 1
    CAN_INFOS.input_voltage_err  = (statusByte & (1 << 2)) ? 1 : 0; // Bit 2
    CAN_INFOS.start_status       = (statusByte & (1 << 3)) ? 1 : 0; // Bit 3
    CAN_INFOS.comm_timeout       = (statusByte & (1 << 4)) ? 1 : 0; // Bit 4
    
    CAN_INFOS.internal_temp = (int16_t)data[6] - 100; // Offset 100 ? ex: 150 = 50 �C

}



/** @fn void Conv_BRM_Act(uint8_t data[])
*   @brief Conversão de dados CAN vindos do ID 0x0A3 - Drive Actual values
*   @param[in] Ponteiro de dados para os dados CAN recebidos
*
*   infos: 
*/
/*void Conv_BRM_Status(uint8_t data[])
{
    uint8 tempData;
    uint16 partData, fullData;
    
    //Primeira informação no primeiro byte
    BRM_Infos.Edrv_nrChksDern  = data[0]; //Scale 1 e Offset 0
    
    tempData = data[1];
    //Segunda informação no segundo byte, primeiros 4 bits
    BRM_Infos.Edrv_nrAlvCntrDern = tempData&0xF; //Scale 1 e Offset 0
    
    //Terceira informação
    BRM_Infos.Edrv_milRequest = (tempData>>7)&0x1; //Scale 1 e Offset 0
    
    //Quarta informação bytes 2 e 3
    tempData = data[2];
    partData = (tempData<<2)&0x3FC;
    tempData = data[3];
    fullData = partData | ((tempData>>6)&0x3);
    
    BRM_Infos.Edrv_tqMinAvl = (0.1*(float)fullData)-90; //Scale 0,1 e Offset -90
    
    //Quinta informação bytes 3 e 4
    partData = (tempData<<4)&0x3F0;
    tempData = data[4];
    fullData = partData | ((tempData>>4)&0xF);
    
    BRM_Infos.Edrv_tqMaxAvl = (0.1*(float)fullData)-12.3; //Scale 0,1 e Offset -12,3
    
    //Sexta informação só no byte 4
    BRM_Infos.Edrv_stActDern = tempData&0xF; //Scale 1 e Offset 0
    
    //Sétima informação só no byte 5
    tempData = data[5];
    
    BRM_Infos.Edrv_ratTCritIvtr = (tempData>>1)&0x7F; //Scale 1 e Offset 0
    
    //Oitava informação nos bytes 5 e 6
    partData = (tempData<<6)&0x40;
    tempData = data[6];
    
    BRM_Infos.Edrv_ratTCritMac = partData | ((tempData>>2)&0x3F); //Scale 1 e Offset 0
    
    //Nona informação nos bytes 6 e 7
    partData = (tempData<<8)&0x300;
    tempData = data[7];
    fullData = partData | (tempData&0xFF);
    
    BRM_Infos.Edrv_stFltId = (uint16)fullData;
}*/
