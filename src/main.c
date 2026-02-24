#include <errno.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>

#include "info.h"

int main(/*int argc, char *argv[]*/) {
  int rc = libusb_init_context(NULL, NULL, 0);
  if (rc < 0) {
    printf("Error: %s\n", libusb_strerror(errno));
    return rc;
  }

  libusb_device **devices;
  ssize_t count_devices = libusb_get_device_list(NULL, &devices);
  if (count_devices < 0) {
    libusb_exit(NULL);
    printf("Error: %s\n", libusb_strerror(errno));
    return (int)count_devices;
  }
    
  info *device_info = (info *)calloc(count_devices, sizeof(info));
  for (int i = 0; i < count_devices; i++) {
    get_info(devices[i], &device_info[i]);
    printf("Device %d:\n", i);
    show_info(&device_info[i]);
  }

  free(device_info);
  libusb_free_device_list(devices, 0);
  libusb_exit(NULL);
  return 0;
}