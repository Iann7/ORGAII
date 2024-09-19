;Primero cosa a tener a mano son los manuales 
;Volume 1 : Basic Architectures
;Volume 2:  Instruction Set reference 
;Volume 3 : System Programming guide
;entonrno de ejecución de 64 bits de intel 
;PC=Instruction Pointer Register 
;instrucciones reciben dos argumentos 
;section data-> segmento de data (directiva de ensamblador)
;%define SYS_MUTE directiva de preprocesador 
;PSEUDO INSTRUCCIONES 
;@@msg db '¡Hola Mundo!',10
;len EQU $ - msg
;$ es la direccion de memoria esa que apunta a la ultima posicion (en este caso lo que haya despues de 10) 
;$ es la direccion de lo ultimo que se escribio en el archivo 
;Msg direccion de memoria donde empezaban los datos 
;db es llenar memoria con cosas
;EQU a ver 

;Los operandos pueden ser 
;	Registros 
;	(add rdi rsi)
;	Memoria 
;	mov [LABEL] rax
;	sub r10 [rdx+4*rax+OFFSET]
;
;[1003] solo displacement
;[rbx] registro base solamente 
;[rbx + rsi*4] base + index*4
;[rbx+rdx] scale es 1
;[rax -8] displacement es -8
;[rax + rdi*8 -200] todos los componentes
;[rbx+counter] direccion de variable 'counter' como desplazamiento
;200 decimal 
;0200 decimal
;0xc8 hexa 
;0hc8 hexa
;0q310 octal
;110101010b binario
; times 4 db 'ja -> "jajajaja"
; db 0x55 -> solo el byte 0x55
buffer resb 64 ;reserva 64 bytes
wordvar resw 1 ;reserva un word
realarray resq 10; array de 10 qwords

;estas pseudo instrucciones deben ir en section .bss
; argument build: parametros de una funcion a ser invocada
; variables locales (si no alcanzan los registros)
; registros guardados
; frame pointer anterior
; frame de la funcion invocante 
; direccion de retorno
;   pusheada por call
; argumentos para esta función
;   del septimo para adelantae (64 bits)
;   en 32bits  TODOS
; caller saved
; caleee saved 
; para el ABI los punteros son enteros
; antes de realizar una llamada a una funcion la pila debe quedar alineada a 16 bytes
; los parametros se pasaran de derecha a izquierda a traves de la pila haciendo PUSH
; TODO PUSH DEBE TENER SU POP
; ¿Por que hace falta alinear la pila a 16 bytes si hacemos una llamada a otra biblioteca?
; para garantizar que siempre que tenemos la pila en la misma condicion cuando la tratamos
; ADMINISTRACION ABI
; espacio se reserva al entrar y se libera el salir
; frame pointer : rbp
; stack pointer rsp
; rsp apunta a rip
; padding para alinear a 16 bytes
; para hacer padding restamos 
; la pila esta alineada cuando RSp es multiplo de 16 
; registro volatil => preservar valores 
; acuerdense de poner ret en el parcial
; la ABI te da la garantia(te obliga) antes de hacer un call que la pila este alineada
; luego se llama call mas tus obligaciones lo cual va a desalinear a la pila
; PADDING LUEGO PARAMS LUEGO rip LLAMADORA, LA IDEA ES QUE PARAMS ESTE ALINEADO


; PROLOGO: es donde se reserva espacio en la pila para datos
; temporales, se agrega padding para mantenerla alineada a 16
; bytes y se preserva los valores de los registros no vol´atiles


;EPILOGO: es donde restauramos los valores de los registros no
;vol´atiles y devolvemos la pila a su estado inic

; ¿Cuál es el mecanismo utilizado para almacenar **variables temporales**?
;se almacenan en los registros y si no hay suficiente espacio se utiliza el stack para almacenarlos.

;RSP (Stack Pointer) -> tope de la pila
;RIP(Instruction Pointer) es lo que te apunta a la proxima instruccion 
;RBP(Base Pointer) para acceder a variables, justo abajo de RIP 