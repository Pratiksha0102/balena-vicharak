include balena-image.inc

BALENA_BOOT_PARTITION_FILES:append_rockpi-4b-rk3399 = " \
    extlinux/extlinux.conf_flasher:/extlinux/extlinux.conf \
    rk3399-vaaman-linux.dtb:/ \
    ${KERNEL_IMAGETYPE}${KERNEL_INITRAMFS}-${MACHINE}.bin:/${KERNEL_IMAGETYPE} \
"

BALENA_BOOT_PARTITION_FILES:append_rk3588-axon = " \
    extlinux/extlinux.conf_flasher:/extlinux/extlinux.conf \
    rk3588-axon-linux.dtb:/ \
    ${KERNEL_IMAGETYPE}${KERNEL_INITRAMFS}-${MACHINE}.bin:/${KERNEL_IMAGETYPE} \
"
