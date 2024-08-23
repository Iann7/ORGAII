#include <stdio.h>
/*
cuando vos declaras variables el compilador va a intentar alienarte los datos 
palabra(word) es la cantidad de bits natural que el procesador puede manejar por oepración

la memoria es direccionable a nivel BYTE
los accessos a memoria son mas eficientes si se hacen en palabras 

la alineación de los datos es importante para el rendimiento

un dato se encuentra alineado a N bytes si su dirección de memoria es multiplo de N 

cada TIPO DE DATO tiene su propio req de alineación 

EJ: un int de 32 debe estar alineado a 4 bytes

PADDING 
*/

//IMPORTANTE
//LOS STRUCT SE COPIAN!!!!!
#define NAME_LEN 50 

struct player {
	long elo;
	char name[NAME_LEN+1];
	int ranking;
};

struct player player1 = {2800,"Magnus Carlsen",1};
struct player player2 = {100,"yo",100};
struct player player3 = {.name = "Nakamura",.ranking=2,.elo=2600};




//DEFINICIÓN DE TIPOS
/*
et an alternate name to 
 existing data type. The typedef keyword in C is very useful in assigning a
 convenient alias to a built-in data type as well as any derived data type such as a struct, a union or a pointer.

 useful for unwieldy types such as struct blah blah 
*/
typedef float real_t;
typedef int quantity_t;

/*
dials_code_t country_codes[100] = {
2 [0] = {"Argentina", 54},
3 [1] = {"Brasil", 55},
4 [2] = {"Chile", 56},
5 [3].pais = "Uruguay", [3].code = 598,
  me pareció copado la linea 5 que define solo a una variable de una struct 
7 };
*/

// cada campo esta alienado con su tamaño, se inserta padding para cumplir con los req de alineación
// una estructura siempre se alinea con el mayor de los req de alineación de sus campos 
// NO confundir sizeof con tamaño de alineación 
// packed deshabilita el padding 
// que responsabilidad cae sobre el programador? ordenar bien las variables del struct para utilizar apropiadamente 
// el espacio en memoria 
//para que sirve el packet? 
/*
por ej en redes viene todo en serie sin padding, entonces cuando vos queres leer eso una forma linda de leerlo es con packet asi te
ahorras de quilombos :]
*/

//cual es el tamaño de player

//If we have a 32-bit processor, then the processor reads 4 bytes at a time, which means that 1 word is equal to 4 bytes.

//UN PUNTERO ES UNA VARIABLE QUE ALMACENA DIRECCIÓN EN LA MEMORIA 
/*
TIPOS DE MEMORIA EN C 
					Scope		  					Lifetime
GLOBAL				Archivo completo				tiempo de vida de la app
ESTATICA			depende donde se declare		tiempo de vida de la app 
AUTOMATICA(LOCAL)	depende donde se declare		mientras la funcion/bloque este en aplicación
DINAMICA			determinado por los punteros	Hasta que la memoria sea liberada	
					que referencian esta memoria
*/

//se come el primer character (no lo pone en mayus) por las razones listadas abajo
void to_uppercase(char *str) { 
	//POR ASOCIATIVIDAD GANA EL ++
	//el while termina cuando termina el string 
	// VERSION ARREGLADA => str[i] != '\0'
	while (*str++){
		// if esta en el rango de las minusculas 
 		if (*str >= 'a' && *str <= 'z') {
			//then aumenta el valor para que pase a ser MAYUS 
 			*str += ('A' - 'a');
 		}
 	}
 }




