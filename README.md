# Basic-Interpreter( in development )

--Interprete de BASIC--

Compilacion en GNU/Linux:
./compile

Limpiar proyecto en GNU/Linux:
./clean.sh

Comandos:

QUIT //Sale del editor
LOAD //Carga el archivo program.bas
SAVE //Guarda el archivo program.bas
RUN //Ejecuta el programa


Ejemplo de codigo BASIC:


0 COUNT = 1
10 COUNT = COUNT + 1
20 IF COUNT<99 THEN GOTO 1
30 PRINT COUNT
40 SUMA = 10
50 RESTA = 20
60 PRINT SUMA - RESTA


TODO:
    ->Solo acepta mayusculas
    ->Agregar FOR, RESTA, STRINGS,MAYOR, IGUAL, MENOR_IGUAL, etc.
