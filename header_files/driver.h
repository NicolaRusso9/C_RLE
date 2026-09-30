//
// @author: Nicola Russo
// @created: 30/09/26
//

#ifndef C_COMPRESSOR_DRIVER_H
#define C_COMPRESSOR_DRIVER_H
#include <stdio.h>

typedef int (*stream_operation_fn)(FILE *in, FILE *out);

/**
 * Processes a file operation by opening input and output streams.
 *
 * @param input_path The input path from user params in cli.
 * @param target_ext Target extension (txt or rle)
 * @param stream_fn Pointer to the stream processing callback function
 * @return SUCCESS (0) on successful processing and closing of files,
 *         or an error status code indicating the failure reason.
 */
int process_file_operation(const char *input_path, const char *target_ext, stream_operation_fn stream_fn);

#endif //C_COMPRESSOR_DRIVER_H
