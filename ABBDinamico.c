/**
 * @file Tarea2Marcelo
 * @author Marcelo Alfredo Paz Pezo
 * @firma …ᘛ⁐̤ᕐᐷ ICINF UBB
 * @brief 
 * @version 0.1.0
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
 * - 
 * -
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(x,y) (x>y?x:y)

/* Estructura del elemento */

typedef struct s_tupla{
	float x;
	float y;
} TUPLA;

/* Estructura del árbol */

typedef struct s_nodo{
	int elemento;
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

NODO agregarNodo(NODO, int);
NODO remover(NODO, int);
NODO eliminar(NODO, int);
void insertar(NODO *, int);
int buscar(NODO, int);

/* Recorridos por profundidad */

void inOrden(NODO);
void preOrden(NODO);
void postOrden(NODO);

/* Funcionalidad particular sobre el árbol */

void cantidadNodosHoja(NODO, int *);
int mayorValor(NODO);
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
	
	int n;
	do
	{
		printf("Ingrese la cantidad de nodos que desea ingresar: ");
		scanf("%d",&n);
	} while (n<0);
	
	int i, valor, total = 0, eliminado;
	/* Inicializa el árbol */
	NODO raiz = NULL;
	
	/* Inserta n nodos en el árbol */
	for(i=1; i <= n; i++){
		/* Obtiene el valor a insertar */
		printf("Valor : ");
		scanf("%d", &valor);
		/* Inserción de forma iterativa */
		//raiz = agregarNodo(raiz, valor);
		/* Inserción usando recursividad */
		insertar(&raiz, valor);
	}
	/* Muestra contenido del ABB usando los recorridos por profundidad */
	printf("\nINORDEN\n\t"); inOrden(raiz);
	printf("\nPREORDEN\n\t"); preOrden(raiz);
	printf("\nPOSTORDEN\n\t"); postOrden(raiz);

	/* Obtiene la cantidad de nodos hojas que tiene el árbol */
	cantidadNodosHoja(raiz, &total);
	printf("\nArbol tiene %d hojas\n", total);
	/* Obtiene el mayor valor almacenado en el árbol */
	printf("\nMayor valor : %d\n", mayorValor(raiz));
	/* Obtiene la altura del árbol */
	printf("\nAltura : %d\n", retornarAltura(raiz));

	/* Testea de funcionalidad de búsqueda */
	printf("Valor buscado: ");
	scanf("%d", &valor);
	printf("%d %s existe\n", valor, (buscar(raiz, valor)==1?"SI":"NO"));	

	/* Muestra el recorrido en anchura */
	printf("Inicio Recorrido en anchura ...\n");
	recorridoAnchura(raiz);
	printf("\nFin Recorrido en anchura ...\n");

	/* Prueba la funcionalidad de eliminación de un nodo */

	printf("Valor a eliminar : ");
	scanf("%d", &eliminado);
	raiz = remover(raiz, eliminado);
	/* Vuelve a mostrar el recorrido por profundidad IN-ORDEN */
	printf("Resultado despues de eliminar ...\n");
	inOrden(raiz);
	printf("\n");
	
	/* Para pausar la consola hasta que se presione una tecla cualquiera */
	system("pause");
	return 0;
}

/**
 * @brief Agrega un nuevo nodo al arbol
 * 
 * @param raiz puntero a la raiz del arbol
 * @param valor elemento a agregar al arbol
 * @return Arbol actualizado
 */
NODO agregarNodo(NODO raiz, int valor){
	NODO anterior, auxiliar;
	/* Crea el nuevo nodo */
	NODO nuevo = (NODO) malloc(sizeof(struct s_nodo));
	/* Setea los componentes de la estructura */
	nuevo->elemento = valor;
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
            if (valor < auxiliar->elemento){
                auxiliar = auxiliar->izquierdo;
            }else{
                auxiliar = auxiliar->derecho;
            }
        }
        if (valor < anterior->elemento){
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
		printf("%d ", r->elemento);
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
		printf("%d ", r->elemento);
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
		printf("%d ", r->elemento);
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
int mayorValor(NODO raiz){
    if (raiz != NULL){
        NODO auxiliar = raiz;
        while (auxiliar->derecho != NULL)
            auxiliar = auxiliar->derecho;
        return auxiliar->elemento;
    }
    return -1;
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
 * @param elem elemento a insertar
 * 
 * @return altura del arbol
 */
void insertar(NODO *a, int elem){
	if (*a == NULL){
    	*a = (NODO) malloc(sizeof(struct s_nodo));
    	(*a)->elemento = elem;
    	(*a)->izquierdo =  NULL;
    	(*a)->derecho = NULL;
  	}
  	else if ((*a)->elemento < elem)
    	insertar(&(*a)->derecho, elem);
  	else if ((*a)->elemento > elem)
    	insertar(&(*a)->izquierdo, elem);
}

/**
 * @brief Busca un elemento dentro del arbol
 * 
 * @param raiz raiz del arbol
 * @param elemento elemento a buscar
 * @return 1 en caso de exito en la busqueda y 0 en caso contrario 
 */
int buscar(NODO raiz, int elemento){
  if (raiz == NULL) return 0;
  else if (raiz->elemento < elemento)
    return buscar(raiz->derecho, elemento);
  else if (raiz->elemento > elemento)
    return buscar(raiz->izquierdo, elemento);
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
		printf("%d ", verFrente(aux)->elemento);
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
NODO remover(NODO raiz, int eliminado){
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
NODO eliminar(NODO raiz, int eliminado){
	if (raiz == NULL){
		return NULL;
	}
	/* Verifica si el elemento está en la actual raíz */
    if (raiz->elemento == eliminado){
		return unir(raiz->izquierdo, raiz->derecho);
    }
	/* Ya no estaba en el nodo raíz, por lo tanto, busca en el aub-árbol adecuado */
	if (raiz->elemento > eliminado){
		raiz->izquierdo = eliminar(raiz->izquierdo, eliminado);
	}
	else{
		raiz->derecho = eliminar(raiz->derecho, eliminado);
	}
	return raiz;
}


