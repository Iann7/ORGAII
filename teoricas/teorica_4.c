/*
cache: a hidden store of things or the place where they are kept

En base al concepto de estructura jerarquica. La memoria cache ocupa el primer nivel de la jerarquia
Es a primer memoria que se encuentra la direccion que la cpu coloca el address bus 

Tamaño ideal de memoria cache
	1-suficientemente grande para que el procesador resuelva l a mayor cantidad posible de
	busquedas de codigo y datos en esta memoria asegurando una alta performance

	2-suficientemente pequeña para no afectar el consumo ni el costo del sistema

		HIT acceso a un item que se encuentra en la memoria cache
		MISS acceso a un item que no se encuentra en la memoria cache

		HIT RATE =  cantidad de accesos con hit
					----------------------------
					cantidad de accesos con miss
	
	80386 ->	procesador 40k de cache y no lo podian poner adentro del procesador, salian 150 dolares 
				hit rate 5 de cada 10 

				- NO Pongan mas de 64 por que no van a mejorar de .95 (hit rate)		
				
	Relacion entre el tamaño del cache y el tamaño de la RAM					

	Cuando el item requerido por la CPU no se encuentra en el cache, el tiempo de recuperación del miss no es facil de determinar 
	ya que depende de las caracteristicas del sistema 

	la memoria cache se administra por bloques o lines basado en el principio de vecindad. Al requerirse un item traera al cache la 
	mayor cantidad posible de vecinos (ademas de aprovechar al maximo la capacidad de transferencia del bus)					

	si esta en los niveles inferiores de memoria, el tiempo de recupero del item dependera del LATENCY y
	del BANDWITDHs, de la memoria con que se este implementando ese nivel de la jerarquia 

	si el procesador ejecuta instrucciones en orden, se detien hasta conseguir el item requerido. Si ejecuta fuera de orden,
	puede seguir con otras instrucciones dejando en espera a la que generó el Miss

	La memoria principal normamlmente esta administrada por bloques fijos a los que llamamos paginas

	el elemento buscado podria entonces no estar ubicado en una pagina que se encuentre alojada en la memoria principal
	En tal caso estara en la memoria virtual, es decir, el disco

	LA SIGUIENTE EXPRESION DETERMINA DE MANERA GENERAL EL TIEMPO DE EJECUCION DE UNA CPU 
	CPU_exectime = (CPU_CLOCK_CYCLES) + ( . . . )

	Miss_penalty es un valor fuertemente dependiente de cada sistema, lo mejor que podemos hacer es obtener un valor promedio 
	en base a experimentar con una contidad de casos suficientemente grandes como para ser representativa 

	EL CACHE ES UNA COPIA

	Miss_rate

	el procesador delega el controlador del bus al controlador del cache 

-----------------------------------------------------------------------------
	                    ┌───────────────────────────────────────────────┐        
                        │          PROCESADOR                           │        
                        │                                               │        
                        └───────┬───────────────────────────────┬───────┘        
                                │                       ▲─┐     │ ▲              
                        control │                       │ │     │ │              
                                │                       │ │     │ │              
                                │                      D│ │     │ │              
                                ▼                       │ │     │ │              
                     ┌───────────────────┐             A│ │     │ │              
┌────────────┐control│  Controlador      │              │ │     │ │              
│ memoria    │◄───── │  Cache            │             T│ │     │ │              
│ cache      │       │                   │              │ │     │ │              
└┬───────────┘       └───────┬───────────┘             A│ │     │ │              
 │                           │                          │ │     │ │              
 │                           │                          │ │     │ │              
 └───────────────────────────┼──────────────────────►   │ │     │ │              
            DATA             │                          │ │     │ │              
                             │                          │ ▼     ▼ │              
                             │                ┌──────────┐    ┌─────────┐        
                             │                │  buffer  │    │ BUFFER  │        
                             │                └──┬───▲───┘    └────┬────┘        
                             │                   │   │             │             
                             │                   │   │             │             
                             │                   │   │             │             
                             ▼                   │   │             │             
                                                 │   │             │             
                         ┌───────┐               │   │             │             
                         │ buffer│               │   │             │             
                         │       │               │   │             │             
                         └──┬────┘               │   │             │             
                            │                    │   │             │             
                   ┌────────▼────────────────────▼───┼─────────────▼────────────┐
                   │                                                            │
                   │        BUS DEL SISTEMA                                     │
                   │                                                            │
                   └───────┬──▲────────────────────────────────▲───┬────────────┘
                           │  │                                │   │             
                           │  │                                │   │             
                           │  │                                │   │             
                           │  │                                │   │             
                           │  │                                │   │             
                           |  │                                │   │             
                        ┌──▼──────┐                           ┌─┴───▼─┐           
                        │         │                           │       │           
                        │ memoria │                           │ E/S   │           
                        │         │                           │       │           
                        └─────────┘                           └───────┘           


----------------------------------------------------------------------------------------------

En un ciclo de clock te lo dice si tiene o no tiene al archivo -> CONTROLADOR DE CACHE 

                 ┌───────────────────────┐                      
                 │                       │                      
                 │                       │                      
                 │      MEMORY           │                      
                 │      READ             │                      
                 │                       │                      
                 └───────────┬───────────┘                      
                             │                                  
                             │                                  
                             │                                  
                             │                                  
                             │                                  
                             ▼                                  
              ┌─────────────────────┐               
   HIT        │    CACHE            │  MISS                     
 ┌────────────┼    DIRECTORY        ┼───────────┐               
 │            │    SEARCH           │           │               
 │            └─────────────────────┘           │               
 │                                              │               
 │                                              │               
 │                                              │               
 │                ┌───────────────┬─────────────|               
 ▼                ▼               ▼             ▼               
                                                                
READ ENABLE     CACHE           WRITE           READ ENABLE DRAM
CACHE MEMORY    DIRECTORY       ENABLE          MEMORY          
  │             UPDATE          CACHE             │             
  │                               │               │             
  │               │               │               │             
  │               │               │               │             
  │               │               │               │             
  │               │               ▼               ▼             
  └───────────────┼────────────────────────────────             
                  │                                             
                  │                                             
                  │                                             
                  │                                             
                  │                                             
                  ▼                                             
			-------------
			| USE ITEM 	|
			-------------


¿Como se organiza un cache?
	- tag 	| LINEAS
		  	| 1...		 
		  	| 2...
			| ...
			| 8

	si las lineas son de 8 bytes arrancan en posiciones multiples sde 8 

C tiene un atribute align, nos sirve para alinear con cache (por ej)
No necesariamente el orden de la memoria es el orden del cache 
La memoria cache no tiene direcciones que vos puedas ver como programador 

El elemento minimo de palabra de datos o codigo dentro del cache, es entonces la LINEA 

¿Como organizamos el cache?
	Lnine placemente
	Line identificaction
	Line replacement-> ¿Que pasa cuando se me llena el cache?
	Write policies -> ¿Que pasa cuando escribe cuando no deberia

	LINE PLACEMENT ¿DONDE VA UNA LINEA DE CACHE?
		fULLY ASSOCIATIVE: El menos restrictivo posible. Una linea de memoria principa puede ubicars een cualquiera de las lineas de cache		|
		Direct Mapped = es el mas restrictivo: Una inea de memoria principal puede ubicarse en unica linea del cache,							|--> opuestos
						cucho numero queda determinado por la siguiente expresion																|
						(Line Frame address) mod (Cache#Lines)

		SET ASSOCIATIVE
						set de lineas en cache en las que se puede guardarse una nueva linea leida desde  la memoria principal
						cuyo numero queda establecido por la siguient expresion
						(Line frame address) mod (Cache # sets)
						En general si tenemos n sets posibles para almacenar al linea el sistema se refiere como 
						n-way set associative 

	El controlador divide a la memoria en bloques, y luego lo vuelve a dividir en lineas 
	si bien corresponde a un multiplo de tamaño de la palabra de datos 
	CONFLICT MISS

	n-way set way associative
		ventajas: simplifica al macimo el placement y la busqueda. Minimiza el soporte de hardware y en consecuencia  . . .
	

	CASOS PRACTICOS AMD OPTERON CACHE L1 
		en 2003 AMD presenta esta linea de procesadores que implementa por primera vez al arquitectura 
		de 64bit AMD64, que a posteriori intel deberia incluir en su linea x86 luego del fracaso 
		comercial ITanium 

		El primer procesador de arquitectura denominada SledgeHammer, tenia un solo core con ejecucion fuera de orden y dos niveles de Cache 64 kib y 256 kib 

		en 64 bit el procesador trabaja con direcciones virtuales de 48 bit, y envia al address bus direcciones fisicas de 40 bit (con el tiempo al igual que los intel 
		este numero crecera hasta 52 bit actuales 
		
		el cache L1 es set asociativo de 2 vias y trabaja con un tamaño de linea de 64b 

		en 2 ciclos de clock todo el proceso 

		victim buffer vienen las lineas que estan modificadas 
		si la modifique tiene que ir para abajo 

		split cache 
			un cache para datos y otro cache para codigo 
		
		dual port = cache lvl 1
		 	puedo escribit y lerr un registro en el mismo ciclo 
		
		A que llamamos core? procesador y cache en el mismo CI (circuito integrado)

		Cada core corre 2 threads 

		en cada core se corre un codigo de flujo 	

		si los core lo netes en un mismo circuito se llama MULTICORE 

		los procesadores pueden tener una cache compartida (en general tienen cache compartida)

		un multicore son core que comparten cache compartida 

		trabajar multicores con su propia d ram y una matriz de interconexion de alta velocidad 
		que conectan entre si 

		numa => NON UNIFORM MEMORY ACCESS

		DSM distributed shared memory 

		1 bus = 1 PROCESADOR A LA VEZ 
		¿Por que? 
			se mezclaria la informacion
			y ademas se quema todo 
			contencion de bus 
			bus flotante 
				anti impedancia 
				impedancia alta = no toma corriente 
				ESTADO FLOTANTE: resitencia electrica tan alta que no pasa corriente 

	no sobrecargar el bus con transacciones al cohete 
	

	PROTOCOLOS DE COHERENCIA 
		son mecanismos para lelvar un tracking d ecada linea compartida entre cores 

		Requiere poder establecer estados para cada liena. Del mismo modo que en un sistema con un solo
		presador se señala Dirty a una linea modificada

		Hay dos clases
			Directory based: El estado de las lienas se mantiene en un directorio  centralizado accsible de manera rapida por todos los cores 
			Puede ser un area de cahe externa a cada core 

			es mas complejo. En auge a partir de sistemas distributed shared shared memory  
			en sistemas multicore modernos debido a los multiples niveles de cache integrados 


			Snoopy: Cada core amntiene el estado de sus lineas y puede monitorear el estado de los otros 
		
		write invalidate 
			asegura acceso exclusivo al procesador que va a escribit el dato, antes de que la escritura 
			se lleve a cabo. El resto debe poder detectar la escritura e invalidar la linea que contiene el dato en caso de tenerla en su 
			cache. Garantiza que no existe otra copia del dato una vez escrito este en el cache destino

		Write update 
					tambien cnoocido como write broadcast, ya que actualiza la linea en todos los yara yara 

		Snoop bus es entnoces un conjunto de lineas entrantes a cada controlador cache con el cual este espia 
		lo que hacen los demas procesadores en particular con la memoria 

		el otro controlador cache detecte el acceso mediante su snoop bus 

		Copy back vamos a lograr usar el bus de manera super eficiente y ganar performance en el proceso local 
		el procesador va a estar siempre escribiendo en su cahe y va a chusmear que onda que hacen los otros
		si tiene esa direccion modifica de ser necesario 

		cualquier protocolo de coherencia tiene dos atributos 
			ownership: quien lo(S) tiene en el cache 
						pueden ser shared 

			coherencia: 	coherencia es cuanto todas las copias tienen lo mismo.
							la coherencia marca como esta el dato en un cache en un core respecto al resto de la jerarquia
							si esta igual que el resto de la jerarquia => coherente
							si no => dirty

			NO PODEMOS TENER UN DATO COMPARTIDO Y QUE SEA DIRTY
			cuando uno lo modifica el resto lo tiene que invalidar 

			una vez que lo invalidas el dato no lo tenes mas 
			(en todos los niveles inferiores tambien)

			conflict miss: estoy leyendo un dato y lo tengo que almacenar en una linea que ya estaba ocupada 
							yo tenia un valor pero me viene otra que me la desaloja 
							la linea cambia, pero sigue estando shared                                                                                                                                      
*/						