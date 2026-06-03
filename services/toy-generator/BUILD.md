Build instructions for the watermark tool

Quick g++ compile (if you prefer a single-file compile):

    g++ -std=c++11 watermark.cpp -o watermark `pkg-config --cflags --libs opencv4`

CMake-based build (recommended):

    mkdir -p build && cd build
    cmake ..
    cmake --build .

Usage:

    ./watermark <path_to_image>

The resulting file will be written as watermarked_<original_filename> in the same directory.
