#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#include <stdbool.h>

//funciónes sobre dict
#define DICT_SIZE 500

typedef char * string;
typedef struct{
	string elem;
	int card;//cardinalidad
}string_dict_entry;//tipo de dato de las entradas del diccionario, este será un arreglo de dicho tipo

void init_dict(string_dict_entry toinit[], size_t size );
int compare_card_dict( const void* elem1, const void* elem2 );
void cuenta_strings( const string arr[], size_t size_of_tocount, string_dict_entry res[] , size_t size_of_res ); //TODO: to cpcy


//Funciónes sobre strings
#define STRING_SIZE 35
#define STRING_ARR_SIZE 1000


string new_string(void);
void init_stringArr( string arr[], const size_t size);
void delete_stringArr(string arr[], const size_t size);
int compare_string(const void* s1, const void* s2);
void limpia_entrada(string arr[] , size_t size);

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main()
{
	string_dict_entry diccionario[DICT_SIZE];
	init_dict(diccionario, DICT_SIZE );
	
	diccionario[0].elem="holi";
	diccionario[0].card++;

	printf("%35s , %d", diccionario[0].elem, diccionario[0].card);


}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
void init_dict(string_dict_entry toinit[], size_t size )
//inicializa un arreglo diccionario, los elementos tienen 0 de cardinalidad
{
	for(size_t i=0; i<size ; i++ )
	{
		toinit[i].elem=new_string();
		toinit[i].card=0;
	}
}

int compare_card_dict( const void* elem1, const void* elem2 )
{
	string_dict_entry *val1= (string_dict_entry*)elem1;
	string_dict_entry *val2= (string_dict_entry*)elem2;

	return (val1->card > val2-> card) ? 1 : (val1->card < val2-> card) ? -1 : 0 ;
}

void cuenta_strings( const string arr[], size_t size_of_tocount, string_dict_entry res[] , size_t size_of_res ) 
// de un arreglo ordenado de string, cuénta las occurrencias de sus elementos y guarda el elemento y su ocurrencia en un arreglo diccionario
{
	string current=new_string();
	size_t next=0,
	       dict_index=0;

	//guarda la primera cadena
	strcpy( current, arr[next] );

	//copia en diccionario
	strcpy( res[dict_index].elem, current ); 
	res[dict_index].card++;


	for( ; next< size_of_tocount && dict_index < size_of_res ; )
	{
		next++;//pasa al siguiente
		//copia en diccionario
		while( strcmp( current, arr[next] )==0 )
		{
			res[dict_index].card++;
			next++;
		}

		strcpy( res[dict_index].elem, current ); 
		strcpy( current, arr[next] );
		dict_index++ ;
	}
}

		



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
int compare_string(const void *s1, const void *s2)
//compara lexicográficamente strings, se ṕasa un puntero a esta función a qsort()
{
	int res= strcmp( (string)s1, (string)s2);
	return (res > 0) ? 1 : (res <0 ) ? 1 : 0;
}

