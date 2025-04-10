Bienvenido al repositorio oficial de nuestro proyecto 🤓

Este proyecto es una aplicación en C++ para gestionar información sobre el clan y la familia que han mantenido a salvo el shogun. Permite leer datos de archivos CSV, mostrarlos y realizar diferentes operaciones con ellos. Podemos Buscar y editar miembros, actualizar al lider, agregar y editar contribuidores, etc.

Empecemos con la instalacion:
Partiendo de ya tener Visual Studio Code instalado, con un compilador como MinGW.
Desde la terminal de Visual Studio Code:

1. Clona el repositorio usando:

   git clone https://github.com/benchimol2305/proyectoedd

2. Una vez clonado el repositorio, para ubicarte en la carpeta, usa el siguiente comando desde la terminal:
   
   cd proyectoedd
   
3. Estando en "proyectoedd", hay que ubicarnos en la sub carpeta "bin", donde esta ubicado el ejecutable:

   cd bin
   
4. Una vez ubicado en la carpeta, compilar el archivo usando en la terminal:

   g++ main.cpp -o main

5. Una vez compilador ejecutar con el siguiente comando:

    ./main
  
6. El programa te presentará un menú interactivo donde podrás:

   1 . Mostrar linea de sucesion: Se muestra la línea de sucesión actual considerando únicamente a los miembros vivos, lo cual permite conocer de inmediato quiénes podrían ser los futuros líderes.
   
   2 . Actualizar liderazgo: En caso de fallecimiento o de que el líder supere los 70 años, el programa asigna automáticamente un nuevo lider
     
   3 . Mostrar todos los miembros: El programa muestra a todos los mienbros existentes del clan junto a los contribuidores que estan asocidos a ellos con los siguientes atributos
     - ID
     - Nombre 
     - Apellido 
     - Genero
     - Edad
     - ID del padre
     - Esta muerto
     - fue Lider
     - Es Lider

   4 . Buscar miembro por ID: El programa buscara a cada mienbro existente en el clan por su ID mostrando sus datos 

   5 . Buscar miembro por nombre: El programa buscara a cualquier mienbro existente en el clan mostrando todos sus datos y los contribuidores asociados a este 

   6 . Editar miembro: El programa te da la opcion de  editar a cualquier mienbro del clan asignando otro nombre, edad, ID, y si alguna vez fue lider o si es el actual lider  

   7 . Agregar contribuidor: Podras asignar un contribuidor a cualquier mienbro del clan asi registrando su apoyo a este mismo 

     8 . Mostrar todos los contribuidores:  Cada nodo incluye una lista de contribuidores al clan. Cada contribuidor se define con los siguientes atributos:  
     - Nombre  
     - Edad actual  
     - ID único  
     - Descripción de la contribución  
     - Grado de contribución (rango de 1 a 10)  

     9 . Buscar contribuidor por nombre: El programa da a mostrar a cualquier contribuidor existente por su nombre mostrando que aporte tuvo en el clan 

   10 . Editar contribuidor: El programa te da la opcion de editar a cualquier contribuidor existente asignando otro rango de contribucion, ID, edad, nombre y su aporte al clan

   11 . Salir de la ejecucion del programa.

Las contribuciones son bienvenidas 😃 

En caso de que quieras hacer alguna contribucion, sigue estos pasos para contribuir

1. Haz un fork del proyecto. (Click en el boton Fork en la pagina original del repositorio)
2. Crea una nueva rama usando: git checkout -b "nombre de la rama"
3. Realiza los cambios necesarios y haz un commit. (git commit -m "Comentario"
4. Sube los cambios. (git push -u origin "Nombre de la rama que creaste"
5. Crea un pull request. (Es como una solicitud formal que le envías al dueño del proyecto)

Contacto
- Luis Chirinos - Email - luisemilio2006@gmail.com
- Eldi Rangel - Email - eldi456.rangel@gmail.com
- Cesar Benchimol - Cesarbenchimoldavila@gmail.com


