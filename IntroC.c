#include<stdbool.h>
#include<stdio.h>
int main(){
    char c=100;
    short s=-800;
    int i= 123456;
    long l=1234567890;

    /*
    MENCIONES NOTABLES
    int8_t blah blah
    OPERADORES BINARIOS & >> << la casita y la curvita 
    ++i incrementa y devuelve 
    i++ devuelve y incrementa 
    */

    printf("char(%lu): %d \n",sizeof(c),c);
    printf("char(%lu): %d \n",sizeof(s),s);
    printf("char(%lu): %d \n",sizeof(i),i);
    printf("char(%lu): %ld \n",sizeof(l),l);   
    printf("WASSUP\n");
    return 0;
}