FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit resin-u-boot
RPROVIDES_${PN}-scripts += "u-boot-rockchip-scripts"

# create extlinux.conf for the internal image
UBOOT_EXTLINUX = "1"
UBOOT_EXTLINUX_KERNEL_IMAGE = "/boot/Image"
UBOOT_EXTLINUX_CONSOLE = "1500000n8"
UBOOT_EXTLINUX_ROOT = "${resin_kernel_root}"
UBOOT_EXTLINUX_KERNEL_ARGS_append = " rootfstype=ext4"
UBOOT_EXTLINUX_FDT = "/boot/rk3588-axon-linux.dtb"

BALENA_BOOT_PART_rk3588-axon = "1"
BALENA_DEFAULT_ROOT_PART_rk3588-axon = "2"

SRC_URI += " \
    file://0001-Integrate-with-Balena-u-boot-environment.patch; \
    file://0002-Integrate-with-Balena-u-boot-environment-rk3588-axon.patch; \
    file://0003-fs-fat-fix-wrong-casting-to-unsigned-value-of-sect.patch; \
    file://balenaos_bootcommand.cfg; \
    file://increase_env_size.cfg; \
"

# avoid compile error while buildingin Jenkins: [Errno 11] write could not complete without blockingERROR: Task (/work/build/../layers/meta-radxa/recipes-bsp/u-boot/u-boot-radxa-cm3-io.bb:do_compile) failed with exit code '1'
# ref: https://www.yoctoproject.org/irc/%23yocto.2020-09-16.log.html and https://stackoverflow.com/questions/54185874/logging-chokes-on-blockingioerror-write-could-not-complete-without-blocking
EXTRA_OEMAKE += " > /dev/null 2>&1"

# Ensure this isn't re-used from sstate
do_deploy[nostamp] = "1"

do_deploy_append() {

    KERNEL_CMDLINE_ARGS_FLASHER="console=tty1 console=ttyFIQ0,1500000n8 rw root=LABEL=flash-rootA rootfstype=ext4 rootwait flasher"

    # Create extlinux config file for flasher image
    mkdir -p ${DEPLOY_DIR_IMAGE}/extlinux || true
    cat >${DEPLOY_DIR_IMAGE}/extlinux/extlinux.conf_flasher <<EOF
default BalenaOS

label balenaOS
    kernel /${KERNEL_IMAGETYPE}

    devicetree /$(echo "${KERNEL_DEVICETREE}" | cut -d '/' -f 2)
    append ${KERNEL_CMDLINE_ARGS_FLASHER}
EOF

}

PACKAGE_BEFORE_PN += "${PN}-scripts"
FILES_${PN}-scripts = " \
	/boot/extlinux/extlinux.conf \
"
