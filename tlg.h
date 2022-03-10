// Calmis Liviu - 311 CB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;
  struct celulag *pre, *urm;
} TCelulaG, *TLG;

typedef int (*TFCmp)(void*, void*);   /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE *g);     /* functie afisare element */
typedef void (*TFree)(void*);   /* functie eliberare un element */

int InsLG(TLG*, void*);
TLG InitLG();
void Eliminare(TLG *aL, void *el, TFCmp cmpPereche);
int cmpKey(void *e1, void *e2);
#endif
