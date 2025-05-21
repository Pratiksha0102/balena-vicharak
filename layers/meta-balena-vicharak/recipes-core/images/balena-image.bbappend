include balena-image.inc

BALENA_BOOT_PARTITION_FILES:append_rockpi-4b-rk3399 = " \
    idbloader.bin:/ \
    u-boot.img:/ \
    trust.img:/ \
"


BALENA_BOOT_PARTITION_FILES:append_rk3588-axon = " \
    idblock.img:/ \
    uboot.img:/ \
"

# for the Rock Pi 4 add the dtb, extlinux.conf, overlays to rootfs /boot directory
IMAGE_INSTALL:append_rockpi-4b-rk3399 = " \
    kernel-devicetree \
    u-boot-rockpi-4-scripts \
"

IMAGE_INSTALL:append_rk3588-axon = " \
    kernel-devicetree \
    u-boot-rockchip-scripts \
    linux-rockchip-overlays \
"
