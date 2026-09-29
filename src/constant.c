//
// @author: Nicola Russo
// @created: 29/09/26
//
#include <stdio.h>
#include "../header_files/constants.h"

/**
 * Displays manual and standard usage options.
 */
void print_usage(const char *prog_name) {
    printf("Syntax use:\n");
    printf("Compress:   %s -c <relative_file_path.txt>\n", prog_name);
    printf("Decompress: %s -d <relative_file_path.rle>\n", prog_name);
    printf("Help:       %s -h\n", prog_name);
}