# Trabajo de fin de máster - CaxidyEngine

## Descripción del proyecto
Se ha realizado el desarrollo de un motor gráfico. Además, se ha desarrollado un videojuego utilizando el motor gráfico desarrollado.

El desarrollo se ha realizado utilizando C++ 11 y para la programación en GPU se ha utilizado GLSL 3.30. Además se ha utilizado cmake como sistema de compilación

El proyecto se llevó a cabo en la Escuela Técnica Superior de Ingenierías Informática y de Telecomunicación (Universidad de Granada (UGR)) y fue tutorizado por Carlos Ureña Almagro.

Además, agradecer a  Real-Time Innovations todos los conocimientos obtenidos durante mis prácticas, ya que me permitieron reemplazar el sistema de compilación del motor  gráfico por uno mejor utilizando CMake.

## Tecnología utilizada
### Software utilizado
* Visual Studio Code
* CMake
* Blender

### Librerías utilizadas
* OpenGL 3.0+
* SDL2
* SDL2 Mixer
* SDL2 TTF
* RapidJson
* RapidXml
* Glew 1.10
* Stb image 1.33


## Como usar
Lo primero que debemos hacer es instalar las diferentes librerías que necesitaremos. En el caso de
ubuntu (versión 18.04) debemos instalar los siguientes comando:
```
sudo apt-get install libsdl2-2.0-0 libsdl2-dev
sudo apt-get install libglew-dev
sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev
sudo apt-get install libsdl2-mixer-2.0-0 libsdl2-mixer-dev
sudo apt-get install libsdl2-ttf-2.0-0 libsdl2-ttf-dev
sudo apt-get install libglm-dev
sudo apt-get install mingw-w64-i686-dev
```

Tras esto, debemos realizar la instalación de cmake, para ello:
```
sudo apt-get install cmake
```

Una vez tenemos todo los paquetes necesarios instalados podemos realizar
la compilación de nuestro motor gráfico y los dos videojuegos de ejemplo.
Para ello:

```
mkdir build ; cd build
cmake ../
```

Una vez realizada la configuración de cmake tendremos generados los makefiles necesarios para compilar nuestro sistema, para compilarlo debemos:
```
make
```

Tras esto, habremos generados los binarios necesarios. y ya solo debemos
ejecutar los videojuegos, para ello:
```
./build/example/BasicVideoGame/BasicVideoGame
./build/example/VideoGame/main
```
