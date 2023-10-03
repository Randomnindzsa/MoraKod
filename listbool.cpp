//
// Created by balint on 2023. 09. 26..
//
#include <iostream>
#include <list>
#include <vector>



using namespace std;

void feltoltes(vector<bool>* chunktomb, unsigned int szam){
    for (unsigned int i = 0; i < szam; ++i) {
        while (chunktomb[i].size() < 4){
            chunktomb[i].push_back(false);
        }
    }
}

void showlist(vector<bool> g){
    vector<bool>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
        cout << "\t" << *it;
    }
    cout << '\n';
}

unsigned int chunk_szam(vector<bool> bit_kod){
    unsigned int szam = bit_kod.size()/4;
    if(bit_kod.size() % 4 !=0 ){
        szam++;
    }
    return szam;
}

void koddarabolo(vector<bool> bit_kod, vector<bool>* chunktomb) {
    int k = 0;
    int j = -1;
    for (int i = bit_kod.size()-1; i >= 0; --i) {
        if (k % 4 == 0) {
            j++;
            vector<bool> newVector;
            chunktomb[j] = newVector;
            chunktomb[j].push_back(bit_kod.at(i));
        } else {
            chunktomb[j].push_back(bit_kod.at(i));
        }
        k++;
    }
}


int main(){
    vector<bool> bit_kod={false, false, true, false, true, false, true, false, false, true, true};
    unsigned int szam = chunk_szam(bit_kod);
    vector<bool> chunktomb[szam];
    koddarabolo(bit_kod, chunktomb);
    showlist(bit_kod);
    for (unsigned int i = 0; i < szam; ++i) {
        showlist(chunktomb[i]);
    }
    feltoltes(chunktomb, szam);
    for (unsigned int i = 0; i < szam; ++i) {
        showlist(chunktomb[i]);
    }
    return 0;
}