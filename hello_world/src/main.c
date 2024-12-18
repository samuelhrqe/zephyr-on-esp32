#include <zephyr/kernel.h>
#include <zephyr/device.h>

int main(void)
{
    while (true) {
        printk("Hello, World!\r\n");
        k_msleep(1000);
    }

    return 0;
}