# Descriere
In momentul accesarii unei pagini web este lansat un DNS QUERY catre un server DNS,
pentru a obtine IP-ul paginii web ce se doreste a fi accesata, urmand ca ulterior sa se initieze o
conexiune care va aduce toata informatia paginii respective. Cand cererea ajunge la serverul
DNS, acesta va cauta in memorie o intrare de tipul (Name, IP), unde "Name" este adresa paginii
web, iar IP este IP-ul asociat.

Se cere implementarea structurii memoriei unui server DNS.

# Implementare
In cazul unui QUERY DNS de forma (google.ro, IP=?), serverul DNS trebuie sa itereze
prin vector pana gaseste inregistrarea corespunzatoare.
De aceea se va folosi un hashtable.

Hashtable-ul va fi reprezentat ca un vector cu M elemente (bucket-uri) – fiecare bucket
este reprezentat printr-o lista dublu inlantuita circulara generica. Elementele din liste vor fi de
forma (Key, Value). Functie hash va calcula restul impartirii sumei caracterelor ce fac parte din
cheile (Key) stocate in hash la numarul maxim de bucketuri ce pot fi stocate in hashtable (M).

Operatiile efectuate in hashtable sunt:

### put <<d>Key Value>
- adauga perechea (Key, Value) in hashtable
(daca Key exista in hastable, aceasta nu va mai
fi adăugata)
### get <<d>Key> 
- intoarce valoarea corespunzatoare cheii "Key";
daca “Key” nu exista, intoarce NULL.
### remove <<d>Key > 
- sterge perechea (Key, Value) din hashtable
(in cazul in care aceasta exista)
### find <<d>Key > 
- caută Key in hashtable și ȋntoarce True/False.
### print
- afiseaza toate valorile “Value” din hashtable;
pentru fiecare bucket (lista) nevid; se va afisa
indicele si toate elementele acestuia (Value).
Elementele listei sunt afisate toate pe aceeasi
linie, separate de un spatiu; indicii sunt
considerati de la 0.
### print_bucket <index_bucket>
- afiseaza valorile ("Value") din bucketul cu
indicele index_bucket, pe o singura linie;
separarea elementelor afisate se face numai
prin spatii; daca lista asociata bucket-ului este
vida se va afisa VIDA.

## Descriere functii
### Functia InitTH
- Initializeaza tabela hash prin atribuirea valorilor necesare campurilor
M(numarul maxim de liste), fh(functia hash), si *v(listele din tabela)

### Functia DistrTH
- Elibereaza memoria ocupata de tabela hash si elementele din aceasta

### Functia print
- Parcurge listele din tabela hash si afiseaza elementele acestora

### Functia print_bucket
- Afiseaza elementele listei cu indicele i primit parametru

### Functia find
- Cauta key-ul in tabela hash si afiseaza True/False

### Functia get
- Cauta key-ul in tabela hash si afiseaza valoarea daca exista,
NULL in caz contrar

### Functia Remove
- Cauta key-ul in tabela hash si elimina perechea(key, value) daca exista

### Functia put
- Verifica daca perechea(key, value) exista deja in tabela hash, daca nu 
atunci o introduce in tabela

### Functia INSLG
- Parcurge lista in care trebuie sa introduca perechea. Daca lista e
vida atunci o initializeaza si introduce elementul. Daca nu e vida 
atunci o parcurge si introduce elementul inaintea perechii cu key-ul
mai mic lexicografic

### Functia Eliminare
- Cauta elementul in lista si il elimina.

### Functia codHash
- Functia ce calculeaza codul hash in dependenta de key si parametrul dat
la executia programului.

### Functia afisare
- Afiseaza valoarea elementului primit parametru

### Functia getValue
- Functia ce afiseaza valoarea elementului daca key-ul acestuia si 
key-ul primit parametru sunt identice

### Functia cautaKey
- Returneaza 1/0 daca key-rile sunt identice/diferite

### Functia cmpPereche
- Functia de comparare a 2 elemente primite parametru. Returneaza
1/0 daca sunt identice/diferite

### Functia cmpKey
- Functia ce compara key-urile elementelor primite parametru.
Returnul e rezultatul functiei strcmp intre cele 2 key

### Functia GenerareHash
- Functia ce introduce elementul in tabela hash(primite ca parametru)
si returneaza tabela hash cu elementul introdus

# Rulare
Programul va fi rulat:
```
./tema1 M hashi.in hashi.out
```
unde:
```
• M – reprezinta numarul de bucket-uri din tabela hash
• hashi.in – fisierul de date de intrare
• hashi.out – fisierul de iesire
• Fisierul de intrare va contine fiecare comanda pe o linie noua
• Rezultatele corespunzatoare fiecarei comenzi se vor afisa pe cate o linie
• In cazul aparitiei coliziunii, inserarea perechilor (Key, Value) in bucket-uri se va face ordonat dupa cheie ("Key")
• Implementare folosind liste dublu inlantuite circulare generice.
```

# ------------------------------------------
Drepturile de autor fata de crearea checkerului si conditiei apartin echipei de Structuri de Date 2021 UPB

Implementarea codului: Calmis Liviu