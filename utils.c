/*
 * utils.c
 *
 *  Created on: 6 abr. 2021
 *      Author: eneko
 */
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void clearIfNeeded(char *str, int max_line){
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}
//	función para concatenar 2 cadenas caracteres
char* concat (char* c, char* c2){
	int i = 0;
	int cont = 0;
	int i2 = 0;
	int cont2 = 0;
	int i3 = 0;
	int i4 = 0;
	while(c[i] != '\0'){
		cont++;
		i++;
	}
	while(c2[i2] != '\0'){
		cont2++;
		i2++;
	}
	char* concatenacion = (char *) malloc((cont + cont2 + 1) * sizeof(char));
	while(c[i3] != '\0'){
		char s = c[i3];
		concatenacion[i3] = s;
		i3++;
	}
	while(c2[i4] != '\0'){
		char s = c2[i4];
		concatenacion[i3+i4] = s;
		i4++;
	}
	concatenacion[i3+i4] = '\0';
	return concatenacion;
}
