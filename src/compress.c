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
int compress (FILE *in, FILE *out) {
    if (!in || !out) {
        return ERROR_INVALID_ARGS;
    }

    int current_char = fgetc(in);
    while (current_char != EOF) {
        if (current_char == '\n' || current_char == '\r') {
            if (fputc(current_char, out) == EOF) {
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
            return ERROR_FILE_WRITE;
        }

        current_char = next_char;
    }

    if (ferror(in)) {
        return ERROR_FILE_READ;
    }

    return SUCCESS;
}