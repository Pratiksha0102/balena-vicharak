IMAGE_FSTYPES += "balenaos-img"

PARTITION_TABLE_TYPE_radxa-cm3-io-rk3566 = "gpt"
PARTITION_TABLE_TYPE_rockpi-4b-rk3399 = "gpt"
PARTITION_TABLE_TYPE_rk3588-axon = "gpt"

DEVICE_SPECIFIC_SPACE_radxa-cm3-io-rk3566 = "40960"
DEVICE_SPECIFIC_SPACE_rockpi-4b-rk3399 = "40960"
DEVICE_SPECIFIC_SPACE_rk3588-axon = "40960"

# we need to increase the rootfs size
IMAGE_ROOTFS_SIZE_radxa-cm3-io-rk3566="487424"
IMAGE_ROOTFS_SIZE_radxa-zero-s905y2="487424"
IMAGE_ROOTFS_SIZE_rockpi-4b-rk3399="733184"
IMAGE_ROOTFS_SIZE_rk3588-axon="733184"
BALENA_BOOT_SIZE_rockpi-4b-rk3399="524288"
BALENA_BOOT_SIZE_rk3588-axon="524288"

IMAGE_INSTALL:append_rockpi-4b-rk3399 = " bluetooth-broadcom"

# for the Radxa CM3 add the dtb, u-boot scripts to rootfs /boot directory
IMAGE_INSTALL:append_radxa-cm3-io-rk3566 = " \
    kernel-devicetree \
    u-boot-radxa-cm3-io-scripts \
"

# add the dtb, overlays, u-boot scripts and u-boot binaries to rootfs /boot directory
IMAGE_INSTALL:append_radxa-zero-s905y2 = " \
    kernel-devicetree \
    linux-radxa-zero-overlays \
    u-boot-radxa-zero-bins \
    u-boot-radxa-zero-scripts \
"

BALENA_BOOT_PARTITION_FILES:append_radxa-zero-s905y2 = " \
    uEnv.txt:/ \
"

BALENA_BOOT_PARTITION_FILES:append_radxa-cm3-io-rk3566 = " \
    overlays/cm3-io-sata.dtbo:/overlays/cm3-io-sata.dtbo \
    overlays/radxa-cm3-io-hd101boe9365-display.dtbo:/overlays/radxa-cm3-io-hd101boe9365-display.dtbo \
    overlays/radxa-cm3-io-i2c0-hym8563.dtbo:/overlays/radxa-cm3-io-i2c0-hym8563.dtbo \
    overlays/radxa-cm3-io-radxa-10p1inch-display.dtbo:/overlays/radxa-cm3-io-radxa-10p1inch-display.dtbo \
    overlays/radxa-cm3-io-sharp-lq133t1jw01-without-hdmi.dtbo:/overlays/radxa-cm3-io-sharp-lq133t1jw01-without-hdmi.dtbo \
"

device_specific_configuration_rockpi-4b-rk3399() {
    parted -s ${BALENA_RAW_IMG} unit s mkpart loader1 64 8063
    parted -s ${BALENA_RAW_IMG} unit s mkpart loader2 16384 24575
    parted -s ${BALENA_RAW_IMG} unit s mkpart trust 24576 32767
}

IMAGE_CMD_balenaos-img:append_rockpi-4b-rk3399 () {
    dd if=${DEPLOY_DIR_IMAGE}/idbloader.bin of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=64
    dd if=${DEPLOY_DIR_IMAGE}/u-boot.img of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=16384
    dd if=${DEPLOY_DIR_IMAGE}/trust.img of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=24576
}

#device_specific_configuration_rk3588-axon() {
#    parted -s ${BALENA_RAW_IMG} unit s mkpart loader1 64 16383
#    parted -s ${BALENA_RAW_IMG} unit s mkpart loader2 16384 25599
#}

IMAGE_CMD_balenaos-img:append_rk3588-axon () {
    dd if=${DEPLOY_DIR_IMAGE}/idblock.img of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=64
    dd if=${DEPLOY_DIR_IMAGE}/uboot.img of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=16384
}

BALENA_BOOT_PARTITION_FILES:append_rk3588-axon = " \
    overlays/rk3588-axon_v0.3-i2c1.dtbo.disabled:/overlays/rk3588-axon_v0.3-i2c1.dtbo.disabled \
    overlays/rk3588-axon_v0.3-i2c2.dtbo.disabled:/overlays/rk3588-axon_v0.3-i2c2.dtbo.disabled \
    overlays/rk3588-axon_v0.3-i2c5.dtbo.disabled:/overlays/rk3588-axon_v0.3-i2c5.dtbo.disabled \
    overlays/rk3588-axon_v0.3-i2c7.dtbo.disabled:/overlays/rk3588-axon_v0.3-i2c7.dtbo.disabled \
    overlays/rk3588-axon_v0.3-pwm0.dtbo.disabled:/overlays/rk3588-axon_v0.3-pwm0.dtbo.disabled \
    overlays/rk3588-axon_v0.3-pwm1-m0.dtbo.disabled:/overlays/rk3588-axon_v0.3-pwm1-m0.dtbo.disabled \
    overlays/rk3588-axon_v0.3-pwm1-m1.dtbo.disabled:/overlays/rk3588-axon_v0.3-pwm1-m1.dtbo.disabled \
    overlays/rk3588-axon_v0.3-spi1.dtbo.disabled:/overlays/rk3588-axon_v0.3-spi1.dtbo.disabled \
    overlays/rk3588-axon_v0.3-spi1-enc28j60.dtbo.disabled:/overlays/rk3588-axon_v0.3-spi1-enc28j60.dtbo.disabled \
    overlays/rk3588-axon_v0.3-uart1.dtbo.disabled:/overlays/rk3588-axon_v0.3-uart1.dtbo.disabled \
    overlays/rk3588-axon_v0.3-uart4.dtbo.disabled:/overlays/rk3588-axon_v0.3-uart4.dtbo.disabled \
    overlays/rk3588-axon_v0.3-uart6.dtbo.disabled:/overlays/rk3588-axon_v0.3-uart6.dtbo.disabled \
"

device_specific_configuration_radxa-cm3-io-rk3566() {
    parted -s ${BALENA_RAW_IMG} unit s mkpart loader1 64 8063
    parted -s ${BALENA_RAW_IMG} unit s mkpart loader2 16384 24575
}

IMAGE_CMD_balenaos-img:append_radxa-cm3-io-rk3566 () {
    dd if=${DEPLOY_DIR_IMAGE}/idbloader.img of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=64
    dd if=${DEPLOY_DIR_IMAGE}/u-boot.itb of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=16384
}

IMAGE_CMD_balenaos-img:append_radxa-zero-s905y2 () {
    dd if=${DEPLOY_DIR_IMAGE}/u-boot.bin of=${BALENA_RAW_IMG} conv=notrunc bs=512 seek=1
}

# Ensure extlinux.conf files are deployed
do_rootfs_balenaos-img[depends] += " u-boot-rockchip:do_build "
