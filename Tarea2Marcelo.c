/**
 * @file Tarea2Marcelo
 * @author Marcelo Alfredo Paz Pezo
 * @firma …ᘛ⁐̤ᕐᐷ ICINF UBB
 * @brief 
 * @version 0.1.3
 * @date 2022-08-09
 * 
 * @copyright Copyright (c) 2022 
 * 
 */

/* 
Tarea 2 
Estructura de datos
@autor - Marcelo Alfredo Paz Pezo …ᘛ⁐̤ᕐᐷ ICINF UBB
*/



/**	COSAS QUE HACER
 * - podria la funcion buscar para evitar remover un valor que no existe
 * -
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x,y) (x>y?x:y)

/* Estructura del elemento */

typedef struct s_tupla{
	float distancia, x, y;
} TUPLA;

/* Estructura del árbol */

typedef struct s_nodo{
	TUPLA elemento;
	struct s_nodo *izquierdo, *derecho;
} *NODO;

/* Estructura para realizar el recorrido por anchura */

typedef struct s_elemento{
	NODO valor;
	struct s_elemento *siguiente;
} *NODO_FILA;

typedef struct s_fila_enlazada{
	NODO_FILA frente, ultimo;
} FILA;

/* Operaciones del árbol */

NODO agregarNodo(NODO, TUPLA);
NODO remover(NODO, TUPLA);
NODO eliminar(NODO, TUPLA);
void insertar(NODO *, TUPLA);
int buscar(NODO, TUPLA);

/* Recorridos por profundidad */

void inOrden(NODO);
void preOrden(NODO);
void postOrden(NODO);

/* Funcionalidad particular sobre el árbol */

void cantidadNodosHoja(NODO, int *);
TUPLA mayorValor(NODO);
TUPLA menorValor(NODO);
int retornarAltura(NODO);

/* Recorrido por anchura o amplitud */

void recorridoAnchura(NODO);

/* Operaciones de fila */

FILA crearFila();
FILA agregar(FILA, NODO);
FILA extraer(FILA);
int esVacia(FILA);
NODO verFrente(FILA);

/* Operaciones especiales */

void recorrerFila(FILA f);

/* Funcion principal */

