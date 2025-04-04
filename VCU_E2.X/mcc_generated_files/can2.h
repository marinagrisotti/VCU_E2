/**
  CAN2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    can2.h

  @Summary
    This is the generated header file for the CAN2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for CAN2.
    Generation Information :
        Product Revision   :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device             :  dsPIC33CH256MP508
    The generated drivers are tested against the following:
        Compiler           :  XC16 v2.10
        MPLAB              :  MPLAB X v6.05
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

#ifndef CAN2_H
#define CAN2_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "can_types.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

// Transmit FIFO's Custom Name
#define CAN2_TX_TXQ   CAN2_TXQ

typedef enum 
{
    CAN2_TXQ = 0,
} CAN2_TX_FIFO_CHANNELS; 

/**
  Section: CAN2 Module APIs
*/

/**
  @Summary
    Initialization routine that takes inputs from the CAN2 UI

  @Description
    This routine initializes the CAN2 module.
    This routine must be called before any other CAN2 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    int main()
    {
        // initialize the device
        SYSTEM_Initialize();
   
        while (1)
        {      
            CAN2_Tasks();
        }
      
        return 0;
    }
    </code> 
*/
void CAN2_Initialize(void);

/**
  @Summary
    Set the CAN2 operation mode

  @Description
    This function set the CAN2 operation mode.

  @Preconditions
    CAN2_Initialize() function should be called before calling this function.
 
  @Param
    requestMode - CAN2 operation modes

  @Returns
    CAN2 Operation mode request to set.
    CAN_OP_MODE_REQUEST_SUCCESS - Requested Operation mode set successfully
    CAN_OP_MODE_REQUEST_FAIL - Requested Operation mode set failure. Set configuration 
                               mode before setting CAN normal or debug operation mode.
    CAN_OP_MODE_SYS_ERROR_OCCURED - System error occurred while setting Operation mode.

  @Example
    <code>
    int main()
    {
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                //User Application code
            }
        }

        while (1)
        {      
            CAN2_Tasks();
        }
      
        return 0;
    }
    </code> 
*/
CAN_OP_MODE_STATUS CAN2_OperationModeSet(const CAN_OP_MODES requestMode);

/**
  @Summary
    Get the CAN2 operation mode

  @Description
    This function get the CAN2 operation mode.

  @Preconditions
    CAN2_Initialize() function should be called before calling this function. 
 
  @Param
    None

  @Returns
    Return the present CAN2 operation mode. 

  @Example
    <code>
    int main()
    {
        CAN_OP_MODES mode;
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
            
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                mode = CAN2_OperationModeGet();
                //User Application code
            }
        }
    
        while (1)
        {      
            CAN2_Tasks();
        }
      
        return 0;
    }
    </code> 
*/
CAN_OP_MODES CAN2_OperationModeGet(void);

/**
  @Summary
    Reads the message object from CAN2 receive FIFO.

  @Description
    This routine reads a message object from the CAN2 receive FIFO.

  @Preconditions
    CAN2_Initialize() function should be called before calling this function. 
    The CAN2_ReceivedMessageCountGet() function should be checked to see if the receiver
    is not empty before calling this function.

  @Param
    rxCanMsg    - pointer to the message object

  @Returns
    true        - Receive successful
    false       - Receive failure

  @Example
    <code>
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(CAN2_ReceivedMessageCountGet() > 0) 
                    {
                        if(true == CAN2_Receive(&msg))
                        {
                            break;
                        }
                    }

                    CAN2_Tasks();
                }
            }
        }

        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
bool CAN2_Receive(CAN_MSG_OBJ *rxCanMsg);

/**
  @Summary
    Transmits the message object from user buffer to CAN2 Transmit FIFO.

  @Description
    This routine Writes a message object to the CAN2 Transmit FIFO.

  @Preconditions
    CAN2_Initialize function should be called before calling this function. 
    The transfer status should be checked to see if transmitter is not full 
    before calling this function.

  @Param
    fifoChannel - CAN2 Transmit priority FIFO selection
    txCanMsg     - pointer to the message object

  @Returns
    CAN2 Transmit message status.
    CAN_TX_MSG_REQUEST_SUCCESS - Transmit message object successfully placed into transmit FIFO
    CAN_TX_MSG_REQUEST_DLC_EXCEED_ERROR - Transmit message object DLC size is more than transmit FIFO configured DLC size
    CAN_TX_MSG_REQUEST_BRS_ERROR - Transmit FIFO configured has Non BRS mode and CAN Transmit Message object has BRS enabled
    CAN_TX_MSG_REQUEST_FIFO_FULL - Transmit FIFO Full

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                {
                    CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                }
            }
        }

        while (1)
        {
            CAN2_Tasks();
        }
        return 0;
    }
    </code>
*/
CAN_TX_MSG_REQUEST_STATUS CAN2_Transmit(const CAN2_TX_FIFO_CHANNELS fifoChannel, CAN_MSG_OBJ *txCanMsg);

