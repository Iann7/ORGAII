/*
VAMOS A USAR UN PROCESADOR INTEL 
- Micros de Intel...complicados 
- modalidad de la clase: levantan la mano y preguntan (je)
- Que vamos a poder hacer/aprender despues de la materia?
	- vamos a aprender a como hacer un pequeño kernel en un sistema operativo 
	- manejo entre OS y hardware 
- Que tanto cambia respecto a la materia vieja? (nada, jajaja)
- BIBLIOGRAFIA 
	- manuales de Intel 
	- 
- VAMOS A VER ASSEMBLER 
- Que es la arquitectura de un computador (en la mayoría de los casos,assembler)
- INTRODUCCIÓN HISTORICA 
- Que es una computadora de proposito general? 
	es un tema de escala... no hay una def ni vale la pena 
	buscarlo por que las definiciones van cambiando 
- primera computadora general? Babbage
- Z3, computadora general nazis en berlin quemada (1941)
- Alan Turing, 1936, maquina de Turing, esbozo un modelo matematico
  que modela el computo de problemas
	-maq de turing: cinta infinita (memoria),avanzaba y retrocedia 
					en funcion del contenido que encuentra 
					y pone un uno o un 0 segun lo que encuentre 
- Von neumann, pero fue este pibe (turing) (lo dijo el profe)
- ENIAC: "primer" computadora de proposito general 
		- no tenia programa almacenado
		- operadores y operadores que cambiaban cables de lugar, generando una modificación
		  del algoritmo
		- la valvula se comportaba como un transistor 
- von Newmann: 
	- "publish or perish"
	- primer arquitectura bien documentada 
	- ALU, CONTROL UNIT, MEMORY UNIT, INPUT DEVICE, OUTPUT DEVICE
	- MEMORIA EXTERNA: en su momento era una cinta, información grabada en 
					forma analogica
	- clock: en el primer flanco busco la instruccion
			 en el segundo la decodifico (ver de que se trata la orden)
			 buscar el operando
			 te ejecuto (hacer cuenta en la alu)
			 te almaceno el resultado 
	- 5 ciclos de clock 
	- una unica unidad de memoria para datos y codigo (no encaja con el nuevo paradigma)
	- Von Newmann bottleneck
	- como podemos hacer para no fumarnos el bottleneck? ya lo habian resuelto, en Harvard 
	 	la Mark I, 766k engranaje, 800km cable, basada en babbage, en decimal
		0.3s a 10s por calculo, 
	- Mark I: unidad de control en el centro que atendia al Instruction Memory y
			 Data memory al mismo tiempo
	- escucharon de Cache? todos los procesadores tienen cache de instrucciones y datos 
		al lado del procesador (que viejo son los trapos-profe)
- Como son las maquinas hoy? un mix de Newmann y Harvard 
	- Unica memoria que contiene todo
	- pero hay arquitectura adentro del chip adentro de la arquitectura para 
		facilitar el procesamiento de ordenes 
	-pipeline es responsable que esas 5 operaciones sean solapades y en paralelo
-primeros microprocesadores con rquitectura Harvard se dieron en la decada del 80 
 con el advenidmiento de los DSP(procesadores de señales)
- Split-cache en nivel 1 (Intel x86,ARM CORTEX-A,CORTEX-R)
-Segunda generación: 
	-Lab Bell
	-Menos consumo
	-Mayor procesamiento 
	-lenguajes de alto nivel
	-compiladores de alto nivel 
	-FORTRAN
	- VS IBM XEROX DEC (RIP xerox y dec)
-Tercera generación:
	- Texas instrument 
	- primeros circuitos integrados 
	- PDP8 
	- CMOS
	- Fairchild
	- minicomputadores: costaban un orden de cantidad menos que las enormes computadores 
						con transistores 
	- Programación estructurada y C 
	- UNIX PDP 7  
	- General Electrics, querían hacer un OS con Bell 
	- UNIX + C
	- 16k de RAM
	- Intel era un fabricante de memoria hasta que vino
		una empresa ponja y le pidió un procesador para una calculadora de bolsillo 
		hicieron un procesador de 4 bits, 2300 transisores
	- NOTA DE COLOR:  federico firmo el procesador(?)
	- "nosotros vamos a hacer procesadores compatibles, manteniendo la arquitectura"
	   sin tener que hacer un quilombo cada vez que se cambia de procesador 
	- objetivo: masificar el procesador a uso hogareño
	- accessible a evolucionarla 
4ta generación
	- El desarrollo de la tecnología de integración evoluciono de acuerdo con 
	  la ley de Moore
	- MOSFET
	- Al momento de escribir esto, la Ley de moore esta llegando a su fin,
	  simpemente por que se han alcanzado dimensiones fisicas a niveles atomicos
	  ya no es posible reducir mucho mas las dimensiones de una compuerta MOSFET
	- AMD 
hoy los procesadores se diseñan buscando un menor consumo de energía 
hace 4 o 5 decadas se diseñaban pensando en que los programas consuman 
la minima cantidad de memoria posible 
BAJAR. CONSUMO.
los objetivos de diseños cambian segun la epoca y sus necesidades---!!!!
la gente tenia restricciones que hoy estan superadas 
no importanta cuantos ciclos de clocks andaban, importaba el espacio en memoria
que llevaban las instrucciones 
- 8086 Organización
	-pipeline de 2 etapas 
	-primer concepto de pipeline (etapas que trabajan en paralelo)
	-trabajar en paralelo sobre INSTRUCCIONES DIFERENTES!!!!
	-1978S
ARQUITECTURA
	-Registros
	-Set de instrucciones
	-estructuras de memoria
	-los recursos que usamos para programarlo
MICROARQUITECTURA --> la implementación en silicio de la arquitectura 
Hay que empezar a pensar como armamos el set de instrucciones,
como manejamos la memoria,diseño logico,etc. 
SKILLS NECESARIOS
	- Diseño logico 
	- Tecnología de encapsulado 
	- Funcionamiento y diseño de compiladores y Sistemas Operativos 
	- no esta disociado 
	- verilog
DEFINIENDO UN ISA 
(INSTRUCTION SET ARCHITECTURE)
Clases de ISA proposito general vs registros dedicados
Direccionamiento de memoria Alineacion obligatoria de datos vs admin de bytes
Modo de direccionamiento como se especifican los operandos 
Tipos y tamaños de operandos
Operaciones 
Instrucciones de control de flujo... saltos condicionales,calls
Long de codigo: instrucciones de tamaño fijo vs variable
(PAUSA)
floats y doubles (32 y 64)
AMD e Intel pueden tener la misma ISA pero hay cosas que a nivel FISICO de harware
que cambia un montón 
Pentium 4M: todo lo que no uso lo apago 
AÑOS 80
aparecen instrucciones con un set de instrucciones RISC en contraposición de
los CISC que era el standard 
Testing de las CISC es MUY complejo
Es mucho mas facil validar un sistema RISC con muchisima menos instrucciones
David Patterson y John Henessy (Stanford) PADRES DE RISC
Cuantos clocks llevaba dividir en un procesador 8086? 144
el tamaño de los programas sea mayor en RISC.
PROCESDAOR 8086 
IBM le pidio una modificación a INTEL para que el bus pase de 16 bits a 8 bits
lo arreglaron con un demultiplexor 
Primer prueba de compatibilidad 
Intel 80286 
	- 16 bits
	- multitasking
	- nuevas instrucciones
	- xenix UNIX para 286 
Intel 80386
	- 32 bits 
	- reina en el mercado 1/2 decadas 
A fines de los '90 Intel y Hewlett Packard desarollan una arquitectura de 64 bits 
(esta arquitectura ya esta)
Itanum e Itanum 2, no tuvieron el exito con los x86 
generar codigo que se ejecute en PARALELO (Itanium)
AMD agregó las extensiones de 64 bits a los procesadores IA-32.
Esta nueva arquitectura x86-64 AMD64 fue un EXITO
-Es una arquitectura que tiene que ser analizada bajo su contexto
 historico en el que se gestó
-INSTRUCTION POINTER=PROGRAM COUNTER
-FLAGS=registro de estado(carry,overflow,lalalaa)
- pagina=tamaño fijo
- segmento=tamaño variable 
- los constraints MARCAN las decisiones de DISEÑO 
- FS Y GS = dos registros menos utilizados en la historia de la humanidad 
FLOATING POINT UNIT
8088 lo presento con un segundo procesador, el FPU(Floating Point Unit, 8087)
recien el 486 mergea los dos procesadores en uno solo
- bit mas significativo = signo
- bits de exponente 
- como no se pueden representar los reales en una computadora se garantiza un grado de 
  precisión y magnitud 
- mas bit a la mantisa= mas precisión 
- single precision = 12 decimales exactos
- double precision = 15?
- extended double 
- MMX para procesar audio y video 
- si trabajas con floating point NO podes trabajar con MMX
  (SON LO MISMO)
- Pentium 3 XMM (registros posta)
- Extensiones de 64 bits(made by AMD) (8 registros XMM)
- Algoritmos de deteccion de borde (neighboring 8)
- dispositivos de entrada/salida van en un mapa aparte y ese pin 
  determina si es un port o memoria 
NOP=ciclo de clock al pedo 
HALT=paro por tiempo indeterminado
WFI=Wait For Interrupt 
CLC=Clear Carry 
Cuando no hay nada que haces HALTEAS para AHORRAR ENERGIA 
¿while(1) hTop? operación sleep en C
el ascii de 9 es el codigo que corresponde al 9 en el ascii
Literal pool -> lookup table used to store literals during 
				assembly and execution
XOR de dos valores iguales da 0 
RISCV tiene una cosa muy interesante:
	-las especificaciones que estan cerradas NO CAMBIAN MAS
	-estado closed= va a ser asi siempre
	-excepto que haya arquitectura disruptiva que cambie toda la mesa 
lo importante no es tanto el lenguaje si no lo que hagas con los recursos del procesador
hay muchas cosas que esta obsoleta por que no se usan mas
inc rdx = le suma uno a registro (no carry)
modos de direccionamiento a memoria 
memorias por segmento = MUY MUY flexible, incluso caotico
segmentos pueden estar solapados
flexibilidad de reubicación de segmentos
DireccionEfectiva=Base+(indice*escala)+desplazamiento
desplazamiento directo=le pones el numero A LO BESTIA
indice*escala+desplazamiento 
loop va por el siguiente elemento hasta que ECX llegue a 0
buffer=cacho de memoria
buffer de video=4000 bites
¿por que? limitaciones de la pantalla de video 
para dibujar un caracter en una placa de video 
estan los caracteres registrados en la rom que tiene 
la direccion/almacena la forma en la que esta "dibujada" el caracter
LITTLE ENDIAN - granquilombo
el mas chiquitito al final 
cuando vos tenes que ordenar un numero a memoria un gran problema de las arquitectura
es como pones mas de un numero de mas de un byte a partir de un registro de memoria? 
Por que usar LITTLE ENDIAN? 
una estrategia para leer memoria mas rapido es leer mas memoria en el mismo ciclo 
por que usamos little endian? por que el procesador le llega en derecha, si no lo usasemos
							  tendriamos que usar mas energia para los mismos procesos
TCP/IP:BIG ENDIAN
ALINEACION DE DATOS: poner las cosas a partir de direcciones que sean multiples del tamaño de un dato
					 una word alineada empieza en direcciones pares
					 32 bits alineada =multiples de 4
					 and so on 
OPERACION ALIGN: el proximo dato alinealo a x 

*/
