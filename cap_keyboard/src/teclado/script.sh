#!/bin/sh
xc3sprog uart_teclado.bit
insmod cap_keyboard.ko
./daemon_keyboard &
