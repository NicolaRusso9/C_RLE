#include <stdio.h>
#include <string.h>
#include "../header_files/constants.h"
#include "../header_files/compress.h"
#include "../header_files/decompress.h"

int main(int argc, char *argv[]) {
    // If there is only one arguments, user doesn't pass flag/file
    if (argc == 1) {
        fprintf(stderr, "Error: No arguments given\n");
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    // Capturing first flag
    const char *flag = argv[1];

    // Flag -h requires exactly 2 arguments: ./fileCompressor -h
    if (strcmp(flag, "-h") == 0) {
        if (argc != 2) {
            fprintf(stderr, "Error: Invalid argument(s)\n");
            print_usage(argv[0]);
            return ERROR_INVALID_ARGS;
        }
        print_usage(argv[0]);
        return SUCCESS;
    }

    /* Flags -c and -d require exactly 3 arguments: ./fileCompressor -c <input_file> */
    if (strcmp(flag, "-c") == 0 || strcmp(flag, "-d") == 0) {
        // Flags -c and -d require exactly 3 arguments: ./fileCompressor -c <input_file>
        if (argc != 3) {
            fprintf(stderr, "Error: Invalid argument(s)\n");
            print_usage(argv[0]);
            return ERROR_INVALID_ARGS;
        }
        
        const char *file_path = argv[2];
        int status = SUCCESS;

        if (strcmp(flag, "-c") == 0) {
            printf("Initiated compressing \"%s\"...\n", file_path);
            status = compress(file_path);
            if (status == SUCCESS) {
                printf("Successfully compressed \"%s\".\n", file_path);
            } else {
                fprintf(stderr, "Compression of \"%s\" failed\n", file_path);
            }
        } else {
            printf("Initiated decompressing \"%s\"...\n", file_path);
            status = decompress(file_path);
            if (status == SUCCESS) {
                printf("Successfully decompressed \"%s\".\n", file_path);
            } else {
                fprintf(stderr, "Decompression of \"%s\" failed\n", file_path);
            }
        }
        return status;
    }

    /* Unknown flag handling */
    fprintf(stderr, "Error: Invalid argument(s)\n");
    print_usage(argv[0]);
    return ERROR_INVALID_ARGS;
}