//
// Created by balint on 2023. 11. 07..
//

#include "kodolo.h"
#include <random>
#include <sstream>


bool torik_e(unsigned esely){
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned> distribution(1, 100);
    unsigned torik = distribution(generator);  // generates number in the range 1..6
    if(torik < esely){
        return true;
    }else{
        return false;
    }
}

std::bitset<256> toro(std::bitset<256> bemenet, unsigned meret, unsigned honnan){
    if(honnan > 256-meret){
        cerr << "Túl nagy a honnan!";
        return bemenet;
    }
    int lepes = 50/meret;
    int esely = 50;
    for (unsigned int i = 0; i < meret*2+1; ++i) {
        if(i==0){
          bemenet.flip(honnan);
        }
        if(i <= meret){
            if(torik_e(esely)){
                bemenet.flip(honnan+i);
            }
            esely+=lepes;
        }else if(i > meret){
            if(torik_e(esely)){
                bemenet.flip(honnan+i);
            }
            esely-=lepes;
        }
    }
    return bemenet;
}

int main(int argc, char* argv[]){
    std::stringstream bevevitel("001010101000001101111000111101011100111010101000000010110010001110101010001101111000000010000100011000110000001000010000101010100110100110111010\n001010101000001101111000111101011100111010101000000010110010001110101010001101111000000010000100011000110000001000010000101010100110100110111011");
    std::string segment;
    std::vector<std::string> seglist;
    vector<std::string>::iterator itr;
    Kodolo k;

    while(std::getline(bevevitel, segment, '\n'))
    {
        seglist.push_back(segment);
    }
    for (int i = 1; i < 10; ++i) {
        cout << to_string(i*2+1) << " méretű parabola zaj mintázása: " << endl;
        for (itr = seglist.begin(); itr < seglist.end(); itr++) {
            std::bitset<144> bevitel(*itr);
            std::bitset<256> forditott = k.hamming(bevitel);
            std::bitset<256> torot = toro(forditott, i, 7);
            std::bitset<144> kiadas = k.decode(torot);
            cout << *itr << '\n' << kiadas << std::endl;
            bool jo_e = (bevitel == kiadas);
            cout << jo_e << '\n';
        }

    }
    return 0;
}