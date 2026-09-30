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
int decompress (FILE *in, FILE *out) {
    if (!in || !out) return ERROR_INVALID_ARGS;

    int ch = fgetc(in);
    while (ch != EOF) {
        if (ch == '\n' || ch == '\r') {
            if (fputc(ch, out) == EOF) {
                return ERROR_FILE_WRITE;
            }
            ch = fgetc(in);
            continue;
        }

        const char target_char = (char)ch;
        int count = 0;

        int read_status = fscanf(in, "%d", &count);
        if (read_status != 1 || count <= 0) {
            return ERROR_CORRUPT_FILE;
        }

        for (int i = 0; i < count; i++) {
            if (fputc(target_char, out) == EOF) {
                return ERROR_FILE_WRITE;
            }
        }

        ch = fgetc(in);
    }

    if (ferror(in)) {
        return ERROR_FILE_READ;
    }

    return SUCCESS;
}