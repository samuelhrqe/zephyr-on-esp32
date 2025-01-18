#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED_NODE DT_NODELABEL(blinking_led)
#define BUTTON_NODE DT_NODELABEL(push_button)

#if !DT_NODE_EXISTS(LED_NODE) || !DT_NODE_HAS_STATUS_OKAY(LED_NODE)
    #error "LED node not founded or not okay"
#endif

#if !DT_NODE_EXISTS(BUTTON_NODE) || !DT_NODE_HAS_STATUS_OKAY(BUTTON_NODE)
    #error "Button node not founded or not okay"
#endif

/**
 * @brief Configure the push button and the blinking LED
 * 
 * Configure ISR for the push button and toggle the blinking LED.
 * Debounce software is implemented to avoid multiple toggles.
 */

volatile bool flag_button_pressed = false;

// Get the debounce interval from the devicetree
#define DEBOUNCE_INTERVAL_MS DT_PROP(DT_PATH(buttons), debounce_interval_ms)

void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    flag_button_pressed = true;
}

int main(void) {
    static struct gpio_callback button_cb_data;
    static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
    static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
    static int64_t last_time = 0;

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

    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_RISING);

    if (ret != 0) {
        return ret;
    }

    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    while (true) {
        if (flag_button_pressed) {
            if ((k_uptime_get() - last_time) >= DEBOUNCE_INTERVAL_MS) {
                int ret = gpio_pin_toggle_dt(&led);
                if (ret != 0) {
                    printk("Failed to toggle LED GPIO pin\r\n");
                }
                last_time = k_uptime_get();
            }

            flag_button_pressed = false;
        }

        k_msleep(10);
    }
}