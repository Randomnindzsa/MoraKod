/**
 * Author: Balint
 * Date: 2023. 11. 07.
 * 
 * Rewritten by: Andruida (on 2024. 02. 24.)
 * 
 */


#include "bitset.h"
#ifdef PC_DEBUG
#include <stdio.h>
#endif
/** 
 * Epic list
 * Ezzel a kóddal generálható:
 *
 * int epic_list[256];
 * for (int i = 0; i < 16; i++) {
 *     for (int j = 0; j < 16; j++) {
 *         epic_list[16 * i + j] = i + 16 * j;
 *     }
 * }
 */
static int epic_list[256] = {
    0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240,
    1, 17, 33, 49, 65, 81, 97, 113, 129, 145, 161, 177, 193, 209, 225, 241,
    2, 18, 34, 50, 66, 82, 98, 114, 130, 146, 162, 178, 194, 210, 226, 242,
    3, 19, 35, 51, 67, 83, 99, 115, 131, 147, 163, 179, 195, 211, 227, 243,
    4, 20, 36, 52, 68, 84, 100, 116, 132, 148, 164, 180, 196, 212, 228, 244,
    5, 21, 37, 53, 69, 85, 101, 117, 133, 149, 165, 181, 197, 213, 229, 245,
    6, 22, 38, 54, 70, 86, 102, 118, 134, 150, 166, 182, 198, 214, 230, 246,
    7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183, 199, 215, 231, 247,
    8, 24, 40, 56, 72, 88, 104, 120, 136, 152, 168, 184, 200, 216, 232, 248,
    9, 25, 41, 57, 73, 89, 105, 121, 137, 153, 169, 185, 201, 217, 233, 249,
    10, 26, 42, 58, 74, 90, 106, 122, 138, 154, 170, 186, 202, 218, 234, 250,
    11, 27, 43, 59, 75, 91, 107, 123, 139, 155, 171, 187, 203, 219, 235, 251,
    12, 28, 44, 60, 76, 92, 108, 124, 140, 156, 172, 188, 204, 220, 236, 252,
    13, 29, 45, 61, 77, 93, 109, 125, 141, 157, 173, 189, 205, 221, 237, 253,
    14, 30, 46, 62, 78, 94, 110, 126, 142, 158, 174, 190, 206, 222, 238, 254,
    15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 255};

/**
 * Így generálható:
 * A kodolo_javitas függvényben kap értéket.
 *
 * bitset<64>all_chunks = 0b0000000100100100100000110110110010101001010111101101101101111111;
 *
 * bitset<112>beszorzott_chunks;
 *
 * bitset<4> tmp_eredmeny;
 * bitset<7> tmp_append;
 * unsigned index = 0;
 * unsigned szorzott_index = 0;
 *
 * for(int i = 0; i < 64; i++){
 *     tmp_eredmeny[index] = all_chunks[i];
 *     cout << "Az index: " << index << "az [i] darab " << all_chunks[i] << endl;
 *     if(index == 3){
 *         cout << tmp_eredmeny << endl;
 *         cout << i << endl;
 *         tmp_append = kodolo_matrix(tmp_eredmeny);
 *         cout << tmp_append << endl;
 *         for(int j = 0; j < 7; j++){
 *             beszorzott_chunks[szorzott_index] = tmp_append[j];
 *             szorzott_index++;
 *         }
 *         index = -1;
 *     }
 *     index++;
 * }
 */
static bitset(112) *kod_szavak = NULL;

void kodolo_free() {
    if (kod_szavak != NULL) {
        bitset_free(kod_szavak);
    }
}

/**
 * elvégzi a mátrixszorzást Hammming-kód generátormátrixával
 * @param c_chunk a 4 bites chunk
 * @param kodolt a 7 bites kódolt chunk
 */
void kodolo_matrix(bitset(4) * c_chunk, bitset(7) * kodolt)
{

    for (int i = 0; i < 4; i++)
    {
        bitset_set(kodolt, i + 3, bitset_get(c_chunk, i));
    }

    /**
     * e: 1110
     * f: 1101
     * g: 0111
     */

    // e:
    bitset_set(kodolt, 2, bitset_get(c_chunk, 3) ^ bitset_get(c_chunk, 2) ^ bitset_get(c_chunk, 1));

    // f:
    bitset_set(kodolt, 1, bitset_get(c_chunk, 3) ^ bitset_get(c_chunk, 2) ^ bitset_get(c_chunk, 0));

    // g:
    bitset_set(kodolt, 0, bitset_get(c_chunk, 2) ^ bitset_get(c_chunk, 1) ^ bitset_get(c_chunk, 0));
}

/**
 * Bekéri az eredeti 144-es bitsort és visszadja a 256-os kódolt bitsort
 * @param bit_in a 144 bites bemeneti bitsor
 * @param bit_out a 256 bites kódolt kimeneti bitsor
 */