int main(){
	//DECIMOS QUE P "APUNTA" A X 
	int x=42;
	int *p =&x;
	char text[] ="poneme en mayusculas,flaco!";
	int arr[7] = 	{1,2,3,4,5,6,7};
	int *arr_pointer = arr; 
	__uint32_t a[]={100,200,300};
	__uint32_t *p_dos = a;

	/*
	IMPORTANTE!!!:(void*) estamos casteando &x &p como void pointer :]
	The void pointer in C is a pointer that is not associated with any data types
	(void*) &<tu_variable> me da la dirección de la variable
	(void*) p me devuelve el valor de p (la dirección de X)
	*p si p es un puntero me da el valor
	*/

	/*
	p es un puntero a int,por lo tanto al hacer p+1 estamos	sumando 4 bytes a la dirección de memoria ne p
	p[0] == *(p+0) == *p
    p[1] == *(p+1)
 	...
    p[n] == *(p+n)
	*/

	/*
	1 void swap(int a, int b) {
	2 int tmp = a;
	3 a = b;
	4 b = tmp;	
	5 }
	6 int main() {
	7 int x = 10, y = 20;
	8 swap(x, y);
	9 printf("x: %d, y: %d\n", x, y);
	10 }

	este codigo no funciona por que cambia los valores en swap pero no actualiza las variabeles de main()
	por lo cual, no cambia nada 
	*/

	/*
	1 void swap(int *a, int *b) {
	2 int tmp = *a;
	3 *a = *b;
	4 *b = tmp;
	5 }
	6 int main() {
	7 int x = 10, y = 20;
	8 swap(&x, &y);
	9 printf("x: %d, y: %d\n", x, y);
	10 }

	ESTO VALE, por que le estas pasando los punteros (i.e la dir de mem) y luego modificando 
	los valores en su dir de mem original
	*/

	printf("Dir de x: %p Valor: %d\n", (void*) &x, x);
	printf("Dir de pi: %p Valor: %p\n", (void*) &p, (void*) p);
	printf("Valor de lo que apunta p: %d\n", *p);

	printf("x: %d\n", x);
	*p = 200;
	printf("x: %d\n", x);

	//ARITMETICA PUNTEROS 
	//parte 1
	printf("%d\n",*p_dos); //PRINTEA 100
	p_dos++;
	printf("%d\n",*p_dos); //PRINTEA 200
	p_dos++;
	printf("%d\n",*p_dos); //PRINTEA 300

	//parte 2
	printf("%d\n", *arr_pointer); // imprime 1
	printf("%d\n", *(arr_pointer+1)); // imprime 2
	printf("%d\n", *(arr_pointer+2)); // imprime 3
	printf("%d\n", arr_pointer[4]); // imprime 5

	//CHAR ARITMETICA 
	to_uppercase(text);
	printf("Texto en mayus: %s\n",text);
	return 0;

	//MEMORIA DINAMICA
	//area de memoria que se asigna en tiempo de ejecución
	//una de las capacidades de los punteros radica en la capcidad de alocar memoria en tiempo de ejec
	//malloc SE USA PARA ALOCAR MEMORIA
	//free PARA LIBERAR MEMORIA
	//void *malloc(size_t size); 
	//void free(void *ptr);
	//MEMORIA DINAMICA TE SIRVE CUANDO NO SABES CUANTAS VARIABLES TENES DANDO VUELTA

	// EJEMPLO DE ENUM
	typedef enum e_type{
		TypeFAT32=0,
		TypeEXT4 =1,
		TypeNFTS = 2
	} type_t;

	 typedef struct node {
		void* data;
		struct node* next;
	} node_t;
	typedef struct list {
 		type_t type;
 		__uint32_t size;
 		node_t* first;
 	} list_t;

}
//valgrind es muy util para detectar los siguientes errores 
//DOUBLE FREE: es LIBERAR la dirección de memoria dos veces 
//USE AFTER FREE: acceder a memoria que ya fue liberada 
//DANGLING POINTER: pointer que apunta a una dirección de memoria que ya NO es valida
//(*p_struct).field es equivalente a p_struct->field USAR FLECHITA
//PUNTERO NULL ES UN PUNTERO QUE NO APUNTA A NADA,
//SE USA PARA INDICAR QUE EL PUNTERO NO APUNTA A NADA
// el problema de las memory leaks es con los programas que la siguen generando constantemente 

/*
MEMORIA DINAMICA 
--------------------> Direcciones altas
segmento STACk	|
------------	|
	|			|--> TAMAÑO LIBRE
	V			|
espacio libre	| 
	 ^			|
	 |			|
-------------
segmento HEAP 	| 
segmento BSS 	|---> SEGMENTO FIJO
segmento DATA 	|
segmento TEXT 	|
---------------------> direcciones bajas
Stack frame: direcciones de retorno, parametros y var locales
HEAP: variables dinamicas administradas por malloc/free
BSS: variables globales no inicializadas y variables estaticas
DATA variables globales inicializadas y variables estaticas
*/
/*
puntero a funcion EJEMPLO
la idea es que tenes un puntero...que apunta a una funcion
lo divertido es que podes hacer que el puntero apunte a cualquier otra funcion y funca!
void (*print)(int) = print_int;
13 print(42); // () desreferencia el puntero a funci´on
14 print = print_float;
15 print(3.14);
*/