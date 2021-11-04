////////////////////////////////////////////////////////////////////////////
//
//  This file is part of RTIMULib
//
//  Copyright (c) 2014-2015, richards-tech, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
//  Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "RTPressureBMP388.h"

RTPressureBMP388::RTPressureBMP388(RTIMUSettings *settings) : RTPressure(settings)
{
    m_validReadings = false;
}

RTPressureBMP388::~RTPressureBMP388()
{
}

bool RTPressureBMP388::pressureInit()
{
    unsigned char result;
    unsigned char data[24];


    m_pressureAddr = m_settings->m_I2CPressureAddress;

    // check ID of chip

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ID, 1, &result, "Failed to read BMP388 id"))
        return false;

    if (result != BMP388_ID) {
        HAL_ERROR1("Incorrect BMP388 id %d\n", result);
        return false;
    }

    // check if sensor is ready
     if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_STATUS, 1, &result, "Failed to read BMP388 id"))
        return false;
    
    if (!(result & BMP388_REG_VAL_CMD_RDY)) {
        HAL_ERROR1("Incorrect BMP388 status %d\n", result);
        return false;
    } else {
        HAL_INFO1("BMP388 status %d\n", result);
    }

    if (!m_settings->HALWrite(m_pressureAddr, BMP388_REG_ADD_CMD, BMP388_REG_VAL_SOFT_RESET, "Failed to soft reset")) {
        return false;
    }

    // enable pressure and temperature
    if (!m_settings->HALWrite(m_pressureAddr, BMP388_REG_ADD_PWR_CTRL, (BMP388_REG_VAL_PRESS_EN | BMP388_REG_VAL_TEMP_EN | BMP388_REG_VAL_NORMAL_MODE), "Failed to enable normal mode temperature and pressure")) {
        return false;
    }

    read_calibrations();

    if (!(result & BMP388_REG_VAL_CMD_RDY)) {
        HAL_ERROR1("Incorrect BMP388 status %d\n", result);
        return false;
    } else {
        HAL_INFO1("BMP388 status %d\n", result);
    }

    m_state = BMP388_STATE_IDLE;

    return true;
}

bool RTPressureBMP388::pressureRead(RTIMU_DATA& data)
{
    data.pressureValid = false;
    data.temperatureValid = false;
    data.temperature = 0;
    data.pressure = 0;

    uint8_t pressure_data[3];
    uint8_t temperature_data[3];

    uint8_t status = 0x00;

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_PRESS_XLSB, 3, pressure_data, "Failed to read BMP388 pressure")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_TEMP_XLSB, 3, temperature_data, "Failed to read BMP388 Temperature")) {
        return false;
    }

    uint32_t raw_pressure = ((((uint32_t)(pressure_data[0])) << 16) + ((uint32_t)(pressure_data[1])) << 8) + (((uint32_t)(pressure_data[2])));
    uint32_t raw_temperature = ((((uint32_t)(temperature_data[0])) << 16) + ((uint32_t)(temperature_data[1])) << 8) + (((uint32_t)(temperature_data[2])));

    printf("P: %f, T: %f\n", raw_pressure, raw_temperature);

    if (m_validReadings) {
        data.pressureValid = true;
        data.temperatureValid = true;
        data.temperature = compensate_temperature(raw_temperature);
        data.pressure = compensate_pressure(raw_pressure);
        printf("P: %f, T: %f\n", m_pressure, m_temperature);
    }
    return true;
}

RTFLOAT RTPressureBMP388::compensate_temperature(uint32_t rt)
{
        RTFLOAT int_rt = rt;
        RTFLOAT partial_data1 = int_rt - 256 * calibration_temp_1;
        RTFLOAT partial_data2 = calibration_temp_2 * partial_data1;
        RTFLOAT partial_data3 = partial_data1 * partial_data1;
        RTFLOAT partial_data4 = partial_data3 * calibration_temp_3;
        RTFLOAT partial_data5 = partial_data2 * 262144 + partial_data4;
        RTFLOAT partial_data6 = partial_data5 / 4294967296;
        T_fine = partial_data6;
        RTFLOAT comp_temp = partial_data6 * 25 / 16384;

        printf("Tfine : %f \n", T_fine);

    return comp_temp;
}

