#include<balancedbst.h>

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
	balancedbst* balancedbst_p = get_balancedbst(NON_SELF_BALANCING, key_cmp);
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){10}), &((ts){500, "five"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){6}), &((ts){300, "three"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){14}), &((ts){700, "seven"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){4}), &((ts){200, "two"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){8}), &((ts){400, "four"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){12}), &((ts){600, "six"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){16}), &((ts){800, "eight"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){0}), &((ts){0, "zero"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){18}), &((ts){900, "nine"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){5}), &((ts){250, "two and half"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){7}), &((ts){350, "three and half"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){11}), &((ts){550, "five and half"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	put_entry(balancedbst_p, &((ke){13}), &((ts){650, "six and half"}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	remove_value(balancedbst_p, &((ke){14}));
	print_balancedbst(balancedbst_p, print_key, print_ts);

	delete_balancedbst(balancedbst_p);
	return 0;
}