#ifndef _GRC_H_
#define _GRC_H_

#include <Arduino.h>
#include <Wire.h>

class GRC {
public:
    GRC(TwoWire& wire, uint8_t slaveAddress);
    ~GRC();

    int begin();
    void end();


}

#endif // _GRC_H_
