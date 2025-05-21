FILESEXTRAPATHS:append := ":${THISDIR}/files"

HOSTAPP_HOOKS += "99-resin-uboot"

HOSTAPP_HOOKS:append_rockpi-4b-rk3399 = " \
    99-flash-bootloader \
"

HOSTAPP_HOOKS:append_rk3588-axon = " \
    99-flash-bootloader-rk3588-axon \
"

HOSTAPP_HOOKS:append_radxa-cm3-io-rk3566 = " \
    99-flash-bootloader-radxa-cm3-io-rk3566 \
"

HOSTAPP_HOOKS:append_radxa-zero-s905y2 = " \
    99-flash-bootloader-radxa-zero-s905y2 \
"
