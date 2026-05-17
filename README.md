[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3SRI_-8J)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23396244)
# Proiect PA 2025

Repository-ul conține scheletul proiectului și testele publice.

## Structură

`include/`
Headerele pentru modulele cerute.

`src/`
Fișierele pe care trebuie să le completați.

`tests/public/`
Teste publice pentru fiecare pas. Aici găsiți fișierele de intrare și ieșirea așteptată.

`build/`
Conține binarele pentru rularea testelor publice:
- `build/public_pas1`
- `build/public_pas2`
- `build/public_pas3`
- `build/public_pas4`

## Rulare teste publice

Pentru a rula toate testele publice:

```bash
make public-test
```

Pentru a rula testele publice doar pentru un pas:

```bash
./build/public_pas1 tests/public/pas1/entitati.csv tests/public/pas1/relatii.csv tests/public/pas1/interogari.txt
./build/public_pas2 tests/public/pas2/entitati.csv tests/public/pas2/relatii.csv tests/public/pas2/interogari.txt
./build/public_pas3 tests/public/pas3/entitati.csv tests/public/pas3/relatii.csv tests/public/pas3/interogari.txt
./build/public_pas4 tests/public/pas4/entitati.csv tests/public/pas4/relatii.csv tests/public/pas4/interogari.txt
```

Fiecare test public are și un fișier `expected.txt` cu rezultatul așteptat.

## Teste publice și teste private

Există două tipuri de teste:
- teste publice, incluse în acest repository;
- teste private, folosite la evaluare.

Faptul că testele publice trec nu garantează punctaj maxim.


## Descrierea implementarii

Proiectul implementeaza un Knowledge Graph reprezentat printr-un graf orientat ponderat. 
- Fiecare entitate este citita din fisierul `entitati.csv` si ii este atribuita un id, in ordinea citirii, iar apoi este stocata ca un nod in graf. 
- Relatiile sunt citite din `relatii.csv` si sunt adaugate in listele de adiacenta ale nodurilor sursa. 
- Interogarile sunt citite din `interogari.txt` si sunt puse intr-o coada de tip FIFO, procesarea se face in ordinea citirii interogarilor.

### Structurile de date utilizate

- **Graf cu liste de adiacenta**: Fiecare entitate devine un nod din graf, iar fiecare relatie devine o muchie orientata intre doua entitati. Muchiile unui nod sunt memorate intr-o lista de adiacenta. Aceasta reprezentare este facila pentru interogari care trebuie sa acceseze rapid vecinii unui nod. Pentru grafuri rare, listele de adiacenta sunt mai eficiente ca memorie decat o matrice de adiacenta, deoarece se aloca spatiu doar pentru muchiile existente.

- **Vector dinamic pentru nodurile grafului**: Nodurile grafului sunt pastrate intr-un vector dinamic. Fiecare nod are un `id` egal cu pozitia sa in vector, ceea ce permite acces rapid la un nod atunci cand se cunoaste id-ul acestuia.Vectorul este redimensionat atunci cand capacitatea curenta devine insuficienta. Astfel, proiectul nu depinde de o limita fixa pentru numarul de entitati.

- **BST pentru indexarea entitatilor dupa nume**: Pentru cautarea eficienta a entitatilor dupa nume se foloseste un arbore binar de cautare (Binary Search Tree). Cheia de comparatie este `entity.name`, iar comparatia se face lexicografic cu `strcmp`. Nodurile BST nu copiaza entitatile, ci pastreaza doar pointeri catre nodurile deja existente in graf. Astfel se evita duplicarea datelor si se pastreaza o singura sursa pentru informatia despre fiecare entitate.

- **Coada FIFO pentru interogari**: Interogarile citite din fisierul `interogari.txt` sunt memorate intr-o coada FIFO implementata cu lista simplu inlantuita si sunt procesate exact in ordinea in care apar in fisier. Fiecare element din coada contine o copie alocata dinamic a liniei citite, pentru a pastra continutul interogarii valid si dupa ce bufferul folosit la citire este reutilizat.

- **Vector folosit drept coada pentru BFS**: Pentru interogarea `PATH`, algoritmul BFS are nevoie de o coada in care sa introduca id-urile nodurilor prin care a trecut. Problema este ca noi deja avem o coada generica, dar ea stocheaza siruri de caractere, nu id-uri, ceea ce rezulta la crearea unei noi cozi implementate printr-un vector. Astfel, id-urile sunt stocate mult mai usor decat sa le convertim in stringuri si inapoi in id-uri. Aceasta coada are si ea pointer `head` si `tail`. 

