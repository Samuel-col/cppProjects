# Análisis Bayesiano de las horas de estudio de los estudiantes de ocho colegios
## Modelo bayesiano normal jerarquico con varianza común a los colegios
##### Samuel Sánchez
##### Thu Sep 16 08:49:36 2021

## Muestreador
Se ejecutó el algoritmo con 2 iteraciones del periodo de calentamiento, 14 iteraciones reales y los siguientes valores iniciales:

 * $\theta_j=0$ para $j=1,2,...,8.$
 * $\sigma^2=100$
 * $\mu^2=0$
 * $\tau^2=100$

## Evaluación de la convergencia
## Medias posteriores e intervalos de confianza al 95%
|Parámetro|q0.05|Media|q0.95|
|:-------:|----:|----:|----:|
|$\sigma^2$|13.9899|13.9898|13.9886|
|$\mu$|7.34942|7.444|7.45253|
|$\tau^2$|4.07279|4.0067|4.0009|

## Estudio de R
$R=\tau^2/(\tau^2+\sigma^2)$

### Densidad de R:
