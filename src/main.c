#include <stdio.h>
#include <string.h>
#include "../header_files/constants.h"
#include "../header_files/utils.h"
#include "../header_files/driver.h"
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

    // Flags -c and -d require exactly 3 arguments: ./fileCompressor -FLAG <input_file>
    if (argc != 3) {
        fprintf(stderr, "Error: Invalid argument(s)\n");
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    const char *input_path = argv[2];
    int status = SUCCESS;

    if (strcmp(flag, "-c") == 0) {
        printf("Initiated compressing \"%s\" ...\n", input_path);
        status = process_file_operation(input_path, ".rle", compress);      // Set compress function pointer
    }
    else if (strcmp(flag, "-d") == 0){
        printf("Initiated decompressing \"%s\"...\n", input_path);
        status = process_file_operation(input_path, ".txt", decompress);    // Set decompress function pointer
    }
    /* Unknown flag handling */
    else {
        fprintf(stderr, "Error: Invalid argument(s)\n");
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    if (status != SUCCESS) {
        fprintf(stderr, "Operation failed with error code: %d\n", status);
    }
    else {
        fprintf(stderr, "Operation completed.");
    }

    return status;
}