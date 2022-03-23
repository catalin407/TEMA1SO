# ***C Preprocessor***

## *Organizare*

Am folosit un '_hashmap_', un struct ce are ca atribute:
 - char *name
 - char *value

Luand drept exemplu linia

```
 #define VAR0 10 + 2
```

In acest caz *name* ar fi *VAR0* (symbol), iar *value* ar fi *"10 + 2"* (mapping)

### *Idee generala*

Programul functioneaza in urmatorul fel: 

0. Se citesc parametrii din linia de comanda, adica: 
    - fisierul de input .in din care se face citirea, daca acesta este omis, se face citire din stdin
    - fisierul de output in care se scrie, daca este omis, se face scriere la stdout
    - "pre"definiri de tipul KEY=VALUE
    - path-ul care directoare in care se afla headere
  1. Se citeste linie cu linie din fisier. In cadrul liniei sunt procesate/prelucrate cuvintele, astfel incat linia initiala se modifica, la nevoie.
  2. Din linia citita verificam cu _strstr_ daca avem o directiva de preprocesare (*#define*, *#if* etc), daca nu, atunci scriem linia respectiva, daca da, vedem care tip de directiva este folosind _strstr_ iar, pentru ce sti ce logica ar trebui folosita
  3. V1: Daca nu este citita o directiva, se apeleaza o functie de _find_and_replace_, care gaseste string-uri ce exista in hashmap, caz in care le inlocuieste, facand un nou string. Este luat in calcul si cazul in care nu ar trebui sa fie afisat/inlocuit (cand key-ul se afla intre " ", caz in care ar trebui sa fie considerat string)
  4. V2: Daca este citita o directiva, atunci se merge pe o logica specifica directivei. De mentionat este existenta unei auxiliare _static int canWrite_, care precizeaza state-ul in cazul directivelor conditionale
  
  > Side note: pentru #include se repeta pasii de mai sus pe noul fisier ce ar trebui inclus

  ## *How to use*

  ### *Linux*

Se foloseste make. Acesta va face compilarea si link-editarea fisierelor so-cpp.c, functions.c, hashmap.c, rezultant la final un executabil so-cpp. Acesta poate fi rulat fara argumente (citire din stdin), sau cu argumente, caz in care trebuie neaparat precizat path-ul catre un fisier de intrare

```
$ make
$ ./so
SAU
$ ./so -D VAR0=10 <input_file_path> <input_file_path>
```

### *Windows*

Se foloseste nmake. Similar cu varianta Linux, doar ca aici executabilul va fi de forma so-cpp.exe.
```
> nmake
> ./so-cpp.exe
SAU
> ./so.exe -D VAR0=10 <input_file_path> <input_file_path>
```
## Utilitate

Tema mi s-a parut utila, chit ca destul de muncitoreasca. Am inteles mai bine lucrul cu string-uri, dar in special ca am lucrat cu valgrind si am putut sa vad mult mai usor de unde apar memory leaks sau alte posibile erori. In schimb checker-ul pentru coding style nu mi s-a parut prea friendly, unele 'idei' pe care le dadea nu pareau atat de utile.

## Performanta?

Nu cred ca implementarea este cea mai buna (nici chiar naiva), sunt sigur ca ar fi loc de mai bine, in special la lucrul cu #include
## Git repository
[SO-assignments/Tema1](https://github.com/VilciuRazvan/SO-assignments)

## Bibliografie

https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm

https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm

https://www.tutorialspoint.com/c_standard_library/c_function_strchr.htm

https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
