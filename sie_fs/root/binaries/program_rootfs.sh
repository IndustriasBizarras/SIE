#!/bin/bash
ROOTFS=openwrt-xburst-qi_lb60-root.ubi
sudo usbboot -f ./usbboot_2gb_nand.cfg  -c "boot"
sudo usbboot -f ./usbboot_2gb_nand.cfg  -c "nprog 2048 $ROOTFS 0 0 -n"
