#!/bin/bash

cd /sys/kernel/config/usb_gadget/g1

# Disable the gadget
echo "" > UDC

# Remove the functions from the configs
rm configs/c.1/hid.usb0
rm configs/c.1/hid.usb1

# Remove the string directories in configs
rmdir configs/c.1/strings/0x409

# Remove the configs
rmdir configs/c.1

# Remove functions
rmdir functions/hid.usb0
rmdir functions/hid.usb1

# Remove string directories in the gadget
rmdir strings/0x409

# Remove the gadget
cd ..
rmdir g1

# Unload modules
rmmod usb_f_hid
rmmod libcomposite






