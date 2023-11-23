#ifndef _GRC_AI_H_
#define _GRC_AI_H_

#include <Arduino.h>
#include <Wire.h>

#include "grc/Grc.hpp"
#include "grc/drivers/arduino/grc_arduino.h"


class GRC_AI : public Grc {
public:
    GRC_AI(TwoWire& wire, int reset_pin);
    ~GRC_AI();

    uint32_t version() const;

private:
    struct grc_ll_i2c_dev_arduino ll_dev;


};

#endif // _GRC_AI_H_
