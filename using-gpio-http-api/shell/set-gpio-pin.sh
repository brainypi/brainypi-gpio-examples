#!/bin/bash

GPIO_SERVER_IP="localhost"
GPIO_SERVER_PORT=9000
GPIO_SERVER_URL="http://${GPIO_SERVER_IP}:${GPIO_SERVER_PORT}/gpiorpc"
GPIO_PIN=38
GPIO_VALUE=true

CURL=$( which curl || { echo "Curl is not installed. Please install curl by running command sudo apt install curl ."; exit 1; })
JQ=$( which jq || { echo "jq is not installed. Please install jq by running command sudo apt install jq ."; exit 1; })

${CURL} -X POST ${GPIO_SERVER_URL} -H "Content-Type: application/json"\
  -d '{"jsonrpc":"2.0","reqid":'$RANDOM',"method":"gpioset","params":{"pin":'${GPIO_PIN}',"value":'${GPIO_VALUE}'}}' 
