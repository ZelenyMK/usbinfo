#include "info.h"

#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_info(libusb_device *dev, info *i) {
  struct libusb_device_descriptor descriptor;
  libusb_get_device_descriptor(dev, &descriptor);
  i->vendor_ID = descriptor.idVendor;
  i->product_ID = descriptor.idProduct;
  i->b_class = descriptor.bDeviceClass;
  i->subclass = descriptor.bDeviceSubClass;
  i->protocol = descriptor.bDeviceProtocol;
  i->conf_num = descriptor.bNumConfigurations;

  i->bus_number = libusb_get_bus_number(dev);
  i->port_number = libusb_get_port_number(dev);
  i->device_address = libusb_get_device_address(dev);
  i->device_speed = libusb_get_device_speed(dev);

  libusb_device_handle *handle;
  int open_result = libusb_open(dev, &handle);
  if (open_result == LIBUSB_ERROR_ACCESS) {
    printf(
        "Error: insufficient permissions:\nPlease rerun the program with root "
        "rights\n");
    exit(1);
  } else if (open_result < 0) {
    printf("Error opening device: %d\n", open_result);
    exit(1);
  }

  if (libusb_get_string_descriptor_ascii(handle, descriptor.iManufacturer,
                                         (unsigned char *)i->manufacturer,
                                         sizeof((i->manufacturer))) < 0) {
    strcpy(i->manufacturer, "Manufacturer not supported");
  }
  if (libusb_get_string_descriptor_ascii(handle, descriptor.iProduct,
                                         (unsigned char *)i->product,
                                         sizeof((i->product))) < 0) {
    strcpy(i->product, "Product not supported");
  }
  if (libusb_get_string_descriptor_ascii(handle, descriptor.iSerialNumber,
                                         (unsigned char *)i->serial_number,
                                         sizeof((i->serial_number))) < 0) {
    strcpy(i->serial_number, "Serial number not supported");
  }
  libusb_close(handle);
}

void show_info(info *i) {
  printf("\tBus: %03u\n", i->bus_number);
  printf("\tPort number: %u\n", i->port_number);
  printf("\tDevice address: %03u\n", i->device_address);
  printf("\tDevice speed: %d\n", i->device_speed);
  printf("\tSerial number: %s\n", i->serial_number);
  printf("\tProduct: %s\n", i->product);
  printf("\tProduct ID: %u\n", i->product_ID);
  printf("\tVendor ID: %u\n", i->vendor_ID);
  printf("\tManufacturer: %s\n", i->manufacturer);
  printf("\tDevice class: %u\n", i->b_class);
  printf("\tDevice subclass: %u\n", i->subclass);
  printf("\tDevice protocol: %u\n", i->protocol);
  printf("\tNumber of configurations: %u\n", i->conf_num);
}