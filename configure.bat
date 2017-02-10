@echo off

if not exist "build" mkdir build
cd build
cmake ..

echo "Copy your lib*_loader[d].dll libraries to output path"
echo "Copy your lib*_config[d].dll libraries to output/configurations path"
