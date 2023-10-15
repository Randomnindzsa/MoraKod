#include <iostream>
#include <bitset>

using namespace std;

// elvégzi a mátrixszorzást Hammming-kód generátormátrixával
bitset<7> matrix(bitset<4> &c_chunk){

    bitset<7> kodolt;

    for(int i = 0; i < 4; i++){
        kodolt[i+3] = c_chunk[i];
    }

    /*
     * e: 1110
     * f: 1101
     * g: 0111
     */

    // e:
    kodolt[2] = (c_chunk[3]&1)^(c_chunk[2]&1)^(c_chunk[1]&1);

    // f:
    kodolt[1] = (c_chunk[3]&1)^(c_chunk[2]&1)^(c_chunk[0]&1);

    // g:
    kodolt[0] = (c_chunk[2]&1)^(c_chunk[1]&1)^(c_chunk[0]&1);

    return kodolt;
}

// megtalálja a bit indexét a 256-os bitsorban.
unsigned index_finder(unsigned &bit_out_index){

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
bitset<256> hamming(bitset<144> &bit_in){

    bitset<256> bit_out;

    bit_out.set(255, true);
    bit_out.set(254, true);
    bit_out.set(253, true);
    bit_out.set(252, true);


    bitset<4> current_chunk;
    unsigned chunk_index = 0;
    unsigned bit_out_index = 0;

    for(int i = 0; i < 144; i++) {

        current_chunk[chunk_index++] = bit_in[i];

        if(chunk_index == 4){
            bitset<7> kodolt = matrix(current_chunk);
            for(int j = 0; j < 7; j++){
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
    for(unsigned int i = 0; i < 256; i++){
        tmp_bit[i] = bit_out[index_finder(i)];
    }

    return tmp_bit;
}



// dekódolja a bitset és visszadja az eredeti alakot
bitset<144> dekodolo(bitset<256> &bit_out){
    bitset<256> un_bit;
    bitset<144> de_bit;

    for(unsigned i = 0; i < 256; i++){
        un_bit[i] = bit_out[index_finder(i)];
    }

    unsigned index = 3;
    unsigned counter = 0;
    for(int i = 0; i < 144; i++){
        de_bit[i] = un_bit[index++];
        counter++;
        if(counter == 4){
            index += 3;
            counter = 0;
        }
    }


    return de_bit;

}


int main() {

    bitset<144> bit_in(string("001010101000001101111000111101011100111010101000000010110010001110101010001101111000000010000100011000110000001000010000101010100110100110111010"));

    /*
    bitset<144> bit_in;

    bool bit;
    int index = 0;
    while (std::cin >> bit) {

    }
    */


cout << hamming(bit_in) << endl;

bitset<256> res_bit = hamming(bit_in);

cout << dekodolo(res_bit) << endl;


    return 0;
}
