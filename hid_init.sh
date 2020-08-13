#!/bin/bash

# Variables
MOUSE_DESCRIPTOR=$(pwd)/mouse_report_descriptor
KEYBOARD_DESCRIPTOR=$(pwd)/keyboard_report_descriptor

# Make sure GadgetFS ConfigFS is running
modprobe libcomposite

# Create our gadget
mkdir /sys/kernel/config/usb_gadget/g1
cd /sys/kernel/config/usb_gadget/g1

# Create the gadget folders
mkdir configs/c.1
mkdir strings/0x409
mkdir configs/c.1/strings/0x409

# Configure the gadget
echo 0x1234 > idProduct
echo 0x9999 > idVendor
echo "0123456789" > strings/0x409/serialnumber
echo "Paul Wareing" > strings/0x409/manufacturer
echo "Injector Gadget" > strings/0x409/product
echo "Config 1" > configs/c.1/strings/0x409/configuration
echo 120 > configs/c.1/MaxPower
echo 0xa0 > configs/c.1/bmAttributes

# Add the mouse function
mkdir functions/hid.usb0
echo 2 > functions/hid.usb0/protocol
echo 1 > functions/hid.usb0/subclass
echo 9 > functions/hid.usb0/report_length
cat $MOUSE_DESCRIPTOR > functions/hid.usb0/report_desc

# Add the keyboard function
mkdir functions/hid.usb1
echo 1 > functions/hid.usb1/protocol
echo 1 > functions/hid.usb1/subclass
echo 9 > functions/hid.usb1/report_length
cat $KEYBOARD_DESCRIPTOR > functions/hid.usb1/report_desc

# Install the device
ln -s functions/hid.usb0 configs/c.1
ln -s functions/hid.usb1 configs/c.1

# Enable USB Device Controller. (choose from /sys/class/udc/)
echo musb-hdrc.0 > UDC 
