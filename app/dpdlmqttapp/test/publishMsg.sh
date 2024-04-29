#!/bin/sh
echo "publishing message...."
mosquitto_pub -h 127.0.0.1 -p 1883 -t "dpdl/123/test" -m "Dpdl Hello Mqtt message_1"
echo "done"