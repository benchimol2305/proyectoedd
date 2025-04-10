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
   
   3 . Actualizar liderazgo: En caso de fallecimiento o de que el líder supere los 70 años, el programa asigna automáticamente un nuevo lider
     
   5 . Mostrar todos los miembros: El programa muestra a todos los mienbros existentes del clan junto a los contribuidores que estan asocidos a ellos

   6 . Buscar miembro por ID. 

   7. Buscar miembro por nombre: El programa buscara a cualquier mienbro existente en el clan 

   8. Editar miembro: 

   9. Agregar contribuidor: Podras asignar un contribuidor a cualquier mienbro del clan asi registrando su apoyo a este mismo 

     10 . Mostrar todos los contribuidores:  Cada nodo incluye una lista de contribuidores al clan. Cada contribuidor se define con los siguientes atributos:  
     - Nombre  
     - Edad actual  
     - ID único  
     - Descripción de la contribución  
     - Grado de contribución (rango de 1 a 10)  

     12 . Buscar contribuidor por nombre: El programa da a mostrar a cualquier contribuidor existente por su nombre mostrando que aporte tuvo en el clan 

   13. Editar contribuidor: Pordras editar a cualquier contribuidor existente asignando otro rango de contribucion, ID, edad, etc 

   14. Salir de la ejecucion del programa.

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