RTFLOAT RTPressureBMP388::compensate_pressure(uint32_t rp){
        RTFLOAT int_rp = rp;
        RTFLOAT partial_data1 = T_fine * T_fine;
        RTFLOAT partial_data2 = partial_data1 / 0x40;
        RTFLOAT partial_data3 = partial_data2 * T_fine / 256;
        RTFLOAT partial_data4 = calibration_press_8 * partial_data3 / 0x20;
        RTFLOAT partial_data5 = calibration_press_7 * partial_data1 * 0x10;
        RTFLOAT partial_data6 = calibration_press_6 * T_fine * 4194304;
        RTFLOAT offset = calibration_press_5 * 140737488355328 + partial_data4 + partial_data5 + partial_data6;

        partial_data2 = calibration_press_4 * partial_data3 / 0x20;
        partial_data4 = calibration_press_3 * partial_data1 * 0x04;
        partial_data5 = (calibration_press_2 - 16384) * T_fine * 2097152;
        RTFLOAT sensitivity = (calibration_press_1 - 16384) * 70368744177664 + partial_data2 + partial_data4 + partial_data5;

        partial_data1 = sensitivity / 16777216 * int_rp;
        partial_data2 = calibration_press_10 * T_fine;
        partial_data3 = partial_data2 + 65536 * calibration_press_9;
        partial_data4 = partial_data3 * int_rp / 8192;
        partial_data5 = partial_data4 * int_rp / 512;
        partial_data6 = int_rp * int_rp;
        partial_data2 = calibration_press_11 * partial_data6 / 65536;
        partial_data3 = partial_data2 * int_rp / 128;
        partial_data4 = offset / 0x04 + partial_data1 + partial_data5 + partial_data3;
        RTFLOAT comp_press = partial_data4 * 25 / 1099511627776;
    return comp_press;
}



bool RTPressureBMP388::read_calibrations() {

    uint8_t cal_T_1[2];
    uint8_t cal_T_2[2];
    uint8_t cal_T_3;

    uint8_t cal_P_1[2];
    uint8_t cal_P_2[2];
    uint8_t cal_P_3;
    uint8_t cal_P_4;
    uint8_t cal_P_5[2];
    uint8_t cal_P_6[2];
    uint8_t cal_P_7;
    uint8_t cal_P_8;
    uint8_t cal_P_9[2];
    uint8_t cal_P_10;
    uint8_t cal_P_11;

    printf("Setup BMP388 -- preparing calibration values\n");
    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_T1_LSB, 2, cal_T_1, "Failed to read BMP388 cal_T_1")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_T2_LSB, 2, cal_T_2, "Failed to read BMP388 cal_T_2")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_T3, 1, &cal_T_3, "Failed to read BMP388 cal_T_3")) {
        return false;
    }

    calibration_temp_1 = (uint32_t)cal_T_1[0] << 8 + cal_T_1[0];
    calibration_temp_2 = (uint32_t)cal_T_2[0] << 8 + cal_T_2[0];
    calibration_temp_3 = (uint32_t)cal_T_3;
    
    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P1_LSB, 2, cal_P_1, "Failed to read BMP388 cal_P_1")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P2_LSB, 2, cal_P_2, "Failed to read BMP388 cal_P_2")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P3, 1, &cal_P_3, "Failed to read BMP388 cal_P_3")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P4, 1, &cal_P_4, "Failed to read BMP388 cal_P_4")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P5_LSB, 2, cal_P_5, "Failed to read BMP388 cal_P_5")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P6_LSB, 2, cal_P_6, "Failed to read BMP388 cal_P_6")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P7, 1, &cal_P_7, "Failed to read BMP388 cal_P_7")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P8, 1, &cal_P_8, "Failed to read BMP388 cal_P_8")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P9_LSB, 2, cal_P_9, "Failed to read BMP388 cal_P_9")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P10, 1, &cal_P_10, "Failed to read BMP388 cal_P_10")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_ADD_P11, 1, &cal_P_11, "Failed to read BMP388 cal_P_11")) {
        return false;
    }

    calibration_press_1 = (uint32_t)cal_P_1[1] << 8 + cal_P_1[0];
    calibration_press_2 = (uint32_t)cal_P_2[1] << 8 + cal_P_2[0];
    calibration_press_3 = (uint32_t)cal_P_3;
    calibration_press_4 = (uint32_t)cal_P_4;
    calibration_press_5 = (uint32_t)cal_P_5[1] << 8 + cal_P_6[0];
    calibration_press_6 = (uint32_t)cal_P_6[1] << 8 + cal_P_6[0];
    calibration_press_7 = (uint32_t)cal_P_7;
    calibration_press_8 = (uint32_t)cal_P_8;
    calibration_press_9 = (uint32_t)cal_P_9[1] << 8 + cal_P_9[0];
    calibration_press_10 = (uint32_t)cal_P_10;
    calibration_press_11 = (uint32_t)cal_P_11;
    return true;

}

