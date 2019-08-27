//no sirve scanf con macros
//	posible solución: usar snprintf para pasar formato
//	solución probisional: numero mágicos
#include <stdio.h>
#include <errno.h> 
#include <string.h>
#include <stdbool.h>

#define STR_MAX 31
#define DICT_SIZE 500

typedef struct{
	char str[STR_MAX];
}string;

typedef struct{
	string palabras[DICT_SIZE];//TODO: pensar en un mejor nombre
	size_t elementos;
}dict;
void dict_init(dict* toinit){ toinit->elementos=0; }
void dict_sort( dict* diccionario);//TODO

FILE *open_file(const char *filename, const char *mode);//funciona como fopen, pero maneja los errores
int close_file(FILE *fptr);//funciona como fclose, pero maneja los errores
bool str_isnumORispunct(const char *cadena);//TODO

int main()
{
	char nombre_de_archivo[STR_MAX];
	FILE *entrada, *salida;
//	char *format;//TODO, formato de entrada
	dict diccionario;
	
//	snprintf();//inicialización del formato
	dict_init( &diccionario); //inicialización de diccionario

	printf("Nombre de archivo con extensión: ");
	scanf("%31s" , nombre_de_archivo );

	entrada= open_file(nombre_de_archivo, "r" );
	salida= open_file("Resultados.txt", "w" );
	
	//lee palabras del archivo en un arreglo de strings
	while( diccionario.elementos < DICT_SIZE  && !feof(entrada) ) /*incremento dentro del if*/
	{
		char palabra[STR_MAX];
		fscanf(entrada, "%31s", palabra);//TODO: revisar si es suficiente para incluir '\0'
	//TODO	if( !str_isnumORispunct(palabra) )//limpia entrada: TODO
		{
			strcpy(diccionario.palabras[diccionario.elementos++].str, palabra);
		}
	}

/*TEST*/for(size_t i=0; i< diccionario.elementos ; i++)
		puts(diccionario.palabras[i].str );

	puts("jala chido :)");
/*
	//ordena las palabras de forma lexicográfica, así las palabras iguales terminan juntas y facilita el conteo
	//	si el algoritmo de ordenamiento es de complejidad O(nlogn), entonces esto propociona un método eficiente de conteo
	dic_sort( &diccionario);

	//cuenta  ocurrencias;
	//escribe en archivo de resultados
	//CERRAR ARCHIVOS



*/
}

FILE *open_file(const char *filename, const char *mode)
/*		*/ 
{
	FILE *fptr;
	errno=0;

	if( (fptr=fopen( filename, mode))== NULL )
		fprintf(stderr, "el archivo %s no pudo abrirse \n\terror: %s\n",filename, strerror(errno) ); 
	return fptr;
}

int close_file(FILE *fptr)
/*		*/
{
	int s=0;
	if( fptr == NULL )//ignora este caso
		return 0;
	s=fclose(fptr);
	if( s== EOF )
		perror("error al cerrar");
	return s;
}

