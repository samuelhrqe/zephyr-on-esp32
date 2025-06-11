#include <zephyr/random/random.h>

static const int32_t sleep_time_ms = 1000;

int main() {
    uint32_t random_value;

    while (true) {
        random_value = sys_rand32_get();
        printk("Random value: %u\n", random_value);

        k_msleep(sleep_time_ms);
    }

    return 0;
}