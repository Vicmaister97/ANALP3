/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Alfonso Villar y Víctor García
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include "busqueda.h"

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:12/10/16 */
/* Autores: Alfonso Villar y Víctor García         */
/*                                                 */
/* Entradas:  0 <= n_perms  &&   0<= tamanio       */
/* pfunc_ordena metodo: es un puntero a la funcion */
/* de ordenacion                                   */
/* int n_perms: numero de permutaciones a generar y*/
/* ordenar                                         */
/* int tamanio: tamanio de cada permutacion        */
/* ptiempo: puntero a la estructura de tipo PTIEMPO*/
/*                                                 */
/* Salida:                                         */
/* Devuelve ERR si hay error u OK si ordena        */
/* las tablas correctamente                        */
/*                                                 */ 
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int tamanio, 
                              PTIEMPO ptiempo)
{
	int i;
	int medio_ob = 0;
	int max_ob = 0;
	int min_ob = INT_MAX;
	int ob = 0;
	clock_t ini, fin;
	int **perms = genera_permutaciones(n_perms, tamanio);
	if (perms == NULL){
		return ERR;
	}
	ini = clock(); /*ini = clock_gettime(); */
	for (i = 0; i < n_perms; i++){
		ob = metodo(perms[i], 0, tamanio - 1);
		if (ob == ERR)
			return ERR;
		if (max_ob < ob) /*Comparamos OB iterativamente con max_ob para actualizar el numero maximo de OB*/
			max_ob = ob;
		if (min_ob > ob)/*Comparamos OB iterativamente con min_ob para actualizar el numero minimo de OB*/
			min_ob = ob;
		medio_ob += ob;
	}
	
	fin = clock(); /*fin = clock_gettime(); */
	ptiempo->n_perms = n_perms;
	ptiempo->tamanio = tamanio;
	ptiempo->medio_ob = (double) medio_ob / n_perms;
	ptiempo->max_ob = max_ob;
	ptiempo->min_ob = min_ob;
	ptiempo->tiempo = (double) (fin - ini) / n_perms / CLOCKS_PER_SEC;
	ptiempo->n_veces = ob;
	for (i = 0; i < n_perms; i++)
		free(perms[i]);
	free(perms);
	return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:12/10/16*/
/* Autores: Alfonso Villar y Víctor García         */
/*                                                 */
/* Entradas:  0 <= num_min, num_max, incr, n_perms */
/*                     && num_min < num_max        */
/* pfunc_ordena metodo: es un puntero a la funcion */
/* de ordenacion                                   */
/* char* fichero: fichero donde se escriben los    */
/* tiempos medios, los numeros promedio, minimo y  */
/* maximo de veces que se ejecuta la OB            */
/* int num_min: numero minimo (e incluido) del     */ 
/* rango del tamanio de las permutaciones          */
/* int num_max: numero maximo (e incluido) del     */ 
/* rango del tamanio de las permutaciones          */
/* int incr: valor del incremento del rango del    */
/* tamanio de las permutaciones                    */
/* int n_perms: numero de permutaciones            */
/*                                                 */
/* Salida:                                         */
/* Devuelve ERR si hay error u OK si ordena        */
/* las tablas correctamente                        */
/*                                                 */ 
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  	int i;
	int iteraciones;
	iteraciones = (int)((num_max-num_min)/(incr))+1;
	PTIEMPO ptiempo;
	ptiempo = (PTIEMPO) malloc (iteraciones * (sizeof (TIEMPO)));
	if (ptiempo == NULL)
		return ERR;

	for (i = 0; i < iteraciones; i++){
		if (tiempo_medio_ordenacion(metodo, n_perms, (num_min+i*incr) , &ptiempo[i]) == ERR){
			free(ptiempo);
			return ERR;
		}
	}

	if (guarda_tabla_tiempos (fichero, ptiempo, i) == ERR){
		free(ptiempo);
		return ERR;
		}

	free(ptiempo);
	return OK;
}


/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:  13/10/16  */
/*                                                 */
/* Entradas:  0 <= N  && fichero /= NULL           */
/*                                                 */
/* char* fichero: fichero donde se escriben los    */
/* tamanios de la permutacion, el tiempo de        */
/* ejecucion y el numero promedio, maximo y minimo */
/* de veces que se ejecuta la OB                   */
/* maximo de veces que se ejecuta la OB            */
/* PTIEMPO tiempo: guarda los tiempos de ejecucion */ 
/* int N: tamanio del array tiempo                 */
/*                                                 */
/* Salida:                                         */
/* Devuelve ERR si hay error u OK si ordena        */
/* las tablas correctamente                        */
/*                                                 */ 
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N){

	FILE *fp = fopen(fichero, "w");
	if (fp == NULL)
		return ERR;

	int i;

	for (i = 0; i < N; i++){
		fprintf (fp, "%-20d %-20.9f %-20.2f %-20d %-20d\n", tiempo[i].tamanio, 
				tiempo[i].tiempo, 
				tiempo[i].medio_ob, 
				tiempo[i].max_ob,
				tiempo[i].min_ob);
	}
	
	fclose(fp);
	return OK;
}