/**
  @Summary
    CAN2 transmitter FIFO status.

  @Description
    This returns the CAN2 transmitter FIFO status. The returned status 
    contains a transmit FIFO status.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    fifoChannel - CAN2 TX priority FIFO selection

  @Returns
    CAN2 Transmit FIFO status.
    CAN_TX_FIFO_FULL         - CAN Transmit FIFO is full
    CAN_TX_FIFO_AVAILABLE     - CAN Transmit FIFO message space is available

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                {
                    CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        
        return 0;
    }
    </code>
*/
CAN_TX_FIFO_STATUS CAN2_TransmitFIFOStatusGet(const CAN2_TX_FIFO_CHANNELS fifoChannel);

/**
  @Summary
    Checks whether the transmitter is in bus off state.

  @Description
    This routine checks whether the transmitter is in bus off state.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    true    - Transmitter in Bus Off state
    false   - Transmitter not in Bus Off state

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.

    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN2_IsBusOff() == false)
                {
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        return 0;
    }
    </code>
*/
bool CAN2_IsBusOff(void);

/**
  @Summary
    Checks whether the transmitter is in the error passive state.

  @Description
    This routine checks whether the transmitter is in the error passive state.
    If Transmitter error counter is above 127, then the transmitter error passive 
    state is set.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    true    - Transmitter in Error Passive state
    false   - Transmitter not in Error Passive state

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    // sample code to demonstrate CAN transmit error passive APIs usage.

    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN2_IsTxErrorPassive() == false)
                {
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        return 0;
    }
    </code>
*/
bool CAN2_IsTxErrorPassive(void);

/**
  @Summary
    Checks whether the transmitter is in the error warning state.

  @Description
    This routine checks whether the transmitter is in the error warning state.
    If Transmitter error counter is above 95 to below 128, then transmitter error 
    warning state is set.

  @Preconditions
    CAN2_Initialize function should be called 
    before calling this function.

  @Param
    None

  @Returns
    true    - Transmitter in Error warning state
    false   - Transmitter not in Error warning state

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      sample code to demonstrate CAN transmit error warning APIs usage.

    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN2_IsTxErrorWarning() == false)
                {
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        return 0;
    }
    </code>
*/
bool CAN2_IsTxErrorWarning(void);

/**
  @Summary
    Checks whether the transmitter is in the error active state.

  @Description
    This routine checks whether the transmitter is in the error active state.
    If Transmitter error counter is above 0 to below 128, then transmitter error 
    active state is set.

  @Preconditions
    CAN2_Initialize function should be called 
    before calling this function.

  @Param
    None

  @Returns
    true    - Transmitter in Error active state
    false   - Transmitter not in Error active state

  @Example
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      sample code to demonstrate CAN transmit error active APIs usage.

    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;
            
                if(CAN2_IsTxErrorActive() == false)
                {
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        return 0;
    }
    </code>
*/
bool CAN2_IsTxErrorActive(void);

