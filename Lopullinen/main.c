/***************************************************************************** 
 * Product:  Pankkiautomaatti  
 * Version:  . .  
 * Released: Apr 18 2012 
 * Updated:  Apr 18 2012 
 * 
 * Copyright (C) 2002-2004 Pertti Rautio. All rights reserved. 
 * 
 * <licensing terms>  
 * 
 * <Company contact information> 
 *****************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 256

void emptyBuffer(void);
int tarkistaSyote(const char syote[],int MAX);
void reverseString(char* begin);
void ohjeet();
void luoTilit();
int nollanPaikka = ((int)'0');
int ysinPaikka = ((int)'9');
int onkoTiliOlemassa(int tilinumero);
int nostaRahaa(int tilinumero, char nosto[]);
int talletaRahaa(int tilinumero, char summa[]);
void tulostaSaldo(int tilinumero);
void alustaTaulu(char* begin);
void trimLeadingZeros(char trimmattava[]);
void zeroFill(char nollattava[]);
int checkString(char taulukko);
int onkoNumero(char *merkki);
int tarkistaTunnusluku (char syotettyTunnusluku[], int tilinumero);


typedef struct tiliStruct {
	int tilinumero;
	char saldo[BUFFER_SIZE];
} tiliMalli;


int main (void){
	
	int tilinumero;
	int lopetus = 1;
	int syote;
	char summa[BUFFER_SIZE];
	char syotettyTunnusluku[5];
	int tulos;
	
	alustaTaulu(summa);
	luoTilit();   
	
	    printf("Anna nelinumeroinen tilinumero: \n");	
		scanf("%d", &tilinumero);
		emptyBuffer();
	
	
		while(onkoTiliOlemassa(tilinumero) != 1){
			printf("Tilia ei loytynyt!\n");
			printf("Anna tilinumero uudestaan :");
			scanf("%d", &tilinumero);
		} 
	
	
	printf("Tili loytyi...\n\n");
	
	
	
	while(lopetus){
		
		ohjeet();
		scanf("%d", &syote);
	
		switch ( syote ) {
			case  1:
				
				printf("Paljonko haluat nostaa? \n");
				printf(": ");
				
				do {
					scanf("%s",summa);
					printf("Anna tunnusluku: ");
					do {
						scanf("%s", syotettyTunnusluku);
					} while (tarkistaTunnusluku(syotettyTunnusluku,tilinumero) == 0);
				} while (onkoNumero(summa) == 0);
				
				tulos = nostaRahaa(tilinumero, summa);
				
				if (tulos == 0) {
					printf("Tilillä ei tarpeeksi rahaa\n");
				} 
				else if (tulos == 1) {
					printf("Talletetaan...\n\n");
				}
				break;
				
			case  2:
				
				printf("Paljonko haluat tallettaa? \n");
				printf(": ");
				
				do {
					scanf("%s", summa);
				} while (onkoNumero(summa) == 0);
				
				tulos = talletaRahaa(tilinumero,summa);
				
				if (tulos == 0) {
					printf("Tilille ei mahdu enempää rahaa\n");
				} 
				else if (tulos == 1) {
					printf("Talletetaan tulos");
				}
				break;
			case  3:
				
				tulostaSaldo(tilinumero);
				
				break;
			case  0:
				
				printf("Ohjelma lopetetaan, tervetuloa uudelleen! \n");
				lopetus = 0;
				
				break;
		} 
		
		void emptyBuffer(void);
		
	} //while
	
	return(0);

} //main

void ohjeet(){
	
	printf( "Valise toiminto:\n 1 - Nosto\n 2 - Talleta\n 3 - Saldo\n 0 - Lopeta\n\n Valitasi: " );
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// luoTilit metodi luo tilit .tili tiedostoihin
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void luoTilit(){
	
	FILE *outfilep;
	int i;
	int tilinumero1 = 1234;
    int tilinumero2 = 4321;
    int tilinumero3 = 5678;
    int tilinumero4 = 8765;
	char saldo [BUFFER_SIZE];
	
	alustaTaulu(saldo);
	
	char tiliString[30];							         // Talletetaan avattavan tilin nimi tähän taulukkoon (esim 1234.tili) sprintf() funktiolla

	outfilep = fopen("1234.tili","w+");
	fprintf(outfilep,"%d\n%s\n",tilinumero1,saldo);
	fclose(outfilep);
	
	outfilep = fopen("4321.tili","w+");
	fprintf(outfilep,"%d\n%s\n",tilinumero2,saldo);
	fclose(outfilep);
	
	outfilep = fopen("5678.tili","w+");
	fprintf(outfilep,"%d\n%s\n",tilinumero3,saldo);
	fclose(outfilep);
	
	outfilep = fopen("8765.tili","w+");
	fprintf(outfilep,"%d\n%s\n",tilinumero4,saldo);
	fclose(outfilep);
		
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// onkoTiliOlemassa tarkistaa onko haettu tili olemassa
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int onkoTiliOlemassa(int tilinumero){
	
	FILE *infilep;
	int i;
	tiliMalli tilit[4];
	
	if((infilep=fopen("1234.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&tilit[0].tilinumero,tilit[0].saldo);
	} // else
	
	if((infilep=fopen("5678.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&tilit[1].tilinumero,tilit[1].saldo);
	} // else
	
	if((infilep=fopen("8765.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&tilit[2].tilinumero,tilit[2].saldo);
	} // else
	
	if((infilep=fopen("4321.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&tilit[3].tilinumero,tilit[3].saldo);
	} // else
	
	fclose(infilep);

	for(i=0; i<4 ; i++){
		if(tilit[i].tilinumero == tilinumero){
			return 1;
		}
	}//for

	return 0;
} //onkoTiliOlemassa

  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// nostaRahaa lukee tiedostosta tilillä olevan summan, tekee vähennyslaskun ja tallettaa uuden luvun tiedostoon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nostaRahaa(int tilinumero, char nosto[]) {
	
	FILE *infilep, *outfilep;
	char tiliString[10];							         // Talletetaan avattavan tilin nimi tähän taulukkoon (esim 1234.tili) sprintf() funktiolla
	char saldo[BUFFER_SIZE];					             // Luetaan tilin saldo tiedostosta tähän taulukkoon 
	char lopullinen[BUFFER_SIZE];
	int  avatunTilinumero;							         // Luetaan tilin tilinumero tiedostosta tähän taulukkoon
	int pituusSaldo, pituusNosto, i;										// luetaan montako merkkiä taulukkoon tallettui
	sprintf(tiliString, "%d.tili", tilinumero);		         // Talletataan tilin nimi tiliString taulukkoon jotta se voidaan avata fopen() funktiolla
	
	if((infilep=fopen(tiliString,"r+"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&avatunTilinumero,saldo);      //  (fscanf lukee merkkijonon loppuun NULL terminaalin '\0' Luetaan kyseisen tilin tiedot tiedostosta ja talletetaan muuttujiin avatunTilinumer jo avatunSaldo
	} // else										
	fclose(infilep);
	
	pituusSaldo = strlen(saldo);
	pituusNosto = strlen(nosto);
	
	if (pituusNosto > pituusSaldo) {						 // jos nostettava summa on suurempi kuin tilillä oleva rahamäärä, ei tehdä mitään
		return 0;
		}
	
	reverseString(saldo);									  // käännetään numerot taulukossa
	zeroFill(saldo);										  // täytetään 'tyhjät paikat' nullilla '\0' 
	reverseString(nosto);									  // käännetään numerot taulukossa
	zeroFill(nosto);										  // täytetään 'tyhjät paikat' nullilla '\0' 

	int saldoInt, nostoInt, yhteissumma, muisti = 0;

	for (i=0; i <BUFFER_SIZE-1; i++) {
		
		saldoInt = (((int)saldo[i])-48);
		nostoInt = (((int)nosto[i])-48);
		yhteissumma = (saldoInt - nostoInt - muisti);
		
		if (yhteissumma < 0) {
			muisti = 1;
			yhteissumma	= yhteissumma + 10;				
			lopullinen[i] = (char)yhteissumma+48;
		}else {
			lopullinen[i] = (char)yhteissumma+48;
			muisti = 0;
		}
	} //for
	
	if (muisti == 1) {
		return 0;
	}
	
	trimLeadingZeros(lopullinen);      
	reverseString(lopullinen);			
	outfilep = fopen(tiliString,"w+");
	fprintf(outfilep,"%d\n%s\n",tilinumero,lopullinen);
	fclose(outfilep);
	return 1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// talletaRahaa lukee saldon tiedostosta, vähentää halutun summan ja tallettaa uuden summan tiedostoon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int talletaRahaa(int tilinumero, char summa[]){
    
	FILE *infilep, *outfilep;
	char tiliString[10];
	char avatunTilinSaldo[BUFFER_SIZE];
	int loytyi,i;
	
	alustaTaulu(avatunTilinSaldo);
	int avatunTilinTilinumero, viimeinenMerkki;
	sprintf(tiliString, "%d.tili", tilinumero);
	
	if((infilep=fopen(tiliString,"r+"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s%d",&avatunTilinTilinumero,avatunTilinSaldo, &viimeinenMerkki);
	} // else
	
	fclose(infilep);
    reverseString(avatunTilinSaldo);
	reverseString(summa);
	char summattuTaulukko[BUFFER_SIZE];
	alustaTaulu(summattuTaulukko);
	
	int avatunPituus,summanPituus, pienempi, isompi,k;
	avatunPituus = strlen(avatunTilinSaldo);
	summanPituus = strlen(summa);
	
	if (avatunPituus < summanPituus) {     // katsotaan kumpi taulukko on pitempi
		pienempi = avatunPituus;
		isompi = summanPituus;
	}
	else {
		pienempi = summanPituus;
		isompi = avatunPituus;
	}

	int kolmas = 0;
	
	for (k = 0; k<255; k++) {
		if ( k < pienempi ){
			
			int yhteisSumma, eka, toka;
			
			eka = (((int)avatunTilinSaldo[k])-nollanPaikka);
			toka = (((int)summa[k])-nollanPaikka);
			yhteisSumma = eka + toka;
			
			int jakojaannos = yhteisSumma%10;
			
			summattuTaulukko[k] = ((char)(jakojaannos + kolmas + nollanPaikka));
			
			kolmas = yhteisSumma/10;
			
		} else if ( isompi <= k) {
			// do nothing;
		} else if ( summanPituus <= k ) {
			summattuTaulukko[k] = (char)((int)avatunTilinSaldo[k] + kolmas);
			kolmas = 0;
		} else if ( avatunPituus <= k) {
			summattuTaulukko[k] = (char)((int)summa[k] + kolmas);
			kolmas = 0;		}
	}
	
	
	reverseString(summattuTaulukko);
	
	for (i=0; i<BUFFER_SIZE+1; i++) {           // tarkistetaan löytyykö 256 solun sisältä '\0' merkkiä, jos ei löydy niin taulukko on liian suuri
		
		if (summattuTaulukko[i] == NULL) {
			
			loytyi = 1;
		
		} else {
			loytyi = 0;
		}
		
		if (loytyi == 1) {
			return 0;
		}else if (loytyi == 0) {
			if((outfilep = fopen(tiliString,"w+"))==NULL){
				printf("\nTiedoston avaaminen epaonnistui");
			}else{
				fprintf(outfilep,"%d\n%s\n",tilinumero,summattuTaulukko);
			} // else
			
			fclose(outfilep);
			return 1;
		}
	}
} //talletaRahaa


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// tulostaSaldo lukee tilin saldon tiedostosta ja tulostaa sen näytölle
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tulostaSaldo(int tilinumero){
	
	
	FILE *infilep;
	char tiliString[10];
	char avatunTilinSaldo[BUFFER_SIZE];
	alustaTaulu(avatunTilinSaldo);
	int avatunTilinTilinumero;
	
	sprintf(tiliString, "%d.tili", tilinumero);
	
	if((infilep=fopen("1234.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%d%s",&avatunTilinTilinumero,avatunTilinSaldo);
	} // else
	
	if (avatunTilinSaldo[0] == NULL) {
		printf("Tililläsi ei ole rahaa!\n");
	}else{
	    printf("Tilisi saldo on: %s\n	", avatunTilinSaldo);
	}
	
	fclose(infilep);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// emptyBuffer tyhjentää stdin bufferin
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void emptyBuffer(void) {
	
	while( getc(stdin) !='\n');
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reverseString lukee merkkejä taulukon alusta ja kirjoittaa ne taulukon loppuosaan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverseString(char* begin){
    char temp;
    char* end;
    end = begin + strlen(begin)-1;
	
    while(end>begin){
        temp = *end;
        *end = *begin;
        *begin = temp;
        end--;
        begin++;
    } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// zeroFill täyttää taulukon tyhjät paikat NULL:iksi eli '\0' merkillä
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void zeroFill(char nollattava[]) { 
	
	int pituus = strlen(nollattava);
	int i;
	
	for (i = pituus; i < BUFFER_SIZE-1; i++) {
		nollattava[i] = '0';
	}
	
	nollattava[BUFFER_SIZE-1] = '\0';
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// alustaTaulu alustaa taulukon NULL:iksi eli '\0' merkillä
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alustaTaulu(char* begin) {
	
	int i;
	
	for (i=0; i<BUFFER_SIZE; i++) {
		begin[i] = NULL;
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// funktio etsii missä ensimmäinen !=0 sijaitsee ja merkitsee sitä seuraavan taulukon paikan NULL:iksi '\0'
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void trimLeadingZeros(char trimmattava[]){     

	int i = BUFFER_SIZE-2;
	int totuus = 0, loytyi;
	int x,y,z; 
	
	while (i > -1 && totuus == 0) {
		if (trimmattava[i] != '0') {
			totuus = 1;
			loytyi = i;
		}
		i--;
	}
	if (totuus == 1) {
		trimmattava[loytyi+1] = '\0';
		x=0;
	while (trimmattava[x] != '\0') {
		x++;
	}
	
	}else {
		trimmattava[0] = '0';
		trimmattava[1] = '\0';
		x=0;
		while (trimmattava[x] != '\0') {
			x++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// onko numero tarkistaa merkki kerrallaan onko annettu merkki ascii -taulukon välillä 48 - 57 (eli numero väliltä 0-9) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int onkoNumero(char *merkki) {
	
	int i;
	int pituus = strlen(merkki);
	for (i = 0; i <pituus; i++) {
		if ((int)merkki[i] >= 48 && (int)merkki[i] <= 57) {
			;
		}
		else {
			printf("Syötä vain kokonaislukuja\n");
			return(0);			
		}
	}
	return(1);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// tarkistaTunnusluku vertailee tiedostosta luettua ja annettua tunnuslukua keskenään ja palauttaa 0 jos luvut eivät täsmää ja 1 jos luvut täsmäävät
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int tarkistaTunnusluku (char syotettyTunnusluku[], int tilinumero) {
	
	FILE *infilep;
	char tiliString[10];
	char avatunTilinSaldo[BUFFER_SIZE];
	alustaTaulu(avatunTilinSaldo);
	char avatunTilinTilinumero[5];
	
	sprintf(tiliString, "%d.tili", tilinumero);
	
	if((infilep=fopen("1234.tili","r"))==NULL){
		printf("\nTiedoston avaaminen epaonnistui");
	}else{
		fscanf(infilep,"%s%s",avatunTilinTilinumero,avatunTilinSaldo);
	} // else
	
	fclose(infilep);
	
	for (int i=0; i < strlen(syotettyTunnusluku); i++) {
		int x;
		x = strcmp (syotettyTunnusluku ,avatunTilinTilinumero);
	if ( x == 0 ){		
		;
	}else {
		printf("Väärä tunnusluku\n");
		return 0;
	}
	} //for
	
	return 1;
}








