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
