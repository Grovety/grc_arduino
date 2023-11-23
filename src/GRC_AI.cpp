#include "GRC_AI.h"
#include "grc/drivers/arduino/grc_arduino_impl.h"


GRC_AI::GRC_AI(TwoWire& wire, int reset_pin)
    : Grc(nullptr)
{
    ll_dev.type = PROTOCOL_INTERFACE_I2C_ARDUINO;
    ll_dev.arduino_wire = &wire;
    ll_dev.reset_pin = reset_pin;
    this->dev_.ll_dev = &ll_dev;
}

GRC_AI::~GRC_AI()
{
}

uint32_t GRC_AI::version() const
{
    return dev_.version;
}
