Année: 2025-2026
----------------

# Travaux pratiques 4

## Objectifs

L'objectif de ce TP est d'intégrer un évaluateur d'expressions arithmétiques dans un interpréteur en langage C, capable de gérer les expressions en notations infixée et postfixée. Il s'agit de développer les structures de données et les algorithmes nécessaires pour analyser (parser) et évaluer ces expressions, en s'assurant que l'évaluateur s'intègre correctement dans l'interpréteur existant.

1. **Parser une expression en notation postfixée :** Implémenter un algorithme pour convertir une expression arithmétique en notation infixée vers sa forme postfixée (notation polonaise inverse).

2. **Évaluer l'expression postfixée :** Utiliser une pile (stack) pour évaluer correctement une expression en notation postfixée et produire le résultat.

3. **Intégrer l'évaluateur dans l'interpréteur existant :** Assurer que l'évaluateur s'intègre de manière fluide dans l'interpréteur déjà développé, permettant de traiter et d'évaluer les expressions arithmétiques saisies.


## Exercice 4.1 [★★★]

### Parser l'expression en notation postfixée

**Objectif :**

Écrire une fonction qui prend en entrée une chaîne de caractères représentant une expression arithmétique en notation infixée (par exemple, "3 + 4 * 5") et renvoie une chaîne de caractères représentant la même expression en notation postfixée (par exemple, "3 4 5 * +").

### Structures de données :

- **Tableau de caractères** : Utiliser un tableau pour stocker les opérateurs (par exemple, "+", "-", "\*", "/") et leurs priorités associées.
- **Pile d'opérateurs** : Utiliser une structure de pile (par exemple, un tableau de caractères avec un pointeur sur le sommet) pour stocker les opérateurs pendant la conversion.

### Étapes à suivre :

1. **Initialiser la pile d'opérateurs.**

2. **Parcourir la chaîne de caractères en entrée de gauche à droite.**

3. **Lorsqu'un opérateur est rencontré :**
   - Le pousser sur la pile si celle-ci est vide ou si l'opérateur courant a une priorité supérieure à celle de l'opérateur au sommet de la pile.
   - Sinon, évaluer les opérateurs sur la pile jusqu'à ce que la pile soit vide ou que l'opérateur courant ait une priorité inférieure à celle de l'opérateur au sommet de la pile.

4. **Lorsqu'un opérande (un nombre) est rencontré, l'ajouter directement à la chaîne de caractères de sortie.**

5. Répéter les étapes 3 et 4 jusqu'à la fin de la chaîne de caractères en entrée.

6. **Ajouter les opérateurs restants de la pile à la chaîne de caractères de sortie.**

### Exemple :

- **Entrée** : "3 + 4 * 5"
- **Sortie** : "3 4 5 * +"

## Exercice 4.2 [★★]

### Gérer les expressions avec parenthèses

**Objectif :**

Écrire une fonction (ou modifiez la fonction de l'exercice 4.1) qui prend en entrée une chaîne de caractères représentant une expression arithmétique en notation infixée incluant des parenthèses (par exemple, "(3 + 4) \* 5") et qui renvoie une chaîne de caractères représentant la même expression en notation postfixée (par exemple, "3 4 + 5 \*"). L'objectif est d'étendre le parser pour gérer les priorités des opérations en utilisant les parenthèses.

### Structures de données :

- **Pile d'opérateurs** : Utiliser une pile pour stocker les opérateurs et gérer la priorité des opérations, y compris les parenthèses.

### Étapes à suivre :

1. **Initialiser la pile d'opérateurs.**

2. **Parcourir la chaîne de caractères en entrée de gauche à droite.**

3. **Lorsqu'une parenthèse ouvrante `(` est rencontrée :**
   - La pousser directement sur la pile.

4. **Lorsqu'une parenthèse fermante `)` est rencontrée :**
   - Dépiler les opérateurs de la pile et les ajouter à la chaîne de sortie jusqu'à ce qu'une parenthèse ouvrante `(` soit rencontrée (la supprimer de la pile).

5. **Gérer les opérateurs et les opérandes comme précédemment :**
   - Ajouter les opérandes directement à la sortie.
   - Utiliser la pile pour gérer les opérateurs en tenant compte de leur priorité.

6. **Ajouter les opérateurs restants de la pile à la chaîne de caractères de sortie.**

### Exemple :

- **Entrée** : "(3 + 4) * 5"
- **Sortie** : "3 4 + 5 \*"

## Exercice 4.3 [★★]

### Évaluer l'expression postfixée

**Objectif :**

Écrire une fonction qui prend en entrée une chaîne de caractères représentant une expression arithmétique en notation postfixée (par exemple, "3 4 5 \* +") et renvoie la valeur de l'expression.

### Structures de données :

- **Pile d'opérandes** : Utiliser une structure de pile (par exemple, un tableau de nombres avec un pointeur sur le sommet) pour stocker les opérandes pendant l'évaluation.

### Étapes à suivre :

1. **Initialiser la pile d'opérandes.**

2. **Parcourir la chaîne de caractères en entrée de gauche à droite.**

3. **Lorsqu'un opérande est rencontré, le pousser sur la pile.**

4. **Lorsqu'un opérateur est rencontré :**
   - Extraire les deux derniers opérandes de la pile.
   - Évaluer l'opération avec ces opérandes.
   - Pousser le résultat de l'opération sur la pile.

5. Répéter les étapes 3 et 4 jusqu'à la fin de la chaîne de caractères en entrée.

6. **La valeur finale sur la pile est le résultat de l'expression.**

### Exemple :

- **Entrée** : "3 4 5 * +"
- **Sortie** : 23


## Exercice 4.4 [★]

### Intégrer l'implémentation dans l'interpréteur

**Objectif :**

Intégrer les fonctions de parsing et d'évaluation des expressions arithmétiques dans l'interpréteur existant afin de permettre l'exécution de commandes comportant des expressions arithmétiques.

### Étapes à suivre :

1. **Ajouter les fonctions de parsing et d'évaluation à l'interpréteur.**

2. **Adapter l'interpréteur pour reconnaître les expressions arithmétiques :**
   - Modifier l'interpréteur pour qu'il détecte automatiquement les expressions arithmétiques dans les commandes saisies.
   - Appeler les fonctions de parsing et d'évaluation appropriées lorsque des expressions arithmétiques sont détectées.

3. **Tester l'interpréteur avec des expressions arithmétiques :**
   - Vérifier que l'interpréteur retourne des résultats corrects pour diverses expressions arithmétiques en notation infixée et postfixée.

### Exemple :

- **Entrée** : `> 3 + 4 * 5`
- **Sortie** : `23`

