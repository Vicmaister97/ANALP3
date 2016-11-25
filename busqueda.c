/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Alfonso Villar y Víctor García
 * Version: 1.0
 * Fecha: 18-11-2016
 *
 */

#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden)
{
	if (tamanio < 1 || (orden != ORDENADO && orden != NO_ORDENADO))
		return NULL;

	PDICC dic = (PDICC) malloc (sizeof (DICC)*tamanio);
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

void libera_diccionario(PDICC pdicc)
{
	assert (pdicc != NULL);

	free (pdicc->tabla);
	free (pdicc);
	return;
}

int inserta_diccionario(PDICC pdicc, int clave)
{
	assert (pdicc != NULL && clave >= 0);

	if (pdicc->tamanio == pdicc->n_datos)
		return ERR;

	if (pdicc->orden == NO_ORDENADO){
		pdicc->tabla[pdicc->n_datos] = clave;
		pdicc->n_datos ++;
		return OK;
	}

	else{
		pdicc->tabla[pdicc->n_datos] = clave;
		int j = pdicc->n_datos-1;

		while (j >= 0 && pdicc->tabla[j] > clave){
			pdicc->tabla[j+1] = pdicc->tabla[j];
			j--;
		}

		pdicc->tabla[j+1] = clave;
	}

	return OK;
}

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

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	assert(pdicc != NULL && clave >= 0);

	if (metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos) == ERR)
		return ERR;

	return OK;
}

void imprime_diccionario(PDICC pdicc)
{
	assert(pdicc != NULL);

	int i;
	for (i = 0; i < pdicc->n_datos; i++){
		printf ("%d/t", pdicc->tabla[i]);
	}
	return;
}

/* Funciones de busqueda del TAD Diccionario */

int bbin(int *tabla, int P, int U, int clave, int *ppos)
{
	assert (tabla != NULL && P <= U && clave >= 0);

	return bbin_rec (tabla, P, U, clave, ppos);
}

int bbin_rec(int *tabla, int P, int U, int clave, int *ppos){
	int m = (int) (P + U) / 2;

	if (tabla[m] == clave){
		ppos = &(tabla[m]);
		return tabla[m];
	}

	if (clave < tabla[m] && P <= (m-1)){
		return bbin_rec (tabla, P, m-1, clave, ppos);
	}

	if (clave > tabla[m] && m+1 <= U){
		return bbin_rec (tabla, m+1, U, clave, ppos);
	}

	return NO_ENCONTRADO;
}


int blin(int *tabla,int P,int U,int clave,int *ppos){
	assert (tabla != NULL && P <= U && clave >= 0);

	int i;
	for (i = P; i <= U; i++){
		if (tabla[i] == clave){
			ppos = &(tabla[i]);
			return OK;
		}
	}

	return NO_ENCONTRADO;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
	assert (tabla != NULL && P <= U && clave >= 0);
	int aux;
	int i;

	for (i = P; i <= U; i++){
		if (tabla[i] == clave){
			if (i == P){
				ppos = &(tabla[i]);
				return OK;
			}
			aux = tabla[i];
			tabla[i] = tabla [i-1];
			tabla[i-1] = aux;
			ppos = &(tabla[i]);
			return OK;
		}
	}

	return NO_ENCONTRADO;
}
