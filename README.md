# Registro de Actividad Física

Unidad 3, Tema 2 de Fundamentos de Programación. Programa en C++ que registra la actividad física diaria y calcula estadística descriptiva sobre ella.

## Estructura de datos

Tres arreglos paralelos sincronizados por índice: pasos (entero), minutos de actividad (entero) y calorías quemadas (flotante), para un máximo de 31 días.

## Estadística implementada

Media, mediana y moda, con funciones sobrecargadas para trabajar tanto sobre `vector<int>` como sobre `vector<float>`.

## Análisis específico

| Variable | Indicador |
| --- | --- |
| Pasos | Días que superan la meta de 10 000 pasos |
| Minutos | Porcentaje de días activos, con 30 minutos o más |
| Calorías | Total quemado en el periodo |

## Funcionalidades

1. Ingresar los datos iniciales con validación de rango en cada campo.
2. Insertar un registro en una posición específica.
3. Modificar un día concreto.
4. Buscar un valor en cualquiera de los tres arreglos.
5. Ordenar los tres arreglos de forma ascendente o descendente manteniendo la correspondencia entre ellos.
6. Eliminar por posición o por condición, por ejemplo todos los días con menos de 1000 pasos.
7. Mostrar el análisis estadístico completo.

## Compilación y ejecución

```
g++ PaúlAndrésGuerraVicuña.cpp -o actividad
./actividad
```

---

**Paúl Andrés Guerra Vicuña** · Fundamentos de Programación · Ingeniería en Ciencias de Datos e Inteligencia Artificial · Universidad Nacional de Chimborazo (UNACH)
