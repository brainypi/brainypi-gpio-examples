/**
 * @file gpioapi.h
 * @brief Header file for Core functions which use HTTP API to manipulate GPIO.
 */

#include <iostream>
#include <curl/curl.h>
#include <cstring>

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

/**
 * @brief Function to set gpio.
 *
 * @param[in] ip IP address of the BrainyPi.
 * @param[in] pin Pin number to be set.
 * @param[in] value Value to be set.
 * @return 0 if the program executed successfully, -ve on error.
 */
extern int setGpio(const std::string ip, const uint8_t pin, const bool value); 
/**
 * @brief Function to get gpio value.
 *
 * @param[in] ip IP address of the BrainyPi.
 * @param[in] pin Pin number.
 * @param[out] value Value of the gpio pin.
 * @return 0 if the program executed successfully, -ve on error.
 */
extern int getGpio(const std::string ip, const uint8_t pin, uint8_t &value); 
