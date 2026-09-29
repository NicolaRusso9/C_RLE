//
// @author: Nicola Russo
// @created: 29/09/26
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../header_files/utils.h"

/**
 * Checks if a file exists at the given path safely.
 */
FILE *open_file_safe(const char *path, const char *mode) {
    FILE *file = fopen(path, mode);
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }
    return file;
}

/**
 * Checks if a file exists at the given path safely.
 */
int file_exists(const char *path) {
    if (!path) {
        fprintf(stderr, "Error: path is NULL\n");
        return 0;
    }

    // Try to open file in read mode.
    FILE *file = fopen(path, "r");

    // Check if file exist.
    if ( file ) {
        fclose(file);
        return 1;
    }

    // ENOENT is the only error that indicates that the file doesn't exist at the given path.
    if (errno != ENOENT) {
        return 1;
    }

    // File doesn't exist.
    return 0;
}

/**
 * Generates a unique output file path given an input path and target extension.
 */
char *generate_output_path(const char *input_path, const char *new_ext) {
    if (!input_path || !new_ext) {
        return NULL;
    }

    const size_t path_len = strlen(input_path);

    // Find last dot position into input path
    const char *last_dot = strrchr(input_path, '.');

    const size_t base_len = (last_dot != NULL) ? (size_t)(last_dot - input_path) : path_len;
    const size_t ext_len = strlen(new_ext);

    /* Construct candidate path: <base><new_ext> */
    const size_t buf_size = base_len + ext_len + 32; /* Buffer allocated for counter suffixes */
    char *output_path = (char *)malloc(buf_size);

    /* Check allocation memory fails and print error message */
    if (!output_path) {
        fprintf(stderr, "Error: Memory allocation failed for output path\n");
        return NULL;
    }

    snprintf(output_path, buf_size, "%.*s%s", (int)base_len, input_path, new_ext);

    /* If path doesn't exist use base path */
    if (!file_exists(output_path)) {
        return output_path;
    }

    /* Versioned suffixes (_1, _2, ...) until free filename found */
    int version = 1;
    while (1) {
        snprintf(output_path, buf_size, "%.*s_%d%s", (int)base_len, input_path, version, new_ext);
        if (!file_exists(output_path)) {
            break;
        }
        version++;
    }

    return output_path;
}