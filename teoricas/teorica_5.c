/*
WRITE INVALIDATE: invaliden por que yo la piso 
	a partir de ahi la linea la tengo solo yo
	cualquier persona que quiera la linea despues y no la encuentre 
	cuando genera un readme que salga por el cache y yo me entero 
	voy a decir "este va a buscar fruta", despues vemos que hacemos

	Cualquier otro cache que la busque va a tener MISS

SHARED: cambia el ownership, ahora la propiedad de la linea es mia y de otros

Protocolos de coherencia 
	Son mecanismos para llevar tracking de lineas compartidas entre cores 
	Requiere establecer estados para cada linea. Del mismo modo que en un sistema con
	un solo procesador se señala DIRTY a la linea modificada 

	Directory based vs snoopy
		Snoopy cada core mantiene el estado de sus lineas
		Directory based el estado de las lineas se mantiene en un directorio centralizado 
	
	Snoop Bus 
		conjunto de lineas entrantes a cada controlador de cache con el cual 
		"espia" lo que hacen los demas procesadores en particular con la memoria 

		Si un procesador necesita un dato y no esta en su cache(READ MISS)
		genera el acceso hacia la jerarquia inferior. Si fue un Hit,
		lo resuelve desde su cache (baja a la jerarquia solo por CACHE MISS)

	
	CACHE MISS: event in which a system or app makes a request to retrieve data 
	
	|			from cache but that specific data is not currently in cache memory

	
	M - Modified L´ınea presente solamente en ´este cache que vari´o respecto de su valor en memoria del sis-
			tema (dirty). Requiere write back hacia la memoria del sistema antes que otro procesador
			lea desde all´ı el dato (que ya no es v´alido).
	E – Exclusive Linea presente solo en esta cache, que coincide con la copia en memoria principal (clean)
	S-Shared Linea del cache presente y PUEDE estar almacenada en los caches de otros procesadores
	I-invalida linea es invalida 
	
	(MESI) -> protocolo de coherencia 
	

Alta Impedancia: ES FUNDAMENTAL, si no se quema todo 

Tengo que sacarlo del core al dato compartido y pasarlo a (minimo) LEVEL 3

RFO -> A write may be performed freely if the cache line is in the modified 
		or Exclusive state.If it is in the Shared state, all other cached copies
		must be invalidated first. This is typically done by a broadcast operation 
		known as RFO (Request for ownership)

		A cache that hold a line in the modified state must snoop all attempted reads
		and insert the data that it holds 

		A cache that holds a line in the shared state must listen for invalidate or 
		RFO broadcasts from other caches, and discard the line (by moving it into Invalid
		state) on a match 

		The Shared state may be imprecise: if another cache discards a Shared line,
		this cache may become the sole owner of that cache line, but it will not be promoted to Exclusive state

		Modified (M)
    		The cache line is present only in the current cache, and is dirty - 
			it has been modified (M state) from the value in main memory. 
			The cache is required to write the data back to the main memory at some time in the future, 
			before permitting any other read of the (no longer valid) main memory state. 
			The write-back changes the line to the Shared state(S).
		Exclusive (E)
    		The cache line is present only in the current cache, but is clean - it matches main memory. 
			It may be changed to the Shared state at any time, in response to a read request. 
			Alternatively, it may be changed to the Modified state when writing to it.
		Shared (S)
    		Indicates that this cache line may be stored in other caches of the machine and is clean 
			- it matches the main memory. The line may be discarded (changed to the Invalid state) at any time.
		Invalid (I)
    		Indicates that this cache line is invalid (unused).

		Shared: El gran quilombo 
				el dato esta COHERENTE, hay mas DE UNO,
				como uno o mas?
				suponete que tengo el dato exclusive, otro core el mismo dato
				le aviso al otro core de que estamos en shared y lo cambio yo tambien

				Seguimos trabajando con el dato, yo desalojo la linea (la pongo invalida)
				la invalidacion de un dato no se informa por el bus. 

				Esto provoca que el estado shared sea un estado impreciso, por que la invalidacion 
				no se informa el otro core queda en shared

				Por que no se informa? PARA NO USAR EL BUS AL PEDO 
				
				Se invalida un dato, en este caso, por que deje de usarlo
				Otro caso,un cache flush.

				Que pasa si quiero escribir una linea shared? tengo que avisarles 
				a los otros "che invaliden", como hacemos esto? con RFO!
					-genero la transaccion
					-propago un write miss (simulado)
					-la escribo como modified
					-la tiro mas abajo del cache para que los otros la invaliden 
					-A partir de ese momento todos la tienen modified y los otros
					la tienen invalid 
				
				La frecuencia de las escrituras tiene una probabilidad de ocurrencia menor
				a las invalidaciones (una de las razones de que no se avisan las invalidaciones)

				- exclusive y alguien quiere escribir la linea la invalido
				- shared y alguien quiere escribir la linea la invalido
				- modified y alguien quiere escribir la linea tengo que bancar el RFO
					la bajo a memoria y la escribo como exclusive
				

MESIF Intel agrega a MESI un estado adicional. Forwards como una forma especial de estado S 
	  optimiza el acceso al bus en sistema con memoria distribuida
	  intel agrega a MESI un estado adicional, Forward como una forma especial del estado S
	  el protocolo debe asegurar que entre los caches que tienen una linea determinada en estado
	  S, una de ellas tengan estado F
	
	In a system of caches employing the MESI protocol, a cache line request that is received 
	by multiple caches holding a line in the S state will be serviced inefficiently. 
	It may either be satisfied from (slow) main memory, or all the sharing caches could respond, 
	bombarding the requestor with redundant responses. In a system of caches employing the MESIF protocol, 
	a cache line request will be responded to only by the cache holding the line in the F state

	The F state is a specialized form of the S state, and indicates
	that a cache should act as a designated responder for any requests for the given line. 
	The protocol ensures that, if any cache holds a line in the S state,
	at most one (other) cache holds it in the F state.


Arbitro: se encarga de administrar y repartir los recursos del procesador 
		 segun decida. 

 

MOESI 
	este protocolo lo emplea AMD desde los procesadores opteron 
	O=Owned
	Owned states represent a state that is both modified and shared 
	This avoids the need to write modified data back to main memory
	before sharing it. While the data must be written back eventually 
	the write back may be deferred 	

	Owned cache must respond to a snoop request with data,to ensure 
	the stale copy in main memory is not used 

	buffer es un inversor invertido,amplificador de corriente
	el buffer lo que hace es amplificar la corriente para que una entrada
	pueda escribir adecuadamente en multiples salidas 

	Owned = La tengo yo y otros mas pero yo la puedo escribir 
			si otro la escribe yo me paso a shared y el otro se 
			pasa a owned 

Smart Cache 
	memoria compartida L2 entre cores

MEMORIA DINAMICA 

		A diferencia de las memorias cache que van generalmente en el mismo chip de la CPU 
		estas memoria al momento se ubican en uno o mas chips separados de la CPU 

		capacitor almacena energia electrica pero no en forma definitiva 

		neceistamos refrescar periodicamente la informacion para que no se pierda la informacion 
		almacenada (lectura dummy)

		con la reduccion de escala esto se agrava la cantidad de cargas que puedo poner un capacitor 
		es menor y el timepo que tarda en descargarse es muy chiquito.

		hay que pode sensar el estado de carga durante un intervalo muy pequeño de tiempo ya que una vez 
		que la celda descarga cagaste

	
	Organizacion de una DRAM generica 
		la organizacion de las celdas de una memoria DRAM es como una matriz rectangular
		originalmente la cantidad de pines de un chip era un problema serio desde el punto de vista 
		mecanico (cantidad de pines su ancho y separacion)
		
		por ello se organizaba en una matriz de celdas de NXM con n y m en lo posible del mismo valor o con una unidad
		de diferencia. Se multiplexaban los terminales y se seleccionaba en primer lugar la FIla y luego la columna 

		la cantidad de terminales de address se reduce a la mitad 

		la señal RAS(Row address Strobe) selecciona la fila a leer y CAS(Column address strobe) los elementos
		de esa fila que se copiaran en el buffer de lectura 

		la direccion que vos tenes en los registros de tu programa no tiene nada que ver con la realidad(?)

		quien se encarga de hacer la traduccion direccion humana -> fila y columna? el que se encarga de la memoria 
		jo jo jo

		cualquier maquina que enciendan, al principio no hay absolutamente nada (tampoco la memoria RAM!)
		(por que no tenes iniciado el controlador, lo cual es un archi quilombo)

		la BIOS tiene dos parte, POWER ON SELF TEST! se ejecuta cuando prendes la maquina 
		y el basic input output system, pero ya medio que no lo usa nadie 	

		 POWER ON SELF TEST (POST) 
		 	is an automated check a computer does when powered on to make sure 
			all hardware components are working properly.	
		
		mucha ventajas, entre ellas la alta capacidad que tiene dada 
		la superficie de silicio que usa 

		flanco ascendente del uno es MUY pequeño, necesitamos algo que 
		pueda reconocer esa suba de corriente en un periodo de tiempo
		ridiculamente corto

		cada die de DRAM, contiene uno o varios arrays de nxm celdas 

		dependiendo de la cantidad de matrices las DRAM se llaman 
		2xDRAM,4xDRAM,8xDRAM

		BANCOS DE DRAM
			operan de forma independiente con set de arrays con RESTRICCIONES
			deben ser activadas precargados leidos al MSIMO TIEMPO que otros bancos
			que esten dentro del mismo dispositivo DRAM o en dispositivos diferentes

			el uso de bancos independientes permite aumentar la velocidad de acceso a estos dispositivos
			entrelazando los accesos a bancos diferentes de memoria

			esto se consigue con hardware de mediacion entre la memoria y el procesador

			si los bancos tienen un tiempo de 10ns, leer en forma entrelazada dos bancos
			permite acceder a 5ns

			si se hace round robin con 4 bancos,el tiempo de acceso percibido por el proces es de 2,5 ns

			mapea este rango de direcciones en este banco, la siguiente es el proximo banco para 
			leerlo entrelazado (se puede hacer entre mas de dos bancos,depende de la implementación)

			los bancos son BLOQUES DE DIRECCIONES CONTIGUAS DE MEMORIA

		DIMM (dual in module memory)
			en sistemas que erequieren alta capacidad de almacenamiento las DRAM se organizan en DIMMS 

			los dispositivos DRAM se montan a ambos lados del PCB

			cada DIMM puede pensarse como un banco independiente 

			o bien cada dispositivo o grupo de dispositivos DRAM de un DIMM se puede asignar a un banco 
			independiente 


		DENTRO DEL DRAM DEVICE
			nosotros tenemos word line (fila)
			y bit lien (columna)

			cuando seleccionamos una fila y una columna seleccionamos la word line
			y la bit line,lo cual activa el transistor. El cual solo se va a activar cuando 
			se active la bit line 

			como prendemos la bit line? cargarla con un valor electrico entre 0 y 1

										Al habilitarse una wordline, el capacitor de la bitline habilitada produce una alteraci´on muy pe-
										que˜na en el valor de tensi´on precargado, en mas o en menos dependiendo del estado de su carga.		
			
			AMPLIFICADOR DE DETECCION
			 dos ivnersores 
			 el capacitor puede estar cargado o descargado
			 	Si no cargado 
					0 por arriba
					0 negado abajo
			 	Si cargado 
					si activo la WORD LINE 
					activo al fet(?) de la celda 
					agregamos un delta que desbalancea el sistema
					y nos permite que el sitema nos permita empezar a 
					realimentar la corriente con PUSH PULL 
					hasta que el de arriba llega a Vdd y el otro llega a 0

					el problema es que esto tardo bastante es re lento 

					Vdd = tension de alimentacion 

			si por cada cosito tenemos que tener un amplificador es medio malo
			pero por suerte sirve para una columna

			por que quisiera latchear toda la fila en vez de solo lo que nos pidieron? 
			por el principio de localidad, seguramente querramos usar la informacion de la fila 
			en proximas instrucciones 

			lineas de las cache => 512 bites

			esto es la ram dinamica que tenes en el motherboard 

			la cache esta adentro del procesador, cuando sale de ahi es por que esta accediendo a MEMORIA 

			lo bueno es poder tener un DIMM que sabes que mide tanto que son los suficientemente inteligentes
			que el controlador lo maneja 

			la parte mas dificil de inicializar es esto 

			SDRAM synchronous DRAM todas las generaciones anteriores eran asincronicas 
			sincronizar hace posible aplicar CAs y RAs yara yara 
				como funciona? activando el RAs y CAs
				en general los enables son activos bajos 
				tenes la linea en 1 y me tiras un potente flanco descendente y listo

				la forma en la que se hizo de esta manera es que se diseño en 1974 
				y los pines eran un gran problema, (tampoco habia CI), la idea era intentar
				usar la menor cantidad de lineas posibles. (los buses eran CABLES)						

				al principio era CAS -> RAS -> DATO
				por que no ponemos varias rafagas al mismo tiempo?
				POR EL PRINCIPIO DE LOCALIDAD 

				Column Adress Stroke
				Row Address Stroke 

				Transferencias rafaga (BURST)

				generalmente cuando trabajamos con el clock leemos en un flanco (asc o desc)
				la idea aca es que leemos en AMBOS FLANCOS
				pares en ascendentes impares en descendentes
				con ese truco DUPLICAMOS la lectura

		STANDARD JEDEC 
			las DRAM actualmente son un commodity 
			cualquier DRAM o DIMM actual tienen especificaiones equivalente 
			ancho de bus capacidad velocidad interfaz por citar las mas importantes
			Cualquier DRAm o DIMM actual tiene especificaciones equivalentes: ancho de bus,
			capacidad,velocidad,por citar las mas importantes
			esta compatibilidad esta gobernada por JEDEC
			el data bus por razones de optimizacion de ancho de banda se definio de 64 bits 
			que es no activar chip select? los que no tienen chip select activo estan en 
			ALTA IMPEDANCIA 

		un controlador de memoria puede abastecer a ncores/procesadores

		GDDR is not the same as DDR. Overall, GDDR is built for much higher bandwidth, thanks to a wider memory bus
			
	las transacciones burst tienen dos pos
		burst secuencial
			vos me pedis un burst de 8 rafagas y te las mando secuencialmente
		burst wrapped
			pega un wrap around y agarra las direcciones mas chicas si se pasa 

			con que encaja esto? 8 rafaga de 64 bits, 8 rafagas de 8 bytes 
								 64 bytes, 512 bits, una linea de cache!

		uso el burst wrapped por que primero uso lo que necesito al principio y capaz que 
		lo anterior lo llega a usar  

		alinear para que funcione bien en la cache!

		NADIE USA RAM DINAMICA SI NO HAY UN CACHE EN EL MEDIO
		

		OBSTACULOS DE DATOS
			add r1,r2,r3
			sub r4,r1,r5
			and r6,r1,r7
			todas las intrucciones siguientes a la primera usan r1
			pero la primera escribe en r1 (hay como un bottleneck)

			el pipeline sabe que no puede fetchear ese operando por que se va a
			escribir en otro lado (por ende te genera dos agujeros)

			como mejoramos esto? haciendo forwarding
			ergo no esperar que se escriba en memoria
			en cambio lo reinyectamos en la proxima instruccion 
			ganamos un ciclo de clock!

			lo mas conservador es hacer un stall,la otra es hacer lo del 
			forward

			algunas veces forwarding no es factible 
			normalmente forwarding aplica a opearciones de ALU denominadas 
			back to back, ya que el bypass se efectua desde la alu a un registro entero del procesador

		
		OBSTACULOS DE CONTROL 
			un branch es la peor situacion en perdida de perfomance 
			son lo peor 
			por que un branch, un salto, una interrupcion
			hace que vos lo que venias procesando en forma secuencial 
			se rompa por completo

			por ende todo lo que tenias en el pipeline lo tenes que tirar 
			
			mas profundo pipeline peor es el efecto del salto

			pipeline es una forma de atomizar la tarea de tal forma que todas sean simples

			
 */