- **Min-Heap pentru Dijkstra**: Interogarea `Dijkstra` cauta nodul cu distanta minima, iar pentru a putea selecta acest nod ne folosim de un min-heap, care stocheaza perechi `(node_id, dist)` si este ordonat crescator dupa `dist`, pentru a putea accesa cat mai rapid minimul. Aceasta structura este aleasa pentru a evita selectia minimului prin cautare liniara peste toate nodurile neprocesate.


### Complexitatea operatiilor EXISTS, EDGE, NEIGHBORS

`n` = numar de noduri.
`m` = numar de muchii.

- `EXISTS X`: cauta entitatea `X` in BST pentru a vedea daca exista. Complexitatea medie este `O(log n)`.

- `EDGE X Y`: cauta `X` si `Y` in BST pentru a vedea daca exista cele doua entitati, apoi parcurge lista de adiacenta a lui `X` pentru a vedea daca exista o muchie intre cele doua entitati. Complexitate medie: `O(log n + grad(X))`.Cautarea in BST contribuie cu `O(log n)`, iar verificarea muchiei contribuie cu `O(grad(X))`.

- `NEIGHBORS X`: cauta `X` in BST pentru a vedea daca exista si afiseaza toti vecinii directi din lista de adiacenta. Complexitate medie: `O(log n + grad(X))`.


 In cel mai rau caz, `grad(X)` poate ajunge pana la m (numarul de muchii), deci pentru EDGE si NEIGHBORS complexitatea poate fi scrisa si ca: O(log n + m).

### Complexitatea algoritmilor PATH (BFS) si DIJKSTRA

- **PATH X Y - BFS**: Interogarea `PATH` verifica existenta unui drum orientat de la `X` la `Y`. Pentru aceasta se foloseste BFS, pornind din nodul sursa.

  BFS exploreaza graful pe niveluri si foloseste:
  - un vector `visited`, pentru marcarea nodurilor deja vizitate;
  - un vector `parent`, pentru reconstruirea drumului;
  - o coada de id-uri implementata prin vector, cu indicii `head` si `tail`.

  Fiecare nod este introdus in coada cel mult o data, iar fiecare muchie este analizata cel mult o data. Complexitatea este: `O(n + m)`. Memoria auxiliara folosita este `O(n)`.


  - **DIJKSTRA X Y**: Interogarea `DIJKSTRA` determina drumul de cost minim intre doua noduri. Algoritmul foloseste costurile muchiilor si presupune costuri pozitive.

  Pentru algoritm se folosesc: 
  - un vector `dist`, unde `dist[i]` este cea mai buna distanta cunoscuta pana la nodul `i`;
  - un vector `parent`, pentru reconstruirea drumului minim;
  - un vector `visited`, pentru nodurile deja procesate;
  - un min-heap de perechi `(node_id, dist)`, pentru selectarea nodului cu distanta minima curenta.

  Min-heap-ul evita selectia minimului prin cautare liniara peste toate nodurile neprocesate. 
  La fiecare pas, se extrage cu `heap_pop` nodul cu distanta minima, apoi se relaxeaza muchiile care pleaca din acel nod. 
  Pentru fiecare muchie `u -> v`, se verifica daca drumul prin `u` imbunatateste distanta pana la `v`: `dist[u] + cost(u, v) < dist[v]`. Daca distanta este imbunatatita, se actualizeaza `dist[v]`, `parent[v]` si heap-ul.

  Complexitatea in timp este: `O((n + m) log n)`
  Complexitatea in spatiu este: `O(n)`


## Concluzie


Solutia urmareste ideea principala a proiectului: construirea unui Knowledge Graph pas cu pas, pornind de la datele citite din fisiere si ajungand la raspunsuri eficiente pentru interogari. Am folosit diferite structuri de date: liste de adiacenta pentru relatii, BST pentru cautarea dupa nume, coada pentru pastrarea ordinii interogarilor si min-heap pentru alegerea eficienta a nodului minim in Dijkstra. Rezultatul este o implementare organizata, in care fiecare componenta are un rol clar in procesarea grafului.



