//
// @author: Nicola Russo
// @created: 30/09/26
//
#include <stdio.h>
#include <stdlib.h>
#include "../header_files/driver.h"
#include "../header_files/utils.h"
#include "../header_files/constants.h"

/**
 * Processes a file operation by opening input and output streams.
 */
int process_file_operation(const char *input_path, const char *target_ext, const stream_operation_fn stream_fn) {
    if (!input_path || !target_ext || !stream_fn) {
        return ERROR_INVALID_ARGS;
    }

    char *output_path = generate_output_path(input_path, target_ext);
    if (!output_path) {
        return ERROR_MEMORY;
    }

    FILE *in = open_file_safe(input_path, "r");
    if (!in) {
        free(output_path);
        return ERROR_FILE_OPEN;
    }

    FILE *out = open_file_safe(output_path, "wx");
    if (!out) {
        fclose(in);
        free(output_path);
        return ERROR_FILE_OPEN;
    }

    // Esegue la funzione stream-only (compress_stream o decompress_stream)
    int status = stream_fn(in, out);

    // Chiusura degli stream
    if (fclose(in) != 0 && status == SUCCESS) {
        status = ERROR_FILE_READ;
    }

    if (fclose(out) != 0 && status == SUCCESS) {
        status = ERROR_FILE_WRITE;
    }

    // --- SINGOLO PERCORSO DI CLEANUP IN CASO DI ERRORE ---
    if (status != SUCCESS) {
        remove(output_path); // Rimuove il file parziale/corrotto
    }

    free(output_path);
    return status;
}