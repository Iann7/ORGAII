global maximosYMinimos_asm

section .data 
;formato RGBA (leido como ARGB en memoria)
mascaraRoja: 
db 0, -1 ,-1 ,-1, 	;ABGR 3
db 4, -1, -1, -1,   ;0123 7
db 8, -1, -1, -1, 		; 11
db 12, -1, -1, -1		; 15
mascaraVerde:
db 1, -1 ,-1 ,-1,
db 5, -1, -1, -1,
db 9, -1, -1, -1,
db 13, -1, -1, -1
mascaraAzul:
db 2, -1 ,-1 ,-1,
db 6, -1, -1, -1,
db 10, -1, -1, -1,
db 14, -1, -1, -1


ceroUnoCeroUno:
times 2 dd 0x00_00_00_00, 0xFF_FF_FF_FF

todosUnos:
times 4 dd 0xFF_FF_FF_FF


colocarMyMs:
db 0,0,0,-1		; 0 ,0 ,0 ,M3,0 ,0 ,0 ,M2,0 ,0 ,0 ,M1,0, 0, 0, M0
db 4,4,4,-1		;		   12		   8		   4 		   0
db 8,8,8,-1		; M3,M3,M3,0, M2,M2,M2,0, M1,M1,M1,0, M0,M0,M0,0
db 12,12,12,-1


;########### SECCION DE TEXTO (PROGRAMA)
section .text

;void maximosYMinimos_asm(uint8 *src
;,uint8 *dst
;,uint32 width
;,uint32 height)
;PARAMETROS
; uint8 *src    ->RDI
; uint8 *dst    ->RSI 
; uint32 height ->rdx 
; uint32 width  ->rcx 
maximosYMinimos_asm:
;ej2:
;	push rbp
;	mov rbp, rsp
;	
;	;mascaras canales
;	movdqa xmm2,[mascaraRoja]
;	movdqa xmm3,[mascaraVerde]
;	movdqa xmm4,[mascaraAzul]
;	movdqa xmm8,[colocarMyMs]
;	
;	xor r8d, r8d ; contador de eje y (height)
;	xor rcx, rcx ; paridad
;	y_loop:
;		xor r9d, r9d ; contador de eje x (width)
;		;xor r10d,r10d
;		x_loop:
;
;			movdqu xmm1, [rsi]
;			add rsi, 4*4 ;     ; puntero a src += 4 pixels (4 byte c/u)
;
;			;movemos cada canal a un registro unico 
;			movdqu xmm5,xmm1 ;R
;			movdqu xmm6,xmm1 ;G
;			movdqu xmm7,xmm1 ;B
;
;			;separar los canales
;			pshufb xmm5, xmm2	;[mascaraRoja]
;			pshufb xmm6, xmm3	;[mascaraVerde]
;			pshufb xmm7, xmm4	;[mascaraAzul]
;            
;            ;tenemos que fijarnos paridad! 
;			cmp rcx, 0
;			jnz not_zero
;            
;            pmaxsd xmm5, xmm6
;            pmaxsd xmm5, xmm7
;			; rcx pasa a ser impar para la próxima
;			inc rcx
;
;			continue:
;			; xmm5 	[MaxYMin3, MaxYMin2, MaxYMin1, MaxYMin0]
;			; shufflear par
;            ;cconseguir : M[,M3,M3,0,M2,M2,M2,0,M1,M1,M1,0,M0,M0,M0,0]
;			pshufb xmm5, xmm8
;			;xmm5 ; cargar 4 pixeles blanco y negro a dst
;			add rdi, 4*4 ;
;			times 4 inc r9d ; 4 pixeles más >>>>
;			cmp r9d, edx ; ancho (width)
;			jl x_loop
;            
;            
;            
;		inc r8d  	 ; una fila más v
;		cmp r8d, ecx ; alto (height)
;		jl y_loop
;
;	
;	pop rbp
;	ret
;	not_zero:
;		; minimo de los tres
;        pminsd xmm5, xmm6 
;        pminsd xmm5,xmm7
;		; rcx pasa a aser par para la próxima
;        xor rcx, rcx
;		jmp continue
;

;PARAMETROS
; uint8 *src    ->RDI
; uint8 *dst    ->RSI 
; uint32 height ->rdx 
; uint32 width  ->rcx 
ej22y:	
	push rbp
	mov rbp, rsp

    movdqa xmm1,[mascaraRoja]   ;R
    movdqa xmm2,[mascaraVerde]  ;G
    movdqa xmm3,[mascaraAzul]   ;B
    movdqa xmm11,[ceroUnoCeroUno]   ;estabien??

	xor r9d, r9d
	.y_loop:
			
		xor r10d, r10d
		.x_loop:
			movdqu xmm4, [rsi]
			movdqa xmm5, xmm4
			movdqa xmm6, xmm4
			
			pshufb xmm4, xmm1     ;rojo
			pshufb xmm5, xmm2     ;verde
			pshufb xmm6, xmm3     ;azul

            ;pasammos los 3 canalos a xmm7 ->xmm9
            ;para calcular su maximo
            ;sin pisar el minimo         
			movdqa xmm7, xmm4
			movdqa xmm8, xmm5
			movdqa xmm9, xmm6

			pminud xmm4,xmm5	; min R G
            pminud xmm4,xmm6	; min (min R G) B
			            
            pmaxud xmm7, xmm8	; max R V
            pmaxud xmm7, xmm9	; max (max R G) B


			; 000000 11111 00000 111111
			; 111111 00000 11111 000000
			movdqu xmm0, xmm11	; cargo la máscara implícita			
			pblendvb xmm1, xmm4	; xmm0  >> carga máximos en pos 0 y 2
			pandn xmm0, [todosUnos]	;	>> DI VUELTA LA MASCARA
			pblendvb xmm1, xmm7	;carga minimoos en pos 1 y 3
			

			movdqu [rdi], xmm1
			add r10d, 4
			add rdi, 16
			add rsi, 16
			cmp r10d, edx
			je .x_loop		

		inc r9d
		cmp r9d, ecx
		je .y_loop
	pop rbp
	ret 