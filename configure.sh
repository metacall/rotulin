#!/bin/sh

mkdir -p build
cd build
cmake ..
make

echo
echo

echo "Copy your lib*_loader[d].so libraries to output path"
echo "Copy your lib*_config[d].so libraries to output/configurations path"
