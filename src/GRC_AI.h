#ifndef _GRC_AI_H_
#define _GRC_AI_H_

#include <Arduino.h>
#include <Wire.h>

#include "grc/grc.h"
#include "grc/i2c/drivers/arduino/grc_ll_i2c_arduino.h"

class GRC_AI {
public:
    GRC_AI(uint32_t arch, TwoWire& wire);
    ~GRC_AI();

    uint32_t version() const;

    int begin();
    void end();

private:
    grc_device dev;


};

#endif // _GRC_AI_H_
