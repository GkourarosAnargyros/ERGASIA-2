#ifndef KATASTIMA_H
#define KATASTIMA_H
#define pel 5
#define proionta 20
#define paraggelies 10


typedef struct {
int kwd;
char on[32];
int timi;
int tmx;
}Katalogos;


void dhmiourgiaKatalogou(Katalogos k[]);


#endif
