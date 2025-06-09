#include <zephyr/sys/printk.h>
#include "say_hello.h"

void say_hello() {
    printk("Hello, world!\r\n");
}