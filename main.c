// Calmis Liviu - 311 CB

#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>


typedef struct {
	char *keyg, *valueg;
} TPereche;

// Functie de calculare a codului hash
int codHash(size_t M, void *element)
{
    int i, suma = 0;
    TPereche *pereche = (TPereche*)element;
    char *key = pereche->keyg;
    for(i = 0; key[i] != '\0'; i++){
        suma = suma + key[i];
    }
    return (suma % M);
}

// Functie de afisare a valorii
void afisare(void *element, FILE *g)
{
    TPereche *pereche = (TPereche*)element;
    char *value = pereche->valueg;
    char *key = pereche->keyg;
    fprintf(g, "%s ", value);
}

// Functie de afisare a valorii daca key-urile de la element si cel
// primit ca parametru sunt identice
// Returneaza 1/0 daca keyurile sunt identice/diferite
int getValue(void *element, char *key, FILE *g)
{
    TPereche *pereche = (TPereche*) element;
    if (strcmp(pereche->keyg, key) == 0){
        fprintf(g, "%s\n", pereche->valueg);
		return 1;
    }
	return 0;
}

// Returneaza 1/0 daca key-rile sunt identice/diferite
int cautaKey(void *element, char *key)
{
    TPereche *pereche = (TPereche*) element;
    if (strcmp(pereche->keyg, key) != 0)
		return 0;
	return 1;
}

// Functie comparare pereche(key, value)
int cmpPereche(void *e1, void *e2)
{
	TPereche *pereche1 = (TPereche*) e1;
	TPereche *pereche2 = (TPereche*) e2;
	if (strcmp(pereche1->keyg, pereche2->keyg) != 0)
		return 0;

	if (strcmp(pereche1->valueg, pereche2->valueg) != 0)
		return 0;

	return 1;
}

// Functie comparare key
int cmpKey(void *e1, void *e2)
{
	TPereche *pereche1 = (TPereche*) e1;
	TPereche *pereche2 = (TPereche*) e2;

	return strcmp(pereche1->keyg, pereche2->keyg);
}

// Functie introducere element in tabela hash
TH *GenerareHash(size_t M, TH *h, void* element)
{
    TPereche *pereche = (TPereche*)element;
    int rez;
    int i = 0;
    rez = put(h, pereche, cmpPereche);    

	return h;
}

int main(int argc, char *argv[])
{   
    FILE *f, *g;
    char *line = NULL;
	size_t len = 0;
	int bucket_nr;
	TPereche *pereche;
	
	
    f = fopen(argv[2], "r");
	g = fopen(argv[3], "w");
	if (f == NULL)
		return 1;
		
	static size_t M;
	M = atoi(argv[1]);
	TH *h = NULL;
	// Initializez tabela hash
    h = (TH*)IniTH(M, codHash);
    if(h == NULL)
 	    return 1;
 	// Citesc fisierul .in
    while (getline(&line, &len, f) != -1) {
	    char *comm = strtok(line, " ");
	    char *key = strtok(NULL, " ");
	    char *value = strtok(NULL, " ");
	    if(value != NULL && value[strlen(value) - 1] == '\n')
	        value[strlen(value) - 1] = '\0';
        if(key != NULL && key[strlen(key) - 1] == '\n')
	        key[strlen(key) - 1] = '\0';
        if(comm != NULL && comm[strlen(comm) - 1] == '\n')
	        comm[strlen(comm) - 1] = '\0';
	    
	    if(strcmp(comm, "put") == 0){
	        pereche = (TPereche*)malloc(sizeof(TPereche));
	        pereche->keyg = malloc(strlen(key)*sizeof(char) + 1);
	        pereche->valueg = malloc(strlen(value)*sizeof(char) + 1);
	        strcpy(pereche->keyg, key);
	        strcpy(pereche->valueg, value);
	        h = GenerareHash(M, h, pereche);
	    }
	    if(strcmp(comm, "find") == 0){
	        find(h, key, cautaKey, g);
	    }
	    if(strcmp(comm, "print") == 0){
	        print(h, afisare, g);
	    }
	    if(strcmp(comm, "print_bucket") == 0){
	        bucket_nr = atoi(key);
			if(bucket_nr < M)
	        	print_bucket(h, bucket_nr, afisare, g);
	    }
	    if(strcmp(comm, "get") == 0){
	        get(h, key, getValue, g);
	    }
	    if(strcmp(comm, "remove") == 0){
	        Remove(h, key, cmpPereche, cautaKey);
	    }
    }
	// Eliberez memoria ocupata de tabela hash
	DistrTH(&h, free);
  return 0;
}
