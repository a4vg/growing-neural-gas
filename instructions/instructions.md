# cs3102-GNG

> Se pide implementar una Growing Neural Gas con los siguientes requerimientos:
- Lenguaje C++ 
- Librerias: Opencv para abrir imagenes y mostrarlas (guardar resultado, o mostrar video) 
- Docker (input imagen de entrada, output-> video o image resultante) 

## Pipeline

```
Input: Imagen(4k)

Step 0: Leer imagen 
Step 1: Preprocersar la imagen (escala de grises, redimensionar, etc) 
Step 2: Mascara de sobel. (GX ,GY ,  G = Distancia_euclideana de (GX, GY)  -> Canny si alguien desea. 
Step 3: Clase Grafo (por lista de adyacencia) 
Step 4: Clases GNG
Step 5: Entrenar GNG con Imagen. (establecer hyper parametros adecuados: coeficientes e iteraciones) 
Step 6: Graficar GNG en la Imagen. 

Output: Imagen inicial, imagen con la gng graficada, gng exportada a archivo, sobel, video (si es que lo hay), un archivo de configuracion de hyperparametros, 
```

## Consideraciones finales
- Si no compila se califica sobre 11
- Usen templates, traits, etc.
- Sean ordenados. 

# Fecha de entrega. (23 de Julio) 
