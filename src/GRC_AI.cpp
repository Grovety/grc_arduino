#include "GRC_AI.h"
#include "grc/i2c/drivers/arduino/grc_ll_i2c_arduino_impl.h"


GRC_AI::GRC_AI(uint32_t arch, TwoWire& wire)
{
    // ll_dev.type = PROTOCOL_INTERFACE_I2C_ARDUINO;
    // ll_dev.arduino_wire = &wire;
    // dev.ll_dev = &ll_dev;

    // grc_config cfg = {
    //     .arch = arch,
    // };

    // int res = grc_init(&dev, &cfg);
    // printf("init failed with code: %d\n", res);
    // if (res < 0)
    //     throw res;
}

GRC_AI::~GRC_AI()
{
    // grc_release(&dev);
}

uint32_t GRC_AI::version() const
{
    return dev.version;
}

int GRC_AI::begin()
{
    return 0;
}

void GRC_AI::end()
{

}
