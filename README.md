# Zephyr RTOS on ESP32

This repository contains examples of how to use the Zephyr RTOS on the ESP32.

### Environment Details

| Component               | Version         |
|-------------------------|-----------------|
| OS                      | Ubuntu 22.04    |
| CMake version           | 3.22.1          |
| Python version          | 3.10.12         |
| Zephyr SDK version      | 0.17.0          |
| Zephyr version          | 4.0.99          |
| West version            | 1.3.0           |
| DTC version             | 1.6.0           |
| Python Environment      | Using `venv` as recommended by the Getting Started Guide |

## How to enable VSCode IntelliSense for Zephyr RTOS

To enable IntelliSense for Zephyr RTOS in Visual Studio Code, follow these steps:

1. **Open the project in Visual Studio Code.**

2. **Create a `.vscode` folder in the root of the project.**

3. **Create a `settings.json` file in the `.vscode` folder.**

4. **Fill the `settings.json` file with the following content:**

    ```json
    {
        "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json",
        "files.associations": {},
    }
    ```

5. **Save the file and rebuild the project. IntelliSense should now work in Visual Studio Code.**

## Troubleshooting

### Constant Reboot After Flashing

If the board continuously resets after flashing and displays the following message:

```textplain
I (49) soc_init: ESP Simple boot
I (49) soc_init: compile time Dec 18 2024 20:25:25
W (49) soc_init: Unicore bootloader
I (50) spi_flash: detected chip: generic
I (54) spi_flash: flash io: dio
I (57) soc_init: chip revision: v1.0
E (60) soc_init: You are using ESP32 chip revision (1) that is unsupported. While it may work, it could cause unexpected behavior or issues.
E (73) soc_init: Proceeding with this ESP32 chip revision is not recommended unless you fully understand the potential risk and limitations.
E (85) soc_init: If you choose to continue, please enable the 'CONFIG_ESP32_USE_UNSUPPORTED_REVISION' in your project configuration.
E (97) boot: HW init failed, aborting
Fatal exception (0): IllegalInstruction
epc1=0x400d1422, epc2=0x00000000, epc3=0x00000000, excvaddr=0x00000000, depc=0x00000000
```

This indicates the ESP32 chip revision is unsupported. For older revisions, such as `ESP32-D0WDQ6 (revision v1.0)`, enable support by adding the following line to the `boards/esp32_devkitc_wroom.conf` file:

```kconfig
CONFIG_ESP32_USE_UNSUPPORTED_REVISION=y
```

Rebuild and flash the project after making this change.

---

## References

- How to install: [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)
- [Zephyr RTOS Documentation](https://docs.zephyrproject.org/latest/)
- [Set devicetree overlays](https://docs.zephyrproject.org/latest/build/dts/howtos.html#set-devicetree-overlays)
- [Setting Kconfig configuration values - The Initial Configuration](https://docs.zephyrproject.org/latest/build/kconfig/setting.html#the-initial-configuration)
- [Blinky](https://docs.zephyrproject.org/latest/samples/basic/blinky/README.html#blinky)
