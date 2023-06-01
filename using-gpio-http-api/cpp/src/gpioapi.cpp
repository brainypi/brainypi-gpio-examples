/**
 * @file gpioapi.cpp
 * @brief Core functions which use HTTP API to manipulate GPIO.
 */

#include <iostream>
#include <curl/curl.h>
#include <cstring>

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"


/**
 * @brief Converts bool to string.
 *
 * @param[in] b boolean value.
 * @return true or false string.
 */
inline const std::string BoolToString(bool b) {
  return b ? "true" : "false";
}

/**
 * @brief Callback function to write response data.
 *
 * This function is used as a callback by libcurl to handle the received response data.
 *
 * @param[in] contents Pointer to the received data buffer.
 * @param[in] size Size of each element in the buffer.
 * @param[in] nmemb Number of elements in the buffer.
 * @param[in,out] response Pointer to a std::string object to store the response data.
 * @return The total number of bytes written to the response string.
 */
size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* response) {
  size_t totalSize = size * nmemb;
  response->append(contents, totalSize);
  return totalSize;
}

/**
 * @brief Function to set gpio.
 *
 * @param[in] ip IP address of the BrainyPi.
 * @param[in] pin Pin number to be set.
 * @param[in] value Value to be set.
 * @return 0 if the program executed successfully, -ve on error.
 */
int setGpio(const std::string ip, const uint8_t pin, const bool value) {
  CURL* curl;
  CURLcode res;
  int ret = 0;

  std::string url = "http://" + ip + ":9000/gpiorpc";
  std::string payload = "{\"jsonrpc\":\"2.0\",\"reqid\":100,\"method\":\"gpioset\",\"params\":{\"pin\":"+ std::to_string(pin) + ",\"value\":" + BoolToString(value) + "}}";

  // Initialize curl
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (curl) {
    // Set the URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

    // Set the content type header
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set response data callback
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the POST request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
      ret = -1;
    } else {
      // Process the response
      rapidjson::Document respJson;
      respJson.Parse(response.c_str());
      if (!respJson.HasMember("result")){
        ret = -2;
        std::cout << "Response: " << response << std::endl;
      } else {      
        std::cout << "Response: " << response << std::endl;
      }
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
  }

  // Cleanup global curl resources
  curl_global_cleanup();

  return ret;
}
/**
 * @brief Function to get gpio value.
 *
 * @param[in] ip IP address of the BrainyPi.
 * @param[in] pin Pin number.
 * @param[out] value Value of the gpio pin.
 * @return 0 if the program executed successfully, -ve on error.
 */
int getGpio(const std::string ip, const uint8_t pin, uint8_t &value) {
  CURL* curl;
  CURLcode res;
  int ret = 0;

  std::string url = "http://" + ip + ":9000/gpiorpc";
  std::string payload = "{\"jsonrpc\":\"2.0\",\"reqid\":100,\"method\":\"gpioget\",\"params\":{\"pin\":"+ std::to_string(pin) + "}}";

  // Initialize curl
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (curl) {
    // Set the URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

    // Set the content type header
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set response data callback
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the POST request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
      ret = -1;
    } else {
      // Process the response
      rapidjson::Document respJson;
      respJson.Parse(response.c_str());
      if (!respJson.HasMember("result")){
        ret = -2;
        std::cout << "Response: " << response << std::endl;
      } else {      
        value = respJson["result"].GetInt();
        std::cout << "Value: "<< (int)value << std::endl;
      }
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
  }

  // Cleanup global curl resources
  curl_global_cleanup();

  return ret;
}