/**
  @Summary
    Checks whether the Receiver is in the error passive state.

  @Description
    This routine checks whether the receive is in the error passive state.
    If Receiver error counter is above 127, then receiver error passive 
    state is set.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    true    - Receiver in Error passive state
    false   - Receiver not in Error passive state

  @Example
    <code>
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(CAN2_IsRxErrorPassive() == false)
                    {
                        if(CAN2_ReceivedMessageCountGet() > 0) 
                        {
                            CAN2_Receive(&msg);
                        }
                    }

                    CAN2_Tasks();
                }
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
bool CAN2_IsRxErrorPassive(void);

/**
  @Summary
    Checks whether the Receiver is in the error warning state.

  @Description
    This routine checks whether the receive is in the error warning state.
    If Receiver error counter is above 95 to below 128, then receiver error warning 
    state is set.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    true    - Receiver in Error warning state
    false   - Receiver not in Error warning state

  @Example
    <code>
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(CAN2_IsRxErrorWarning() == false)
                    {
                        if(CAN2_ReceivedMessageCountGet() > 0) 
                        {
                            CAN2_Receive(&msg);
                        }
                    }

                    CAN2_Tasks();
                }
            }
        }

        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
bool CAN2_IsRxErrorWarning(void);

/**
  @Summary
    Checks whether the Receiver is in the error active state.

  @Description
    This routine checks whether the receive is in the error active state.
    If Receiver error counter is above 0 to below 128, then receiver error active 
    state is set.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    true    - Receiver in Error active state
    false   - Receiver not in Error active state

  @Example
    <code>
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(CAN2_IsRxErrorActive() == false)
                    {
                        if(CAN2_ReceivedMessageCountGet() > 0) 
                        {
                            CAN2_Receive(&msg);
                        }
                    }

                    CAN2_Tasks();
                }
            }
        }

        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
bool CAN2_IsRxErrorActive(void);

/**
  @Summary
    Puts CAN2 module in sleep mode.

  @Description
    This routine puts CAN2 module in sleep mode.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    int main(void) 
    {     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                CAN2_Sleep();
                
                //Check CAN2 module is in CAN_DISABLE_MODE
                if(CAN_DISABLE_MODE == CAN2_OperationModeGet())
                {
                    Sleep(); //Call sleep instruction
                    C2INTLbits.WAKIF = 0; // Clear Wake-Up interrupt flag
                    
                    // Recover to Normal mode
                    if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_CONFIGURATION_MODE))
                    {
                        if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
                        {
                            //User Application code                            
                        }
                    }
                }
            }
        }
        
        while (1)
        {
            CAN2_Tasks();
        }
        
        return 0;
    }
    </code>
*/
void CAN2_Sleep();

