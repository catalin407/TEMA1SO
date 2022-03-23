# ***Tema 1 Multi-platform Development***

## *Organizare*

Am implementat o structura de tip '_hashmap_', ce are ca atribute:
 - char *name
 - char *value

M-am ghidat dupa exemplul urmator

```
 #define VAR0 1
```

Unde *name* ar fi *VAR0* (symbol), iar *value* ar fi *1* (mapping)

### *Idee generala*

Programul functioneaza-ish in felul urmator: 

0. Se citesc parametrii din linia de comanda, adica: 
    - fisierul de input .in din care se face citirea, daca acesta nu exista citirea se va face din stdin
    - fisierul de output in care se scrie, daca acesta nu exista afisarea se va face in stdout
    - "pre"definiri in cazul flagului *-D*
  1. Se citeste linie cu linie din fisier. In cadrul liniei sunt prelucrate cuvintele, iar linia se modifica, daca este cazul.
  2. Linia citita este verificata cu _strstr_ daca avem o directiva de preprocesare (*#define*, *#if* etc), daca nu, atunci scriem linia respectiva, daca da, verificam de tip de directiva este cu _strstr_ si aplicam logica corespunzatoare fiecareia
  3. In cadrul functie _add_define_hash_ se petrece toata logica de preprocesare, aici verific ce tip de logica trebuie folosita. Se parcurge fiecare linie citita si se verifica daca exista un _symbol_ din _hashmap_ in acea linie si il inlocuieste cu _value_ din _hashmap_

  ## *How to use*

  ### *Linux*

Se foloseste make. Acesta va face compilarea si link-editarea fisierelor so-cpp.c, functions.c, hashmap.c, rezultant la final un executabil so-cpp. Acesta poate fi rulat fara argumente (citire din stdin), sau cu argumente, caz in care trebuie neaparat precizat path-ul catre un fisier de intrare

```
$ make
$ ./so
SAU
$ ./so -D VAR0=1 <path_of_file> <path_of_file>
```

### *Windows*

Se foloseste nmake. Foarte similar cu varianta Linux, doar ca in acest caz executabilul va fi de forma so-cpp.exe.
```
> nmake
> ./so-cpp.exe
SAU
> ./so.exe -D VAR0=1 <path_of_file> <path_of_file>
```
## Utilitate

Tema mi s-a parut utila, dar doar pentru o aprofundare/reamintire in ceea ce priveste lucrul cu _char*_. Cand vine vorba de checker, pot spune ca nu este cel mai formidabil, mai ales partea de coding-style, ce mi se pare mult prea restrictiv, mai ales ca in atatia ani toata lumea si-a format un coding-style ce sigur s-ar fi incadrat in standarde fara acele teste de coding-style ce mai mult iti te incurca, de multe ori dand sfaturi inutile. 

## Performanta?

Performanta nu este una formidabila, mai ales ca nu sunt implementare toate directivele.
## Git repository
[TEMA1SO](https://github.com/catalin407/TEMA1SO)

## Bibliografie

https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm

https://www.youtube.com/watch?v=2Ti5yvumFTU

https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm

https://www.tutorialspoint.com/c_standard_library/c_function_strchr.htm

https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

https://stackoverflow.com/
