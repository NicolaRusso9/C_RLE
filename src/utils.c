//
// @author: Nicola Russo
// @created: 29/09/26
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../header_files/utils.h"
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

/**
 * Checks if a file exists at the given path safely.
 */
FILE *open_file_safe(const char *path, const char *mode) {
    FILE *file = fopen(path, mode);
    if (!file) {
        fprintf(stderr, "Error opening file '%s': %s\n", path, strerror(errno));
    }
    return file;
}

/**
 * Checks if a file exists at the given path safely.
 */
int file_exists(const char *path) {
    if (!path) {
        //fprintf(stderr, "Error: path is NULL\n");
        return 0;
    }

    // Try to open file in read mode.
    FILE *file = fopen(path, "r");

    // Check if file exist.
    if ( file ) {
        fclose(file);
        return 1;
    }

    // File doesn't exist or not accessible.
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
    const char *last_dot = find_extension_dot(input_path);

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
    for (int version = 1; version <= MAX_VERSIONS; version++) {
        snprintf(output_path, buf_size, "%.*s_%d%s", (int)base_len, input_path, version, new_ext);
        if (!file_exists(output_path)) {
            return output_path;
        }
    }

    fprintf(stderr, "Error: Exceeded maximum file version limit (%d)\n", MAX_VERSIONS);
    free(output_path);
    return NULL;
}

/**
 * Find last dot (.) after last path separator ('/' o '\').
 */
static const char *find_extension_dot(const char *path) {
    if (!path) {
        return NULL;
    }

    const char *last_slash = strrchr(path, '/');
    const char *last_backslash = strrchr(path, '\\');

    const char *filename_start = path;

    if (last_slash && last_slash >= filename_start) {
        filename_start = last_slash + 1;
    }

    if (last_backslash && last_backslash >= filename_start) {
        filename_start = last_backslash + 1;
    }

    return strrchr(filename_start, '.');
}