int main(){
	/* Declaracion de variables */
	int menu, n, i, valid1 = 0, valid2 = 0, valid3 = 0; // valor, total = 0, eliminado;
	/* Inicializa el árbol */
	NODO raiz = NULL;
	
	/* Declarar tupla auxiliar */
	TUPLA PuntoBase, tuplaAux;

	do
	{
		printf("====================> MENU <====================\n");
		printf("1) Cantidad 'n' de puntos a incluir en el arbol.\n");
		printf("2) Leer coords. punto base.\n");
		printf("3) Leer coords. de los 'n' puntos.\n");
		printf("4) Mostrar punto mas alejado y el mas cercano.\n");
		printf("5) Mostrar el listado del el punto mas cercano a el mas lejano del punto base.\n");
		printf("6) Eliminar un punto y mostrar coords. del punto eliminado.\n");
		printf("7) Salir.\n");
		printf("OPCION >>> ");
		scanf("%d", &menu);

		switch (menu) {
			case 1:
				do
				{
					printf("Ingrese la cantidad de puntos que desea ingresar:\n\tn : ");
					scanf("%d",&n);
				} while (n<0);
				valid1 = 1;

				break;	
			
			case 2:
				printf("Punto base:\n");
				printf("\tX : ");
				scanf("%f", &PuntoBase.x);
				printf("\tY : ");
				scanf("%f", &PuntoBase.y);
				PuntoBase.distancia = 0;
				//insertar(&raiz, PuntoBase);
				valid2 = 1;
				break;
			
			case 3:
				if (valid1 == 1 && valid2 == 1)
				{
					/* Inserta n nodos en el árbol */
					for(i=1; i <= n; i++)
					{
						/* Obtiene el valor a insertar */
						printf("Punto #%d:\n", i);
						printf("\tX : ");
						scanf("%f", &tuplaAux.x);
						printf("\tY : ");
						scanf("%f", &tuplaAux.y);
						printf("\n");
						
						/* Inserción de forma iterativa */
						//raiz = agregarNodo(raiz, valor);

						/* Inserción usando recursividad */
						tuplaAux.distancia = sqrt(pow(tuplaAux.x - PuntoBase.x, 2) + pow(tuplaAux.y - PuntoBase.y, 2));
						insertar(&raiz, tuplaAux);
					}
					valid3 = 1;
				}
				else if (valid3 == 1)
					printf("Los puntos no pueden ser modificados");
				else
					printf("Debe completar 1) y 2) para continuar.\n");
				break;	
			
			case 4:
				if(valid3 == 1)
				{
					tuplaAux = menorValor(raiz);
					printf("Punto mas cercano : (%.3f, %.3f) Distancia: %.3f\n", tuplaAux.x, tuplaAux.y, tuplaAux.distancia);
					
					tuplaAux = mayorValor(raiz);
					printf("Punto mas alejado : (%.3f, %.3f) Distancia: %.3f\n", tuplaAux.x, tuplaAux.y, tuplaAux.distancia);
				}
				else
					printf("Debe completar el item 3) para continuar.\n");
				break;
			
			case 5:
				if(valid3 == 1)
				{
					printf("\nINORDEN\n"); inOrden(raiz);
					printf("\n");
				}
				else
					printf("Para continuar debe completar el item 3)\n");
				break;

			case 6:
				if(valid3 == 1)
				{
					printf("Punto a eliminar:\n");
					printf("\tX : ");
					scanf("%f", &tuplaAux.x);
					printf("\tY : ");
					scanf("%f", &tuplaAux.y);
					tuplaAux.distancia = sqrt(pow(tuplaAux.x - PuntoBase.x, 2) + pow(tuplaAux.y - PuntoBase.y, 2));
					if (buscar(raiz, tuplaAux) == 1)
					{
						raiz = remover(raiz, tuplaAux);
						printf("ELIMINACION EXITOSA\n");
					}
					else
						printf("Proceso fallido, no se ha encontrado este punto\n.");
					printf("\n");
				}
				else
					printf("Para continuar debe completar el item 3)\n");
				
				break;

			case 7:                
				printf("-->Deseas salir? SI[1]  / NO[0]: ");
				scanf("%d", &menu);
				fflush(stdin);
                if (menu == 1)
                    menu = 0;
				else
					menu = -1;
                break; 

			default:
				printf("Elija una opcion valida\n");
				break;
		}
	} while (menu != 0);

	/*
	// Muestra contenido del ABB usando los recorridos por profundidad
	
	printf("\nPREORDEN\n\t"); preOrden(raiz);
	printf("\nPOSTORDEN\n\t"); postOrden(raiz);

	// Obtiene la cantidad de nodos hojas que tiene el árbol
	cantidadNodosHoja(raiz, &total);
	printf("\nArbol tiene %d hojas\n", total);
	// Obtiene el mayor valor almacenado en el árbol
	printf("\nMayor valor : %d\n", mayorValor(raiz));
	// Obtiene la altura del árbol
	printf("\nAltura : %d\n", retornarAltura(raiz));

	// Testea de funcionalidad de búsqueda
	printf("Valor buscado: ");
	scanf("%d", &valor);
	printf("%d %s existe\n", valor, (buscar(raiz, tuplaAux)==1?"SI":"NO"));	

	// Muestra el recorrido en anchura
	printf("Inicio Recorrido en anchura ...\n");
	recorridoAnchura(raiz);
	printf("\nFin Recorrido en anchura ...\n");

	// Prueba la funcionalidad de eliminación de un nodo

	printf("Valor a eliminar : ");
	scanf("%d", &eliminado);
	raiz = remover(raiz, eliminado);
	// Vuelve a mostrar el recorrido por profundidad IN-ORDEN
	printf("Resultado despues de eliminar ...\n");
	inOrden(raiz);
	printf("\n");
	*/
	/* Para pausar la consola hasta que se presione una tecla cualquiera */
	//system("pause");
	return 0;
}

/**
 * @brief Agrega un nuevo nodo al arbol
 * 
 * @param raiz puntero a la raiz del arbol
 * @param t elemento a agregar al arbol
 * @return Arbol actualizado
 */
NODO agregarNodo(NODO raiz, TUPLA t){
	NODO anterior, auxiliar;
	/* Crea el nuevo nodo */
	NODO nuevo = (NODO) malloc(sizeof(struct s_nodo));
	/* Setea los componentes de la estructura */
	nuevo->elemento = t;
	nuevo->izquierdo = NULL;
	nuevo->derecho = NULL;

	/* Verifica si es el primer nodo */
	if (raiz == NULL){
		raiz = nuevo;
	} 
	else{
		/* De forma iterativa busca el lugar "correcto" del nuevo elemento */
		auxiliar = raiz;
        while (auxiliar != NULL){
            anterior = auxiliar;
            if (t.distancia < auxiliar->elemento.distancia){
                auxiliar = auxiliar->izquierdo;
            }else{
                auxiliar = auxiliar->derecho;
            }
        }
        if (t.distancia < anterior->elemento.distancia){
            anterior->izquierdo = nuevo;
        }else{
            anterior->derecho = nuevo;
        }
	}
	return raiz;
}

