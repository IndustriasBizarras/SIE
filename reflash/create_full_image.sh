UBOOT=openwrt-xburst-u-boot.bin
KERNEL=openwrt-xburst-uImage.bin
ROOTFS=openwrt-xburst-sie-rootfs.ubi

rm -rf fullimage.bin

FILESIZE=$(stat -c%s "$UBOOT")
let COUNT=4194304-$FILESIZE

dd if=/dev/zero of=u-boot_END.img count=1 bs=$COUNT
cat $UBOOT u-boot_END.img > u-boot.img

FILESIZE=$(stat -c%s "$KERNEL")
let COUNT=4194304-$FILESIZE

dd if=/dev/zero of=kernel_END.img count=1 bs=$COUNT
cat $KERNEL kernel_END.img > kernel.img

cat u-boot.img kernel.img $ROOTFS  > fullimage.bin


rm -rf *img




