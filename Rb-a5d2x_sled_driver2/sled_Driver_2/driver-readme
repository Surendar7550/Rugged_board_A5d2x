Enable toolchain

$ make distclean

$ make clean


******( Adding Driver in kernel in static way )******

Step1:

        copy sled.c drivers/misc/

Step2:
	vim drivers/misc/Makefile
	obj-$(CONFIG_SLED) 	+= sled.o

Step3:
	vim drivers/misc/Kconfig

config SLED
        tristate "gpio-led driver"
        default y
        help
          This is my test driver for sled

Step4: 
	Describe Hardware in a5d2x_rugged_board_common.dtsi file....
	
	sled {

		compatible = "sled";
		pinctrl-name =  "default";
		pinctrl-0 = <&pinctrl_pc13_default>;
	     //   button-gpios = <&pioA PIN_PC12 0>;
		led-gpios = <&pioA PIN_PC13 0>;

		status = "okay";
	     };


	pinctrl_pc13_default:pc13_default {
		pinmux = <PIN_PC13__GPIO>,
			<PIN_PC17__GPIO>,
			<PIN_PC19__GPIO>,
			<PIN_PC12__GPIO>;	
		bias-disable;
	};		


$ make rb_a5d2x_defconfig

$ make menuconfig

$ make -j4

=> zImage present in /arch/arm/boot/  copy into  BOOT dir of SD Card for SD Card Flash and for NOR Flash copy into /var/lib/tftpboot/ and then copy to NOR flash 

=> a5d2x_rugged_board.dtb present in /arch/arm/boot/dts/  copy into  BOOT dir of SD Card for SD Card Flash and for NOR Flash copy into /var/lib/tftpboot/ and then copy to NOR flash 



  ******( Adding Driver in kernel in dynamic way )*******

Step1:

        copy sled.c drivers/misc/

Step2:
	vim drivers/misc/Makefile
	obj-$(CONFIG_SLED) 	+= sled.o

Step3:
	vim drivers/misc/Kconfig

config SLED
        tristate "gpio-led driver"
        default m
        help
          This is my test driver for sled

Step4: 
	Describe Hardware in a5d2x_rugged_board_common.dtsi file....
	
	sled {

		compatible = "sled";
		pinctrl-name =  "default";
		pinctrl-0 = <&pinctrl_pc13_default>;
	     //   button-gpios = <&pioA PIN_PC12 0>;
		led-gpios = <&pioA PIN_PC13 0>;

		status = "okay";
	     };


	pinctrl_pc13_default:pc13_default {
		pinmux = <PIN_PC13__GPIO>,
			<PIN_PC17__GPIO>,
			<PIN_PC19__GPIO>,
			<PIN_PC12__GPIO>;	
		bias-disable;
	};		

$ make rb_a5d2x_defconfig

$ make menuconfig

$ make -j4

=> zImage present in /arch/arm/boot/  copy into  BOOT dir of SD Card for SD Card Flash and for NOR Flash copy into /var/lib/tftpboot/ and then copy to NOR flash 

=> a5d2x_rugged_board.dtb present in /arch/arm/boot/dts/  copy into  BOOT dir of SD Card for SD Card Flash and for NOR Flash copy into /var/lib/tftpboot/ and then copy to NOR flash 		
		
=> sled.ko present in /driver/misc/  copy into  /rootfs/home/ of SD Card

after booting the board 
	$ cd /home/
	$ insmod sled.ko      ===>to insert the driver
	$ ./blinky







