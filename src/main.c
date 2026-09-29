#include <stdio.h>
#include <string.h>
#include "../header_files/constants.h"
#include "../header_files/compress.h"
#include "../header_files/decompress.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: Invalid number of arguments.\n");
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    // Flag -h
    if (strcmp(argv[1], "-h") == 0) {
        print_usage(argv[0]);
        return SUCCESS;
    }

    if (argc < 3) {
        fprintf(stderr, "Error: Missing file path argument.\n");
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    const char *flag = argv[1];
    const char *file_path = argv[2];

    int status = SUCCESS;

    if (strcmp(flag, "-c") == 0) {
        printf("Initiated compression for %s...\n", file_path);
        status = compress(file_path);

        if (status == SUCCESS) {
            printf("Successfully compressed %s.\n", file_path);
        } else {
            fprintf(stderr, "Compression failed for %s.\n", file_path);
        }

    } else if (strcmp(flag, "-d") == 0) {
        printf("Initiated decompression for %s...\n", file_path);
        status = decompress(file_path);

        if (status == SUCCESS) {
            printf("Successfully decompressed %s.\n", file_path);
        } else {
            fprintf(stderr, "Decompression failed for %s.\n", file_path);
        }

    } else {
        fprintf(stderr, "Error: Unknown flag '%s'.\n", flag);
        print_usage(argv[0]);
        return ERROR_INVALID_ARGS;
    }

    return status;
}