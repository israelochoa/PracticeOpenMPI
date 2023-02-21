# PracticeOpenMPI

GUÍA DE PRÁCTICAS DE LABORATORIO
PRÁCTICA NRO 4
Fecha: 20 de Febrero de 2023

CODE TO GITHUB: https://github.com/israelochoa/PracticeOpenMPI.git
CODE TO YOUTTUBE: https://youtu.be/W9Kb1Y8hnUc


Carrera: Ingeniería en Computación
Docente: José Oswaldo Guamán Quinche
Semestre: Séptimo
Periodo lectivo:
Abril - Septiembre 2022
Asignatura: Algoritmos, Análisis y Programación Paralela
Paralelo:
“A”
Resultado de Aprendizaje:
Paralelización de un código secuencial a paralelo  
Nombre de la Unidad: Patrones algorítmicos paralelos o Algoritmos específicos
Tema: Solución de problemas concurrentes
Número horas: 5


OBJETIVO DE LA PRÁCTICA
Realizar la solución del problema aplicando diagrama de tareas
Realizar la solución del problema en MPI
MATERIALES, EQUIPOS Y HERRAMIENTAS
IDE de programación
SO  linux
MPI
Ejercicio 1 
De una matriz 100000X100000 se debe buscar el número de veces que aparece un número dentro de la matriz.

Ejercicio 2 
De una matriz 100000X100000 se debe extraer la diagonal y de ahi hacer las siguientes operaciones:
Calcular la suma de las diagonales (por separado)
Calcular el valor más alto de las diagonales (por separado)
Cual tiene el valor más alto de las diagonales
Cual diagonal es más grande

Para ambos ejercicios se necesita:
Implementar todo en MPI e ingresar datos por teclado
Un video explicando el funcionamiento del código
El código en git

El documento con los resultados obtenidos en la sección ACTIVIDADES A DESARROLLAR
Fundamentos teóricos
Los visto en clases
ACTIVIDADES A DESARROLLAR (Por parte del estudiante)
Realizar las instrucciones por parte del docente
RESULTADOS OBTENIDOS
EJERCICIO 1
Test del Ejercicio 1 con una matriz de 5 *5 funciona para cualquier tamano

Figura. Ejercicio 1 Cálculo de cantidad de un elemento de búsqueda en una matriz

EJERCICIO 2
Test del Ejercicio 2 con una matriz de 5 *5 funciona para cualquier tamano

Figura. Ejercicio 2 Calculo de las diagonales de una matriz
CONCLUSIONES
En conclusión, MPI proporciona una variedad de métodos de comunicación para intercambiar datos entre procesos en aplicaciones paralelas. Los cuatro métodos principales son enviar, recibir, recopilar y dispersar. Aquí hay algunos puntos clave para cada método:

Send: El método de envío permite que un proceso envíe un mensaje a otro proceso. El proceso de envío especifica el proceso de destino y los datos del mensaje. El método de recepción debe usarse en el proceso de recepción para recibir el mensaje.

Receive: el método de recepción permite que un proceso reciba un mensaje de otro proceso. El proceso de recepción especifica el proceso de origen y el búfer para recibir los datos del mensaje. El método de envío debe usarse en el proceso de envío para enviar el mensaje.

Gather: el método de recopilación permite que un grupo de procesos envíe sus datos a un solo proceso. El proceso de recepción recopila los datos en un único búfer. Este método puede ser útil para operaciones como calcular la suma de vectores o concatenar cadenas.

Scatter: el método de dispersión permite que un solo proceso distribuya datos a un grupo de procesos. Los datos se dividen en fragmentos de igual tamaño y se distribuyen entre los procesos. Este método puede ser útil para operaciones como la partición de un gran conjunto de datos para el procesamiento en paralelo.

En general, el uso de estos métodos depende de los requisitos de la aplicación paralela específica. La elección del método puede afectar el rendimiento y la eficiencia de la aplicación. Por ejemplo, los métodos de dispersión y recopilación pueden ser más eficientes para operaciones que requieren que todos los procesos tengan una copia de los mismos datos, mientras que los métodos de envío y recepción pueden ser más eficientes para intercambiar cantidades más pequeñas de datos entre una cantidad menor de procesos. Es importante considerar cuidadosamente las necesidades de comunicación de la aplicación y elegir el método adecuado para lograr el rendimiento y la escalabilidad deseados.





RECOMENDACIONES
Utilice tipos de datos que coincidan con la precisión y el tamaño de los vectores. Por ejemplo, use MPI_DOUBLE para vectores de precisión doble y MPI_FLOAT para vectores de precisión simple. Esto puede ayudar a evitar la pérdida de precisión y mejorar el rendimiento. Utilice la comunicación sin bloqueo cuando sea posible. La comunicación sin bloqueo permite la superposición de la comunicación y el cálculo, lo que puede mejorar el rendimiento. 
Utilice MPI_Isend y MPI_Irecv para iniciar la comunicación y continuar con el cálculo mientras espera que se complete la comunicación. Utilice MPI_Wait o MPI_Waitall para esperar a que se complete la comunicación antes de acceder a los datos recibidos. Distribuya el trabajo uniformemente entre los procesos. Si los vectores tienen un tamaño que no es divisible por el número de procesos, distribuya el resto uniformemente entre los procesos. Esto puede ayudar a evitar el desequilibrio de carga y mejorar el rendimiento. Utilice funciones de comunicación colectiva cuando sea posible. 
Las funciones de comunicación colectiva, como MPI_Allreduce o MPI_Reduce, pueden realizar la suma de todos los procesos en una única llamada de función. Esto puede simplificar el código y mejorar el rendimiento al reducir la sobrecarga de comunicación. 
Utilice técnicas de vectorización para optimizar el cálculo. Las técnicas de vectorización, como el desenrollado de bucles, las instrucciones SIMD o las optimizaciones del compilador, pueden ayudar a mejorar el rendimiento del cálculo. Consulte la documentación de su compilador o utilice herramientas de generación de perfiles para identificar las mejores técnicas de optimización para su código. Utilice técnicas de E/S paralelas para optimizar el rendimiento de E/S. Si su programa necesita leer o escribir vectores grandes en el disco, considere usar técnicas de E/S paralelas, como MPI I/O o HDF5, para mejorar el rendimiento de E/S. Estas técnicas pueden distribuir la E/S en varios procesos y mejorar el rendimiento de la E/S.


BIBLIOGRAFÍA




