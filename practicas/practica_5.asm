shuffle_image2: DB 0x02,0x01,0x00,0x03,0x06,0x05,0x04,0x07,0x0A,0x09,0x08,0x0E,0x0D,0x0C,0x0F
todos128: times 16 db 128
; EJERCICIO 1
; el objetivo de este ejrcicio es implementear un cjto de funciones sobre una 
; lista doblemente enlazada de tamaño variable 
; para ello tenemos una estructura que indica el primer y el ultimo nodo,
; y cada nodo tiene punteros al anterior

;typedef struct string_proc_list_t{
;    struct string_proc_node_t* first    ;8
;    struct string_proc_node_t* last     ;8
;} string_proc_list                      ;16
;typedef struct string_proc_node_t{
;   struct string_proc_node_t* next//8
;   struct string_proc_node_t* previous//8
;   uint8_t type //16
;   char* hash //24
; } string_proc_node //32
;
; el primer ejercicio nos
; pide armate la funcion create en assembler 
; string_proc_list_create_asm(){

%DEFINE OFFSET_LIST_FIRST 0
%DEFINE OFFSET_LIST_LAST 8
%DEFINE STRUCT_SIZE_LIST 16
%DEFINE OFFSET_NODE_NEXT 0
%DEFINE OFFSET_NODE_PREVIOUS 8
%DEFINE OFFSET_NODE_TYPE 16
%DEFINE OFFSET_NODE_HASH 24
%DEFINE STRUC_SIZE_NODE 32

string_proc_list_create_asm:
push rbp 
mov rbp,rsp :prologo+alinear
mov rdi, STRUCT_SIZE_LIST
call malloc 
mov qword [rax + OFFSET_LIST_FIRST],0
mov qword [rax + OFFSET_LIST_LAST],0
pop rbp ;epilogo
ret 

;EL NODO TIENE QUE APUNTAR AL HASH PASADO POR PARAMETRO 
;rdi=type,rsi=hash
string_proc_node_create_asm:
push rbp
mov rbp,rsp
push rdi ;|---> preserva registros antes de llamar a calloc 
push rsi ;|-|
mov rdi,STRUC_SIZE_NODE
call malloc 
pop rsi
pop rdi
mov qword [rax+OFFSET_NODE_NEXT],0      ;hacemos qword por que es un inmediat?
mov qword [rax+OFFSET_NODE_PREVIOUS],0  ;hacemos qword por que es un inmediat?
mov [rax+OFFSET_NODE_TYPE].rdi
mov [rax+OFFSET_NODE_HASH],rsi
pop rbp
ret
;   C. dada una lista un tipo y un hash, agrega un nodo nuevo al final de la lista
;   con el tipo y el hash dado. Al igual que en el anterior no hay que copiar el hash   
add rsp,8
pop rdi
mov rsi,[rdi+OFFSET_LIST_LAST]
mov [rdi+OFFSET_LIST_LAST],rax
cmp rsi,0
jne .insertarNuevo
mov [rdi+OFFSET_LIST_FIRST],rax
jmp.fin

.insertarNuevo:
mov [rsi+OFFSET_NODE_NEXT],rax
mov [rax+OFFSET_NODE_PREVIOUS],rsi

.fin:
pop rbp 
ret
; D genera a partir del hash pasado por parametro, un nuevo hash concantenando todos los hashes 
;   de todos los nodos en la lista cuyo tipo coincide con el pasado por el parametro 
; rdi =list,rsi=type,rdx=hash
string_proc_list_apply_asm:
push rbp
mov rbp,rsp
sub rsp,16                          ;reservando espacio en la pila para guardar espacios locales
push r12                            ;pusheando registros no volatiles
push r13                            ;pusheando registros no volatiles
push r14                            ;pusheando registros no volatiles
push r15                            ;pusheando registros no volatiles
mov r15,rdi                         ;list
mov r14,rsi                         ;type
mov r13,rdx                         ;hash
mov rdi,1
call malloc                         ;res=""
mov qword [rax],0
mov [rbṕ-8],rax                     ;guardo tmp=rax
mov rdi,rax                         ;guardo res=""
mov rsi,rdx                         ;preparo con hash
call string_proc_node_create_asm
mov [rbp-16],rax                    ;guardo res=hash(copia)
mov rdi,[rbp-8]                     ;borro reserva tmp
call free 

;[rbp-8]=res,r13=hash,r14=type,r15=list
mov r12,[r15] ;r12=nodo_actual
.while:
cmp r12,0
je .fin ;if list->first == null then ret hash 
cmp [r12+OFFSET_NODE_TYPE],r14
;nodo_actual -> type == type
je .mismoTipo
.next:
mov r12,[r12] ;r12=nodo_actual->next
jmp .while
.mismoTipo:
mov rdi,[rbp-16] ;rdi=base
mov rsi,[r12+OFFSET]
;RSI=NODO_actual->hash
call str_concat
;rax=concat(hash,nodo_actual->hash)
mov rdi,[rbṕ-16] ;tmp=old_hash
mov [rbp-16],rax ;[rbp-16]=new_concat_hash
call free ;free old_hash
jmp .next


;EJERCICIO 2 
;  en orga2 llamamos combinarImagenes al filtro de datos que dadas dos imagenes
;   con formato BGRA de igual tamaño devuelve una tercera que combina las dos de la sig 
; forma 
; res[ij]_b = A[ij]_b + B[ij]_r
; res[ij]_g = { A[ij]_g + B[ij]_g si A[ij]_g > B[ij]_g
;             { promedio(A[ij]_g,B[ij]_g) cc 
; res[ij]_r = B[ij]_b - A[ij]_r
; Se recibe un puntero de memoria donde 
; ¿Cantidad de pixeles? Ancho*alto
; ¿Cantidad de iteraciones? ancho*alto/4
;
push rbp
mov rbp,rsp
mov r10,rdx ;r10 registro volatil no hay que preservarlo

mov eax,r8d
mul ecx
shr eax,2
mov r8d,eax ;r8w=cantidad de iteraciones 

xor rax,rax ;inicializamos rax a 0

.ciclo:
    movdqu xmm1,[rdi+rax]   ;movemos el puntero de rdi + rax 
    movdqu xmm2,[rsi+rax]   ;movemos el puntero de rsi + rax    
    movdqu xmm9,[shuffle_image2] 
    movdqa xmm8,[todos128]
    
    ; res[ij]_b = A[ij]_b + B[ij]_r
    pshufb xmm2,xmm9 ;aplicamos la mascara shuffle_img2
    ;componente blue
    modqu xmm3,xmm1
    paddsub xmm3,xmm2

    ; res[ij]_r = B[ij]_b - A[ij]_r
    ; componente rojo        


    movdqu xmm5,xmm2
    psubusb xmm5,xmm1 ;que instruccion rara TODO

    ;para hacer un promedio podemos hacerlo a mano o podemos hacer pavgb/pavgw
    ;¿Como hariamos la comparacion?
    ; ¡Ojo que PCMPGTB es una comparacion signada!
    ; uno podria resolver esto extendiendo a 16 bits con signo
    ; y despues hago la operacion 
    ; solucion #1 : extender de byte a word! 
    ; solucion #2 : sumar 128 a nuestros valores
    ;               al interpretarlos como signados se 
    ;               va a mantener el valor de orden
    ;               original 

    ;componente green
    ;xmm1 tiene pixeles de A
    ;xmm2 tiene pixeles de B
    movdqu xmm4,xmm1
    movdqu xmm0,xmm1
    movdqu xmm6,xmm1
    pavgb xmm4,xmm2 ;avg componente
    psubusb xmm6,xmm2 ;resta
    ;compare=mascara dinamica
    movdqa xmm5,xmm2
    paddb xmm5,xmm8 
    paddb xmm0,xmm8     
    PCMPGTB xmm0,xmm5 
    PBLENDVB xmm4,xmm6 ;dejo el average si no se cumple que es mas grande    
    ; tenemos los promedios en xmm4 y 
    ; las restas en xmm6
    ; instruccion PBLENDVB
    ; nosotros le pasamos dos registros xmm
    ; con los valores que vamos a querer que se mezclen
    ; asume que xmm0 es una mascara
    ; con eso va a mezclar el source y el destiny 
    ; el blend se va a fijar en la mascara
    ; y la mascara tiene todos unos o todos 0s
    ; en el otro caso era hacer un and
    ; y un and not 
    ; y ver los resultados     

    movdqu [r10+rax],xmm3 ;guardo el resultado en dst 
    add rax,16 
    ;aumentamos el offset asi no estamos 
    ;trabajando siempre con los mismos pixeles

    ;para hacer la primera operacion podemos hacer shift o shuffle
    ;vamos a cambiar los rojos con los azules en la imagen 2 
    
    dec r8d 
    jnz .ciclo 
pop rbp
ret
; typedef struct bgra_t{
;   unsigned char b,g,r,a
; } _a
; el primer atributo del struct es el que esta en la parte mas baja
; 0x00  | 0x1     | 0x2   | 0x3   | . . . 
; 0xBB  | 0xGG    | 0xRR  | 0xAA  | . . . 
; TODO JUGAR CON PACKED Y NOT PACKED
; como se va a ver esto si lo vemos cargado desde asm?
; ALPHA_RED_GREEN_BLUE_...
; 128 bits = 16 BYTES 
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;