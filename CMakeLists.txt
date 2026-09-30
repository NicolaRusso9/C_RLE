cmake_minimum_required(VERSION 4.2)
project(C_Compressor C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Compressor src/main.c
        header_files/decompress.h
        header_files/compress.h
        header_files/utils.h
        header_files/constants.h
        src/utils.c
        src/compress.c
        src/decompress.c
        src/constant.c
        header_files/driver.h
        src/driver.c
)
