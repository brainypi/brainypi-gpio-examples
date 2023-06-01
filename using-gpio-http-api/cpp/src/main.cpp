/**
 * @file main.cpp
 * @brief Example C++ program to set GPIO using HTTP API.
 */

#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include "gpioapi.h"

#define BRAINYPI_IP "localhost"

int main() {
  uint8_t value;

  if(setGpio(BRAINYPI_IP, 38, false) < 0) {
    std::cerr << "Failed to set pin" << std::endl;
    return -1;
  }
  if(getGpio(BRAINYPI_IP, 40, value) < 0) {
    std::cerr << "Failed to set pin" << std::endl;
    return -1;
  }

  return 0;
}
