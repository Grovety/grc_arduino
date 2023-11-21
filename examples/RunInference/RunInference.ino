#include <Arduino.h>
#include <GRC_AI.h>
#include <Wire.h>

float data[] = {
    0.0049, -0.0156, 0.2522, 0.0012, -0.0203, 0.2488, 0.0017, -0.0183, 0.2478, 0.0032,
    -0.0132, 0.2505, 0.0034, -0.0278, 0.2505, -0.0002, -0.0276, 0.2480, -0.0037, -0.0110,
    0.2375, 0.0015, -0.0105, 0.2434, 0.0037, -0.0200, 0.2493, -0.0010, -0.0347, 0.2559,
    0.0056, -0.0232, 0.2546, 0.0046, -0.0220, 0.2522, 0.0059, -0.0249, 0.2483, 0.0002,
    -0.0168, 0.2480, 0.0049, -0.0178, 0.2776, 0.0295, -0.0510, 0.3774, 0.0503, -0.0535,
    0.4106, 0.0510, 0.0139, 0.3843, 0.0701, 0.0024, 0.4519, 0.0415, -0.1250, 0.2603,
    -0.0442, 0.0227, 0.1162, -0.1511, 0.0603, 0.1035, -0.1958, 0.0029, 0.0632, -0.1899,
    -0.0244, 0.0095, -0.2029, -0.0693, -0.1047, -0.1580, 0.0386, -0.0969, -0.1516, 0.0559,
    -0.0845, -0.1150, -0.0466, -0.1211, -0.0381, -0.1624, -0.0447, 0.1240, -0.0723, 0.1426,
    0.1384, 0.0017, 0.2996, 0.1123, -0.1262, 0.2344, 0.1851, -0.0571, 0.4270, 0.1450, 0.0681,
    0.4387, 0.1677, -0.0107, 0.4534, 0.1545, -0.1218, 0.4612, 0.1919, -0.0830, 0.5051, 0.1814,
    0.0022, 0.4653, 0.1421, -0.0750, 0.3867, 0.1379, -0.0198, 0.3635, 0.1680, 0.0098, 0.3628,
    0.0801, -0.0774, 0.2190, -0.0166, -0.0613, 0.1553, -0.1245, 0.0464, 0.0330, -0.1562, 0.0759,
    0.0610, -0.1592, -0.0217, 0.0896, -0.1641, -0.0271, 0.0430, -0.1438, 0.0540, 0.0244, -0.1929,
    0.0669, -0.0576, -0.1951, -0.0190, -0.1628, -0.1155, -0.0276, -0.0901, -0.0605, -0.0676,
    -0.0115, -0.0649, -0.1206, -0.0242, 0.0063, -0.1025, 0.0149, 0.1338, 0.0586, 0.2651, 0.0803,
    -0.0781, 0.3123, 0.1235, -0.1162, 0.3564, 0.2297, -0.0029, 0.5320, 0.2017, -0.0212, 0.5217,
    0.1418, -0.1257, 0.4995, 0.1582, -0.1130, 0.5342, 0.2107, -0.0198, 0.5273, 0.1750, -0.0571,
    0.3940, 0.1528, -0.0518, 0.3403, 0.0889, -0.0452, 0.2092, 0.0020, 0.0200, 0.0962, -0.0710,
    -0.0298, 0.1133, -0.1658, 0.0068, 0.0034, -0.1790, 0.0649, -0.0376, -0.1567, 0.0754, 0.0117,
    -0.1665, 0.0364, -0.0242, -0.2026, 0.0479, -0.1238, -0.1785, -0.0181, -0.1650
};

static grc_device dev;
static grc_ll_i2c_dev_arduino ll_dev;

void setup()
{
    Serial.begin(115200);
    Serial.println("Started...");

    Wire.setPins(12, 13);

    ll_dev.type = PROTOCOL_INTERFACE_I2C_ARDUINO;
    ll_dev.arduino_wire = &Wire;
    dev.ll_dev = &ll_dev;

    grc_config cfg = {
        .arch = I1_N18,
    };

    int res = grc_init(&dev, &cfg);
    if (res < 0)
        printf("init failed with code: %d\n", res);

    struct hp_setup config[] = {
        { .type = PREDICT_SIGNAL, .value = 1.0f },
        { .type = SEPARATE_INACCURACIES, .value = 0.0f },
        { .type = NOISE, .value = 0.00100195 },
        { .type = INPUT_SCALING, .value = 0.566296 },
        { .type = FEEDBACK_SCALING, .value = 0.00168945 },
        { .type = THRESHOLD_FACTOR, .value = 0.86792 }
    };
    res = grc_set_config(&dev, config, sizeof(config) / sizeof(*config));
    if (res < 0)
        printf("config failed with code: %d\n", res);
}

void loop()
{
    grc_training_params t_params = {
        .flags = GRC_PARAMS_OVERWRITE,
        .tag = 0,
    };
    grc_inference_params i_params = { 0 };

    unsigned long start = micros();
    int res = grc_train(&dev, &t_params, data, sizeof(data));
    unsigned long end = micros();

    Serial.printf("Training done in %u us with status %d.\n", end - start, res);

    start = micros();
    grc_inference(&dev, &i_params, data, sizeof(data));
    end = micros();

    Serial.printf("Inference done in %u us with status %d.\n", end - start, res);
    Serial.printf("=======================\n");
    delay(1000);
}
