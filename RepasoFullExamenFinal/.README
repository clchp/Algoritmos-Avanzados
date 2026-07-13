# Algoritmos Avanzados

Este repositorio contiene las implementaciones, apuntes y resúmenes teóricos de los conceptos clave abordados en el curso de **Algoritmos Avanzados**. El objetivo es servir como una guía de referencia rápida y ordenada.

---

## 📋 Índice
1. [GRASP (Greedy Randomized Adaptive Search Procedure)](#grasp)
   - [Idea General](#idea-general)
   - [Construcción de la RCL (Restricted Candidate List)](#construcción-de-la-rcl)
2. [Algoritmos Genéticos (AG)](#algoritmos-genéticos)
   - [Estructura y Operadores](#estructura-y-operadores)
   - [Comparativa: Cromosoma Binario vs. Cromosoma Entero](#comparativa-cromosoma-binario-vs-cromosoma-entero)
   - [Detalle de Modificaciones en Funciones](#detalle-de-modificaciones-en-funciones)

---

## ⚡ GRASP

### Idea General
**GRASP** (Greedy Randomized Adaptive Search Procedure) es una metaheurística iterativa que construye soluciones de buena calidad mediante una **fase constructiva iterativa aleatorizada y adaptativa**, seguida típicamente por una fase de búsqueda local. 

El proceso de construcción consiste en evaluar un criterio *greedy* (ambicioso) para cada elemento candidato y ordenarlos según dicho criterio. Dependiendo del tipo de problema, el criterio será de:
* **Maximización:** Orden descendente (los mejores valores son los más grandes).
* **Minimización:** Orden ascendente (los mejores valores son los más pequeños).

Para introducir diversidad, se construye una **RCL (Restricted Candidate List)** utilizando un parámetro límite $\alpha \in [0, 1]$, el cual determina qué candidatos tienen la calidad suficiente para participar en la selección aleatoria de la solución.

---

### Construcción de la RCL

#### 📈 Caso DESCENDENTE (Maximización)
Se utiliza cuando los mejores valores *greedy* son los más grandes (por ejemplo, maximizar ganancias).

* **Parámetros:**
  * $\beta = \text{greedy máximo}$ (el mejor elemento)
  * $\tau = \text{greedy mínimo}$ (el peor elemento)
  * $\text{límite\_inferior} = \beta - \alpha \cdot (\beta - \tau)$

* **Condición de pertenencia a la RCL:**
  La RCL contendrá todos los elementos $i$ que cumplan con:
  $$\text{greedy}(i) \ge \text{límite\_inferior}$$
  *Es decir, se toman los elementos desde el valor máximo hasta aquellos que alcancen este umbral inferior.*

#### 📉 Caso ASCENDENTE (Minimización)
Se utiliza cuando los mejores valores *greedy* son los más pequeños (por ejemplo, minimizar costos o distancias).

* **Parámetros:**
  * $\beta = \text{greedy mínimo}$ (el mejor elemento)
  * $\tau = \text{greedy máximo}$ (el peor elemento)
  * $\text{límite\_superior} = \beta + \alpha \cdot (\tau - \beta)$

* **Condición de pertenencia a la RCL:**
  La RCL contendrá todos los elementos $i$ que cumplan con:
  $$\text{greedy}(i) \le \text{límite\_superior}$$

---

## 🧬 Algoritmos Genéticos

Un Algoritmo Genético (AG) es una técnica de optimización inspirada en la evolución natural. Trabaja con una población de soluciones candidatas llamadas **cromosomas** y aplica de manera iterativa los siguientes operadores evolutivos:
1. **Selección:** Escoge los cromosomas más aptos para reproducirse.
2. **Cruza / Crossover (Casamiento):** Combina el material genético de dos padres.
3. **Mutación:** Altera aleatoriamente algunos genes para mantener la diversidad.
4. **Inversión:** Invierte el orden de un subsegmento de genes dentro del cromosoma.
5. **Regeneración / Reemplazo:** Define la nueva población para la siguiente generación.

La representación y estructura del cromosoma depende estrictamente de la naturaleza del problema.

---

## 🔄 Comparativa: Cromosoma Binario vs. Cromosoma Entero

A continuación se detallan los cambios estructurales y lógicos al migrar de una representación binaria a una entera:

| Operación / Propiedad | Cromosoma Binario (0 o 1) | Cromosoma Entero ($\{0, 1, \dots, N-1\}$) |
| :--- | :--- | :--- |
| **Representación** | Los genes solo pueden tomar valores `0` o `1`. | Los genes representan índices, IDs de máquinas, operarios, etc. |
| **Base del Alfabeto** | `base = 2` | `base = Cantidad de estados/opciones posibles (+1 si incluye el 0)`. |
| **Cálculo de Fitness** | Basado en la presencia/ausencia del elemento (frecuentemente multiplicaciones por 0/1). | Basado en el significado del entero asignado (mapeo a matrices de rendimiento o costos). |
| **Validación (Aberración)**| Restricciones directas sobre capacidad o peso acumulado (Ej: Mochila). | Restricciones de asignación única, cargas de trabajo máximas por máquina, etc. |

---

## 🛠️ Detalle de Modificaciones en Funciones

### 1. Cálculo de Fitness
* **Binario:** Se evalúa de manera directa si el elemento está incluido o no en la solución.
  ```cpp
  // Ejemplo en Problema de la Mochila
  sumap += cromo[i] * paq[i];
