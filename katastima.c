#include "katastima.h"
#include <stdio.h>
#include <stdlib.h>

void dhmiourgiaKatalogou(Katalogos k[]){
        for (int i=0;i<proionta;i++){
                k[i].kwd=i+1;
                sprintf(k[i].on, "Proion %d" ,i+1);
                k[i].timi= rand() % 100 + 1;
                k[i].tmx=3;
        }
}

