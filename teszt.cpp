//
// Created by balint on 2023. 11. 07..
//

#include "kodolo.h"
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>

unsigned segment_eltort_bit = 0;

bool torik_e(unsigned esely){
    unsigned torik = 1 + (std::rand() % 101);
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
    int lepes = 20/meret;
    int esely = 30;
    for (unsigned int i = 0; i < meret*2+1; ++i) {
        if (i < meret){
            if(torik_e(esely)){
                bemenet.flip(honnan+i);
                segment_eltort_bit++;
            }
            esely+=lepes;
        }else if(i == meret){
            if(torik_e(esely)){
                bemenet.flip(honnan+i);
                segment_eltort_bit++;
            }
            esely-=lepes;
        }else if(i > meret){
            if(torik_e(esely)){
                bemenet.flip(honnan+i);
                segment_eltort_bit++;
            }
            esely-=lepes;
        }
    }
    return bemenet;
}

int main(){
    fstream newfile;
    std::string bevitel;
    std::stringstream bevevitel(bevitel);
    std::string segment;
    std::vector<std::string> seglist;
    vector<std::string>::iterator itr;
    Kodolo k;
    newfile.open("bitek.txt",ios::in);
    if (newfile.is_open()){
        while(std::getline(newfile, segment, '\n')){
            seglist.push_back(segment);
        }
    }


    for (int i = 1; i < 20; ++i) {
        unsigned nem_tort = 0;
        unsigned osszes = 0;
        float eredmeny = .0f;
        float toresi_esely = .0f;
        for (itr = seglist.begin(); itr < seglist.end(); itr++) {
            std::bitset<144> bevitel(*itr);
            std::bitset<256> forditott = k.hamming(bevitel);
            std::bitset<256> torot = toro(forditott, i, 7);
            std::bitset<144> kiadas = k.decode(torot);
            bool jo_e = (bevitel == kiadas);
            if(jo_e){
                nem_tort+= 1;
            }
            osszes+= 1;
        }
        cout << to_string(i*2+1) << " méretű parabola zaj mintázása esetén: " << endl;
        eredmeny =  (nem_tort*100)/osszes;
        cout << to_string(nem_tort) << "lett jó" << endl;
        cout << to_string(eredmeny) << "% lett jó a(z) " << to_string(osszes) << " esetből."<< endl;
        cout << to_string(segment_eltort_bit) << "bit tort el a(z) " << to_string(osszes*144) << " bitből."<< endl;
        segment_eltort_bit = 0;
    }
    return 0;
}