#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief Blink the LED on the board. GPIO0 Pin 25 is used to control the LED.
 * 
 * Part 1: Configures the GPIO pin as an output without Device Tree
 * and using the gpio_pin_set raw() function to control the LED.
 * 
 */

#define LED_PIN 25
#define LOW 0
#define HIGH 1

static const struct device* gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));

int main(void) {
    if (!device_is_ready(gpio_ct_dev)) {
        printk("GPIO device is not ready\r\n");
        return 0;
    }

    int ret = gpio_pin_configure(gpio_ct_dev, LED_PIN, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        printk("Failed to configure GPIO pin\r\n");
        return ret;
    }

    while (true) {
        printk("Hello, World!\r\n");
        ret = gpio_pin_set_raw(gpio_ct_dev, LED_PIN, HIGH);
        if (ret != 0) {
            printk("Failed to set GPIO pin\r\n");
            return ret;
        }
        k_msleep(1000);

        ret = gpio_pin_set_raw(gpio_ct_dev, LED_PIN, LOW);
        if (ret != 0) {
            printk("Failed to set GPIO pin\r\n");
            return ret;
        }
        k_msleep(1000);
    }
}