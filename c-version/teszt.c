#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "kodolo.h"
#include "bitset.h"

static unsigned segment_eltort_bit = 0;

bool torik_e(unsigned esely)
{
    unsigned torik = 1 + (rand() % 101);
    if (torik < esely)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void toro(bitset(256) * data, unsigned meret, unsigned honnan)
{
    if (honnan > 256 - meret)
    {
        printf("Túl nagy a honnan!");
        return;
    }
    int lepes = 20 / meret;
    int esely = 30;
    for (unsigned int i = 0; i < meret * 2 + 1; ++i)
    {
        if (torik_e(esely))
        {
            bitset_set(data, honnan + i, !bitset_get(data, honnan + i));
            segment_eltort_bit++;
        }

        if (i < meret)
        {
            esely += lepes;
        }
        else if (i >= meret)
        {
            esely -= lepes;
        }
    }
}

#define SEGLIST_LENGTH 170000
#define SEGLIST_WIDTH 144

int main()
{
    FILE *f = fopen("../bitek.txt", "r");
    if (f == NULL)
    {
        printf("Nem sikerült megnyitni a fájlt!\n");
        return 1;
    }
    bitset **bitset_list = malloc(SEGLIST_LENGTH * sizeof(bitset *));
    for (int i = 0; i < SEGLIST_LENGTH; i++)
    {
        char seg[SEGLIST_WIDTH + 1];
        fscanf(f, "%s\n", seg);
        bitset_list[i] = bitset_from_bitstring(seg);
        
    }

    bitset(256)* forditott = bitset_alloc(256);
    bitset(144)* kiadas = bitset_alloc(144);

    for (int i = 7; i < 20; ++i) {
        unsigned nem_tort = 0;
        unsigned osszes = 0;
        float eredmeny = .0f;
        float toresi_esely = .0f;
        for (bitset** bevitel = bitset_list; bevitel < bitset_list+SEGLIST_LENGTH; bevitel++) {
            bitset_reset(forditott);
            kodolo_encode(*bevitel, forditott);
            toro(forditott, i, 7);
            bitset_reset(kiadas);
            kodolo_decode(forditott, kiadas);
            

            bool jo_e = bitset_eq(*bevitel, kiadas);
            if(jo_e){
                nem_tort+= 1;
            }
            osszes+= 1;
        }
        // cout << to_string(i*2+1) << " méretű parabola zaj mintázása esetén: " << endl;
        printf("%d méretű parabola zaj mintázása esetén: \n", i*2+1);
        eredmeny =  (nem_tort*100)/osszes;
        // cout << to_string(nem_tort) << "lett jó" << endl;
        printf("%d lett jó\n", nem_tort);
        // cout << to_string(eredmeny) << "% lett jó a(z) " << to_string(osszes) << " esetből."<< endl;
        printf("%f%% lett jó a(z) %d esetből.\n", eredmeny, osszes);
        // cout << to_string(segment_eltort_bit) << "bit tort el a(z) " << to_string(osszes*144) << " bitből."<< endl;
        printf("%d bit tört el a(z) %d bitből.\n\n", segment_eltort_bit, osszes*144);
        segment_eltort_bit = 0;
    }

    // cleanup

    bitset_free(forditott);
    bitset_free(kiadas);

    for (int i = 0; i < SEGLIST_LENGTH; i++)
    {
        bitset_free(bitset_list[i]);
    }
    free(bitset_list);
    kodolo_free();
    fclose(f);
    return 0;
}
