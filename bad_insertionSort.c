
void stringArr_InsertionSort(string arr[] , size_t size)
//ordena lexicográficame un arreglo de palabras en O(n²) de forma ascendente
{
	void stringArr_insert(string arr[], size_t size, const string val, const size_t pos);

	//recorre todos los elementos hasta haber insertado todos en su lugar
	for(size_t i=1; i< size; i++)
		for(size_t j=0; j<i; j++)
			if( strcmp( arr[i] , arr[j] ) <= 0 )//es menor el elemento en desorden que el siguiente en orden ?
				stringArr_insert( arr, size  arr[i], j); //inserta el elemento en la posición  del primer elemento más grande a este

}
	
void stringArr_insert(string arr[], size_t size, const string val, const size_t pos)
//en el arreglo arr de tamaño size, inserta el elemento val en la posición pos
{
	if( pos <size )
	{
		string aux=new_string();
		//swap
		strcpy( aux, arr[pos]);//guarda el que estaba en la posición a insertar
		strcpy( arr[pos], val);//gaurda el valor a insertar 

		stringArr_insert(arr, size, aux, pos+1);
	}

}
