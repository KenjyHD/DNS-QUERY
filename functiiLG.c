// Calmis Liviu - 311 CB

#include "tlg.h"

int InsLG(TLG* aL, void* ae)
{
    // Daca lista e goala atunci o cream
    // si introducem elementul
	if(*aL == NULL){
	    TLG aux = (TLG)malloc(sizeof(TCelulaG));if(!aux) return 0;
	    aux->info = ae;
	    aux->pre = aux->urm = aux;
	    *aL = aux;
	    return 1;
	}

    TLG p, aux1;
    p = *aL;
	aux1 = p;
    TLG ultim = (TLG)malloc(sizeof(TCelulaG));
    if(!ultim) return 0;
    TLG aux = (TLG)malloc(sizeof(TCelulaG));
    if(!aux) return 0;
	        do{
                // Daca key-ul este lexicografic mai mic decit
                // key-ul din primul nod al listei
                // atunci introducem nodul la inceputul listei
                if((cmpKey(ae, p->info) < 0) && (p == *aL)){
                    ultim = p->pre;
	                aux->info = ae;
	                aux->urm = p;
	                p->pre = aux;
	                aux->pre = p;
	                p->pre = aux;
	                aux->pre = ultim;
	                ultim->urm = aux;
                    // Inceputul listei devine nodul
                    // nou introdus
                    *aL = (*aL)->pre;
                return 1;
                }
                // Daca trebuie sa introducem nodul in mijlocul listei
                // atunci il introducem inaintea primului nod cu key-ul
                // mai mare lexicografic
                if((cmpKey(ae, p->info) < 0) && (p != *aL)){
                    ultim = p->pre;
	                aux->info = ae;
	                aux->urm = p;
	                p->pre = aux;
	                aux->pre = p;
	                p->pre = aux;
	                aux->pre = ultim;
	                ultim->urm = aux;
                    p = aux1;
                return 1;
                }
	            p = p->urm;
	        } while(aux1 != p);
            // Daca nu am gasit un key mai mare lexicografic
            // atunci introdum nodul la finalul listei
            ultim = p->pre;
	        aux->info = ae;
	        aux->urm = p;
	        p->pre = aux;
	        aux->pre = p;
	        p->pre = aux;
	        aux->pre = ultim;
	        ultim->urm = aux;
            p = aux1;	
}

void Eliminare(TLG *aL, void *el, TFCmp cmpPereche)
{
    if(*aL == NULL)
        return;
    // Cautam nodul care trebuie sa-l eliminam
    TLG curent = *aL, anterior1 = NULL;
    while (cmpPereche(curent->info, el) == 0){
        if (curent->urm == *aL) {
            return;
        }
        anterior1 = curent;
        curent = curent->urm;
    }
    // Verific daca acesta este unicul nod
    if (curent->urm == *aL && anterior1 == NULL) {
        (*aL) = NULL;
        free(curent);
        return;
    }
  
    // Daca lista are mai mult de un nod,
    // verifica daca e primul nod
    if (curent == *aL) {
        // Anterior1 devine ultimul nod din lista
        anterior1 = (*aL)->pre;
  
        // Mutam inceputul listei
        *aL = (*aL)->urm;

        // Ajustam pointerii pentru anterior1 si inceputul listei *aL
        anterior1->urm = *aL;
        (*aL)->pre = anterior1;
        free(curent);
    }
  
    // verifica daca e ultimul nod
    else if (curent->urm == *aL) {
        
        // Ajustam pointerii pentru anterior1 si inceputul listei *aL
        anterior1->urm = *aL;
        (*aL)->pre = anterior1;
        free(curent);
    }
    else {
        // creez un pointer nou care pointeaza spre urmatorul nod
        // al nodului curent
        TLG temp = curent->urm;
  
        // Ajustam pointerii pentru anterior1 si inceputul listei *aL
        anterior1->urm = temp;
        temp->pre = anterior1;
        free(curent);
    }
}