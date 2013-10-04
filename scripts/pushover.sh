#!/bin/bash

input=`cat`
dir=`dirname $0`
properties=$dir/pushover.properties

if [ -f $properties ]; then
   . $properties
   message=`echo "$input" | grep "Total number of tests run"`
   curl -s \
      -F "token=$APP_TOKEN" \
      -F "user=$USER_KEY" \
      -F "message=$message" \
      https://api.pushover.net/1/messages.json > pushover.log
fi

echo "$input"
