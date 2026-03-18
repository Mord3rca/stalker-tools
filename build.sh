#!/bin/bash

# Yup ... Will use CMake in the futur but for now.
# Lets just use some old and trusty BASH !
# If it survived the 90', it will survive prod

set -xeu

mkdir -p out/
gcc -Wall -g -I include/ -o out/ltx-reader lib/ltx.c lib/ltx_parser.c src/ltx-reader.c
