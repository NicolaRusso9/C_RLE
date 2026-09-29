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

    // Use of "wx" to ensure exclusive creation without accidental overwrites
    FILE *out = open_file_safe(output_file_name, "wx");
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
                fprintf(stderr, "Error: Failed to write character to output file.\n");
                fclose(in);
                fclose(out);
                remove(output_file_name);
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
            fprintf(stderr, "Error: Failed to write encoded pair to output file.\n");
            fclose(in);
            fclose(out);
            remove(output_file_name);
            free(output_file_name);
            return ERROR_FILE_WRITE;
        }

        current_char = next_char;
    }

    // Check if while loop end for EOF or for reading errors.
    if (ferror(in)) {
        fprintf(stderr, "Error: Read error occurred while reading '%s'.\n", input_file_name);
        fclose(in);
        fclose(out);
        remove(output_file_name);
        free(output_file_name);
        return ERROR_FILE_READ;
    }

    // Check if input file close correctly
    if (fclose(in) != 0) {
        fprintf(stderr, "Error: Failed to close input file properly.\n");
        fclose(out);
        remove(output_file_name);
        free(output_file_name);
        return ERROR_FILE_READ;
    }

    // Check if output file close correctly
    if (fclose(out) != 0) {
        fprintf(stderr, "Error: Failed to close output file properly.\n");
        remove(output_file_name);
        free(output_file_name);
        return ERROR_FILE_WRITE;
    }

    free(output_file_name);
    return SUCCESS;
}