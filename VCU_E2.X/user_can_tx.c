/*
 * File:   user_can_tx.c
 * Author: Gustavo Peres - Trackli
 * Version: 1.0
 *
 * Created on 29/02/2024
 * 
 * Programa para envio de mensagens CAN (Tx)
 */
/* Include Files */
#include "xc.h"
#include "mcc_generated_files/can1.h"
//#include "mcc_generated_files/mcc.h"    //header com todas as configurações do mcc

#include "user_can.h"


CAN_MSG_OBJ msgTx;



/* Functions prototypes */
//void SendCAN_BRM(uint32 id, uint8_t data[], CAN_BRM_Tx command);
//void SendCAN_Log(uint32 id, uint8_t data[], CAN_BRM_Rx ActData);

//Funções de montagem e envio de mensagens CAN------------------------------------------
/** @fn void CANTx_Control(canBASE_t *node, uint32 id, uint8_t data[], CANControl control)
*   @brief Construtor e envio de mensagem CAN para o BRM
*   @param[in] node Pointer to CAN node:
*              - canREG1: CAN1 node pointer (Always for this application)
*   @param[in] ID da mensagem CAN a ser enviada - ver user_can.h
*   @param[in] Variável com informações a ser enviada a ControlBox
*/

void SendCAN_StatusMOS(CAN_BMS_TX status)
{
    // ==================== Charging MOS ====================
    msgTx.field.formatType = CAN_2_0_FORMAT;        // Formato CAN 2.0
    msgTx.field.brs = CAN_NON_BRS_MODE;             // Sem bitrate vari�vel
    msgTx.field.frameType = CAN_FRAME_DATA;         // Frame de dados
    msgTx.field.idType = CAN_FRAME_EXT;             // ID estendido (29 bits)
    msgTx.field.dlc = DLC_1;                        // 1 byte de dados

    msgTx.msgId = CHARGING_STATUS;                  // ID da mensagem CAN
    msgTx.data[0] = status.charging_mos;            // 0x00 OFF ou 0x01 ON

    // Envia mensagem CAN
    if (CAN_TX_FIFO_AVAILABLE == (CAN1_TransmitFIFOStatusGet(CAN1_TXQ) & CAN_TX_FIFO_AVAILABLE)) {
        CAN1_Transmit(CAN1_TXQ, &msgTx);
    }

    // ==================== Discharging MOS ====================
    msgTx.msgId = DISCHARGING_STATUS;               // Novo ID para descarga
    msgTx.data[0] = status.discharging_mos;         // 0x00 OFF ou 0x01 ON

    // Envia mensagem CAN
    if (CAN_TX_FIFO_AVAILABLE == (CAN1_TransmitFIFOStatusGet(CAN1_TXQ) & CAN_TX_FIFO_AVAILABLE)) {
        CAN1_Transmit(CAN1_TXQ, &msgTx);
    }
}


