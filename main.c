/*	Projecto 1

*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STRING_SIZE 35
#define STRING_ARR_SIZE 200
#define DICT_SIZE 500

typedef char * string;
typedef struct{
	string elem;
	int card;//cardinalidad
}string_dict_entry;//tipo de dato de las entradas del diccionario, este será un arreglo de dicho tipo


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre FILE*
FILE *open_file(const char *filename, const char *mode);//funciona como fopen, pero maneja los errores
int close_file(FILE *fptr);//funciona como fclose, pero maneja los errores

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes sobre strings

string new_string(void);
void init_stringArr( string arr[], const size_t size);
void delete_stringArr(string arr[], const size_t size);
int compare_string(const void* s1, const void* s2);
//void limpia_entrada(string arr[] , size_t size);//TODO

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//funciónes sobre dict

void init_dict(string_dict_entry* toinit, size_t size );
void init_dict(string_dict_entry toinit[], size_t size );
int compare_card_dict( const void* elem1, const void* elem2 );
size_t cuenta_strings( const string arr[], size_t size_of_tocount, string_dict_entry res[] , size_t size_of_res );
bool assign_dict( string_dict_entry *x, string y );

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main()
{
	char nombre_de_archivo[STRING_SIZE];
	char format_string_input[20];
	FILE *entrada, *salida;
	string palabras[STRING_ARR_SIZE];
	string_dict_entry diccionario[DICT_SIZE];
	size_t contador;//TODO si es de puntuación, resta
	
	//Inicialización
	snprintf(format_string_input, sizeof(format_string_input), "%%%zus", STRING_SIZE-1 );//inicialización de fomato de scanf, así puede leer los strings por el tamaño especificado por el macr STRIG_SIZE
	printf("Nombre de archivo con extensión: ");
	scanf("%31s" , nombre_de_archivo );
	entrada= open_file(nombre_de_archivo, "r" );
	salida= open_file("Resultados.txt", "w" );
	init_stringArr(palabras, STRING_ARR_SIZE);
	init_dict( diccionario, DICT_SIZE );

		
	//lee palabras del archivo en un arreglo de strings
	int numofstrings=0;
	while( !feof(entrada) && numofstrings< STRING_ARR_SIZE )
		fscanf(entrada, format_string_input, palabras[numofstrings++] );//incremento

	//limpia la entrada, si es una cadena ilegal de la forma definida en la función, lo guarda como //TODO
	
	//ordena las palabras de forma lexicográfica, así las palabras iguales terminan juntas y facilita el conteo
	qsort( palabras, STRING_ARR_SIZE, sizeof(palabras[0]), compare_string );

	for(int i; i< numofstrings ; i++)
		printf("%20s\t%ld\n",palabras[i], strlen(palabras[i]) );
			
	//cuenta occurrencia de palabras y guarda en una estructura diccionario
	contador=cuenta_strings( palabras, STRING_ARR_SIZE, diccionario , DICT_SIZE );

	//ordena el diccionario
	qsort(diccionario, contador , sizeof(diccionario[0]) , compare_card_dict );
	
	//imprime el diccionario en el archivo de salida
	
	fprintf( salida, "%-*s\t Instancias\n",STRING_SIZE, "Palabras");
	for(size_t i=0; i < contador ; i++)
	{
		fprintf(salida, "%-*s\t %d\n", STRING_SIZE , diccionario[i].elem, diccionario[i].card );
	}

	//cierra aerchivos, destruye variables pertinentes
	
	close_file(entrada);
	close_file(salida);

	//libera palabras
	for(size_t i=0; i < STRING_ARR_SIZE ; i++ )
		free(palabras[i]);

	//libera diccionario
	for(size_t i=0; i< DICT_SIZE ; i++)
		free(diccionario[i].elem );

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
int compare_string(const void *s1, const void *s2)
//compara lexicográficamente strings, se ṕasa un puntero a esta función a qsort()
{
	int res= strcmp( (string)s1, (string)s2);
	printf("%30s %d %30s ", 
	return (res > 0) ? 1 : (res <0 ) ? -1 : 0;
}
/*
void limpia_entrada(string arr , size_t size)//TODO
//toma una cadena , si contiene signos de puntuación , los borra, mayusculas y minusculas son lo mismo
{
	string buffer=new_string();

	
	for(size_t i=0; i< size ; i++ )
	{
		
	}
}
*/
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Funciónes de dict

void init_dict( string_dict_entry toinit[], size_t size )
//inicializa un arreglo diccionario, los elementos tienen 0 de cardinalidad
{
	for(size_t i=0; i<size ; i++ )
	{
		toinit[i].elem=new_string();
		toinit[i].card=0;
	}
}

int compare_card_dict( const void* elem1, const void* elem2 )
//función de comparación de orden lexicográfico, se pasa a qsort()
{
	string_dict_entry *val1= (string_dict_entry*)elem1;
	string_dict_entry *val2= (string_dict_entry*)elem2;

	return (val1->card > val2-> card) ? 1 : (val1->card < val2-> card) ? -1 : 0 ;
}

size_t cuenta_strings( const string arr[], size_t size_of_tocount, string_dict_entry res[] , size_t size_of_res ) 
// de un arreglo ordenado de string, cuénta las occurrencias de sus elementos y guarda el elemento y su ocurrencia en un arreglo diccionario
{
	string current=new_string();
	size_t next=0,
	       dict_index=0;

	//guarda la primera cadena
	strcpy( current, arr[next] );

	//copia en diccionario
	assign_dict( &res[dict_index], current );

	while(  next< size_of_tocount && dict_index < size_of_res  )
	{
		next++;//pasa al siguiente
		//cuenta repeticiónes
		while( strcmp( current, arr[next] )==0 )
		{
			puts("jala");
			res[dict_index].card+=1;
			next++;
		}

		assign_dict( &res[dict_index], current );
		//strcpy( res[dict_index].elem, current ); 
		strcpy( current, arr[next] );
		dict_index++ ;
	}
	return dict_index+1;
}

bool assign_dict( string_dict_entry *x, string y )
{
	strcpy(x->elem, y);
	(x->card)++;
	if( x->card )
		return true;
	return false;
}
