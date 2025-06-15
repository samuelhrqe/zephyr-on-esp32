#include <zephyr/random/random.h>

#ifdef CONFIG_SAY_HELLO
#include "say_hello.h"
#endif

static const int32_t sleep_time_ms = 1000;

int main() {
    uint32_t random_value;

    while (true) {
        random_value = sys_rand32_get();
        double random_value_scaled = (double)random_value / (UINT32_MAX + 1.0);
        printk("Random value: %u\n", random_value);
        printk("Scaled random value: %f\n", random_value_scaled);

#ifdef CONFIG_SAY_HELLO
        say_hello();
#endif

        k_msleep(sleep_time_ms);
    }

    return 0;
}