void kodolo_encode(bitset(144) * bit_in, bitset(256) * bit_out)
{

    bitset *_bit_out = bitset_alloc(256);

    bitset_set(_bit_out, 255, true);
    bitset_set(_bit_out, 254, true);
    bitset_set(_bit_out, 253, true);
    bitset_set(_bit_out, 252, true);

    bitset(4) *current_chunk = bitset_alloc(4);
    unsigned chunk_index = 0;
    unsigned bit_out_index = 0;

    for (int i = 0; i < 144; i++)
    {

        bitset_set(current_chunk, chunk_index++, bitset_get(bit_in, i));

        if (chunk_index == 4)
        {
            bitset(7) *kodolt = bitset_alloc(7);
            kodolo_matrix(current_chunk, kodolt);
            for (int j = 0; j < 7; j++)
            {
                bitset_set(_bit_out, bit_out_index, bitset_get(kodolt, j));
                bit_out_index++;
            }
            chunk_index = 0;
            bitset_free(kodolt);
        }
    }

    bitset_free(current_chunk);

    // ez a rész alakítja át a bitsort továbbítandó alakra.
    for (unsigned int i = 0; i < 256; i++)
    {
        bitset_set(bit_out, i, bitset_get(_bit_out, epic_list[i]));
    }
    bitset_free(_bit_out);
}

void kodolo_javitas(bitset(7) * c_bit, bitset(7) * res_bit)
{
    if (kod_szavak == NULL)
    {
        kod_szavak = bitset_from_bitstring(
            "0000000000101100101010100111100011000111100110010110000110100111001101010110011101001101010101100001110011111111");
    }

    // a különbség az adott bitsortól
    unsigned diff = 8;

    // leghansonlóbb chunk kezdő indexe
    unsigned k_index = 0;

    // hogy 7-esével legyenek vizsgálva chunkok
    unsigned chunk_index = 0;

    // a jelenleg vizsgált bitsor különbsége az adott bitsortól
    unsigned c_diff = 0;

    for (int i = 0; i < 112; i++)
    {
        if (bitset_get(c_bit, chunk_index) != bitset_get(kod_szavak, i))
        {
            c_diff++;
        }
        chunk_index++;

        if (chunk_index == 7)
        {
            if (c_diff == 0)
            {
                bitset_copy(c_bit, res_bit);
                return;
            }

            if (c_diff < diff)
            {
                diff = c_diff;
                k_index = i - 6;
            }
            c_diff = 0;
            chunk_index = 0;
        }
    }

    unsigned index = 0;
    for (unsigned int i = k_index; i < k_index + 7; i++)
    {
        bitset_set(res_bit, index++, bitset_get(kod_szavak, i));
    }

    return;
}

/**
 * Bekéri a 256-os kódolt bitsort és visszadja a 144-es eredeti/javított bitsort
 * @param bit_in a 256 bites kódolt bemeneti bitsor
 * @param res_bit a 144 bites eredeti kimeneti bitsor
 * @return bool sikeres volt-e a javítás
 */
void kodolo_decode(bitset(256) * bit_in, bitset(144) * res_bit)
{
    bitset(256) *un_bit = bitset_alloc(256);

    for (unsigned i = 0; i < 256; i++)
    {
        bitset_set(un_bit, i, bitset_get(bit_in, epic_list[i]));
    }

    unsigned chunk_index = 0;
    unsigned res_bit_index = 0;
    bitset(7) *javitando = bitset_alloc(7);
    bitset(7) *javitott = bitset_alloc(7);

    for (int i = 0; i < 252; i++)
    {
        bitset_set(javitando, chunk_index, bitset_get(un_bit, i));
        chunk_index++;

        if (chunk_index == 7)
        {

            kodolo_javitas(javitando, javitott);

            chunk_index = 0;
            for (int j = 3; j < 7; j++)
            {
                bitset_set(res_bit, res_bit_index, bitset_get(javitott, j));
                res_bit_index++;
            }
        }
    }

    bitset_free(javitando);
    bitset_free(javitott);
    bitset_free(un_bit);
}

/**
 * Bekéri a kódolandó adatsort és hibajavított és kódolt adatsort.
 * @param bytes_in a kódolandó adatsor (18 bájt)
 * @param bytes_out a kódolt adatsor (32 bájt)
*/
void kodolo_encode_bytes(uint8_t* bytes_in, uint8_t* bytes_out)
{
    bitset(144) *bit_in = bitset_from_bytes(bytes_in, 18);
    bitset(256) *bit_out = bitset_alloc(256);

    kodolo_encode(bit_in, bit_out);

    bitset_to_bytes(bit_out, bytes_out);

    bitset_free(bit_in);
    bitset_free(bit_out);

}

/**
 * Bekéri a kódolt adatsort és visszadja az eredeti/javított adatot.
 * @param bytes_in a fogadott (sérült) adatsor (32 bájt)
 * @param bytes_out a javított adatsor (18 bájt)
 */
void kodolo_decode_bytes(uint8_t* bytes_in, uint8_t* bytes_out) {
    bitset(256) *bit_in = bitset_from_bytes(bytes_in, 32);
    bitset(144) *bit_out = bitset_alloc(144);

    kodolo_decode(bit_in, bit_out);

    bitset_to_bytes(bit_out, bytes_out);

    bitset_free(bit_in);
    bitset_free(bit_out);
}