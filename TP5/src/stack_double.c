#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"

// ============================================
// PILE DE NOMBRES (StackDouble) - Implementation
// ============================================

StackDouble* create_stack_double(int capacity) {
    StackDouble* stack = malloc(sizeof(StackDouble));
    if(stack == NULL) return NULL;
    
    stack->data = malloc(sizeof(double) * capacity);
    if(stack->data == NULL) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push_double(StackDouble* stack, double value) {
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

double pop_double(StackDouble* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return 0.0;
}

int is_empty_double(StackDouble* stack) {
    return stack->top == -1;
}

void free_stack_double(StackDouble* stack) {
    if(stack != NULL) {
        free(stack->data);
        free(stack);
    }
}
