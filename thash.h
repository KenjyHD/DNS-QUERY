// Calmis Liviu - 311 CB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */
typedef int (*TFfind)(void*, char*);
typedef int (*TFget)(void*, char*, FILE*);
typedef int (*TFHash)(size_t, void*);
typedef void (*TFree)(void*);   /* functie eliberare element */
typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

TH* IniTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TFree fe);
void print(TH*a, TF afiEl, FILE *g);
int put(TH*a, void* ae, TFCmp f);
void find(TH *ah, char *key, TFfind findKey, FILE *g);
void print_bucket(TH* ah, int i, TF afiEl, FILE *g);
void get(TH *ah, char *key, TFget getValue, FILE *g);
void Remove(TH *ah, char *key, TFCmp f, TFfind findKey);
#endif