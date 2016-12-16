/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Alfonso Villar y Víctor García
 * Version: 2.5
 * Fecha: 8-12-2016
 *
 */

#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */
  
/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 *				 Entradas: claves>0 y max>0
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 *				 Entradas: claves>0 y max>0
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}


/*
*  Funcion: ini_diccionario
*  				Esta funcion inicia el diccionario
*               con un tamaño fijado y en un estado ordenado o desordenado
*/
PDICC ini_diccionario (int tamanio, char orden)
{
	if (tamanio < 1 || (orden != ORDENADO && orden != NO_ORDENADO))
		return NULL;

	PDICC dic = (PDICC) malloc (sizeof (DICC));
	if (dic == NULL)
		return NULL;

	dic->tamanio = tamanio;
	dic->n_datos = 0;
	dic->orden = orden;
	dic->tabla = (int *) malloc (sizeof (int)*tamanio);
	if (dic->tabla == NULL){
		free (dic);
		return NULL;
	}
	return dic;
}


/*
*  Funcion: libera_diccionario
*               Esta funcion libera el diccionario
*/
void libera_diccionario(PDICC pdicc)
{
	assert (pdicc != NULL);

	free (pdicc->tabla);
	free (pdicc);
	return;
}


/*
*  Funcion: inserta_diccionario
*               Esta funcion inserta una clave en el diccionario
*               si esta ordenado lo coloca ordenado y si no al final de todo
*/
int inserta_diccionario(PDICC pdicc, int clave)
{
	int cont = 0;
	assert (pdicc != NULL && clave >= 0);

	if (pdicc->tamanio == pdicc->n_datos)
		return ERR;

	if (pdicc->orden == NO_ORDENADO){ /*Si el diccionario no es ordenado*/
		pdicc->tabla[pdicc->n_datos] = clave;
		pdicc->n_datos++;
	}

	else{ /*Si el diccionario es ordenado*/
		pdicc->tabla[pdicc->n_datos] = clave;
		pdicc->n_datos++;
		int last = pdicc->tabla[pdicc->n_datos-1];
		int j = pdicc->n_datos-2;

		while (j >= 0 && pdicc->tabla[j] > last){
			pdicc->tabla[j+1] = pdicc->tabla[j];
			j--;
			cont++;
		}

		pdicc->tabla[j+1] = clave;
	}

	return cont;
}


/*
*  Funcion: isercion_masiva_diccionario
*               Esta funcion inserta masivamente claves en el diccionario
*               utilizando en bucle inserta_diccionario
*/
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
	assert (pdicc != NULL && claves != NULL && n_claves >= (pdicc->tamanio - pdicc->n_datos) && n_claves >= 1);

	int i;

	for (i = 0; i < n_claves; i++){
		if (inserta_diccionario(pdicc, claves[i]) == ERR)
			return ERR;
	}
	return OK;
}


/*
*  Funcion: busca_diccionario
*               Esta funcion busca una clave en el diccionario y 
*               hará que ppos apunte al numero de la posicion de la clave
*               utilizando un metodo de búsqueda definido por método
*/
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	int cont;
	assert(pdicc != NULL && clave >= 0);

	cont = metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
	
	return cont;
}


/*
*  Funcion: imprime_diccionario
*               Esta funcion imprime el diccionario
*/
void imprime_diccionario(PDICC pdicc)
{
	assert(pdicc != NULL);

	int i;
	for (i = 0; i < pdicc->n_datos; i++){
		printf ("%d\t", pdicc->tabla[i]);
	}
	return;
}
		
/* Funciones de busqueda del TAD Diccionario */


/*
*  Funcion: bbin
*               Esta es una funcion de busqueda en la cual
*               se reduce el tamaño de la tabla a la mitad en cada cdc
*/
int bbin(int *tabla, int P, int U, int clave, int *ppos)
{
	assert (tabla != NULL && clave >= 0);
	int m = (P + U) / 2;

	if (P > U) return NO_ENCONTRADO;

	if (tabla[m] == clave){
		*ppos = m;
		return 1;
	}

	if (clave < tabla[m]){
		return 1 + bbin(tabla, P, m-1, clave, ppos);
	}

	if (clave > tabla[m]){
		return 2 + bbin(tabla, m+1, U, clave, ppos);
	}

	return NO_ENCONTRADO;
}


/*
*  Funcion: blin
*               Esta es una funcion de busqueda en la cual
*               se busca de 1 en 1 por la tabla la clave linealmente
*/
int blin(int *tabla,int P,int U,int clave,int *ppos){
	assert (tabla != NULL && P <= U && clave >= 0);

	int i;
	int cont = 0;

	for (i = P; i <= U; i++, cont++){
		if (tabla[i] == clave){
			*ppos = i;
			cont++;
			return cont;
		}
	}

	return NO_ENCONTRADO;
}


/*
*  Funcion: blin_auto
*               Esta es una funcion de busqueda en la cual
*               se busca de 1 en 1 por la tabla la clave linealmente
*               y que cuando encuentra la clave hace un swap hacia delante
*/
int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
	assert (tabla != NULL && P <= U && clave >= 0);
	int i;
	int cont = 0;

	for (i = P; i <= U; i++, cont++){
		if (tabla[i] == clave){
			if (i == P){
				*ppos = i;
				cont++;
				return cont;
			}
			tabla[i] = tabla [i-1];
			tabla[i-1] = clave;
			*ppos = i-1	;
			return cont;
		}
	}

	return NO_ENCONTRADO;
}