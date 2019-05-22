#include<array.h>

array* get_array(unsigned long long int min_size, unsigned long long int size_of_data_element)
{
	array* array_p = (array*) calloc(1, sizeof(array));
	array_p->max_size = min_size;
	array_p->size = 0;
	array_p->size_of_data_element = size_of_data_element;
	array_p->increment_offset = 1;
	array_p->increment_factor = 2;
	array_p->data_p_p = array_p->max_size > 0 ? ((void**)calloc(array_p->max_size, sizeof(void*))): NULL;
	return array_p;
}

void delete_array(array* array_p)
{
	for(unsigned long long int i = 0; i < array_p->size; i++)
	{
		if(array_p->data_p_p[i] != NULL)
		{
			free(array_p->data_p_p[i]);
		}
	}
	if(array_p->max_size > 0 && array_p->data_p_p != NULL)
	{
		free(array_p->data_p_p);
	}
	if(array_p != NULL)
	{
		free(array_p);
	}
}

void* get_element(array* array_p, unsigned long long int index)
{
	if(array_p->max_size > index)
	{
		return ((void*)(((char**)array_p->data_p_p)[index]));
	}
	else
	{
		return NULL;
	}
}

void append_element(array* array_p, const void* data_p)
{
	if(array_p->max_size < array_p->size && array_p->data_p_p != NULL)
	{
		// you fuck made an error
		return ;	
	}
	else if(array_p->max_size == array_p->size)
	{
		// compute new_size
		unsigned long long int new_max_size = ( array_p->max_size * array_p->increment_factor ) + array_p->increment_offset;

		// taking precaution
		new_max_size = new_max_size == array_p->size ? new_max_size + 1 : new_max_size;

		// request memory for the new computed size
		void** new_data_p_p = ((void**)calloc(new_max_size, sizeof(void*)));

		// copy all pointers from the old pointers array
		memcpy(new_data_p_p, array_p->data_p_p, array_p->size * sizeof(void**));

		// free the old pointers array
		free(array_p->data_p_p);

		// new assignment to data_p_p and the max_size
		array_p->data_p_p = new_data_p_p;
		array_p->max_size = new_max_size;
	}

	// this is the pointer that will hold the new element data memory allocated by this array
	void* new_data_p = NULL;

	if(data_p != NULL)
	{
		// assign by allocating memory using malloc
		new_data_p = malloc(array_p->size_of_data_element);

		// copy data from user's pointer to array's element memory that we requested above
		memcpy(new_data_p, data_p, array_p->size_of_data_element);
	}

	// assign a new data there and then increment the current size of the array
	array_p->data_p_p[array_p->size++] = new_data_p;
}

void print_array(array* array_p, void (*print_element)(void*))
{
	printf("\narray:");
	printf("\n\tsize : %lld", array_p->size);
	printf("\n\tmax_size : %lld", array_p->max_size);
	printf("\n\tsize_of_data_element : %lld", array_p->size_of_data_element);
	for(unsigned long long int i = 0; i < array_p->size; i++)
	{
		printf("\n\telement_index %lld -> ", i);
		void* element = get_element(array_p, i);
		if(element != NULL)
		{
			print_element(get_element(array_p, i));
		}
		else
		{
			printf("NULL");
		}
	}
	printf("\n\tincrement_factor : %lld", array_p->increment_factor);
	printf("\n\tincrement_offset : %lld\n\n", array_p->increment_offset);
}

void sort_array(array* array_p, int (*comparator_function)(void*, void*)){}