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
string_proc_list_add_node_asm:
push rbp
mov rbp.rsp
push rdi
sub rsp,8 
mov rdi,rsi 
mov rsi,rdx
call string_proc_node_create_asm

pop rbp
ret

















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