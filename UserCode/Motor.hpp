//
// Created by Siwei Wang on 2026/10/3.
//

#ifndef ROBOMASTER27ECTRAINING3RD_MOTOR_H
#define ROBOMASTER27ECTRAINING3RD_MOTOR_H
#include <cstdint>



class Motor
{
public:
    explicit Motor(const float ratio);

    void canRxMsgCallback(const uint8_t rx_data[8]);

    float angle() const;
    int16_t speed_rpm() const;
    float currentAmps() const;
    int16_t temperatureC() const;

    void setTxCurrent(float amperes, uint8_t motor_id);

    uint8_t* getTxData();
private:
    const float ratio_;

    int16_t ecd_angle_ = 0;
    int16_t speed_rpm_ = 0;
    float currentA_ = 0;
    int16_t tempC_ = 0;

    float angle_ = 0;
    int16_t last_ecd_ = 0;
    // bool received_ = false;

    uint8_t tx_data_[8] = {};

    void normalizeDataReceived();

    static constexpr uint16_t kEncoderRange = 8192;
};

#endif //ROBOMASTER27ECTRAINING3RD_MOTOR_H
