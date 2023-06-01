#!/bin/bash

GPIO_SERVER_IP="localhost"
GPIO_SERVER_PORT=9000
GPIO_SERVER_URL="http://${GPIO_SERVER_IP}:${GPIO_SERVER_PORT}/gpiorpc"
GPIO_PIN=40

CURL=$( which curl || { echo "Curl is not installed. Please install curl by running command sudo apt install curl ."; exit 1; })
JQ=$( which jq || { echo "jq is not installed. Please install jq by running command sudo apt install jq ."; exit 1; })

GPIO_VALUE=$(${CURL} -X POST ${GPIO_SERVER_URL} -H "Content-Type: application/json"\
  -d '{"jsonrpc":"2.0","reqid":'$RANDOM',"method":"gpioget","params":{"pin":'${GPIO_PIN}'}}'\
  | ${JQ} '.result')

echo "The GPIO value is ${GPIO_VALUE}"

