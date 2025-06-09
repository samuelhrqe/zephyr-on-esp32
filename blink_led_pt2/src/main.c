#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief Blink the LED on the board. GPIO0 Pin 25 is used to control the LED.
 * 
 * Part 2: Use the GPIO DT Spec API to configure and toggle the LED.
 * 
 */

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);

int main(void) {
    if (!device_is_ready(led.port)) { // device_is_ready_dt(&led)
        printk("GPIO device is not ready\r\n");
        return 0;
    }

    // int ret = gpio_pin_configure(led.port, led.pin, led.dt_flags);
	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        printk("Failed to configure GPIO pin\r\n");
        return ret;
    }

    while (true) {
        printk("Hello, World!\r\n");
        ret = gpio_pin_toggle_dt(&led);
        if (ret != 0) {
            printk("Failed to set GPIO pin\r\n");
            return ret;
        }
        k_msleep(1000);
    }
}