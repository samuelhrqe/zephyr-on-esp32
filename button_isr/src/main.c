#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define DEBOUNCE_DELAY 50

/**
 * @brief Configure the push button and the blinking LED
 * 
 * Configure ISR for the push button and toggle the blinking LED.
 * Debounce software is implemented to avoid multiple toggles.
 */

static struct gpio_callback button_cb_data;
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_NODELABEL(push_button), gpios);
static int last_read = 0;

void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    if (gpio_pin_get_dt(&button)) {
        if (k_uptime_get() - last_read >= DEBOUNCE_DELAY) {
            gpio_pin_toggle_dt(&led);
        }
        last_read = k_uptime_get();
    }
}

int main(void) {
    if (!device_is_ready(led.port)) {
        printk("GPIO device is not ready\r\n");
        return 0;
    }

    if (!device_is_ready(button.port)) {
        printk("Button device is not ready\r\n");
        return 0;
    }

    // int ret = gpio_pin_configure(led.port, led.pin, led.dt_flags);
	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        printk("Failed to configure LED GPIO pin\r\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0) {
        printk("Failed to configure button GPIO pin\r\n");
        return ret;
    }

    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);

    if (ret != 0) {
        return ret;
    }

    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    while (true) {
        ret = gpio_pin_get_dt(&button);
        
        printk("Button state: %d\r\n", ret);
        k_msleep(1000);
    }
}