/**
 * @brief Recorrido en INORDEN (IVD)
 * 
 * @param r raiz del arbol
 */
void inOrden(NODO r){
	if (r != NULL){
		inOrden(r->izquierdo); 
		printf("(%.3f, %.3f) Distancia : %.3f\n", r->elemento.x, r->elemento.y, r->elemento.distancia);
		inOrden(r->derecho);
	}
}

/**
 * @brief Recorrido en PREORDEN (VID)
 * 
 * @param r raiz del arbol
 */
void preOrden(NODO r){
	if (r != NULL){
		printf("(%.3f, ", r->elemento.x);
		printf("%.3f) ", r->elemento.y);
		preOrden(r->izquierdo);		
		preOrden(r->derecho);
	}
}

/**
 * @brief Recorrido en POSTORDEN (IDV)
 * 
 * @param r raiz del arbol
 */
void postOrden(NODO r){
	if (r != NULL){		
		postOrden(r->izquierdo);		
		postOrden(r->derecho);
		printf("(%.3f, ", r->elemento.x);
		printf("%.3f) ", r->elemento.y);
	}
}

/**
 * @brief Calcular la cantidad de nodos hoja
 * 
 * @param raiz raiz del arbol
 * @param cantidad referencia que guarda la cantidad
 * 
 * @return : por referencia la cantidad de nodos hoja
 */
void cantidadNodosHoja(NODO raiz, int *cantidad){    
    if (raiz != NULL) {
        if (raiz->izquierdo == NULL && raiz->derecho == NULL)
            (*cantidad)++;
		/* Calcula las hojas de subarbol izquierdo */
        cantidadNodosHoja(raiz->izquierdo,cantidad);
		/* Calcula las hojas de subarbol derecho */
        cantidadNodosHoja(raiz->derecho,cantidad);
    }
}

/**
 * @brief Retorna el mayor valor del arbol
 * 
 * @param raiz raiz del arbol
 * @return mayor elemento almacenado en el arbol
 */
TUPLA mayorValor(NODO raiz){
    if (raiz != NULL){
        NODO auxiliar = raiz;
        while (auxiliar->derecho != NULL)
            auxiliar = auxiliar->derecho;
        return auxiliar->elemento;
    }
	return raiz->elemento;
}

/**
 * @brief Retorna el menor valor del arbol
 * 
 * @param raiz raiz del arbol
 * @return menor elemento almacenado en el arbol
 */
TUPLA menorValor(NODO raiz){
    if (raiz != NULL){
        NODO auxiliar = raiz;
        while (auxiliar->izquierdo != NULL)
            auxiliar = auxiliar->izquierdo;
        return auxiliar->elemento;
    }
	return raiz->elemento;
}

/**
 * @brief Retorna la altura del arbol
 * 
 * @param raiz raiz del arbol
 * @return altura del arbol
 */
int retornarAltura(NODO raiz){
    if (raiz != NULL){
        return 1 + MAX(retornarAltura(raiz->izquierdo)
        ,retornarAltura(raiz->derecho));
    }
    return 0;
}

/* Versiones recursivas de algunas operaciones */
/**
 * @brief Inserta un nuevo nodo en el arbol
 * 
 * @param a raiz del arbol
 * @param t elemento a insertar
 * 
 * @return altura del arbol
 */
void insertar(NODO *a, TUPLA t){
	if (*a == NULL){
    	*a = (NODO) malloc(sizeof(struct s_nodo));
    	(*a)->elemento = t;
    	(*a)->izquierdo =  NULL;
    	(*a)->derecho = NULL;
  	}
  	else if ((*a)->elemento.distancia < t.distancia)
    	insertar(&(*a)->derecho, t);
  	else if ((*a)->elemento.distancia > t.distancia)
    	insertar(&(*a)->izquierdo, t);
}

/**
 * @brief Busca un elemento dentro del arbol
 * 
 * @param raiz raiz del arbol
 * @param t elemento a buscar
 * @return 1 en caso de exito en la busqueda y 0 en caso contrario 
 */
int buscar(NODO raiz, TUPLA t){
  if (raiz == NULL) return 0;
  else if (raiz->elemento.distancia < t.distancia)
    return buscar(raiz->derecho, t);
  else if (raiz->elemento.distancia > t.distancia)
    return buscar(raiz->izquierdo, t);
  else
    return 1;
}

/**
 * @brief Crea una fila vacia
 * 
 * @return FILA vacia
 */
FILA crearFila(){
	FILA nueva;
	nueva.frente = NULL;
	nueva.ultimo = NULL;
	return nueva;
}

