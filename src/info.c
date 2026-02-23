#include "info.h"

#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <stdio.h>

void get_info(libusb_device *dev, info *i) {
  i->bus_number = libusb_get_bus_number(dev);
  i->port_number = libusb_get_port_number(dev);
  i->device_address = libusb_get_device_address(dev);
  i->device_speed = libusb_get_device_speed(dev);
}

void show_info(info *i) {
  printf("\tBus number: %" PRIu8 "\n", i->bus_number);
  printf("\tPort number: %" PRIu8 "\n", i->port_number);
  printf("\tDevice address: %" PRIu8 "\n", i->device_address);
  printf("\tDevice speed: %d\n", i->device_speed);
}