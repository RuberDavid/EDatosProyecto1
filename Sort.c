#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STRING_SIZE 35
#define STRING_ARR_SIZE 10

typedef char * string;

string new_string(void);
void init_stringArr( string arr[], const size_t size);
void delete_stringArr(string arr[], const size_t size);
void insertionSort_stringArr(string arr[],const int size);

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
int compare_string(const void *s1, const void *s2)
//compara lexicográficamente strings, se ṕasa un puntero a esta función a qsort()
{
	int res= strcmp( (char*)s1, (char*)s2);
	return (res > 0) ? 1 : (res <0 ) ? 1 : 0;
}


int main()
{
	string arr[STRING_ARR_SIZE];
	init_stringArr( arr, STRING_ARR_SIZE);

	char format[20];
// ^[,;.:-_?¿¡!]%
	snprintf(format, sizeof(format), "%%%zus" , STRING_SIZE -1);

	for(int i=0; i<STRING_ARR_SIZE ; i++)
	{
		scanf(format, arr[i]);
	}

	puts("jala");
	qsort( arr,  STRING_ARR_SIZE, sizeof(arr[0]) , compare_string );//TODO

	puts( arr[0] );

	puts("jalax2");

	for(int i=0; i<STRING_ARR_SIZE; i++)
	{
		printf("%*s\n", STRING_SIZE-1, arr[i]);
	}
}

	

