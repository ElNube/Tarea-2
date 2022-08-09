/* 
	@objetivo. Implementacion de arbol binario
	@autor. Jazna Meza Hidalgo
	@version. Junio 2020 - Mejorada Agosto 2022
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(x,y) (x>y?x:y)

/* Estrucrtura del árbol */
typedef struct s_nodo{
	int elemento;
	float x, y;
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

void recorrerFila(FILA f);

/* Funcion principal */
int main(){
	int i, valor, total = 0, n = 6, eliminado;
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
	return 0;
}

/*
	Objetivo. Agrega un nuevo nodo al arbol
	@parametros
		raiz  : puntero a la raiz del arbol
		valor : elemento a agregar al arbol
	@retorno : Arbol actualizado
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

/*
	Objetivo. Recorrido en INORDEN (IVD)
	@parametros
		r : raiz del arbol
*/
void inOrden(NODO r){
	if (r != NULL){
		inOrden(r->izquierdo); 
		printf("%d ", r->elemento);
		inOrden(r->derecho);
	}
}

/*
	Objetivo. Recorrido en PREORDEN (VID)
	@parametros
		r : raiz del arbol
*/
void preOrden(NODO r){
	if (r != NULL){
		printf("%d ", r->elemento);
		preOrden(r->izquierdo);		
		preOrden(r->derecho);
	}
}

/*
	Objetivo. Recorrido en POSTORDEN (IDV)
	@parametros
		r : raiz del arbol
*/
void postOrden(NODO r){
	if (r != NULL){		
		postOrden(r->izquierdo);		
		postOrden(r->derecho);
		printf("%d ", r->elemento);
	}
}

/*
	Objetivo. Calcular la cantidad de nodos hoja
	@parametros
		raiz : raiz del arbol
		cantidad : referencia que guarda la cantidad
	@retorno : por referencia la cantidad de nodos hoja
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

/*
	Objetivo. Retorna el mayor valor del arbol
	@parametros
		raiz : raiz del arbol
	@retorno : mayor elemento almacenado en el arbol
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

/*
	Objetivo. Retorna la altura del arbol
	@parametros
		raiz : raiz del arbol
	@retorno: altura del arbol
*/
int retornarAltura(NODO raiz){
    if (raiz != NULL){
        return 1 + MAX(retornarAltura(raiz->izquierdo)
        ,retornarAltura(raiz->derecho));
    }
    return 0;
}

/* Versiones recursivas de algunas operaciones */
/*
	Objetivo. Inserta un nuevo nodo en el arbol
	@parametros
		raiz : raiz del arbol
		elem : elemento a insertar
	@retorno: altura del arbol
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

/*
	Objetivo. Busca un elemento dentro del arbol
	@parametros
		raiz : raiz del arbol
		elemento : elemento a buscar
	@retorno: 1 en caso de exito en la busqueda y 0 en caso contrario
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
	Objetivo. Crea una fila vacia
	@retorno : FILA vacia
*/
FILA crearFila(){
	FILA nueva;
	nueva.frente = NULL;
	nueva.ultimo = NULL;
	return nueva;
}
/*
	Objetivo. Agrega un nuevo elemento a la fila. Regla LIFO
	@parametros 
		f  : fila de elementos
		muevo : nuevo elemento que sera agregado
	@retorno : fila actualizada
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

/*
	Objetivo. Extrae elemento de la fila. Regla LIFO
	@parametros 
		f  : fila de elementos
	@retorno : fila actualizada
*/
FILA extraer(FILA f){		
	f.frente = f.frente->siguiente;
	return f;		
}
/*
	Objetivo. Determina si la fila es vacia
	@parametro  
		f : fila
	@retorno : 1: en caso de que la fila esta vacia y 0 eoc
*/
int esVacia(FILA f){
	return (f.frente == NULL)?1:0;
}
/*
	Objetivo. Retorna (sin extraer) elemento al frente de la fila
	@parametros 
		f  : fila de elementos
	@retorno : primer elemento de la fila
*/
NODO verFrente(FILA f){
	return f.frente->valor;
}

/* 
	@Objetivo. Recorre la fila con el recorrido en anchura 
	@parametros
		f : fila de elementos a recorrer
*/
void recorrerFila(FILA f){
	FILA aux = f;
	while(esVacia(aux) == 0){
		printf("%d ", verFrente(aux)->elemento);
		aux = extraer(aux);
	}
}

/* 
	@Objetivo. Realiza el recorrido en anchira del árbol 
	@parametros
		raiz : nodo raíz del árbol
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

/*
	@objetivo. Eliminar un elemento del arbol
	@parametros
		raiz : nodo raíz del árbol
		eliminado : valor a ser descartado del árbol
	@retorno. Árbol actualizado (un nodo menos si es que existe)
*/
NODO remover(NODO raiz, int eliminado){
	return eliminar(raiz, eliminado);
}

/*
	@objetivo. Unir sub-árboles para reestructurar después de la eliminación.
	@parametros
		izquierdo : sub-arbol izquierdo
		derecho : sub-arbol derecho
	@retorno. Árbol actualizado considerando la unión de los sub-árboles
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

/*
	@objetivo. Elimina un nodo considerando la re-estructuración
	@parametros
		raiz : nodo raíz del árbol
		eliminado : valor a ser eliminado
	@retorno. Árbol actualizado cpn un nodo menos (en caso de que el eliminado exista)
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


