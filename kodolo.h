//
// Created by balint on 2023. 11. 07..
//

#ifndef UNTITLED3_KODOLO_H
#define UNTITLED3_KODOLO_H
#include <iostream>
#include <bitset>

using namespace std;

class Kodolo {
public:
    Kodolo(){}
// elvégzi a mátrixszorzást Hammming-kód generátormátrixával
    bitset<7> matrix(bitset<4> &c_chunk) {

        bitset<7> kodolt;

        for (int i = 0; i < 4; i++) {
            kodolt[i + 3] = c_chunk[i];
        }

        /*
         * e: 1110
         * f: 1101
         * g: 0111
         */

        // e:
        kodolt[2] = (c_chunk[3] & 1) ^ (c_chunk[2] & 1) ^ (c_chunk[1] & 1);

        // f:
        kodolt[1] = (c_chunk[3] & 1) ^ (c_chunk[2] & 1) ^ (c_chunk[0] & 1);

        // g:
        kodolt[0] = (c_chunk[2] & 1) ^ (c_chunk[1] & 1) ^ (c_chunk[0] & 1);

        return kodolt;
    }

// megtalálja a bit indexét a 256-os bitsorban.
    unsigned index_finder(unsigned &bit_out_index) {

        /*Kód epic_list legenárálásához (jobb hard code-ólva?)

        int epic_list[256];
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                epic_list[16 * i + j] = i + 16 * j;
            }
        }
         */

        int epic_list[256] = {
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
                15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 255
        };

        return epic_list[bit_out_index];
    }

//bekéri az eredeti 144-es bitsort és visszadja a 256-os kódolt bitsort
    bitset<256> hamming(bitset<144> &bit_in) {

        bitset<256> bit_out;

        bit_out.set(255, true);
        bit_out.set(254, true);
        bit_out.set(253, true);
        bit_out.set(252, true);


        bitset<4> current_chunk;
        unsigned chunk_index = 0;
        unsigned bit_out_index = 0;

        for (int i = 0; i < 144; i++) {


            current_chunk[chunk_index++] = bit_in[i];

            if (chunk_index == 4) {
                bitset<7> kodolt = matrix(current_chunk);
                for (int j = 0; j < 7; j++) {
                    bit_out.set(bit_out_index, kodolt[j]);
                    bit_out_index++;
                }
                chunk_index = 0;
            }

        }


        // ez a rész alakítja át a bitsort továbbítandó alakra.
        // szerintem ezt majd kiszedem és implementálom egyből az előző for loop-ban
        // (csak ez még nem sikerült)
        bitset<256> tmp_bit;
        for (unsigned int i = 0; i < 256; i++) {
            tmp_bit[i] = bit_out[index_finder(i)];
        }

        return tmp_bit;
    }


// visszaállítja az eredeti bitsort  hibajavítás nélkül
    bitset<144> descramble(bitset<256> &bit_out) {
        bitset<256> un_bit;
        bitset<144> de_bit;


        unsigned index = 3;
        unsigned counter = 0;
        for (int i = 0; i < 144; i++) {
            de_bit[i] = un_bit[index++];
            counter++;
            if (counter == 4) {
                index += 3;
                counter = 0;
            }
        }

        return de_bit;

    }


    bitset<7> javitas(bitset<7> &c_bit) {

        /* így hoztam létre a kod_szavak-at.

        bitset<64>all_chunks = 0b0000000100100100100000110110110010101001010111101101101101111111;

        bitset<112>beszorzott_chunks;

        bitset<4> tmp_eredmeny;
        bitset<7> tmp_append;
        unsigned index = 0;
        unsigned szorzott_index = 0;

        for(int i = 0; i < 64; i++){
            tmp_eredmeny[index] = all_chunks[i];
            cout << "Az index: " << index << "az [i] darab " << all_chunks[i] << endl;
            if(index == 3){
                cout << tmp_eredmeny << endl;
                cout << i << endl;
                tmp_append = matrix(tmp_eredmeny);
                cout << tmp_append << endl;
                for(int j = 0; j < 7; j++){
                    beszorzott_chunks[szorzott_index] = tmp_append[j];
                    szorzott_index++;
                }
                index = -1;
            }
            index++;
        }
        */

        //az összes lehetséges 4 chunkos kód szó Hamming-mátrix szorzatát tartalmazza. 7-es chunkok.
        // a clion error-t jelez erre a deklarációra "Integer literal is too large." Viszont probléma nélkül lefoudol.
        //bitset<112> kod_szavak = 0b0000000000101100101010100111100011000111100110010110000110100111001101010110011101001101010101100001110011111111;




        bitset<112> kod_szavak(
                string("0000000000101100101010100111100011000111100110010110000110100111001101010110011101001101010101100001110011111111"));

        // a különbség az adott bitsortól
        unsigned diff = 8;
        //leghansonlóbb chunk kezdő indexe
        unsigned k_index = 0;

        // hogy 7-esével legyenek vizsgálva chunkok
        unsigned chunk_index = 0;

        // a jelenleg vizsgált bitsor különbsége az adott bitsortól
        unsigned c_diff = 0;

        //cout << "ez c-bit" << c_bit << endl;


        for (int i = 0; i < 112; i++) {
            if (c_bit[chunk_index] != kod_szavak[i]) {
                c_diff++;
            }
            chunk_index++;

            if (chunk_index == 7) {
                if (c_diff == 0) {
                    return c_bit;
                }

                if (c_diff < diff) {
                    diff = c_diff;
                    k_index = i - 6;
                }
                c_diff = 0;
                chunk_index = 0;
            }
        }

        if (diff > 1) {
            cout << "its happening" << endl;
            throw exception();
        }

        bitset<7> res_bit;
        unsigned index = 0;
        for (unsigned int i = k_index; i < k_index + 7; i++) {
            res_bit[index++] = kod_szavak[i];
        }

        //cout << "ez a res_bit " <<  res_bit << endl;

        return res_bit;

    }


    bitset<144> decode(bitset<256> &bit_out) {
        bitset<256> un_bit;

        for (unsigned i = 0; i < 256; i++) {
            un_bit[i] = bit_out[index_finder(i)];
        }

        /*
        for(int i = 0; i < 256; i++){
            cout << un_bit[i];
        }

        cout << endl;
        */

        bitset<144> res_bit;
        unsigned chunk_index = 0;
        unsigned res_bit_index = 0;
        bitset<7> javitando;
        bitset<7> javitott;

        for (int i = 0; i < 252; i++) {
            javitando[chunk_index] = un_bit[i];
            chunk_index++;

            if (chunk_index == 7) {

                javitott = javitas(javitando);
                //cout << javitando << " " << javitott << endl;
                chunk_index = 0;
                for (int j = 3; j < 7; j++) {
                    res_bit[res_bit_index] = javitott[j];
                    res_bit_index++;
                }
            }
        }


        return res_bit;
    }
};

#endif //UNTITLED3_KODOLO_H
