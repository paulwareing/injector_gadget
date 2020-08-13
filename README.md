# Injector Gadget

This is a simple example showing how to set up the Beaglebone Black as a USB HID device.

It is based on ConfigFS, which in turn sets up GadgetFS, and shows how to inject USB HID reports to it's USB host.

## Setup

This project was developed on a Beaglebone Black model B running:

Linux beaglebone 4.19.94-ti-r42 #1buster SMP PREEMPT Tue Mar 31 19:38:29 UTC 2020 armv7l GNU/Linux

Rename the am335x_evm.sh file

	cd /opt/scripts/boot/
	mv am335x_evm.sh am335x_evm.sh.orig

After rebooting your bbb it will no longer present the USB mass storage or network interface peripherals to it's host.  

Make sure you are using another of the possible methods to debug your bbb, either the serial debug cable or ssh via the RJ45 ethernet connection.

Run 

	sudo ./hid_init.sh

to create the HID device.  This will set up a mouse & keyboard device.

Run

	sudo ./hid_exit.sh

to tear down the device correctly.

If the USB host is in sleep mode then run

	./wakeup.sh

to wake the USB host from sleep mode.

## Using the device

The test/ folder contains a small number of examples that show how you can programmatically inject events, mouse or keyboard, to the USB host.

These test examples were tested with a Chrome OS host.  

 - login.c - If the Chrome OS host is a at the login prompt, this example injects a mouse click over the 'login as guest' button.
 - bbc.c - If the Chrome OS host is showing the browser, as it will after logging in as guest, this example maximises the browser, clicks on the URL edit box, and injects 'bbc.co.uk' & ENTER
 - logout.c - This example injects the shortcut key combination to logout of Chrome OS.







