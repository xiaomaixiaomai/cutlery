#include<linkedlist.h>

typedef struct teststruct ts;
struct teststruct
{
	int a;
	char* s;
};

void print_ts(const void* tsv)
{
	if(tsv == NULL)
	{
		printf(" NULL");
		return;
	}
	printf(" %d, %s", ((ts*)tsv)->a, ((ts*)tsv)->s);
}

int test_compare(const void* a, const void* b, const void* additional_params)
{
	if(a==NULL || b==NULL)
	{
		return -1;
	}
	else
	{
		return ((ts*)a)->a - ((ts*)b)->a;
	}
}

int main()
{
	linkedlist* ll = get_linkedlist();
	print_linkedlist(ll, print_ts);

	insert_head(ll, &((ts){2, "two"}));
	print_linkedlist(ll, print_ts);

	insert_head(ll, &((ts){1, "one"}));
	print_linkedlist(ll, print_ts);

	insert_tail(ll, &((ts){5, "five"}));
	print_linkedlist(ll, print_ts);

	insert_tail(ll, &((ts){6, "six"}));
	print_linkedlist(ll, print_ts);

	insert_node_after(ll, ((node*)get_nth_node_from_head(ll, 1)), &((ts){3, "three"}));
	print_linkedlist(ll, print_ts);

	insert_node_before(ll, ((node*)get_nth_node_from_tail(ll, 1)), &((ts){4, "four"}));
	print_linkedlist(ll, print_ts);

	insert_node_before(ll, ((node*)get_nth_node_from_tail(ll, 2)), &((ts){-1, "minus one"}));
	print_linkedlist(ll, print_ts);

	remove_head(ll);
	print_linkedlist(ll, print_ts);

	remove_tail(ll);
	print_linkedlist(ll, print_ts);

	ts to_find = {-1, "lol"};
	const node* found = find_first_in_list(ll, ((void*)&to_find), test_compare, NULL);
	print_ts(found == NULL ? NULL : ((void*)found->data_p));
	printf("\n");

	remove_node(ll, ((node*)get_nth_node_from_head(ll, 2)));
	print_linkedlist(ll, print_ts);

	delete_linkedlist(ll);
	return 0;
}