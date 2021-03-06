/* hid_gadget_test */

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *filename_keyboard = NULL;
const char *filename_mouse = NULL;
int fd_keyboard = 0;
int fd_mouse = 0;

int read_keyboard_led_report()
{
	fd_set rfds;
	int rv, report_in_size, i;
	char report[12];	
	struct timeval timeout;

	FD_ZERO(&rfds);
	FD_SET(fd_keyboard, &rfds);

	timeout.tv_sec = 0;
	timeout.tv_usec = 10000;

	rv = select(fd_keyboard + 1, &rfds, NULL, NULL, &timeout);
	if (rv < 0) {
		perror("select()");
		return -1;
	}
	else if (rv == 0) {
		//printf("timeout\n");
	}
	else {
		report_in_size = read(fd_keyboard, report, sizeof(report));
		printf("recv report:");
		for (i = 0; i < report_in_size; i++)
			printf(" %02x", report[i]);
		printf("\n");
	}
	return 0;
}

int mouse_click_event(int x, int y, char buttons)
{
	int to_send;
	char report[12];

	memset(report, 0x0, sizeof(report));
	report[0] = 0x02; // mouse report ID
	to_send = 6;
    if (write(fd_mouse, report, to_send) != to_send) {
		perror(filename_mouse);
		return -1;
	}

	report[1] = buttons;
	report[2] = (char)(x & 0xff);
	report[3] = (char)((x >> 8) & 0xff);
	report[4] = (char)(y & 0xff);
	report[5] = (char)((y >> 8) & 0xff);
    if (write(fd_mouse, report, to_send) != to_send) {
		perror(filename_mouse);
		return -2;
	}

	report[1] = 0x0; // clear the buttons
    if (write(fd_mouse, report, to_send) != to_send) {
		perror(filename_mouse);
		return -3;
	}

	return to_send;
}

int key_press_event(char keycode, char modifiers)
{
	int to_send;
	char report[12];

	memset(report, 0x0, sizeof(report));
	report[0] = 0x01; // keyboard report ID
	report[1] = modifiers;
	report[3] = keycode;
	to_send = 9;
    if (write(fd_keyboard, report, to_send) != to_send) {
		perror(filename_keyboard);
		return -1;
	}	

	memset(report, 0x0, sizeof(report));
	report[0] = 0x01; // keyboard report ID
    if (write(fd_keyboard, report, to_send) != to_send) {
		perror(filename_keyboard);
		return -2;
	}

	return to_send;
}

int main(int argc, const char *argv[])
{
	char report[12];
	int to_send = 8;
	int retval, i;

	filename_keyboard = "/dev/hidg1";
	if ((fd_keyboard = open(filename_keyboard, O_RDWR, 0666)) == -1) {
		perror(filename_keyboard);
		return 1;
	}

	filename_mouse = "/dev/hidg0";
	if ((fd_mouse = open(filename_mouse, O_RDWR, 0666)) == -1) {
		perror(filename_mouse);
		return 2;
	}

	if (read_keyboard_led_report(fd_keyboard) < 0) {
		perror(filename_keyboard);
		return 3;
	}

	mouse_click_event(4000, 31553, 0x01); // left button;

	close(fd_keyboard);
	close(fd_mouse);
	return 0;
}
