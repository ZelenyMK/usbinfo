#ifndef INFO_H
#define INFO_H

#include <libusb-1.0/libusb.h>
#include <stdint.h>

#define BUFFSIZE 512

typedef struct info {
  uint16_t vendor_ID;
  uint16_t product_ID;
  uint8_t b_class;
  uint8_t subclass;
  uint8_t protocol;
  uint8_t conf_num;
  uint8_t bus_number;
  uint8_t port_number;
  uint8_t device_address;
  int device_speed;
  char manufacturer[BUFFSIZE];
  char product[BUFFSIZE];
  char serial_number[BUFFSIZE];
} info;

void get_info(libusb_device *dev, info *i);
void show_info(info *i);

#endif  // INFO_H