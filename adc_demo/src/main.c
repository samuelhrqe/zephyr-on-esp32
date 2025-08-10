#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>

/**
 * @brief Configure the ADC and read values from a channel.
 * 
 * The GPIO4 pin is used to read an analog value from an ADC channel.
 * In the ESP32 Technical Reference Manual, GPIO4 is connected to ADC2_CH0.
 * In the Zephyr, ADC0 -> ADC1 (Reference Manual) and ADC1 -> ADC2.
 */

static const int32_t sleep_time_ms = 100;

#define MY_ADC_CH DT_ALIAS(my_adc_channel)
static const struct device *adc = DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(MY_ADC_CH);

int main(void) {

    int ret;

    uint16_t raw, val_mv;
    int32_t vref_mv;

    // Get Vref (mV) from Devicetree property
    vref_mv = DT_PROP(MY_ADC_CH, zephyr_vref_mv);

    // Buffer and options for ADC (defined in adc.h)
    struct adc_sequence seq = {
        .channels = BIT(adc_ch.channel_id),
        .buffer = &raw,
        .buffer_size = sizeof(raw),
        .resolution = DT_PROP(MY_ADC_CH, zephyr_resolution)
    };

    if (!device_is_ready(adc)) {
        printk("ADC device not ready\n");
        return 0;
    }

    ret = adc_channel_setup(adc, &adc_ch);
    if (ret < 0) {
        printk("ADC channel setup failed: %d\n", ret);
        return 0;
    }

    while (1) {
        ret = adc_read(adc, &seq);
        if (ret < 0) {
            printk("ADC read failed: %d\n", ret);
            continue;
        }

        // Calculate ADC value in millivolts
        val_mv = raw * vref_mv / (1 << seq.resolution);

        printk("Raw: %u, mV: %u\n", raw, val_mv);

        k_msleep(sleep_time_ms);
    }

    return 0;
}