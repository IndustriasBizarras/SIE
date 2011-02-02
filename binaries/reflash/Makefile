#
# Written 2010, by Xiangfu Liu.
#

LOADER       = openwrt-xburst-qi_lb60-u-boot.bin
KERNEL       = openwrt-xburst-qi_lb60-uImage.bin
ROOTFS_UBI   = openwrt-xburst-qi_lb60-root.ubi
ROOTFS_UBIFS = openwrt-xburst-qi_lb60-root.ubifs
ROOTFS_TGZ   = openwrt-xburst-qi_lb60-rootfs.tar.gz

QI_IMAGE_URL=http://downloads.qi-hardware.com/software/images/Ben_NanoNote_2GB_NAND/latest/
QI_MIRKO_URL=http://downloads.qi-hardware.com/people/mirko/testing/

DL=$(if $(wildcard ../dl/.),../dl,dl)

.PHONY:	all clean reflash_rootfs reflash_kernel reflash_uboot

all: reflash_rootfs reflash_kernel reflash_uboot

$(DL)/$(ROOTFS_TGZ).ok:
	mkdir -p dl
	wget -c -O $(DL)/$(ROOTFS) $(QI_IMAGE_URL)/$(ROOTFS_TGZ)
	touch $@

$(DL)/$(KERNEL).ok:
	mkdir -p dl
	wget -c -O $(DL)/$(KERNEL) $(QI_MIRKO_URL)/$(KERNEL)
	touch $@

$(DL)/$(LOADER).ok:
	mkdir -p dl
	wget -c -O $(DL)/$(LOADER) $(QI_MIRKO_URL)/$(LOADER)
	touch $@

create_rootfs: $(DL)/$(ROOTFS_TGZ).ok
	mkdir -p $(DL)/rootfs_tmp
	tar xvf $(DL)/$(ROOTFS_TGZ) -C $(DL)/rootfs_tmp/
	cp -rf ../sie_rootfs_files/*   $(DL)/rootfs_tmp/
	mkfs.ubifs -r $(DL)/rootfs_tmp/ -m 4096 -e 516096 -c 4095 -o $(ROOTFS_UBIFS)
	ubinize -o $(ROOTFS_UBI) -m 4096 -p 512KiB ubinize.cfg
	touch $@

reflash_rootfs: create_rootfs
	sudo usbboot -f ./usbboot_2gb_nand.cfg -c "boot;nerase 16 512 0 0;nprog 2048 $(DL)/$(ROOTFS_UBI) 0 0 -n" 

reflash_kernel: $(DL)/$(KERNEL).ok
	sudo usbboot -f ./usbboot_2gb_nand.cfg -c "boot;nprog 1024 $(DL)/$(KERNEL) 0 0 -n" 

reflash_uboot: $(DL)/$(LOADER).ok
	sudo usbboot -f ./usbboot_2gb_nand.cfg -c "boot;nprog 0 $(DL)/$(LOADER) 0 0 -n" 

clean:
	rm -rf $(DL)
	rm -rf $(ROOTFS_UBI) $(ROOTFS_UBIFS)
	rm -rf create_rootfs
