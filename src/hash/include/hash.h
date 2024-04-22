#ifndef HASHPIPE_HASH_H
#define HASHPIPE_HASH_H

/**
 * Function that calculates LSB (Last Significant Bits) using a depth to select the number of bits
 * @param key
 * @param depth
 * @return Integer representing LSB
 */
unsigned long
hash_function (unsigned short int key, unsigned short int depth);

#endif //HASHPIPE_HASH_H
