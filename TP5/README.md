# Bibliothèques
* `stdio.h`
* `string.h`
* `stdlib.h`
* `ctype.h`

# Références
*
*

# Difficultés
* Problèmes de gestion des contextes avec `strtok` : une mauvaise compréhension des contextes de cette fonction nous a bloqués sur l'exercice 5.2, lors du split d'un string sur l'espace. Repli sur `strtok_r`
* Gestion des références initialement mauvaise, notamment sur les `char*` : utilisation de `strdup` pour régler le problème

# Commentaires
* Un `Makefile` est présent pour compiler et lancer simplement le TP.

  - `make` compile le projet
  - `make run` lance l'exécutable
  - `make clean` supprime l'exécutable

