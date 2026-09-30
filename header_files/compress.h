//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_COMPRESS_H
#define C_Compressor_COMPRESS_H

/**
 * Compresses a text file using Run-Length Encoding (RLE).
 *
 * @param in Pointer to input stream .txt file.
 * @param out Pointer to out stream .rle file.
 * @return SUCCESS (0) or error code on failure.
 */
int compress(FILE *in, FILE *out);

#endif //C_Compressor_COMPRESS_H
