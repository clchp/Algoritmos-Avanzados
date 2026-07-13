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
  * $\text{limite}_{\text{inf}} = \beta - \alpha \cdot (\beta - \tau)$

* **Condición de pertenencia a la RCL:**
  La RCL contendrá todos los elementos $i$ que cumplan con:
  $$\text{greedy}(i) \ge \text{limite}_{\text{inf}}$$
  *Es decir, se toman los elementos desde el valor máximo hasta aquellos que alcancen este umbral inferior.*

#### 📉 Caso ASCENDENTE (Minimización)
Se utiliza cuando los mejores valores *greedy* son los más pequeños (por ejemplo, minimizar costos o distancias).

* **Parámetros:**
  * $\beta = \text{greedy mínimo}$ (el mejor elemento)
  * $\tau = \text{greedy máximo}$ (el peor elemento)
  * $\text{limite}_{\text{sup}} = \beta + \alpha \cdot (\tau - \beta)$

* **Condición de pertenencia a la RCL:**
  La RCL contendrá todos los elementos $i$ que cumplan con:
  $$\text{greedy}(i) \le \text{limite}_{\text{sup}}$$

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
* **Entero:** Ya no se evalúa una condición binaria, sino el impacto de la asignación específica del gen.
  ```cpp
  int maquina_asignada = cromo[i];
  fitness += matriz_rendimiento[i][maquina_asignada];
  ```
### 2. Aberración (Validación de Factibilidad)
Evalúa si un cromosoma representa una solución válida ante las restricciones del problema.
* **Binario:** Control de límites lineales simples, como que el peso total no supere la capacidad máxima.
* **Entero:** Validaciones lógicas más complejas, por ejemplo:
  * Controlar la cantidad máxima de tareas asignadas a una misma máquina.
  * Garantizar que al menos un operador esté asignado a cada máquina crítica.

### 3. Base de Representación
Determina el rango numérico que puede tomar cada gen.
* **Binario:** La base es fijada en `2` (valores permitidos: 0 y 1).
* **Entero:** La base cambia según las opciones del problema.
  * *Ejemplo:* Si existen las máquinas del 1 al 5 y la posición `0` indica "no asignado", la base es `6` (rango de valores: 0, 1, 2, 3, 4, 5).

### 4. Generación de Población Inicial
* **Binario:**
  ```cpp
  cromo[i] = rand() % 2; // Genera 0 o 1
  ```
* **Entero:**
  ```cpp
  cromo[i] = rand() % base; // Genera valores de 0 a (base - 1)
  ```

### 5. Mutación
* **Binario:** Operación simple de inversión de bits (flip).
  ```cpp
  if (gen == 0) gen = 1;
  else gen = 0;
  ```
* **Entero:** Se selecciona un valor aleatorio dentro del alfabeto, asegurando idealmente que no se repita el valor actual.
  ```cpp
  int nuevo;
  do {
      nuevo = rand() % base;
  } while (nuevo == padres[i][gen]); // Evita mutar al mismo valor
  
  padres[i][gen] = nuevo;
  ```

### 6. Inversión
* **Binario:** Comúnmente suele implementarse cambiando los valores de los bits en un rango.
* **Entero:** Se realiza una inversión posicional de un subsegmento mediante intercambios (`swap`), preservando la estructura interna del cromosoma.
  ```cpp
  int fin = rand() % padres[i].size();
  int inicio = rand() % padres[i].size();
  
  if (inicio > fin) {
      swap(inicio, fin);
  }
  
  while (inicio < fin) {
      swap(padres[i][inicio], padres[i][fin]);
      inicio++;
      fin--;
  }
  ```

---

> 📝 **Notas Finales:** Las modificaciones lógicas dependen enteramente de cómo se codifique el cromosoma. Aunque la estructura macro del algoritmo genético se conserva, la flexibilidad radica en adaptar el **Fitness**, la **Aberración (factibilidad)** y los **Operadores de variación** según el dominio del problema.
