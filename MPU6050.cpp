/* 
 * File:   BBB_I2C.cpp
 * Author: Cagdas Caglak
 * E-mail: cagdascaglak@gmail.com
 * Code is free but There is not warranty.
 * Created on July 26, 2013, 5:08 PM
 * ----------------------------------------
 * 03/08/2013 "BBB_I2C"s Previous methods changed ...NoExit() methods.
 */

#include "MPU6050.h"

MPU6050::MPU6050() {
}

MPU6050::~MPU6050() {
}

void MPU6050::setSleepMode(bool mode) {
    int8_t byte = i2c.readByteNoExit(DEV_ADD, PWR_MGMT_1);
    if (mode) {
        byte = byte | 64;
        i2c.writeByteNoExit(DEV_ADD, PWR_MGMT_1, byte);
    } else {
        byte = byte & ~64;
        i2c.writeByteNoExit(DEV_ADD, PWR_MGMT_1, byte);
    }
}

bool MPU6050::getSleepMode() {
    int8_t byte = i2c.readByteNoExit(DEV_ADD, PWR_MGMT_1);
    byte = byte >> 6;
    byte %= 2;
    if (byte == 1) {
        return true;
    } else {
        return false;
    }
}

void MPU6050::setRangeAcceleration(uint8_t range) {
    uint8_t afs;
    afs = i2c.readByteNoExit(DEV_ADD, ACCEL_CONFIG);
    if (range == 0) {
        afs = afs & ~24;
    } else if (range == 1) {
        afs = afs | 8;
        afs = afs & ~16;
    } else if (range == 2) {
        afs = afs & ~8;
        afs = afs | 16;
    } else {
        afs = afs | 24;
    }
    i2c.writeByteNoExit(DEV_ADD, ACCEL_CONFIG, afs);
}

uint8_t MPU6050::getRangeAcceleration() {
    uint8_t afs;
    afs = i2c.readByteNoExit(DEV_ADD, ACCEL_CONFIG);
    afs = afs >> 3;
    afs = afs % 4;
    return afs;
}

void MPU6050::setRangeGyroscope(uint8_t range) {
    uint8_t fs;
    fs = i2c.readByteNoExit(DEV_ADD, GYRO_CONFIG);
    if (range == 0) {
        fs = fs & ~24;
    } else if (range == 1) {
        fs = fs | 8;
        fs = fs & ~16;
    } else if (range == 2) {
        fs = fs & ~8;
        fs = fs | 16;
    } else {
        fs = fs | 24;
    }
    i2c.writeByteNoExit(DEV_ADD, GYRO_CONFIG, fs);
}

uint8_t MPU6050::getRangeGyroscope() {
    uint8_t fs;
    fs = i2c.readByteNoExit(DEV_ADD, GYRO_CONFIG);
    fs = fs >> 3;
    fs = fs % 4;
    return fs;
}

void MPU6050::init() {
    setSleepMode(false);
    setRangeAcceleration(0);
    setRangeGyroscope(0);
}

void MPU6050::getAccelerations(int16_t *ax, int16_t *ay, int16_t *az) {

    *ax = i2c.readWordNoExit(DEV_ADD, ACCEL_XOUT_H, ACCEL_XOUT_L);
    *ay = i2c.readWordNoExit(DEV_ADD, ACCEL_YOUT_H, ACCEL_YOUT_L);
    *az = i2c.readWordNoExit(DEV_ADD, ACCEL_ZOUT_H, ACCEL_ZOUT_L);

}

int16_t MPU6050::getAccelerationX() {
    return i2c.readWordNoExit(DEV_ADD, ACCEL_XOUT_H, ACCEL_XOUT_L);
}

int16_t MPU6050::getAccelerationY() {
    return i2c.readWordNoExit(DEV_ADD, ACCEL_YOUT_H, ACCEL_YOUT_L);
}

int16_t MPU6050::getAccelerationZ() {
    return i2c.readWordNoExit(DEV_ADD, ACCEL_ZOUT_H, ACCEL_ZOUT_L);
}

void MPU6050::getAngularVelocities(int16_t* gx, int16_t* gy, int16_t* gz) {

    *gx = i2c.readWordNoExit(DEV_ADD, GYRO_XOUT_H, GYRO_XOUT_L);
    *gy = i2c.readWordNoExit(DEV_ADD, GYRO_YOUT_H, GYRO_YOUT_L);
    *gz = i2c.readWordNoExit(DEV_ADD, GYRO_ZOUT_H, GYRO_ZOUT_L);

}

int16_t MPU6050::getAngularVelocityX() {
    return i2c.readWordNoExit(DEV_ADD, GYRO_XOUT_H, GYRO_XOUT_L);
}

int16_t MPU6050::getAngularVelocityY() {
    return i2c.readWordNoExit(DEV_ADD, GYRO_YOUT_H, GYRO_YOUT_L);
}