/***************************************************/
/* Funcion: genera_tiempos_busqueda Fecha:09/12/16 */
/* Autores: Alfonso Villar y Víctor García         */
/*                                                 */
/* Entradas: fichero!=NULL & 0<num_min<=num_max &  */
/* incr>0 & n_veces>0                              */
/*												   */
/* pfunc_busqueda metodo: introduce el metodo de   */
/* busqueda a usar                                 */
/* int n_veces: veces a ejecutar cada busqueda     */
/* int incr: incremento del tamaño de la tabla     */
/* int num_max: tamaño máximo de la tabla          */
/* int num_min:tamaño mínimo de la tabla           */
/* int fichero:fichero donde guardar los resultados*/
/* int orden: indica si la tabla esta o no ordenada*/
/* pfunc_generador_claves:introduce el metodo de   */
/* generacion de claves                            */
/*												   */
/* Salida:                                         */
/* Devuelve ERR si hay error u OK si no            */
/*                                                 */ 
/***************************************************/

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, int num_min, int num_max, 
                                int incr, int n_veces){

	int i;
	int iteraciones;
	iteraciones = (int)((num_max-num_min)/(incr))+1;
	PTIEMPO ptiempo;
	ptiempo = (PTIEMPO) malloc (iteraciones * (sizeof (TIEMPO)));
	if (ptiempo == NULL)
		return ERR;

	for (i = 0; i < iteraciones; i++){
		if (tiempo_medio_busqueda(metodo, generador, orden, num_min+i*incr, n_veces, &ptiempo[i]) == ERR){
			free(ptiempo);
			return ERR;
		}
	}

	if (guarda_tabla_tiempos (fichero, ptiempo, i) == ERR){
		free(ptiempo);
		return ERR;
		}

	free(ptiempo);
	return OK;
}



/***************************************************/
/* Funcion: tiempo_medio_busqueda Fecha:09/12/16   */
/* Autores: Alfonso Villar y Víctor García         */
/*                                                 */
/* Entradas: 0<num_min<=num_max & n_veces>0        */
/*												   */
/* pfunc_busqueda metodo: introduce el metodo de   */
/* busqueda a usar                                 */
/* int n_veces: veces a ejecutar cada busqueda     */
/* int num_max: tamaño máximo de la tabla          */
/* int num_min:tamaño mínimo de la tabla           */
/* int orden: indica si la tabla esta o no ordenada*/
/* pfunc_generador_claves:introduce el metodo de   */
/* generacion de claves                            */
/*                                                 */
/* Salida:                                         */
/* Devuelve ERR si hay error u OK si no            */
/*                                                 */ 
/***************************************************/

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, 
                              int n_claves, int n_veces, PTIEMPO ptiempo){

	int ob = 0;
	int i, pos;
	int medio_ob = 0;
	int max_ob = 0;
	int min_ob = INT_MAX;
	clock_t ini, fin;

	PDICC pdicc = ini_diccionario (n_claves, orden);
	if (pdicc == NULL) return ERR;

	int* perm = genera_perm(n_claves);
	if (perm == NULL){
		libera_diccionario (pdicc);
		return ERR;
	}

	if (insercion_masiva_diccionario(pdicc, perm, n_claves) == ERR){
		libera_diccionario (pdicc);
		free (perm);
		return ERR;
	}

	int* tabla = (int*) malloc (sizeof (int) * n_claves * n_veces);
	if (tabla == NULL){
		libera_diccionario (pdicc);
		free (perm);
		return ERR;
	}

	generador (tabla, n_claves*n_veces, n_claves);

	ini = clock();
	for (i = 0; i < n_claves*n_veces; i++){
		ob = busca_diccionario(pdicc, tabla[i], &pos, metodo);
		if (ob == ERR)
			return ERR;
		if (max_ob < ob) /*Comparamos OB iterativamente con max_ob para actualizar el numero maximo de OB*/
			max_ob = ob;
		if (min_ob > ob) /*Comparamos OB iterativamente con min_ob para actualizar el numero minimo de OB*/
			min_ob = ob;
		medio_ob += ob;

	}
	fin = clock();
	ptiempo->n_perms = n_claves;
	ptiempo->tamanio = n_claves;
	ptiempo->medio_ob = (double) medio_ob / n_claves / n_veces;
	ptiempo->max_ob = max_ob;
	ptiempo->min_ob = min_ob;
	ptiempo->tiempo = (double) (fin - ini) / n_claves / n_veces / CLOCKS_PER_SEC;
	ptiempo->n_veces = ob;

	libera_diccionario (pdicc);
	free (tabla);
	free (perm);
	return OK;
}