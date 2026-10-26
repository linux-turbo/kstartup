#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Error: Please run this script with root privileges (sudo ./install.sh)." >&2
    exit 1
fi

echo "=== KStartup Generic Installer ==="

rm -rf build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..

echo "Compiling with 6 CPU cores..."
make -j$(nproc)

echo "Installing to system..."
make install

echo "=== Installation complete! Type 'kstartup' to launch. ==="
