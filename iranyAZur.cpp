#include <iostream>
#include <bitset>

using namespace std;


long unsigned int  kod_hosszt_szamit(bitset<13>& bit_kod){
    long unsigned int szam = bit_kod.size()/4;
    if(bit_kod.size() % 4 !=0 ){
        szam++;
    }
    return szam;
}

void koddarabolo(bitset<13> bit_kod, bitset<4>* chunktomb){
    int j = -1;
    string bit_size_ki = to_string(bit_kod.size());
    cout << bit_size_ki << endl;
    for (long unsigned int i = 0; i < bit_kod.size(); i++) {
        if (i % 4 == 0) {
            j++;
            bitset<4> new_bit_chunk;
            chunktomb[j] = new_bit_chunk;
        }
        if (bit_kod[i]){
            cout << "Itt egy van" << endl;
            chunktomb[j].set(i%4);
        }
    }
}
//
//bitset<4> kodolo(bitset<4>& bit_kod){
//    for (unsigned int i = 0; i < bit_kod.size(); ++i) {
//        bit_kod.flip(i);
//    }
//    bit_kod.set(4);
//    string bit_kod_ki
//    cout >>
//    return bit_kod;
//}
//
//bitset<4> kodfejto(bitset<4>& bit_kod){
//    for (unsigned int i = 0; i < bit_kod.size(); ++i) {
//        bit_kod.flip(i);
//    }
//    return bit_kod;
//}


int main() {
    bitset<13> bit_kod(string("1010101000111"));
    long unsigned int chunk_szam = kod_hosszt_szamit(bit_kod);
    bitset<4> chunktomb[chunk_szam];
    koddarabolo(bit_kod, chunktomb);
    string szam_ki = to_string(chunk_szam);
    cout << szam_ki << endl;
    for (long unsigned int i = 0; i < chunk_szam; ++i) {
        string bit_ki = chunktomb[i].to_string();
        cout << bit_ki << endl;
    }
    return 0;
}

