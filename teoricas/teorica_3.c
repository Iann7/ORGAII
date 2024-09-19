/*
SINGLE INSTRUCTION SINGLE DATA 
refers to the traditional von Neumann architecture where
a single sequential processing element operates on a single stream of data

cada registro se carga en una sola instrucción 
la operacion se efectua en la segunda instrucción 
0.

los saltos nos pudren al eficiencia del algoritmo, son discontinuidades del flujo de la aplicación 



SINGLE INSTRUCTION MULTIPLE DATA
computers with multiple processing elements that perform the same operation on multiple data points simultaneously 

cada registro se carga en una sola instrucción 
la operacion se efectua en la segunda instrucción 

una sola operacion sobre un conjunto multiple de datos 
se refiere a esta tecnica como paralelismo a nivel de datos 
util para procesar audio,video o imagenes donde se aplican algoritmos repetitivos
el modelo provio fue SISD
necesita un loop para aplicar todas las instrucciones a todos los datos, ya que solo se puede procesar un dato por cada instruccion

en su momento estas arquitecturas eran DEDICADAS (DSPs)
en general resuelven suma de productos . . . 

Multimedia extensions - MMX 
	8 registros
	MM por multimedia 
	registros de 64 bits
	lo incluyo en el pentium 
	al principio empezó con aritmetica entera (por que sky y el resto trabajaban con eso)
	Tipos de datos
		1 quad word (tipo de data en 64 bits!!!)
		2 doble words enteros empaquetados
		4 words enteros empaquetados
		8 bytes enteros empaquetados
	Pentium 3 mete 8 registros nuevos 
		18 byes enteros empaquetados
		8 words enteros empaquetados
		4 doble words enteros empaquetados
		1 doble quad word
		4 puntos flotante . . .
	ISA en 32 bits
		registros totalmente desproporcionados comparados uno con el otro 
		los registros MMX en el '92 no podian tirar "mucha manteca al techo"
		por ende decidieron hacer 'alias' de otro registro (usaron otros registros fisicos y lo renombraron)
		si queres usar los "dos registros" al mismo tiempo vas a tener que restaurar lo que tenias en el otro 
	No se pueden almacenar (o representar) todos los numeros reales
	los tenemos que representar de algun modo (FLOATING POINT)

	en general podemos formalizar la representación de un numero rel expresado en los siguientes formatos
		- punto fijo------>muy poca precision y rango 
		- punto flotante ------>
	
	para el caso de nros reales se trabaja con notacion cientifica
		n = +- f*10^e
	se representan mediante una expresion de tipo
	(an,...,a0)_2 = (-1)^S + blah ....
	Mantisa y exponente se pueden representar como:
		con signo
		sin signo
		con notacion complemento
		con notacion exceso m 
	para que las representaciones sean unicas, las mantisas deberan estar normalizadas. 
	better call IEEE (estandarizo todos los formatos de representacion en punto flotante)
	la norma salió muy bien (un espejo del 8087 de Intel)
	en 2008 introdujeron un formato de 16 bits y el de 80 fue reemplazado por uno de 128 bits
	(IEEE 754-2008)
	16 bits tiene 3 digitos de precisión
	formulado por NVIDIA (y reduce la cantidad de memoria necesaria para una operación)
	el consumo energetico de un procesamiento de informacion se produce principalmente en el translado de datos 
	por que pasaron de 80 a 128? precisión 
	el bit mas significativo es el bit de signo 

	codificacion de los numeros normalizados 
	ceros signados
	numeros finitos de-normalizados
	base -> binario desplazado M 
	como es binario desplazado? al numero le resto la mitad de la escala 
	e=255 => -infinito 	
	E=255 mantisa 1.0XX => SNaN
	E=255 mantisa 1.1XX => QNaN
	la cuestion de la precision es cuanto estas dispuesto a perder? 
	lo mismo con la seguridad informatica 

	NaN = not a number
	QNaN = quiet not a number
	SNaAN = signaled NaN

	con las extensiones SSE, Intel incluye el registro MXCSR
		flush to zero ------------|
		rounding control------------|
		precision mask---------------|
		underflow mask----------------|
		overflow mask------------------|
		divide by dero mask-------------|
		denormal operation mark
		invalid operation mark
		denormals are zero
		precision flag
		udnerflow flag
		overflow flag
		divide by dero flag
		denormal flag
		invalid operation flag 	
	
	INSTRUCCIONES 
	------------------------------------------------------------|
	MOVD MOVQ => move doubleword/quadword 						|
	MOVSS MOVSD => moves a 32bit single FP/ 64bits double FP	|
	------------------------------------------------------------|
	MOVDQA MOVDQU =>move aligned/unaligned quadword 			|
	MOVAPS MOVUPS => moves 4 aligned/unaligned 32bits singles	|
	MOAPD MOVUPD => Moves 2 aligned/unaligned 64bit doubles 	|
	------------------------------------------------------------|
	son todos para algotitmos bastante extraños

	SINGLE PRECISION DOUBLE PRECISION??????

	OPERACIONES LOAD/STORE
	 	------------------------------------------------------------------------
	|	PMOVSXBW	PMOVZXBW		| PACKED sign/zewro extension byte to wrod		|
	|	PMOVSXBD	PMOVZXBD		| packed sign/zero extension bye to dword		|
	|	PMOVXSBQ	PMOVZQB			| packed sign/zero extension byte to qword		|
	|	PMOVSXWD 	PMOVZXWD		| packed sign/zero extension to dword			|
	|	PMOVSXWQ	PMOVZXWQ		| packed sign/zero extension word to qword		|
	|	PMOVSXDQ	PMOVZQDQ		| packed sign/zero extension word to dqword		|
		------------------------------------------------------------------------
	
Acumulacion de resultados sobre un registro
	A medida que acumulamos resultados en un registro. llegamos inexorablemente el punto que el rango de resultado 
	llegamos inexorablemente al punto en el que el rango del resultado excede la capacidad de bits del registro de
	acumulación

	En ese punto los procesadores te informan que hay un overflow y en el operando destino se almacena 
	el valor de DESBORDE 

	la aplicacion chequea dentro del lazo de cálculo de este flag y decide si seguir almacenandolo o no 

ARITMETICA DE DESBORDE
	wraparround y mantenes el overflow
ARITMETICA SATURADA
	se mantiene en el valor maximo de representacion 

Cuando usar aritmetica saturada o de desborde? 
	PMULHW = packet multiplication high word
	PMULLW = packet multiplication low word
	PADD = packet add
	PSUB = packet sub
	PMIN = packet min
	PMAX = packet max 
	PXOR 
	bitwise 

LEY DE MOORE 
transistores cada vez mas chiquititos 
nanometro
EUV extreme ultra violet
Lightography escribir con luz 
FPGA = sale. caro.
	   no es optimo 
	   useful for remote deployments 
	   can reconfigure the hardware to meet specific usecase req
20 armstrong;estamos por "debajo" del nanometro 
TENDENCIAS TECNOLOGICAS
las tarea de un diseñador es permamente y moldeada por el rumbo de la tecnologia 
	1 la densidad de transistores por unidad de superficie aumenta 35% en promedio
	  otra forma de la ley de moore
	2 la velocidad de clock ya no crece. Parece haber alcanzado un techo en los 3ghz 
	
	3 scaling: habla del tamaño de los componentes del procesador (transistores, etc)
	los transistores se cuentan por mm cuadrado de silicio 
	otro parametro importante es su rendimiento
	cuando se reduce el tamaño de un transistor en sentido vertical hay que considerar el
	tamaño de alimentacion 
	Como no es posible cambiar la rension de operacion cada vez que se reduce la escala,
	la mejora en el rendimiento con cada avance en el scaling no es cuadratica, sino que tiende a ser lineal 
	core i3,i5,i7 es cuanto anda y cuanto no andan
	los "alambres" con los caminos de señal que conectan los diferentes componentes 
		conforman los buses internos
		estos caminos de señal, en las escalas actuales y a las frecuencias de trabajo actuales
		generan dos problemas
			delays 
			consumo de energía 
	-En fisica,energia es el trabajo efectuado para realizar una tarea
	-aplicado a un sis de computo, puede pensarse como la cantidad de carga de una bateria que demanda
	un algoritmo
	-sin embargo, en gral, los fabricantes de microprocesadores y memorias 
	suelen especificar potencia instantanea (Watts)
	- La potencia instantanea promedio se refieroe al consumo en el periodo 
	de conmutacion de un transistor CMOS (corte a saturación o vicesversa)
		Pavg = (Pdynamic + Pstatic) ~ Ctot*V^2_DDf + L_leak + Vdd
		C_tot = capacidad total de carga del CMOS 
		Vdd = tension de alimentacion
		F = frecuencia de conmutacion (clock)
		L_leak = corriente de perdida (aun en corte hay una pequeña corriente de salida)
	
	P_static deberia ser cero pero NO LO ES (hay un cacho de corriente)
	POTENCIA ES CALOR :]
	que se mide en miliampere/hora? la bateria del celular (queremos que consuma poco)
	modificas arquitectural (gaste 30 miliampere hora y tengo que hacerlo con 25)
	POTENCIA=CORRIENTE*TENSION
	ENERGIA=POTENCIA*TIEMPO
	C_tot  
	EFECTO TUNEL ES LO QUE HACE QUE UN ELECTRON PASE DEL GATE AL DRAIN 
	no conectar muchas cargas a la misma salida 
	si no los hacemos tan chiquititos podemos apilarlos si el Vdd es bajo(EXPERIMENTAL)	
	E_d = C_s*V^2
	haces lo mismo mas despacio! mas bateria menos rendimiento!
	esta no es la solucion para maquinas con alto desempeño 
	PROBLEMA: corriente de perdida 
		muy baka, pero a partir de las tecnologias de 45 a 30 nm
		dejo de disminuir conforme se miniaturiza un transistor. Otra mala noticia para el 
		tramo final de la Ley de moore;leakage paso a ser un "big issue"
	intel: apaga lo que no se usa 
	ARQUITECTURA set de recursos accesibles para el programador,
	que por lo general tienen a lo largo de los diferentes modelos de procesadores de esa arquitectura
	(puede evolucionar pero la tendencia es mantener compatibilidad hacia modelos anteriores)
		-Registros
		-Sets de instrucciones
		-Estructuras de memoria (descriptores de segmento de pagina)
	MICROARQUITECTURA
		es la implementación en el silicio de la arquitectura. Lo que esta detras del set de registros
		y del modelo de programación. Puede ser muy simple o sumamente robusta y poderosa.
		Cambia de un modelo a otro dentro de una misma familia


ARM cayo preso de TIME TO MARKET
objetivo de origen de RISCV: algo que no dependa of the woes of the market 
PARA QUE SEA RISCV TIENE QUE TENER ESTAS INSTRUCCIONES DE ESTA FORMA 
pero no te pide NADA MAS		

ARQUITECTURA - EL SISTEMA DE MEMORIA 
antecedentes 
memoria de tanque de mercurio para la computadora EDSAC 
capacidad 2 bytes

It's the memory, stupid! 
publicado en microporcessor report
alfa 21064 CPU@200MHz  dos vias de instrucciones a ejecutar por ciclo de clock 
en ese momento estimaron una prospeccion a 25 años (2017)
performance x1000,etc
4 años despues analizaron su prospeccion y masomenos le pegaron 
nucleo es mucho mas que un procesador (lo vemos la proxima clase)
para medirlo lo probaron en un benchmark TPC 
observaron que mandaban muchas instrucciones al clock, pero tenian que esperar
3 CICLOS DE CLOCK ESPERANDO A LA MEMORIA
CONCLUSION: era la memoria :]
JERARQUIA DE LA MEMORIA 
	la memoria es un SUBSISTEMA
	tanto o mas complicado que un procesador
	el sueño: 	un sistema con una sola tecnologia sin jerarquia. 
				diseño simple. barato.FIN <3
	la realidad: solo posible en sistemas triviales masados en microcontroladores
		- Gran capacidad de almacenamiento 
		- Tiempo de acceso minimo
		- capacidad de mantener los datos cuando se apaga el equipo
		- Y ADEMAS QUEREMOS QUE SEA BARATA >:d
		------------------------------------------------
				|
				v
				este problema es el tipico "manta corta"; no alcanza la manta para cubrir todo
		CONCLUSION: necesitamos pensar la memoria en niveles jerarquicos 
	LOCALIDAD DE REFERENCIAS
		el acceso de la memoria no es tan aleatorio
		es bastante predecible 
		observacion empirica:
			si agarramos cualquier programa razonablemente bien escrito
			esos programas van a reutilizar datos que usaron recientemente 
	LOCALIDAD TEMPORAL => patron de acceso a las mismas direcciones de memoria de intervalo temporal
						  finito y acotado 
		la posibilidad de que la CPU solicite en los proximos ciclos de acceso a memoria los mismos
		registros, es muy alta
		Contrariamente es muy poco probable que utilice direcciones de memoria lejas a las actuales 
		ALGORITMO DE CONVOLUCIÓN 
			las variables I J SUMA cumplen el principio de vecindad temporal; sus 
			direcciones se acceden en frecuencia muy muy alta

			IDEA FUERZA: si logramos que este codigo y las variables esten en una memoria 
						 rapida la ejecucion va a ser mucho mas rapida 
MEMORIA: JERARQUIA PIRAMIDAL
	Velocidad -> (a la punta de la torre)
	Costo por bit -> (a la punta de la torre)
	<- capacidad (a la base de la torre)
		   *^*
		  ------
	     /  Reg  \
	    /   L1    \
	   /    L2     \
	  /    DRAM     \
	 /    Storage    \
	/ Backup offline  \
	------------------
	RAM
	random access memory 
	mismo tiempo de acceso a todos los registros
	ROM
	read only memory 

MEMORIAS NO VOLATILES 
dispositivos capaces de retener la informacion almacenada cuando se les desconecta 
la alimentación 

e^2 crom
RAM=> su tiempo de acceso es siempre el mismo independientemente de la ubicacion en la memoria 
OTPROM 
memorias volatiles dinamicas DRAM
	los capacitores siempre encuentran una forma de descargarse >:C
	hay que ponerle un cricuito de refresco que regenere la carga 
	las dos cosas (escribir y mantener el capacitor "prendido") REQUIEREN MUCHO TIEMPO	

	como soluciono el tema de la descarga? periodicamente simulas una lectura boba 
									   y lo demas ni me importa (muchas veces por ms) 

memorias volatiles dinamicas (SRAM)
	6 transistores 1 bit
	consumo una bocha 
	consumo electrico de la RAM dinamica? ridiculamente bajo 
	cual es la ventaja de esta? es rapidisimo
								y ademas no la tenes que refrescar

memoria no volatil => almacena el programa de arranque 
				PROCESADOR
-------------------------------------------------------
		|1			|2			|3
		V			V			V
		BUFFER		BUFFER	  	BUFFER
		|			^			|
		|1			|2			|3
		V			V			V
		-------------------------
		|			BUS			|
		|			DEL 		|
		|			SISTEMA		|
		..........................
		^						 ^
		|						 |
		V						 V
		MEMORIA					e/s

		1 CONTROL
		2 DATA 
		3 ADDRESS

RAM DINAMICA 
consumo minimo
capacidad de almacenamiento alta
costo bit bajo
tiempo de accesso alto
RAM ESTATICA
alto consumo relativo
capacidad de almacenamiento baja
costo por bit bajo
Tiempo de acceso bajo(es mas rapida)
*/