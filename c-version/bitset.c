#include "bitset.h"
#include <string.h>
#ifdef PC_DEBUG
#include <stdio.h>
#endif

bitset* bitset_alloc(size_t size) {
    bitset* b = malloc(sizeof(bitset));
    b->size = size;
    b->data = calloc(bitset_size_in_bytes(b), sizeof(uint8_t));
    return b;
}

void bitset_free(bitset* b) {
    free(b->data);
    free(b);
}

size_t bitset_size(bitset* b) {
    return b->size;
}

size_t bitset_size_in_bytes(bitset* b) {
    return (b->size + 7) / 8;
}

bool bitset_get(bitset* b, size_t index) {
    if (index >= b->size) { // out of bounds handling
        #ifdef PC_DEBUG
        printf("out of bounds, index: %lu, size: %lu\n", index, b->size);
        #endif
        return false; // bad
    }
    return (b->data[index / 8] >> (index % 8)) & 1;
}

void bitset_set(bitset* b, size_t index, bool value) {
    if (index >= b->size) { // out of bounds handling
        #ifdef PC_DEBUG
        printf("out of bounds, index: %lu, size: %lu\n", index, b->size);
        #endif
        return; // bad
    }
    if (value) {
        b->data[index / 8] |= 1 << (index % 8);
    } else {
        b->data[index / 8] &= ~(1 << (index % 8));
    }
}


bitset* bitset_from_bitstring(char* str) {
    bitset* b = bitset_alloc(strlen(str));
    for (size_t i = 0; i < b->size; i++) {
        if (str[i] == '1') {
            bitset_set(b, b->size - (i+1), true);
        }
    }
    return b;
}

// LSB first
bitset* bitset_from_bytes(uint8_t* bytes, size_t size) {
    bitset* b = bitset_alloc(size * 8);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < 8; j++) { // LSB first
            bitset_set(b, i * 8 + j, (bytes[i] >> j) & 1);
        }
    }
    return b;
}

// LSB first
void bitset_to_bytes(bitset* b, uint8_t* bytes) {
    for (size_t i = 0; i < bitset_size_in_bytes(b); i++) {
        bytes[i] = 0;
        for (size_t j = 0; j < 8; j++) { // LSB first
            bytes[i] |= bitset_get(b, i * 8 + j) << j;
        }
    }
}

void bitset_to_bitstring(bitset* b, char* str) {
    for (size_t i = 0; i < b->size; i++) {
        str[i] = bitset_get(b, b->size - (i+1)) ? '1' : '0';
    }
    str[b->size] = '\0';
}

void bitset_copy(bitset* b, bitset* dst) {
    free(dst->data);
    dst->data = calloc(bitset_size_in_bytes(b), sizeof(uint8_t));
    dst->size = b->size;
    memcpy(dst->data, b->data, bitset_size_in_bytes(b));
}

bitset* bitset_clone(bitset* b) {
    bitset* other = bitset_alloc(b->size);
    other->size = b->size;
    memcpy(other->data, b->data, bitset_size_in_bytes(b));
    return other;
}

bool bitset_eq(bitset* a, bitset* b) {
    if (a->size != b->size) {
        return false;
    }
    return memcmp(a->data, b->data, bitset_size_in_bytes(a)) == 0;
}

void bitset_reset(bitset* b) {
    memset(b->data, 0, bitset_size_in_bytes(b));
}