#!/usr/bin/bash

[[ $# -ne 2 ]] && exit 1

gcc -o "$2" -march=native -masm=intel -fno-verbose-asm -S -fdiagnostics-color=always -O2 "$1"