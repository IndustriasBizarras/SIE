sudo rm -rf openwrt-xburst-sie-rootfs.ubifs openwrt-xburst-sie-rootfs.ubi  rootfs
mkdir rootfs
cd rootfs
sudo tar zxf ../rootfs_sie.tar.gz
cd ..
rm -rf openwrt-xburst-sie-rootfs.ubifs openwrt-xburst-sie-rootfs.ubi
sudo mkfs.ubifs -r rootfs/ -m 4096 -e 516096 -c 4095 -o openwrt-xburst-sie-rootfs.ubifs  -x zlib
sudo ubinize -o openwrt-xburst-sie-rootfs.ubi  -m 4096 -p 512KiB ubinize.cfg