/**
 * @brief Agrega un nuevo elemento a la fila. Regla LIFO
 * 
 * @param f fila de elementos
 * @param valor nuevo elemento que sera agregado
 * @return FILA actualizada 
 */
FILA agregar(FILA f, NODO valor){
	/* Crea el nodo y setea los componentes de la estructura */
	NODO_FILA nuevo = (NODO_FILA) malloc(sizeof(struct s_elemento));
	nuevo->valor = valor;
	nuevo->siguiente = NULL;
	/* Verifica si hay otros elementos */
	if (f.frente != NULL){
		f.ultimo->siguiente = nuevo;
		f.ultimo = nuevo;
	}
	else{
		f.frente = nuevo; f.ultimo = nuevo;
	}
	return f;
}

/**
 * @brief Extrae elemento de la fila. Regla LIFO
 * 
 * @param f fila de elementos
 * @return FILA actualizada 
 */
FILA extraer(FILA f){		
	f.frente = f.frente->siguiente;
	return f;		
}

/**
 * @brief Determina si la fila es vacia
 * 
 * @param f fila
 * @return 1: en caso de que la fila esta vacia y 0 eoc 
 */
int esVacia(FILA f){
	return (f.frente == NULL)?1:0;
}

/**
 * @brief Retorna (sin extraer) elemento al frente de la fila
 * 
 * @param f fila de elementos
 * @return primer elemento de la fila 
 */
NODO verFrente(FILA f){
	return f.frente->valor;
}

/**
 * @brief Recorre la fila con el recorrido en anchura 
 * 
 * @param f fila de elementos a recorrer
 */
void recorrerFila(FILA f){
	FILA aux = f;
	while(esVacia(aux) == 0){
		printf("(%.3f, ", verFrente(aux)->elemento.x);
		printf("%.3f) ", verFrente(aux)->elemento.y);
		aux = extraer(aux);
	}
}

/**
 * @brief Realiza el recorrido en anchira del árbol
 * 
 * @param raiz nodo raíz del árbol 
 */
void recorridoAnchura(NODO raiz){
	/* Crea las estructuras auxiliares */
	FILA a = crearFila();
	FILA b = crearFila();

	NODO aux = raiz;
	
	if (raiz != NULL){
		a = agregar(a, raiz);
		while(esVacia(a) == 0){			
			b = agregar(b, (aux = verFrente(a)));
			a = extraer(a);			
			if (aux->izquierdo != NULL){
				a = agregar(a, aux->izquierdo);
			}
			if (aux->derecho != NULL){			
				a = agregar(a, aux->derecho);				
			}			
		}		
		recorrerFila(b);
	}
}

/**
 * @brief Eliminar un elemento del arbol
 * 
 * @param raiz nodo raíz del árbol
 * @param eliminado valor a ser descartado del árbol
 * @return Árbol actualizado (un nodo menos si es que existe)
 */
NODO remover(NODO raiz, TUPLA eliminado){
	return eliminar(raiz, eliminado);
}

/**
 * @brief Unir sub-árboles para reestructurar después de la eliminación.
 * 
 * @param izquierdo sub-arbol izquierdo
 * @param derecho sub-arbol derecho
 * @return Árbol actualizado considerando la unión de los sub-árboles 
 */
NODO unir(NODO izquierdo, NODO derecho){
	NODO centro;
	if (izquierdo == NULL) return derecho;
	if (derecho == NULL) return izquierdo;
	/* Obtiene el elemento central */
	centro = unir(izquierdo->derecho, derecho->izquierdo);
	/* Re estructura */
	izquierdo->derecho = centro;
	derecho->izquierdo = izquierdo;
	return derecho;
}

/**
 * @brief Elimina un nodo considerando la re-estructuración
 * 
 * @param raiz nodo raíz del árbol
 * @param eliminado valor a ser eliminado
 * @return Árbol actualizado cpn un nodo menos (en caso de que el eliminado exista) 
 */
NODO 	eliminar(NODO raiz, TUPLA eliminado){
	if (raiz == NULL){
		return NULL;
	}
	/* Verifica si el elemento está en la actual raíz */
    if (raiz->elemento.x == eliminado.x && raiz->elemento.y == eliminado.y){
		return unir(raiz->izquierdo, raiz->derecho);
    }
	/* Ya no estaba en el nodo raíz, por lo tanto, busca en el aub-árbol adecuado */
	if (raiz->elemento.distancia > eliminado.distancia){
		raiz->izquierdo = eliminar(raiz->izquierdo, eliminado);
	}
	else{
		raiz->derecho = eliminar(raiz->derecho, eliminado);
	}
	return raiz;
}


