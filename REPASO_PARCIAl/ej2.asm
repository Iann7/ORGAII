extern rand

section .data


cliente_str_nombre	         EQU	0
cliente_str_apellido	     EQU	21
cliente_str_nombre_compra    EQU    48
cliente_str__dni             EQU    60
stuct_cliente_str            EQU    64 

PACKED_cliente_str_nombre	        EQU	    0
PACKED_cliente_str_apellido	        EQU	    21
PACKED_cliente_str_nombre_compra    EQU     42
PACKED_cliente_str__dni             EQU     54 

section .text

global random_elem

; cliente_t[] ->rdi
; longitud    ->rsi  
random_elem:
    push rbp
    mov rbp,rsp
    v
    push rdi 
    push rsi 


    call rand ;nos queda el valor en rax 


    pop rdi 
    pop rsi

    div rax,rsi ;queda el modulo en rdx 
    mul rdx,64  ;multiplicamos por 64 (tamaño de la estructura) 
    mov rax,rdx ;movemos el offset a rax 
    add rax,rdi ;sumamos la direccion de memoria + el offset previamente calculado
    ;listo! ya tenemos todo

    pop rbp
    ret