//
// @author: Nicola Russo
// @created: 29/09/26
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../header_files/decompress.h"
#include "../header_files/constants.h"
#include "../header_files/utils.h"

/**
 * Decompresses an RLE-encoded file into original text file.
 */
int decompress(const char *input_file_name) {
    if (!input_file_name) {
        return ERROR_INVALID_ARGS;
    }

    char *output_file_name = generate_output_path(input_file_name, ".txt");
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

    int ch = fgetc(in);
    while (ch != EOF) {

        if (ch == '\n' || ch == '\r') {

            if (fputc(ch, out) == EOF) {
                fprintf(stderr, "Error: Failed to write newline character.\n");
                fclose(in);
                fclose(out);
                remove(output_file_name);
                free(output_file_name);
                return ERROR_FILE_WRITE;
            }

            ch = fgetc(in);
            continue;
        }

        const char target_char = (char)ch;
        int count = 0;

        int read_status = fscanf(in, "%d", &count);
        if (read_status != 1 || count <= 0) {
            fprintf(stderr, "Error: Corrupted or invalid compressed format in '%s'.\n", input_file_name);
            fclose(in);
            fclose(out);
            remove(output_file_name);
            free(output_file_name);
            return ERROR_CORRUPT_FILE;
        }

        for (int i = 0; i < count; i++) {
            if (fputc(target_char, out) == EOF) {
                fprintf(stderr, "Error: Failed to write decompressed sequence.\n");
                fclose(in);
                fclose(out);
                remove(output_file_name);
                free(output_file_name);
                return ERROR_FILE_WRITE;
            }
        }

        ch = fgetc(in);
    }

    // Check error on input stream.
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