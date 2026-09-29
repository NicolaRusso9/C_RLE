//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_COMPRESS_H
#define C_Compressor_COMPRESS_H

/**
 * Compresses a text file using Run-Length Encoding (RLE).
 *
 * @param input_file_name Path to input .txt file.
 * @return SUCCESS (0) or error code on failure.
 */
int compress(const char *input_file_name);

#endif //C_Compressor_COMPRESS_H
