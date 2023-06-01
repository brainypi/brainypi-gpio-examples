import requests
import json

GPIO_SERVER_IP = "localhost"
GPIO_PIN = 40

def send_gpioget_request(server_ip, pin):
    """
    Send an HTTP POST request to control GPIO.

    This function sends an HTTP POST request to the specified URL with the provided JSON payload to control GPIO.

    :return: The response object.
    :rtype: requests.Response
    """

    url = "http://"+ server_ip +":9000/gpiorpc"
    headers = {
        "Content-Type": "application/json"
    }
    data = {
        "jsonrpc": "2.0",
        "reqid": 100,
        "method": "gpioget",
        "params": {
            "pin": pin 
        }
    }

    response = requests.post(url, headers=headers, data=json.dumps(data))
    return response


# Example usage
try:
    response = send_gpioget_request(GPIO_SERVER_IP, GPIO_PIN)
    response.raise_for_status()  # Raises an exception for unsuccessful status codes
    response_data = response.json()
    print("GPIO value is {}".format(response_data['result']))
    # Process the response data here
except requests.exceptions.RequestException as e:
    print("Error occurred during the request:", e)
except json.JSONDecodeError as e:
    print("Error occurred while decoding the response:", e)
