
refer this link   for more information
https://www.linux4sam.org/bin/view/Linux4SAM/Sama5d27Som1EKMainPage



Kernel update for ruggedboard_a5d2x:
------------------------------------

step1: Getting Kernel sources
use this linke download the sourced code

$ git clone https://github.com/linux4microchip/linux.git

output:

Cloning into 'linux'...
remote: Enumerating objects: 8587836, done.
remote: Total 8587836 (delta 0), reused 0 (delta 0), pack-reused 8587836
Receiving objects: 100% (8587836/8587836), 3.49 GiB | 13.44 MiB/s, done.
Resolving deltas: 100% (7117887/7117887), done.
Updating files: 100% (70687/70687), done.

The source code has been taken from the master branch which is pointing on the latest branch we use.

step2:change the directry
$ cd linux

step3:
$ git remote add linux4microchip https://github.com/linux4microchip/linux.git
$ git remote update linux4microchip
Fetching linux4icrochip
From https://github.com/linux4microchip/linux
 * [new branch]                linux-5.10-mchp -> linux4microchip/linux-5.10-mchp
 * [new branch]                linux-5.15-mchp -> linux4microchip/linux-5.15-mchp
 * [new branch]                linux-6.1-mchp -> linux4microchip/linux-6.1-mchp
 * [new branch]                master     -> linux4microchip/master
If you want to use another branch, you can list them and use one of them by doing this:

$ git branch -r
  origin/HEAD -> origin/master
  origin/linux-5.10-mchp
  origin/linux-5.15-mchp
  origin/linux-6.1-mchp
  origin/master
$ git checkout origin/linux-6.1-mchp -b linux-6.1-mchp
Branch linux-6.1-mchp set up to track remote branch linux-6.1-mchp from origin.
Switched to a new branch 'linux-6.1-mchp'





step4: Setup ARM Cross Compiler
$ sudo apt-get install gcc-arm-linux-gnueabi

$ export CROSS_COMPILE=arm-linux-gnueabi-

step5: 
Configure and Build the Linux kernel
Now you have to configure the Linux kernel according to your hardware. We have two default configuration at91 SoC in arch/arm/configs
arch/arm/configs/at91_dt_defconfig
arch/arm/configs/sama5_defconfig
arch/arm/configs/sama7_defconfig
at91_dt_defconfig: for SAM9 (ARM926) series chips
sama5_defconfig: for SAMA5 series chips
sama7_defconfig: for SAMA7 series chips
Now we Configure and Build kernel for sama5d27_som1_ek board:


$ make ARCH=arm sama5_defconfig

output:

  HOSTCC  scripts/basic/fixdep
  HOSTCC  scripts/kconfig/conf.o
  SHIPPED scripts/kconfig/zconf.tab.c
  SHIPPED scripts/kconfig/zconf.lex.c
  SHIPPED scripts/kconfig/zconf.hash.c
  HOSTCC  scripts/kconfig/zconf.tab.o
  HOSTLD  scripts/kconfig/conf
#
# configuration written to .config
#

step6:At this step, you can modify default configuration using the menuconfig

$ make ARCH=arm menuconfig

note:exit and goto next step



step7:Build the Linux kernel image, before you build you need set up the cross compile toolchain,

$ make ARCH=arm


[..]

  Kernel: arch/arm/boot/Image is ready
  Kernel: arch/arm/boot/zImage is ready
Now you have an usable compressed kernel image zImage.

If you need an uImage you can run this additional step:

step8:

$ make ARCH=arm dtbs

[..]

  DTC     arch/arm/boot/dts/at91-kizbox2-2.dtb
  DTC     arch/arm/boot/dts/at91-kizbox3-hs.dtb
  DTC     arch/arm/boot/dts/at91-nattis-2-natte-2.dtb
  DTC     arch/arm/boot/dts/at91-sama5d27_som1_ek.dtb
  DTC     arch/arm/boot/dts/at91-sama5d27_wlsom1_ek.dtb
  DTC     arch/arm/boot/dts/at91-sama5d2_icp.dtb
  DTC     arch/arm/boot/dts/at91-sama5d2_ptc_ek.dtb
  DTC     arch/arm/boot/dts/at91-sama5d2_xplained.dtb
  DTC     arch/arm/boot/dts/at91-sama5d3_xplained.dtb
  DTC     arch/arm/boot/dts/at91-dvk_som60.dtb
  DTC     arch/arm/boot/dts/at91-gatwick.dtb
  DTC     arch/arm/boot/dts/at91-tse850-3.dtb
  DTC     arch/arm/boot/dts/at91-wb50n.dtb
  DTC     arch/arm/boot/dts/sama5d31ek.dtb
  DTC     arch/arm/boot/dts/sama5d33ek.dtb
  DTC     arch/arm/boot/dts/sama5d34ek.dtb
  DTC     arch/arm/boot/dts/sama5d35ek.dtb
  DTC     arch/arm/boot/dts/sama5d36ek.dtb
  DTC     arch/arm/boot/dts/sama5d36ek_cmp.dtb
  DTC     arch/arm/boot/dts/at91-sama5d4_ma5d4evk.dtb
  DTC     arch/arm/boot/dts/at91-sama5d4_xplained.dtb
  DTC     arch/arm/boot/dts/at91-sama5d4ek.dtb
  DTC     arch/arm/boot/dts/at91-vinco.dtb
  DTC     arch/arm/boot/dts/at91-sama7g5ek.dtb
  DTC     arch/arm/boot/dts/at91-sam9x60_curiosity.dtb

[..]
If the building process is successful, the final images can be found under arch/arm/boot/ directory.

note: if its not working goto this arch/arm/boot/dts/directory find at91-sama5d27_som1_ek.dts
copy that file and rename has a5d2x-rugged_board.dts 
paste  arch/arm/boot/dts/directory 
open vim Makefile 
arch/arm/boot/dts/directory 

add file name after this line 
dtb-$(CONFIG_SOC_SAM_V7)
a5d2x-rugged_board.dtb \
then save that file 

next open this file vi a5d2x_rugged_board.dts
change  status "disable" to "okay"

uart3: serial@fc008000 {
                                atmel,use-dma-rx;
                                atmel,use-dma-tx;
                                pinctrl-names = "default";
                                pinctrl-0 = <&pinctrl_uart3_default>;
                                status = "okay"; /* Conflict with isc. */
                                
after that give:
$ make ARCH=arm dtbs

you will find a5d2x-rugged_board.dtb file in arch/arm/boot/dts/director

use this two files and boot the board :
1) a5d2x-rugged_board.dtb
2) zImage








