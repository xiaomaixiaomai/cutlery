#include<hashmap.h>

typedef struct teststruct ts;
struct teststruct
{
	int a;
	char* s;
};

typedef struct key ke;
struct key
{
	int k;
};

unsigned long long int hash_function(const void* key)
{
	return (*((unsigned long long int *)key))-1;
}

int key_cmp(const void* key1, const void* key2)
{
	return (((ke*)key1)->k) - (((ke*)key2)->k);
}

void print_ts(const void* tsv)
{
	printf(" %d, %s", ((ts*)tsv)->a, ((ts*)tsv)->s);
}

void print_key(const void* key)
{
	printf("%d", (*((int*)key)));
}

int main()
{
	hashmap* hashmap_p = get_hashmap(4, hash_function, key_cmp,
		/*NO_POLICY*/ ELEMENTS_AS_LINKEDLIST /*ELEMENTS_AS_RED_BLACK_BST*/ /*ELEMENTS_AS_AVL_BST*/);

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){1}), &((ts){100, "one"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){2}), &((ts){200, "two"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){3}), &((ts){300, "there"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	update_value_in_hash(hashmap_p, &((ke){3}), &((ts){300, "three"}), NULL);

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){4}), &((ts){400, "four"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){5}), &((ts){500, "five"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){6}), &((ts){600, "six"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){7}), &((ts){700, "seven"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){8}), &((ts){800, "eight"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){9}), &((ts){900, "nine"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	printf("\nStarting to remove few entries\n\n");

	int nodes_deleted = 0;

	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){6}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){2}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){6}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){4}), NULL, NULL);

	printf("\nnodes deleted : %d\n\n", nodes_deleted);nodes_deleted = 0;

	print_hashmap(hashmap_p, print_key, print_ts);

	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){6}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){7}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){5}), NULL, NULL);
	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){8}), NULL, NULL);

	printf("\nnodes deleted : %d\n\n", nodes_deleted);nodes_deleted = 0;

	print_hashmap(hashmap_p, print_key, print_ts);nodes_deleted = 0;

	nodes_deleted += delete_entry_from_hash(hashmap_p, &((ke){9}), NULL, NULL);

	printf("\nnodes deleted : %d\n\n", nodes_deleted);nodes_deleted = 0;

	print_hashmap(hashmap_p, print_key, print_ts);nodes_deleted = 0;

	printf("\nCompleted removing entries\n\n");

	insert_entry_in_hash(hashmap_p, &((ke){60}), &((ts){6000, "sixty"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){70}), &((ts){7000, "seventy"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	update_value_in_hash(hashmap_p, &((ke){70}), &((ts){70000, "seven hundred"}), NULL);

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){80}), &((ts){8000, "eighty"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){20}), &((ts){2000, "twenty"}));

	print_hashmap(hashmap_p, print_key, print_ts);

	insert_entry_in_hash(hashmap_p, &((ke){40}), &((ts){4000, "forty"}));

	printf("\n\nBefore rehashing - 16\n");
	print_hashmap(hashmap_p, print_key, print_ts);

	rehash_to_size(hashmap_p, 16);

	printf("\n\nAfter rehashing - 16\n");
	print_hashmap(hashmap_p, print_key, print_ts);

	printf("\n\nBefore rehashing - 20\n");
	print_hashmap(hashmap_p, print_key, print_ts);

	rehash_to_size(hashmap_p, 20);

	printf("\n\nAfter rehashing - 20\n");
	print_hashmap(hashmap_p, print_key, print_ts);

	delete_hashmap(hashmap_p);

	return 0;
}