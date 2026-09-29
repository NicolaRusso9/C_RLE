//
// @author: Nicola Russo
// @created: 29/09/26
//
#include <stdio.h>
#include <stdlib.h>
#include "../header_files/compress.h"
#include "../header_files/constants.h"
#include "../header_files/utils.h"

/**
 * Executes the RLE compression algorithm on a target file.
 */
int compress(const char *input_file_name) {
    if (!input_file_name) {
        return ERROR_INVALID_ARGS;
    }

    char *output_file_name = generate_output_path(input_file_name, ".rle");
    if (!output_file_name) {
        return ERROR_MEMORY;
    }

    FILE *in = open_file_safe(input_file_name, "r");
    if (!in) {
        free(output_file_name);
        return ERROR_FILE_OPEN;
    }

    FILE *out = open_file_safe(output_file_name, "w");
    if (!out) {
        fclose(in);
        free(output_file_name);
        return ERROR_FILE_OPEN;
    }

    int current_char = fgetc(in);
    while (current_char != EOF) {

        /* Preserve linebreaks without counting */
        if (current_char == '\n' || current_char == '\r') {

            if (fputc(current_char, out) == EOF) {
                fprintf(stderr, "Error writing to output file\n");
                fclose(in);
                fclose(out);
                free(output_file_name);
                return ERROR_FILE_WRITE;
            }

            current_char = fgetc(in);
            continue;
        }

        int count = 1;
        int next_char = fgetc(in);

        while (next_char != EOF && next_char == current_char) {
            count++;
            next_char = fgetc(in);
        }

        if (fprintf(out, "%c%d", current_char, count) < 0) {
            fprintf(stderr, "Error writing to output file\n");
            fclose(in);
            fclose(out);
            free(output_file_name);
            return ERROR_FILE_WRITE;
        }

        current_char = next_char;
    }

    fclose(in);
    if (fclose(out) != 0) {
        fprintf(stderr, "Error closing output file (flush failed)\n");
        free(output_file_name);
        return ERROR_FILE_WRITE;
    }

    free(output_file_name);
    return SUCCESS;
}