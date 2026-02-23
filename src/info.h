#ifndef INFO_H
#define INFO_H

#include <libusb-1.0/libusb.h>
#include <stdint.h>

typedef struct info {
  uint8_t bus_number;
  uint8_t port_number;
  uint8_t device_address;
  int device_speed;
} info;

void get_info(libusb_device *dev, info *i);
void show_info(info *i);

#endif  // INFO_H