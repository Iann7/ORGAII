#include<stdbool.h>
#include<stdio.h>
#define  N 4
int main(){
    char c=100;
    short s=-800;
    int i= 123456;
    long l=1234567890;

    __uint32_t aa[N] ={0,20,14,40};
    __uint32_t bb[] ={0,20,14,40};
    __uint32_t cc[N]={0}; // {0,0,0,0}
    __uint32_t dd[] ={[1]=20,[2]=14,[3]=40};
    __uint32_t ee[N]; 
    __uint32_t f[N] ={2,4};

    bool bb = true==false ? true : true;
    printf("POS 1: %d \n",f[0]);
    printf("POS 2: %d \n",f[1]);
    printf("POS 3: %d \n",f[2]);
    printf("POS 4: %d \n",f[3]);

    /*
    MENCIONES NOTABLES
    int8_t blah blah
    OPERADORES BINARIOS & >> << la casita y la curvita 
    ++i incrementa y devuelve 
    i++ devuelve y incrementa
    a=b=c=0 asigna 0 a a,b y c. :]
    devuelven 1 si la condicion es verdadera y 0 si es falsa 
    un entero es considerado verdadero si es distinto de 0 
    MUY BIEN PIBE 
    i++ != ++i 
    << =desplazamiento a izq
    >> =desplazamiento a der 
    EVITAR COMPORTAMIENTOS INDEFINIDOS :[
    a que le llamamos mascaras? 
    nos sirve para extraer información de los bits 
    ^ :^]
    ^ = xor 
    ~ = negar un bit
    ARRAYS :D 
    el objeto array no guarda el length del array  
    char s[] = "hola!";
    char u[] = {'a','b','c','\0'}; es importante cerrar con 0 sino se va a quedar buscandolo 
    char *u = "string!"; //u es un puntero a un char, en este caso a S 
    *u no es un array tradicional, no lo vas a poder escribir 
    por que solo estas apuntando al primer string 
    va a tirar un segfault :D
    debugger godtier 
    se declara la funcion antes de implementarla 
    block scope y file scope
    el scope se refiere al lugar en el codigo donde un identificador 
    puede ser accedido
    */

    printf("char(%lu): %d \n",sizeof(c),c);
    printf("char(%lu): %d \n",sizeof(s),s);
    printf("char(%lu): %d \n",sizeof(i),i);
    printf("char(%lu): %ld \n",sizeof(l),l); 
    printf("%d\n",N);  
    printf("WASSUP\n");
    /*while (i--)
    {
        printf("i=%d\n",i); // imprimiria el 0 
        //por que vale en la condicion i-- (devuelve 1)

    }*/ 

   __uint32_t a[N];
   /*int i=0;
   while(i<N){
    a[i]=i;
    i++;
   }
   for(int k=0;k<N;k++){
    a[i]=i;
   }*/
    return 0;
}