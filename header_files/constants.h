//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_CONSTANTS_H
#define C_Compressor_CONSTANTS_H

/* General status and exit codes */
#define SUCCESS            0
#define ERROR_INVALID_ARGS 1

/* File error */
#define ERROR_CORRUPT_FILE 10
#define ERROR_FILE_OPEN    11
#define ERROR_FILE_CREATE  12
#define ERROR_FILE_WRITE   13
#define ERROR_FILE_READ    14

/* Memory error */
#define ERROR_MEMORY       20

/* Buffer Size */
#define BUFFER_SIZE      4096

/* Max loop to find file name */
#define MAX_VERSIONS     1000

#endif //C_Compressor_CONSTANTS_H
