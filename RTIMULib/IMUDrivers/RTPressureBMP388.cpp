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

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_DATA0, 3, pressure_data, "Failed to read BMP388 pressure")) {
        return false;
    }

    if (!m_settings->HALRead(m_pressureAddr, BMP388_REG_DATA4, 3, temperature_data, "Failed to read BMP388 Temperature")) {
    return false;
    }

    m_validReadings = true;

    int32_t m_pressure = ((((uint32_t)(pressure_data[2])) << 16) + ((uint32_t)(pressure_data[1])) << 8) + (((uint32_t)(pressure_data[0])));
    int32_t m_temperature = ((((uint32_t)(temperature_data[2])) << 16) + ((uint32_t)(temperature_data[1])) << 8) + (((uint32_t)(temperature_data[0])));


    if (m_validReadings) {
        data.pressureValid = true;
        data.temperatureValid = true;
        data.temperature = m_temperature;
        data.pressure = m_pressure;
        // printf("P: %f, T: %f\n", m_pressure, m_temperature);
    }
    return true;
}
