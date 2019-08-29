#include <stdio.h>
#include <stdlib.h>
#include <bool.h>
#define STRING_SIZE 35

typedef char * string;

string new_string( string my_string );

void InsertionSort(string arr[], size_t size );

string new_string( size_t size)
//inicializa un string con memoria dinámica y lo regresa, si hubo un error imprime mensaje de error
{
	string my_string= (char*)malloc(sizeof(char)*size);
	if( my_string== NULL )
		fprintf(stderr, "new_string failed!\n");
	return my_string;
}

void stringArr_InsertionSort(string arr[] , size_t size)
//ordena lexicográficame un arreglo de palabras en O(n²) de forma ascendente
{
	void stringArr_insert(string arr[], size_t size, const string val, const size_t pos);

	//recorre todos los elementos hasta haber insertado todos en su lugar
	for(int i=1; i< size; i++)
		for(int j=0; j<i; j++)
			if( strcmp( arr[i] , arr[j] ) <= 0 )//es menor el elemento en desorden que el siguiente en orden ?
				stringArr_insert( arr, size,  arr[i], j-1); //inserta el elemento antes del primer elemento más grande a este

}
	
void stringArr_insert(string arr[], size_t size, const string val, const size_t pos)
//inserta val en la posición pos de arr
{
	string aux=new_string(STRING_SIZE);

	strcpy( aux, arr[pos];
	strcpy( arr[pos], val);

	//recorre los arreglos
	for(int i=pos; i<size ; i++)
	{
		strcpy(arr[i],aux );//HERE








