//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_CONSTANTS_H
#define C_Compressor_CONSTANTS_H

/* Status and Exit Codes */
#define SUCCESS 0
#define ERROR_INVALID_ARGS 1
#define ERROR_FILE_OPEN 2
#define ERROR_FILE_CREATE 3
#define ERROR_FILE_WRITE 4
#define ERROR_MEMORY 5
#define ERROR_CORRUPT_FILE 6

/* Buffer Size */
#define BUFFER_SIZE 4096

/**
 * Prints user-friendly usage instructions to stdout.
 *
 * @param prog_name Name of the executable.
 */
void print_usage(const char *prog_name);

#endif //C_Compressor_CONSTANTS_H
