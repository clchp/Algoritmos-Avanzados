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
