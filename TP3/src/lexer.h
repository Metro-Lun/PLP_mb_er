#pragma once

typedef enum {
    OPERATEUR,
    OPERANDE
} TypeElement;

typedef enum {
    ENTIER,
    FLOTTANT
} TypeOperande;

typedef struct {
    TypeOperande type;
    union {
        int entier;
        double flottant;
    } valeur;
} Operande;

typedef struct {
    TypeElement type;
    union {
        char operateur;
        Operande operande;
    } data;
} Element;

int add_element(Element** elements, int* size, Element element_to_add);

Element* lex(char* operation);