int16_t MPU6050::getAngularVelocityZ() {
    return i2c.readWordNoExit(DEV_ADD, GYRO_ZOUT_H, GYRO_ZOUT_L);
}

int16_t MPU6050::getTemperature() {
    return i2c.readWordNoExit(DEV_ADD, TEMP_OUT_H, TEMP_OUT_L);
}

void MPU6050::getMotions6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz) {

    *ax = i2c.readWordNoExit(DEV_ADD, ACCEL_XOUT_H, ACCEL_XOUT_L);
    *ay = i2c.readWordNoExit(DEV_ADD, ACCEL_YOUT_H, ACCEL_YOUT_L);
    *az = i2c.readWordNoExit(DEV_ADD, ACCEL_ZOUT_H, ACCEL_ZOUT_L);

    *gx = i2c.readWordNoExit(DEV_ADD, GYRO_XOUT_H, GYRO_XOUT_L);
    *gy = i2c.readWordNoExit(DEV_ADD, GYRO_YOUT_H, GYRO_YOUT_L);
    *gz = i2c.readWordNoExit(DEV_ADD, GYRO_ZOUT_H, GYRO_ZOUT_L);

}

void MPU6050::setDLPFMode(uint8_t mode) {
    uint8_t config = i2c.readByteNoExit(DEV_ADD, CONFIG);
    if (mode == 0) {
        config = config & ~7;
    } else if (mode == 1) {
        config |= 1;
        config &= ~6;
    } else if (mode == 2) {
        config |= 2;
        config &= ~5;
    } else if (mode == 3) {
        config |= 3;
        config &= ~4;
    } else if (mode == 4) {
        config |= 4;
        config &= ~3;
    } else if (mode == 5) {
        config |= 5;
        config &= ~2;
    } else if (mode == 6) {
        config |= 6;
        config &= ~1;
    } else if (mode == 7) {
        config |= 7;
    }

    i2c.writeByteNoExit(DEV_ADD, CONFIG, config);
}

uint8_t MPU6050::getDLPFMode() {
    uint8_t config = i2c.readByteNoExit(DEV_ADD, CONFIG);
    return config % 8;
}

void MPU6050::setSampleRate(uint8_t rate) {
    i2c.writeByteNoExit(DEV_ADD, SMPLRT_DIV, rate);
}

uint8_t MPU6050::getSampleRate() {
    return i2c.readByteNoExit(DEV_ADD, SMPLRT_DIV);
}

void MPU6050::setMotionDetectionThresold(uint8_t value) {
    i2c.writeByteNoExit(DEV_ADD, MOT_THR, value);
}

uint8_t MPU6050::getMotionDetectionThresold() {
    return i2c.readByteNoExit(DEV_ADD, MOT_THR);
}

void MPU6050::setTEMP_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, TEMP_FIFO_EN_BIT);
}

uint8_t MPU6050::getTEMP_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, TEMP_FIFO_EN_BIT);
}

void MPU6050::setXG_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, XG_FIFO_EN_BIT);
}

uint8_t MPU6050::getXG_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, XG_FIFO_EN_BIT);
}

void MPU6050::setYG_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, YG_FIFO_EN_BIT);
}

uint8_t MPU6050::getYG_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, YG_FIFO_EN_BIT);
}

void MPU6050::setZG_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, ZG_FIFO_EN_BIT);
}

uint8_t MPU6050::getZG_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, ZG_FIFO_EN_BIT);
}

void MPU6050::setACCEL_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, ACCEL_FIFO_EN_BIT);
}

uint8_t MPU6050::getACCEL_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, ACCEL_FIFO_EN_BIT);
}

void MPU6050::setSLV2_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, SLV2_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV2_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, SLV2_FIFO_EN_BIT);
}

void MPU6050::setSLV1_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, SLV1_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV1_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, SLV1_FIFO_EN_BIT);
}

void MPU6050::setSLV0_FIFO_EN(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, FIFO_EN, value, SLV0_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV0_FIFO_EN() {
    return i2c.readBitNoExit(DEV_ADD, FIFO_EN, SLV0_FIFO_EN_BIT);
}

uint16_t MPU6050::getFIFO_Count() {
    return i2c.readWordNoExit(DEV_ADD, FIFO_COUNTH, FIFO_COUNTL);
}

void MPU6050::setFIFO_Enable(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, USER_CTRL, value, 6);
}

uint8_t MPU6050::getFIFO_Enable() {
    return i2c.readBitNoExit(DEV_ADD, USER_CTRL, 6);
}

void MPU6050::getFIFO_Data(uint8_t *data, uint8_t length) {
    i2c.readByteBufferNoExit(DEV_ADD, FIFO_R_W, data, length);
}

void MPU6050::setFIFO_Reset(uint8_t value) {
    i2c.writeBitNoExit(DEV_ADD, USER_CTRL, value, 2);
}

uint8_t MPU6050::getFIFO_Reset() {
    return i2c.readBitNoExit(DEV_ADD, USER_CTRL, 2);
}