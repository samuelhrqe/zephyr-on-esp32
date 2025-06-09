#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "say_hello.h"

/**
 * @brief DigiKey Class about Zephyr
 * 
 * Integrate the say_hello library into the Zephyr project using CMake.
 * 
 */
static const int32_t sleep_time_ms = 1000; // Sleep time in milliseconds
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
        say_hello(); // Call the function from say_hello.h
        ret = gpio_pin_toggle_dt(&led);
        if (ret != 0) {
            printk("Failed to set GPIO pin\r\n");
            return ret;
        }
        k_msleep(sleep_time_ms); // Sleep for the specified time
    }
}