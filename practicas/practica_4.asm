; TENER EN CUENTA EXTENSION DE SIGNOS
; SHIT ARITMETICO != SHIFT LOGICO
; --------------------------------
; REPRESENTACION DE PUNTO FLOTANTE
; en floating point tenemos +0 -0 
; +infinito -infinito 
; LITTLE ENDIAN
;   el mas chico primero               
; BIG ENDIAN
;   el mas grande primero 
;
; INTEL SE MANEJA CON LITTLE ENDIAN
;
    mi_dato: db 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07
;   0x00 almacenado en 0x00
;   0x01 almacenado en 0x01
;   . . .
;   . . .
;   0x07 almacenado en 0x07 
;   para definir floats basta como expresarlos como tales (1.0,3.5)
;   mi_float: dd 0.1,0.2,0.3
;   mi_double: dq 0.1,0.2,0.3
;   DB = define byte
;   DW = define word
;   DD = define double word
;   
;   ¿Que es un pixel?
;       un pixel (picture-element) es una muestra de luz en un punto que representamos digitalmente
;       si la representamos con un unico entero de 8 bits solo podremos determinar la intensidad de la luz y formar imagenes
;       en blanco y negro
;       
;       si en cambio dividimos la luz en 3 canales (RGB)
;       podremos mostrar colores en pantalla
;
;       RGBA -> agrega un canal, alpha, que determina la transparencia del pixel 
;       tambien conocido como ARGB, cada uno usa el standard que se le canta 
;
;       typedef struct rgba_pixfmt { 
;               uint8_t r,g,b,a;
;               } rgba_t;
;
;       0x0     0x1     0x2     0x3     0x4     ...and so on 
;       0xRR    0xGG    0xBB    0xAA    0xRR    ...and so on 
;       
;       EN INTEL LOS [] SON ACCESOS A MEMORIA 
;       exceptuando en lea (load effective address) 
;       JNE = JUMP IF NOT EQUAL
;       JNZ = JUMP IF NOT ZERO  
;       ALIGN 16    
;       importante leer alineado 
;       movdqu [rdi] ,xmm0
;       z: zero     p:packed               
;       s:signed,scalar,single,saturated    
;       etc etc 
;       de 0 a x ponemos constantes
;       de 15 a x ponemos var 
;       para entender que esta pasando en el codigo
;       MOVD CARGAMOS EN EL REGISTRO DE XMM 
;       movss hace lo mismo pero le avisa al procesador que es un float
;       mas a la derecha el pixel => mas rojo
;       suma saturada cuando no queremos hacer overflow y volver a 0