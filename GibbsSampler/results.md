# Análisis Bayesiano de las horas de estudio de los estudiantes de ocho colegios
## Modelo bayesiano normal jerarquico con varianza común a los colegios
##### Samuel Sánchez
##### Sat Sep 18 11:27:54 2021

## Muestreador
Se ejecutó el algoritmo con 1000 iteraciones del periodo de calentamiento, 200000 iteraciones reales y los siguientes valores iniciales:

 * $\theta_j=0$ para $j=1,2,...,8.$
 * $\sigma^2=100$
 * $\mu^2=0$
 * $\tau^2=100$

## Evaluación de la convergencia
Se calculó la cadena de log-verosimilitud y se evaluó su convergencia obteniendo que su autocorrelación de primer orden es de 0.0429203. Además, las auto correlaciones de segundo, tercer y cuarto orden son 0.00282944, -0.00075753 y -0.00464903 respectivamente. Por lo tanto, podemos concluir que el algoritmo converge con gran facilidad y se puede proceder a realizar el análisis e interpretación de los resultados.

## Medias posteriores e intervalos de confianza al 95%
|Parámetro|q0.05|Media|q0.95|
|:-------:|----:|----:|----:|
|$\sigma^2$|12.289|14.4778|17.2993|
|$\mu$|6.99322|7.56713|8.33778|
|$\tau^2$|2.98179|5.50184|11.3033|

## Estudio de R
$R=\tau^2/(\tau^2+\sigma^2)$

### Densidad de R:
0.0683706 - 0.109597 :||

0.109597 - 0.150823 :|||||||||||||||||||||||||||||||||||||

0.150823 - 0.192049 :|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

0.192049 - 0.233275 :|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

0.233275 - 0.274501 :|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

0.274501 - 0.315727 :||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

0.315727 - 0.356953 :|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

0.356953 - 0.398179 :|||||||||||||||||||||||||||||||||||||

0.398179 - 0.439405 :||||||||||||||||||

0.439405 - 0.480631 :|||||||||||

0.480631 - 0.521857 :||||

0.521857 - 0.563083 :||

0.563083 - 0.604309 :|

0.604309 - 0.645535 :

0.645535 - 0.686761 :

0.686761 - 0.727987 :

0.727987 - 0.769213 :

0.769213 - 0.810439 :

0.810439 - 0.851665 :

0.851665 - 0.892891 :



## Algunas probabilidades
$P(\theta_7<\theta_6)=0.52416$

$P\left(\theta_7=min\{\theta_1,\theta_2,...,\theta_8\}\right)=0.32524$

## Comparación de medias muestrales y medias posteriores
|Colegio|No Estudiantes|Media Muestral|Media Posterior|
|:-----:|:------------:|-------------:|--------------:|
|1|25|9.464|9.24311|
|2|23|7.03348|7.10205|
|3|20|7.953|7.90218|
|4|24|6.23208|6.39477|
|5|24|10.7658|10.3774|
|6|22|6.205|6.38481|
|7|22|6.13273|6.32104|
|8|20|7.381|7.41093|
