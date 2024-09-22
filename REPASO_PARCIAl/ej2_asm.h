#ifndef ej_2_h
#define ej_2_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 21
typedef struct cliente_str {
char nombre[NAME_LEN];
char apellido[NAME_LEN];
__uint64_t compra;
__uint32_t dni;
} cliente_t;

void random_elem(cliente_str[],int longitud);


#endif