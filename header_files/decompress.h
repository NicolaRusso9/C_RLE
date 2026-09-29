//
// @author: Nicola Russo
// @created: 29/09/26
//

#ifndef C_Compressor_DECOMPRESS_H
#define C_Compressor_DECOMPRESS_H

/**
 * Decompresses an RLE-encoded file into original text file.
 *
 * @param input_file_name Path to input .rle file.
 * @return SUCCESS (0) or error code on failure.
 */
int decompress(const char *input_file_name);

#endif //C_Compressor_DECOMPRESS_H
