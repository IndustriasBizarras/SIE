#!/bin/bash
ROOTFS=openwrt-xburst-sie-rootfs.ubi
#ROOTFS=openwrt-xburst-rootfs.ubi
sudo usbboot -f ./usbboot_2gb_nand.cfg  -c "boot"
sudo usbboot -f ./usbboot_2gb_nand.cfg  -c "nprog 2048 $ROOTFS 0 0 -n"
