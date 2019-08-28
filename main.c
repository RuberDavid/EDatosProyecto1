/*	Projecto 1

*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#include <stdbool.h>

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre FILE*
FILE *open_file(const char *filename, const char *mode);//funciona como fopen, pero maneja los errores
int close_file(FILE *fptr);//funciona como fclose, pero maneja los errores

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre strings
#define STRING_SIZE 35
#define STRING_ARR_SIZE 1000

typedef char * string;

string new_string(void);
void init_stringArr( string arr[], const size_t size);
void delete_stringArr(string arr[], const size_t size);
int compare_string(const string s1, const string s2);
void limpia_entrada(string arr[] , size_t size);

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//funciónes sobre dict
#define DICT_SIZE 500

typedef struct{
	string palabras[DICT_SIZE];//TODO: pensar en un mejor nombre
	size_t elementos;
}dict;
void dict_init(dict* toinit){ toinit->elementos=0; }
void dict_sort( dict* diccionario);//TODO

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main()
{
	char nombre_de_archivo[STRING_SIZE];
	char format_string_input[20];
	FILE *entrada, *salida;
	string palabras[STRING_ARR_SIZE];
	dict diccionario;
	
	snprintf(format_string_input, sizeof(format_string_input), "%%%zus", STRING_SIZE-1 );//inicialización de fomato de scanf, así puede leer los strings por el tamaño especificado por el macr STRIG_SIZE
	printf("Nombre de archivo con extensión: ");
	scanf("%31s" , nombre_de_archivo );
	entrada= open_file(nombre_de_archivo, "r" );
	salida= open_file("Resultados.txt", "w" );
	init_stringArr(palabras, STRING_ARR_SIZE);
	dict_init( &diccionario); 

		
	//lee palabras del archivo en un arreglo de strings
	int numofstrings=0;
	while( !feof(entrada) && numofstrings< STRING_ARR_SIZE )
		fscanf(entrada, format_string_input, palabras[numofstrings++] );//incremento

	//limpia la entrada, si es una cadena ilegal de la forma definida en la función, lo guarda como //TODO
	
	//ordena las palabras de forma lexicográfica, así las palabras iguales terminan juntas y facilita el conteo
	qsort( palabras, STRING_ARR_SIZE, sizeof(palabras[0]), compare_string );

	//cuenta occurrencia de palabras y guarda en una estructura diccionario
	cuenta_string(palabras, STRING_ARR_SIZE); //TODO

	//ordena el diccionario
	
	//imprime el diccionario en el archivo de salida

	//cierra aerchivos, destruye variables pertinentes



}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre FILE*
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
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre strings

string new_string(void )
//inicializa un string con memoria dinámica y lo regresa, si hubo un error imprime mensaje de error
{
	string my_string= (char*)malloc(sizeof(char)*STRING_SIZE);
	if( my_string== NULL )
		fprintf(stderr, "new_string failed!\n");
	return my_string;
}

void init_stringArr( string arr[],const size_t size)
//inicializa un arreglo de strings
{
	for(size_t i=0; i<size; i++)
		arr[i]=new_string();
}

void delete_stringArr(string arr[], const size_t size)
//borra elementos del arreglo
{
	for(size_t i=0; i<size; i++)
		free(arr[i]);
}

int compare_string(const string s1, const string s2);
//compara lexicográficamente strings, se ṕasa un puntero a esta función a qsort()
{
	if( strcmp( s1, s2)>0 )
		return 1;
	if( strcmp( s1, s2)<0 )
		return -1;
	return 0;
}

void limpia_entrada(string arr[] , size_t size)//TODO
{
	for(size_t i=0; i< size ; i++ )
	{
		i

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

