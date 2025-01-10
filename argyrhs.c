#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

#define pel 5
#define proionta 20
#define paraggelies 10
//----------------STRUCT KATALOGOU-----------------
typedef struct{
	int kwd;
	char on[32];
	int timi;
	int tmx;

}Katalogos;
//-----------------ARXIKOPOIHSH KATALOGOU-----------------
void catalogCreator(Katalogos k[]){
	for (int i=0;i<proionta;i++){
		k[i].kwd=i+1;
		sprintf(k[i].on, "Proion %d" ,i+1);
		k[i].timi= rand() % 100 + 1;
		k[i].tmx=3;
	}
}

int main ()//-----------------MAIN--------------------
{
Katalogos k[proionta];
int fd1[2];//epoikoinwnia pelati katastimatos
int fd2[2];//epoikoinwnia katastimatos pelati
int id,j,epitix=0,apotiximenes=0,kerdos=0;
int apotix[20][5]={0};
int pl[20]={0};
//----------------------ARXH SERVER------------------------
	for(j=0;j<pel;j++){
	pipe(fd1);
	pipe(fd2);
	id = fork();
//-------------------Diadikasia Pelati---------------------
	if (id==0){
		close(fd1[0]);
		close(fd2[1]);
		srand(time(NULL) + j);
		char apant[128];
		for (int l = 0; l < paraggelies; l++) {
			int x = rand() % proionta + 1;
			write(fd1[1], &x, sizeof(x));
			read(fd2[0], &apant, sizeof(apant));
			printf("Pelatis %d : %s\n",j+1 , apant);
			sleep(1);
		}
		close(fd1[1]);
		close(fd2[0]);
		exit(0);
	}else{
//---------------------Diadikasia Katastimatos-------------------
		close(fd1[1]);
		close(fd2[0]);
		if(j==0){//Dhlwsh pinaka mono 1 fora
			catalogCreator(k);
		}
		printf("\n");
		for (int i = 0; i < paraggelies; i++) {
			int proion;
			char ap[128];
			read(fd1[0], &proion, sizeof(proion));
			int found = 0;
			for (int i = 0; i < proionta; i++) {
				if (proion == k[i].kwd) {
					pl[i]++;
					if(k[i].tmx>0){
						sprintf(ap, "Epitixhs paraggelia to poso einai: %d", k[i].timi);
						write(fd2[1], &ap, sizeof(ap));
						kerdos+=k[i].timi;
						epitix++;
						k[i].tmx--;
					}else{
						apotix[i][j]++;
						apotiximenes++;
						strcpy(ap, "Mh diathesimo proion");
                                		write(fd2[1], &ap, sizeof(ap));
					}
					break;
				}
			}
		}
	}
	close(fd1[0]);
	close(fd2[1]);
	wait(NULL);
}
//-------------------------------TELOS-------------------------------
printf("\n\n");
//------------------------EMFANISI APOTELESMATWN---------------------
for(int i=0;i<proionta;i++){
	printf("To %s zhtithike: %d fores ",k[i].on,pl[i]);
	printf("kai poulithike: %d fores \n",3-k[i].tmx);
	for (int j=0;j<5;j++){
		if(apotix[i][j]!=0){
			printf("        O pelatis %d apetixe na agwrasei to proion: %d fores \n",j,apotix[i][j]);
		}
	}
printf("--------------------------------------------\n");
}
printf("Se synolo 50 paraggelies eginan: %d  epitiximenes paraggelies \n", epitix);
printf("Kathws kai %d apotiximenes prospathies paraggeliwn\n",apotiximenes );
printf("To synoliko kerdos apo tis paraggelies einai: %d \n",kerdos);

printf("----Telos programmatos----\n");
return 0;
}
