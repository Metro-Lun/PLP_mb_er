#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"

// ============================================
// PILE DE CARACTERES (StackChar) - Implementation
// ============================================

StackChar* create_stack_char(int capacity) {
    StackChar* stack = malloc(sizeof(StackChar));
    if(stack == NULL) return NULL;
    
    stack->data = malloc(sizeof(char) * capacity);
    if(stack->data == NULL) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push_char(StackChar* stack, char c) {
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = c;
    }
}

char pop_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

char peek_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top];
    }
    return '\0';
}

int is_empty_char(StackChar* stack) {
    return stack->top == -1;
}

void free_stack_char(StackChar* stack) {
    if(stack != NULL) {
        free(stack->data);
        free(stack);
    }
}