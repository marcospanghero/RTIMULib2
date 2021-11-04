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

#ifndef _RTPRESSUREBMP388_H_
#define _RTPRESSUREBMP388_H_

#include "RTPressure.h"

//  State definitions

#define BMP388_STATE_IDLE               0
#define BMP388_STATE_TEMPERATURE        1
#define BMP388_STATE_PRESSURE           2

//  Conversion reg defs

#define BMP388_SCO_TEMPCONV             0x2e                // temperature conversion
#define BMP388_SCO_PRESSURECONV_ULP     0                   // ultra low power pressure conversion
#define BMP388_SCO_PRESSURECONV_STD     1                   // standard pressure conversion
#define BMP388_SCO_PRESSURECONV_HR      2                   // high res pressure conversion
#define BMP388_SCO_PRESSURECONV_UHR     3                   // ultra high res pressure conversion

class RTIMUSettings;

class RTPressureBMP388 : public RTPressure
{
public:
    RTPressureBMP388(RTIMUSettings *settings);
    ~RTPressureBMP388();

    virtual const char *pressureName() { return "BMP388"; }
    virtual int pressureType() { return RTPRESSURE_TYPE_BMP388; }
    virtual bool pressureInit();
    virtual bool pressureRead(RTIMU_DATA& data);

private:

    bool read_calibrations();

    RTFLOAT compensate_temperature(uint32_t rt);
    RTFLOAT compensate_pressure(uint32_t rp);

    unsigned char m_pressureAddr;                           // I2C address
    RTFLOAT m_pressure;                                     // the current pressure
    RTFLOAT m_temperature; 
    
    RTFLOAT T_fine;

    uint32_t calibration_temp_1;
    uint32_t calibration_temp_2;
    uint32_t calibration_temp_3;
    
    uint32_t calibration_press_1;
    uint32_t calibration_press_2;
    uint32_t calibration_press_3;
    uint32_t calibration_press_4;
    uint32_t calibration_press_5;
    uint32_t calibration_press_6;
    uint32_t calibration_press_7;
    uint32_t calibration_press_8;
    uint32_t calibration_press_9;
    uint32_t calibration_press_10;
    uint32_t calibration_press_11;

    int m_state;
    bool m_validReadings;
};

#endif // _RTPRESSUREBMP388_H_

