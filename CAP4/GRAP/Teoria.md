# Fórmulas y Rangos de la RCL

Antes de aplicar cualquier rango, primero identifica los extremos según el objetivo:

- $\beta$: Mejor valor de $c(x)$ (valor ideal).
- $\tau$: Peor valor de $c(x)$ (valor menos deseado).

---

## A. Rango para MAXIMIZAR
*(Beneficios, ganancias, cobertura, etc.)*

Como se busca maximizar, el mejor valor ($\beta$) es el más alto y actúa como límite superior. El límite inferior se obtiene restando una tolerancia al máximo.

### Fórmula formal

$$
RCL = \{x \in N : \beta - \alpha(\beta - \tau) \le c(x) \le \beta\}
$$

### Interpretación

Un candidato entra a la RCL si su beneficio se encuentra dentro del intervalo:

$$
[\text{Máximo} - \alpha(\text{Máximo} - \text{Mínimo}),\ \text{Máximo}]
$$

---

## B. Rango para MINIMIZAR
*(Costos, distancias, tiempos, etc.)*

Como se busca minimizar, el mejor valor ($\beta$) es el más bajo y actúa como límite inferior. El límite superior se obtiene sumando una tolerancia al mínimo.

### Fórmula formal

$$
RCL = \{x \in N : \beta \le c(x) \le \beta + \alpha(\tau - \beta)\}
$$

### Interpretación

Un candidato entra a la RCL si su costo se encuentra dentro del intervalo:

$$
[\text{Mínimo},\ \text{Mínimo} + \alpha(\text{Máximo} - \text{Mínimo})]
$$

GRASP (*Greedy Randomized Adaptive Search Procedure*) es una metaheurística multiarranque que repite iterativamente dos fases:

1. **Construcción Greedy Aleatorizada**, donde se genera una solución utilizando una Lista Restringida de Candidatos (RCL).
2. **Búsqueda Local**, donde se mejora la solución obtenida explorando su vecindad.

Al finalizar todas las iteraciones, se retorna la mejor solución encontrada.

## Pseudocódigo General de GRASP

```text
GRASP(Instancia, α)

    mejorGlobal ← NULL

    Mientras no se cumpla la condición de parada hacer

        // =========================
        // FASE DE CONSTRUCCIÓN
        // =========================

        S ← ∅
        N ← conjunto de candidatos

        Mientras N ≠ ∅ hacer

            β ← Mejor { c(x) : x ∈ N }
            τ ← Peor  { c(x) : x ∈ N }

            Si es minimización entonces

                RCL ← { x ∈ N :
                        β ≤ c(x) ≤ β + α(τ - β) }

            Sino // maximización

                RCL ← { x ∈ N :
                        β - α(β - τ) ≤ c(x) ≤ β }

            Fin Si

            x ← elemento aleatorio de RCL

            Agregar x a S

            Actualizar N

        Fin Mientras


        // =========================
        // FASE DE MEJORÍA
        // =========================

        mejora ← verdadero

        Mientras mejora hacer

            mejora ← falso

            Generar vecindad F(S)

            Para cada vecino v ∈ F(S) hacer

                Si v es mejor que S entonces

                    S ← v
                    mejora ← verdadero

                    Salir del ciclo

                Fin Si

            Fin Para

        Fin Mientras


        // =========================
        // ACTUALIZAR MEJOR SOLUCIÓN
        // =========================

        Si mejorGlobal = NULL o
           S es mejor que mejorGlobal entonces

            mejorGlobal ← S

        Fin Si

    Fin Mientras

    Retornar mejorGlobal

Fin GRASP
```
