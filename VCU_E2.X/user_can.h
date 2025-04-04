/* 
 * File:   user_can.h
 * Author: Gustavo Peres - Trackli
 *
 * Created on March 25, 2025, 4:58 PM
 */

#ifndef USER_CAN_H
#define	USER_CAN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
//Includes <>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
//Includes mcc generated
#include "mcc_generated_files/can_types.h"
#include "mcc_generated_files/can1.h"
//#include "crc.h"
    
#define  MSG_SIZE_8 8 //Tamanho padrÃ£o das mensagens CAN em numero de Bytes
#define  MSG_SIZE_7 7 //Tamanho padrÃ£o das mensagens CAN em numero de Bytes

/* IDs de envio RX */ 
    
/*   IDs das mensagens CAN vindas do BMS
*
*    Definição no arquivo Deligreen Power BMS CAN Communication Protocol V1.0
*/
#define BMS_SOC             0x18900140  /*SOC of total voltage and current*/
#define BMS_VOLTAGE         0x18910140  /*Maximum and Minimum voltage */
#define BMS_TMP             0x18920140  /*Maximum and Minimum temperature */
#define BMS_CHARGE          0x18930140  /*Charge and discharge MOS status */
#define BMS_STATUS_INFO1    0x18940140  /*Charger status (0 disconnect 1 access)| Load status (0 disconnect 1 access)| Nº of Temperature | N° of battery string*/ 
#define BMS_CELL_VOLTAGE    0x18950140  /*The voltage of each monomer is 2 byte, according to the actual number of cell, the maximum 96 byte, is sent in 16 frames*/
#define BMS_CELL_TMP        0x18960140  /*Each temperature accounts for 1 byte, according to the actual number of temperature send, the maximum 21 byte, send in 3 frames */   
#define BMS_CELL_BALANCE    0x18970140  /*Cell 1 balance state | 0? Closed 1? Open*/
#define BMS_STATUS_INFO2    0x18980140  /*Battery failure status ERROR*/
    
/*IDs das mensagens CAN vindas do CARREGADOR 
 * Definição no arquivo Deligreen-Q2 1.8kw charger instruction manual */

#define CHARGER_RX          0x18FF50E5 /*Charger emits CAN ID */ 

    
//  IDs de envio TX
    
/*    IDs das mensagens CAN enviadas ao BMS */
#define CHARGING_STATUS      0x18DA0140  // Charging MOS status (0x00 OFF, 0x01 ON)
#define DISCHARGING_STATUS   0x18D90140  // Discharging MOS status (0x00 OFF, 0x01 ON)  
    
/*  IDs das mensagens CAN enviadas ao CARREGADOR */
    
#define CHARGER_TX          0x1806E5F4 /*Charger receives CAN ID */
    
//Structs
    
// CAN Tx >> Estruturas de informações envio CAN ----------------------------------

typedef struct {
    
    uint8_t charging_mos;     // 0x00: OFF, 0x01: ON
    
    uint8_t discharging_mos;  // 0x00: OFF, 0x01: ON
    
} CAN_BMS_TX;

// CAN Rx >> Estruturas de informações recebimento CAN ----------------------------

typedef struct  // struct de cada mensagem
{
  uint16_t totalvoltage;            /*!Cumulative total voltage (0.1 V) */

  uint16_t totalvoltage2;           /*Gather total voltage (0.1 V) */

  uint8_t  soc_percent;           /*SOC (0.1%) */

  uint16_t cell_voltage;        /*Maximum cell voltage value (mV)s*/
  
  uint8_t  cell_number;          /*No of cell with Maximum voltages*/
  
  uint16_t cell_voltage2;       /*Minimum cell voltage value (mV)s*/
  
  uint8_t  cell_number2;         /*No of cell with Minimum voltages*/
  
  uint8_t  temp_value;           /*Maximum temperature value (40 Offset ,°C)*/
  
  uint8_t  temp_number;      /* Maximum temperature cell No */
  
  uint8_t  temp_value2;         /*Minimum temperature value (40 Offset ,°C)*/
  
  uint8_t  temp_number2;           /*Minimum temperature cell No*/
   
  uint8_t  charge_state;         /*State (0 stationary 1 charge 2 discharge)  */
  
  uint8_t  charge_state2;        /*Charge MOS state*/ 
  
  uint8_t  discharge_state;           /*Discharge MOS status*/
  
  uint8_t  bms_life;                /*BMS life (0~255 cycles)??*/ 
  
  uint32_t remaining_capacity;    /*Remain capacity (mAH)*/
  
  uint8_t  status_battery;         /*No of battery string*/
  
  uint8_t status_temp;             /*No of Temperature*/
  
  uint8_t status_charge_bms;         /*Charger status (0 disconnect 1 access)*/
  
  uint8_t status_load;               /*Load status (0 disconnect 1 access)*/
  
  uint8_t bms_error;               
  
  uint8_t bms_error2;
  
  uint8_t bms_error3;
  
  //CARREGADOR 
  
  uint16_t output_voltage;             /*0.1v/bit offset?0 case?Vout=3201, Corresponding voltage is 320.1V*/
  
  uint16_t output_current;             /*0.1A/bit offset?0 case?Iout=582, Corresponding current 58.2A.The highest is the symbol of BIT ,0 for charging ,1 for discharging */
  
  //uint8_t status_charge;               /*0: Normal ;1: failure.*/
  
  uint8_t hw_failure;                  /*0: Normal ;1: Hardware failure.*/
   
  uint8_t charger_overtemp;            /*0: Normal ;1: Charger over temperature protection*/
  
  uint8_t input_voltage_err;           /*0: The input voltage is normal;1: The input voltage is wrong and the charger stops working.*/
  
  uint8_t start_status;                /*0: Battery connection is correct; 1: The battery is not connected or battery is reversed.*/
  
  uint8_t comm_timeout;                /*0: Communication is normal;1: communication reception timeout*/
  
  uint8_t is_discharging;              /*0 = carregando, 1 = descarregando*/
  
  int16_t internal_temp;              /* temperatura pode ser negativa, por isso int16_t*/
  
} CAN_BMS_Rx;

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

//void Conv_BRM_Act(uint8_t data[]);
//void Conv_BRM_Status(uint8_t data[]);
//void SendCAN_BRM(uint32 id, uint8_t data[], CAN_BRM_Tx command);
//void SendCAN_Log(uint32 id, uint8_t data[], CAN_BRM_Rx ActData);

#ifdef	__cplusplus
}
#endif

#endif	/* USER_CAN_H */

