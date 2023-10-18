#include <GRC.h>
#include <Wire.h>

GRC grc(Wire(), 0x36);

void setup() {
    grc.setup();
}

void loop() {

}