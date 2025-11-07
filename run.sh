#!/bin/bash

if [ ! -f "./build/main" ]; then
    echo "Executable not found. Running build script first."
    ./build_and_test.sh
fi

./build/main