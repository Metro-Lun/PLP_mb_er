# Rapport synthétique TP2

Mehdi BOURBON, Eli ROISMAN

## Sommaire

- [Rapport synthétique TP2](#rapport-synthétique-tp2)
  - [Sommaire](#sommaire)
  - [Débogage avec l'outil GDB](#débogage-avec-loutil-gdb)
      - [Dans bash](#dans-bash)
      - [Dans l'invite (gdb)](#dans-linvite-gdb)
  - [Chaîne de compilation GCC](#chaîne-de-compilation-gcc)
      - [Avec un seul fichier](#avec-un-seul-fichier)
    - [Avec plusieurs fichiers](#avec-plusieurs-fichiers)
  - [Manipulation de chaînes de caractères](#manipulation-de-chaînes-de-caractères)
    - [Commandes principales](#commandes-principales)
    - [strcpy](#strcpy)
    - [strlen](#strlen)
    - [strcat](#strcat)
    - [strcspn](#strcspn)
    - [strstr](#strstr)
    - [strcmp](#strcmp)
  - [Gestion des structures pour les données et recherche dans les fichiers](#gestion-des-structures-pour-les-données-et-recherche-dans-les-fichiers)
    - [struct](#struct)
    - [Lecture et recherche dans les fichiers](#lecture-et-recherche-dans-les-fichiers)
    - [fopen, fgets, fclose](#fopen-fgets-fclose)
    - [Algorithme de recherche d'occurrences multiples](#algorithme-de-recherche-doccurrences-multiples)
    - [Comparaison manuelle de chaînes](#comparaison-manuelle-de-chaînes)

## Débogage avec l'outil GDB

#### Dans bash

1. Compiler avec informations de débogage : `gcc -ggdb3 couleurs.c -o couleurs`

2. Lancer GDB : `gdb couleurs`

#### Dans l'invite (gdb)

Exécuter le programme : `r` (le programme s'arrête en cas d'erreur. Pour voir la pile d'appels : `dt`)

Placer un point d'arrêt à la ligne 12, par exemple : `break couleurs.c:12`

Exécuter jusqu’au point d’arrêt : `r`

Inspecter les variables :

```bash
p tableau
p tableau[0]@5
```

Avancer instruction par instruction : `n`

Continuer l’exécution jusqu’au prochain point d’arrêt ou fin : `continue`

Quitter GDB : `quit`

## Chaîne de compilation GCC

#### Avec un seul fichier

```bash
# Préprocesseur
gcc -E couleurs.c -o couleurs.i

# Compilation
gcc -O2 -S couleurs.i -o couleurs.s

# Assemblage
gcc -c couleurs.s -o couleurs.o

# Edition de liens
gcc couleurs.o -lm -o couleurs

# Exécution
./couleurs
```

### Avec plusieurs fichiers

```bash
# Préprocesseur
gcc -E main.c -o main.i
gcc -E volume.c -o volume.i
gcc -E surface.c -o surface.i

# Compilation avec optimisation
gcc -O3 -c main.i -o main.o
gcc -O3 -c volume.i -o volume.o
gcc -O3 -c surface.i -o surface.o

# Edition de liens
gcc main.o volume.o surface.o -lm -o sphere

# Exécution
./sphere
```

## Manipulation de chaînes de caractères

avec l'utilisation de la librairie `string.h`

Pour inclure cette librairie au programme : `#include <string.h>`

Sont recensées ici les commandes utilisées au cours du TP2.

### Commandes principales

### strcpy

`strcpy(dest: char*, src: char*)`

Copie la chaîne `src` à la place de la chaîne `desc`.

Exemple :

```c
char *string1 = "Le beurre";
char *string2 = "Bonjour le monde";

strcpy(string2, string1);
printf("%s", string2); // affiche "Le beurree monde"
```

### strlen

`strlen(string: char*)`

Calcule la longueur d'une chaîne de caractères

Exemple :

```c
char* machin = "J'ai faim";
printf("%lu", strlen(machin)); // affiche 9
```

### strcat

`strcat(dest: char*, src: char*)`

Concatène deux chaînes de caractères.

Exemple :

```c
char dest[50] = "Bonjour ";
char src[8] = "le monde";

strcat(dest, src);

printf("%s", dest); // affiche "Bonjour le monde"
```

### strcspn

`strcspn(string: char*, characters: char*)`

Calcule la taille d'une sous-chaîne de `string` avant la première occurrence de l'un des caractères dans `characters`.

Exemple :

```c
char myStr[] = "Une pomme, une poire";

int pos = strcspn(myStr, ",.!?");
printf("%d", pos); // affiche 9
```

### strstr

`strstr(chaine: char*, souschaine: char*)`

Renvoie un pointeur vers la première occurrence de `souschaine` dans `chaine`. Renvoie un pointeur `NULL` s'il n'y a pas de `souschaine` dans `chaine`.

Exemple :

```c
char chaine[255] = "Hamburger";
char *subptr = strstr(chaine, "urg");
if (subptr != NULL) {
  printf("%s", subptr); // affiche "urger"
}
```

### strcmp

`strcmp(chaine1: char*, chaine2: char*)`

Compare les deux chaînes de caractères et renvoie un "booléen" pour indiquer si elles sont identiques ou non.

Exemple :

```c
char *chaine1 = "Bonjour";
char *chaine2 = "Bonjour";
char *chaine3 = "Hello";
char *chaine4 = "Tartiflette";

printf("%d", strcmp(chaine1, chaine2)); // renvoie 0
printf("%d", strcmp(chaine3, chaine4)); // renvoie 1
```

## Gestion des structures pour les données et recherche dans les fichiers

### struct

Les structures permettent de regrouper plusieurs variables de types différents sous une même entité logique.

Définition et déclaration :

```C
struct etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note;
};
```

Manipulation des données :

Pour manipuler un tableau de structures (par exemple 5 étudiants), on accède aux champs via l'opérateur point .. Attention, l'affectation des chaînes de caractères dans une structure nécessite toujours `strcpy`.

Exemple :

```C
// Pour les chaînes : utilisation de strcpy
strcpy(etudiants[i].nom, nom);

// Pour les types numériques : affectation directe
etudiants[i].note = note;
```

### Lecture et recherche dans les fichiers

### fopen, fgets, fclose

- `fopen(nom, "r")` : Ouvre le fichier en lecture seule. Il est crucial de vérifier si le pointeur retourné est NULL (fichier inexistant ou erreur).
- `fgets(tampon, taille, fichier)` : Lit une ligne complète (y compris les espaces) jusqu'au saut de ligne.
- `fclose(fichier)` : Ferme le fichier proprement après utilisation.

### Algorithme de recherche d'occurrences multiples

Pour compter combien de fois une phrase apparaît dans une ligne, on peut utiliser une boucle while avec arithmétique de pointeurs sur le résultat de `strstr` :

```C
char *pos = ligne;
while ((pos = strstr(pos, phrase)) != NULL) {
    count++;
    // On avance le pointeur de la longueur de la phrase trouvée
    // pour continuer la recherche après celle-ci.
    pos += strlen(phrase); 
}
```

### Comparaison manuelle de chaînes

L'exercice 2.8 (`chercher.c`) demandait de comparer des chaînes sans utiliser la librairie standard (`strcmp`).

La logique implémentée parcourt les deux chaînes caractère par caractère tant qu'ils sont identiques :

```C
int comparer(const char *a, const char *b) {
     int i = 0;
     while (a[i] != '\0' && b[i] != '\0') {
          if (a[i] != b[i]) return 0; // Différence détectée
          i++;
     }
     // Les chaînes sont égales seulement si elles finissent en même temps
     return (a[i] == '\0' && b[i] == '\0');
}
```