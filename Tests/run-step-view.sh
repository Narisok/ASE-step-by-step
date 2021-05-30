#!/bin/bash

gcc Tests/step_view.c AES.c Build/Tests/step_view.o
echo -e "\n"
./Build/Tests/step_view.o
echo -e "\n"