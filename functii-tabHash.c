// Calmis Liviu - 311 CB

#include "thash.h"
// Initiez tabela hash
TH* IniTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}
// Eliberare memorie tabela hash
void DistrTH(TH** ah, TFree fe)
{
    TLG * p, el, aux;
    // Parcurgem listele din tabela hash
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        if (*p){
            el = *p;
            do{
                aux = el;
                el = el->urm;
                fe(aux->info);
                free(aux);
            } while(el != *p);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}
// Afiseaza continutul tabela hash
void print(TH* ah, TF afiEl, FILE *g)
{
    TLG p, aux;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            fprintf(g, "%d: ",i);
            // Parcurg lista pana nu ajung iarasi la primul element
	        aux = p;
	        do{
	            afiEl(p->info, g);
	            p = p->urm;
	        } while(aux != p);
	        fprintf(g, "\n");
            
        }
    }
}

// Afisare continutul bucketului
void print_bucket(TH* ah, int i, TF afiEl, FILE *g)
{
    TLG p, aux;
    p = ah->v[i];
    if(p){
	    aux = p;
        do{
            afiEl(p->info, g);
            p = p->urm;
	    } while(aux != p);
	    fprintf(g, "\n");   
    }
    else fprintf(g, "VIDA\n");
}

// Cauta key-ul in tabela hash
void find(TH *ah, char *key, TFfind findKey, FILE *g)
{
    TLG p, aux;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
	        aux = p;
	        do{
	            if (findKey(p->info, key) == 1){
                    fprintf(g, "True\n");
                    return;
	            }
	            p = p->urm;
	        } while(aux != p);
	    }
    }
    fprintf(g, "False\n");
}

// Cauta key-ul si afiseaza valoarea acestuia
void get(TH *ah, char *key, TFget getValue, FILE *g)
{
    TLG p, aux;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
	        aux = p;
	        do{
	            if (getValue(p->info, key, g) == 1){
                    return;
	            }
	            p = p->urm;
	        } while(aux != p);
	    }
    }
    fprintf(g, "NULL\n");
}

// Eliminare element cu key-ul respectiv din tabela hash
void Remove(TH *ah, char *key, TFCmp f, TFfind findKey)
{
    TLG p, aux;
    int i;
    // Parcurg listele din tab. hash
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        // Daca lista nu e vida atunci caut elementul cu key-ul respectiv
        if(p) {
	        aux = p;
	        do{
                // Daca gasesc elementul necesar atunci il elimin
	            if (findKey(p->info, key) == 1){
	                Eliminare(&ah->v[i], p->info, f);
                    return;
	            }
	            p = p->urm;
	        } while(aux != p);
	    }
    }
}

// Inserare element in tabela hash
int put(TH*a, void* ae, TFCmp f)
{
    int cod = a->fh(a->M, ae), rez;
    TLG el = a->v[cod];
    TLG aux = a->v[cod];
    // Daca elementul deja exista atunci nu il introducem
    do{
        if (el != NULL){
            if (f(el->info, ae) == 1)
                return 0;
        el = el->urm;
        } 
    } while(aux != el);
    // Daca nu exista atunci introducem elementul in lista respectiva
    // din tabela hash
    rez = InsLG(a->v+cod, ae);
    return rez;
}