/**
  @Summary
    CAN2 RX FIFO number of messages that are received.

  @Description
    This returns the number of messages that are received.

  @Preconditions
    CAN2_Initialize function should be called before calling this function.

  @Param
     None

  @Returns
    Number of message received.

  @Example
    <code>
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(CAN2_ReceivedMessageCountGet() > 0) 
                    {
                        CAN2_Receive(&msg);
                    }

                    CAN2_Tasks();
                }
            }
        }

        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
uint8_t CAN2_ReceivedMessageCountGet(void);

/**
  @Summary
    Callback for CAN2 invalid message.

  @Description
    This routine is callback for CAN2 invalid message

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    bool gInvalidMsgOccurred = false;
    
    void CAN2_DefaultInvalidMessageHandler(void)
    {
        gInvalidMsgOccurred = true;
        //CAN Invalid Message application code
    }
 
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;

                while(1)
                {            
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                    
                    if(gInvalidMsgOccurred == true)
                    {
                        break;
                    }

                    CAN2_Tasks();
                }
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultInvalidMessageHandler(void);

/**
  @Summary
    Callback for CAN2 Bus WakeUp activity.

  @Description
    This routine is callback for CAN2 bus wakeUp activity

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    bool gBusWakeUpOccurred = false;
    
    void CAN2_DefaultBusWakeUpActivityHandler(void)
    {
        gBusWakeUpOccurred = true;
        //CAN Bus WakeUp activity application code
    }
 
    int main(void) 
    {
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                CAN2_Sleep();
                            
                //Check CAN2 module is in CAN_DISABLE_MODE
                if(CAN_DISABLE_MODE == CAN2_OperationModeGet())
                {
                    Sleep(); //Call sleep instruction
                    
                    while(1) 
                    {
                        if(gBusWakeUpOccurred == true)
                        {
                            break;
                        }                        
                        
                        CAN2_Tasks();
                    }
                }
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultBusWakeUpActivityHandler(void);

/**
  @Summary
    Callback for CAN2 Bus Error.

  @Description
    This routine is callback for CAN2 bus error

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    bool gBusErrorOccurred = false;
    
    void CAN2_DefaultBusErrorHandler(void)
    {
        gBusErrorOccurred = true;
        //CAN Bus Error application code
    }
 
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;

                while(1)
                {            
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                    
                    if(gBusErrorOccurred == true)
                    {
                        break;
                    }
                
                    CAN2_Tasks();
                }
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultBusErrorHandler(void);

/**
  @Summary
    Callback for CAN2 Mode Change.

  @Description
    This routine is callback for CAN2 mode change

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    bool gModeChangeOccurred = false;
    
    void CAN2_DefaultModeChangeHandler(void)
    {
        gModeChangeOccurred = true;
        //CAN Mode Change application code
    }
 
    int main(void) 
    {
        CAN_MSG_OBJ msg;
     
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);
        
        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(gModeChangeOccurred == true)
                    {
                        break;
                    }                    

                    CAN2_Tasks();
                }
            }
        }

        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultModeChangeHandler(void);

/**
  @Summary
    Callback for CAN2 System Error.

  @Description
    This routine is callback for CAN2 system error

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    bool gSystemOccurred = false;
    
    void CAN2_DefaultSystemErrorHandler(void)
    {
        gSystemOccurred = true;
        //CAN System Error application code
    }
 
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
         
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;

                while(1)
                {            
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                    
                    if(gSystemOccurred == true)
                    {
                        break;
                    }

                    CAN2_Tasks();
                }
                
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultSystemErrorHandler(void);

/**
  @Summary
    Callback for CAN2 Transmit Attempt.

  @Description
    This routine is callback for CAN2 transmit attempt 

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    //Note: Example code here is not based on MCC UI configuration, 
    //      this is a sample code to demonstrate CAN transmit APIs usage.
    
    bool gTxAttemptOccurred = false;
    
    void CAN2_DefaultTxAttemptHandler(void)
    {
        gTxAttemptOccurred = true;
        //CAN Transmit Attempt application code
    }
 
    int main(void) 
    {
        CAN_MSG_OBJ msg;
        uint8_t data[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
        
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                msg.msgId = 0x1FFFF;
                msg.field.formatType = CAN_2_0_FORMAT;
                msg.field.brs = CAN_NON_BRS_MODE;
                msg.field.frameType = CAN_FRAME_DATA;
                msg.field.idType = CAN_FRAME_EXT;
                msg.field.dlc = DLC_8;
                msg.data = data;

                while(1)
                {                               
                    if(CAN_TX_FIFO_AVAILABLE == (CAN2_TransmitFIFOStatusGet(CAN2_TX_FIFO1) & CAN_TX_FIFO_AVAILABLE))
                    {
                        CAN2_Transmit(CAN2_TX_FIFO1, &msg);
                    }
                    
                    if(gTxAttemptOccurred == true)
                    {
                        break;
                    }
                    
                    CAN2_Tasks();
                }
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultTxAttemptHandler(void);

/**
  @Summary
    Callback for CAN2 Receive Buffer OverFlow .

  @Description
    This routine is callback for CAN2 receive buffer overFlow  

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    bool gRxOverFlowOccurred = false;
    
    void CAN2_DefaultRxBufferOverFlowHandler(void)
    {
        gRxOverFlowOccurred = true;
        //CAN Receive Buffer OverFlow application code
    }
 
    int main(void) 
    {    
        // initialize the device
        SYSTEM_Initialize();
        CAN2_OperationModeSet(CAN_CONFIGURATION_MODE);

        if(CAN_CONFIGURATION_MODE == CAN2_OperationModeGet())
        {    
            if(CAN_OP_MODE_REQUEST_SUCCESS == CAN2_OperationModeSet(CAN_NORMAL_2_0_MODE))
            {
                while(1) 
                {
                    if(gRxOverFlowOccurred == true)
                    {
                        gRxOverFlowOccurred = false;
                        // User Application code
                        break;
                        
                    }
                }

                CAN2_Tasks();
            }
        }
        
        while (1)
        {
        }
        
        return 0;
    }
    </code>
*/
void CAN2_DefaultRxBufferOverFlowHandler(void);

/**
  @Summary		
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    CAN2_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to CAN2_Initialize() for an example
    
*/
void CAN2_Tasks(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //_CAN2_H
/**
 End of File
*/

