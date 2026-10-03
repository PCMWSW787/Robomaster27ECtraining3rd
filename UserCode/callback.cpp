//
// Created by Siwei Wang on 2026/10/3.
//

#include "can.h"
#include "can_user.h"
#include "Motor.hpp"
#include "tim.h"

Motor motor1(19.2f);
constexpr uint32_t kMotor1FeedbackId = 0x205;
float test_amperes = 0.0f;
uint8_t test_motor_id = 5;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t data[8];
    if (hcan != &hcan1) return;
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, data) != HAL_OK) return;
    if (rx_header.IDE == CAN_ID_STD && rx_header.RTR == CAN_RTR_DATA && rx_header.DLC == 8
        && rx_header.StdId == kMotor1FeedbackId)
    {
        motor1.canRxMsgCallback(data);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim != &htim6) return;
    if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
    {
        motor1.setTxCurrent(test_amperes, test_motor_id);
        HAL_CAN_AddTxMessage(&hcan1, &tx_header, motor1.getTxData(), &can_tx_mailbox);
    }
}