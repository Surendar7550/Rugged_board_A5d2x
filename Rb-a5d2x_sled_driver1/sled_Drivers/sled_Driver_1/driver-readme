Adding Driver in uboot

Step1:

        copy sled.c drivers/led/

Step2:
	vim drivers/led/Makefile
	obj-y += sled.o

Step3:
	vim drivers/led/Kconfig

config SLED
        bool "SLED support for LEDs"
        depends on LED
        help
          Enable support for LEDs which are connected to GPIO lines. These
          GPIOs may be on the SoC or some other device which provides GPIOs.
          The GPIO driver must used driver model. LEDs are configured using
          the device tree.

Step4: 
	Describe Hardware in dts file....
	
leds {

         compatible = "gpio-leds";

         pinctrl-names = "default";

         pinctrl-0 = <&pinctrl_leds>;

}


Adding command in uboot

Step1:

Command File is sled_test.c file
        cp sled_test.c   uboot-a5d2x/cmd/

Step2:
vim cmd/Makefile

obj-y += sled_test.o

Step3:

vim cmd/Kconfig
config CMD_SLED_TEST
        bool "sled test"
        default y if LED

        help
          Enable the 'sled_test' command which allows for control of LEDs supported
          by the board. The LEDs can be listed with 'led list' and controlled
          with led on/off/togle/blink. Any LED drivers can be controlled with
          this command, e.g. led_gpio.m a


Step4:
After adding all please enable the driver in menuconfig


step5;

	./sled_test ds1 off 
		










