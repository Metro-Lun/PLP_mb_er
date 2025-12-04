#pragma once
#include "lexer.h"

typedef struct {
    char operateur;
    int op1_initialized; // sert à voir si l'opérande 1 contient une valeur
    Operande operande1;
    Operande operande2;
} Expression;

Expression parse(Element* elements);