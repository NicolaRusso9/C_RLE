//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_DECOMPRESS_H
#define C_Compressor_DECOMPRESS_H

/**
 * Decompresses an RLE-encoded file into original text file.
 *
 * @param in Pointer to input stream .rle file.
 * @param out Pointer to out stream .txt file.
 * @return SUCCESS (0) or error code on failure.
 */
int decompress(FILE *in, FILE *out);

#endif //C_Compressor_DECOMPRESS_H
