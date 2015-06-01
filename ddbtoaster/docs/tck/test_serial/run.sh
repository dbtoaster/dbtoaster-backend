#!/bin/sh

gcc -shared -Isrc/include src/serial.c -o target/scala-2.10/classes/serial/NodeIOImpl.jnilib
scala -cp target/scala-2.10/classes serial.SerialTest

