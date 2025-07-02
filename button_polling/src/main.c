#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief Configure the push button with GPIO polling.
 * 
 * This example demonstrates how to configure a GPIO pin for a push button
 * using the Zephyr RTOS. It sets up the button as an input and continuously
 * polls its state in a loop, printing the button state to the console.
 * 
 */

static const int32_t sleep_time_ms = 100;
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(my_button), gpios);

int main(void) {
    int ret;
    int state;

    if (!gpio_is_ready_dt(&button)) {
        printk("Button device is not ready\r\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0) {
        printk("Failed to configure button GPIO pin\r\n");
        return 0;
    }

    printk("Button spec flags: 0x%x\r\n", button.dt_flags);

    while (true) {
        
        // Poll the button state
        state = gpio_pin_get_dt(&button);
        if (state < 0) {
            printk("Error %d: failed to read button state\r\n", state);
        } else {
            printk("Button state: %d\r\n", state);
        }

        k_msleep(sleep_time_ms);
    }

    return 0;
}