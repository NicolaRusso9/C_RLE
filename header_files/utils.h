//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_UTILS_H
#define C_Compressor_UTILS_H
#include <stdio.h>

/**
 * Safely opens a file and logs an error message if opening fails.
 *
 * @param path Path to the file.
 * @param mode Mode string passed to fopen.
 * @return Pointer to FILE, or NULL on failure.
 */
FILE *open_file_safe(const char *path, const char *mode);

/**
 * Generates a unique output file path given an input path and target extension.
 *
 * @param input_path Source relative or absolute file path.
 * @param new_ext Target extension (".rle" or ".txt").
 * @return Heap-allocated string with unique path, or NULL on memory error.
 */
char *generate_output_path(const char *input_path, const char *new_ext);

/**
 * Checks if a file exists at the given path.
 *
 * @param path Path to check.
 * @return 1 if exists, 0 otherwise.
 */
int file_exists(const char *path);

#endif //C_Compressor_UTILS_H
