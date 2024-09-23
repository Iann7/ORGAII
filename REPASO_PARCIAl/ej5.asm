extern malloc 
extern calloc 
extern free 

str_array_size EQU 0 
str_array_capacity EQU 1 
str_array_data EQU 8
STRUCT_str_array EQU 16 


;typedef struct str_array {
;   uint8_t size;----1 byte--0
;   uint8_t capacity; ---1 byte--1 + 6 de padding
;   char** data;---- 8byte-- 8
;} str_array_t;--16

;Implementar las siguientes funciones en asm:
;str_array_t* strArrayNew(uint8_t capacity)
                                ;rdi
;Crea un array de strings nuevo con capacidad indicada por capacity.

;uint8_t strArrayGetSize(str_array_t* a)
;Obtiene la cantidad de elementos ocupados del arreglo.

;char* strArrayGet(str_array_t* a, uint8_t i)
;Obtiene el i-esimo elemento del arreglo, si i se encuentra fuera de rango, retorna NULL.

;char* strArrayRemove(str_array_t* a, uint8_t i)
;Quita el i-esimo elemento del arreglo, si i se encuentra fuera de rango, retorna NULL. El arreglo es reacomodado de
;forma que ese elemento indicado sea quitado y retornado.

;void strArrayDelete(str_array_t* a)
;Borra el arreglo, para esto borra todos los strings que el arreglo contenga, junto con las estructuras propias del tipo
;arreglo.



section .data 


section .text 
    ;parametros 
    ;capacidad->RDI
    strArrayNew:
        push rbp
        mov rbp,rsp
        push r12   ; usamos r12 que es no volatil, tenemos que preservarlo
        push r13


        
        ;sizeof(STRUCT_str_array)
        ; Crear cosas = malloc 
        mov r12,rdi ;pasamos capacity a un reg no volatil
        xor rdi, rdi
        mov rdi, [STRUCT_str_array]; carga el tamaño del struct = 16 bytes
        ;preservamos rdi en la llamada a malloc 
        
        ; un malloc para el struct
        call malloc 

        ; inicializar size = 0
        mov byte [rax+str_array_size], 0        ; porque no tengo arrays aún, solo el
ntenocedor
        ; inicializar capacity
        mov byte [rax+str_arra = y_capacity],r12 ;guardamos la capacidad en el nuevo espacio de memoria
        mov r13,rax ;guardamos la direccion de memoria en r13 (no-volátil, pushearlo)

        ; r12 = capacidad * 8 (tamaño de puntero)
        mul r12,8  ;lo multiplica * la cantidad esperada de ese struct(capacity) 
        ; un malloc para mi nuevo  array de punteros a string > 2 * 8 bytes   (cada puntero es de 64 bits = 8 byte)
        call malloc



        ; r13 tiene el puntero al struct >> [struct + str_array_data] nos da para escribir en char** data, le pasamos el puntero       
         mov [r13+str_array_data],rax ;guardamos la "nueva lista de strings" en el struct 
        mov rax,+r13                  ;devolvemos el puntero a struct 
        
        
        
        pop r13 
        pop r12 ; liberamos el r12 no volatil previamente usado
        add rsp, 8
        ret

; rax puntero para devolver el
; puntero str_array_t* strArrayNew
;parametros
; (str_array_t*) a->RDI
strArrayGetSize:
     push rbp
     mov rbp,rsp

    mov rax,[rdi+str_array_size] ;dir de memoria + el offset del size en el struct     
     
     pop rbp
     ret

;parametros
;str_array_t* a -> rdi
;uint8_t i      -> rsi 



;[puntero_1,puntero_2,puntero_3]
;[*,*,*,*,*] = **
; cada elemento guardado es un puntero
strArrayGet:
     push rbp
     mov rbp,rsp

     xor rdx, rdx
     mov rdx,[rdi+str_array_size] ;cargamos el size en rdx 
     cmp rsi,rdx 
     jg  fuera_de_rango

     ;en este caso como el puntero de 8 bytes pisa todo el registro 
     mov rdx,[rdi+str_array_data] ;cargamos el puntero a char** en rdx
     mul rsi,8                    ;multiplicamos el indice por 8 (el tamaño del puntero) 
     add rdx,rsi                  ;sumamos el indice a la dir de char** 
     mov rax,rdx                  ;movemos el indice a rax para retornarlo
     fin:
     pop rbp
     ret

    fuera_de_rango:
        xor rax,rax ;hacemos que rax sea 0
        jmp fin
     

;parametros
;str_array_t* a -> rdi  
; uint8_t i     -> rsi 
strArrayRemove:
     push rbp
     mov rbp,rsp
     
     ;fuera de rango, tuki

     ;en rango: idea:
          ; conseguir puntero del índice, en us lugar poner 0s, devolver dicho puntero: capacity
          ;queda igual, size = size - 1   xor rdx,rddx


          
     mov rdx,[str_array_size]
     cmp rsi,rdx 
     jg  fuera_de_rango

     mov rdx,[rdi+str_array_data] ;cargamos el puntero a char** en rdx
     mul rsi,8
     add rdx,rsi                  ;sumamos el indice a la dir de char** 
     mov rax,rdx                  ;movemos el indice a rax para retornarlo


    ;

     ;TO-DO LLAMAR A UNA FUNCION QUE LIBERE 
     ;EL RESTO DEL STRING
     ;(ESO LO TENEMOS HECHO EN EL TP1-A)


        ; me guardo valor de string
        ; 000000
        ;*char 

     pop rbp
     ret
     
     fuera_de_rango:
        xor rdi,rdi ;rdi=0
        inc rdi     ;rdi=1
        call malloc ;llamamos a malloc con rdi=1 
        mov byte [rax], 0

        jmp fin


strArrayDelete:
     push rbp
     mov rbp,rsp
     
    
    ;??? ??? ??? 


     pop rbp
     ret








