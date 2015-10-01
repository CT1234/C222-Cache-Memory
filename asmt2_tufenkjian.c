// ============================================================================
// Name: ASHOD CHRIS TUFENKJIAN
// Project#2: CACHE MEMORY
// Due: October 7th, 2014
// COMP 222
// ============================================================================
#include <stdio.h>
#include <stdlib.h>

int  mem_size = NULL;
int  cache_size = NULL;
int  block_size = NULL;
int  number_of_blocks;
int  number_of_tags;
int* validated_tags = NULL;
int* initial_memory = NULL;

 struct cache
{
 int tag;
 int* block;
};

struct cache* cache_struct_array = NULL;

void allocate_memory(int number_of_tags, int number_of_blocks)
{
    cache_struct_array = (struct cache*) malloc (number_of_tags * sizeof(struct cache));
    int i;
    for (i=0; i < number_of_tags; i++ )
    {
        cache_struct_array[i].block = (int*) malloc (number_of_blocks*sizeof(int));
    }

    initial_memory = (int*) malloc (mem_size * sizeof(int));
    int l;
    l = 0;
    for (i=0; i < mem_size; i++ )
    {
        initial_memory[i] = mem_size - l++;
    }
    return;
}

void OPTION_1()
{
    printf("Entered selection 1: \n");
	printf("Enter main memory size (words): ");
	scanf("%d", &mem_size);

    printf("Enter cache size (words): ");
	scanf("%d", &cache_size);

    printf("Enter block size (words/block): ");
	scanf("%d", &block_size);

	number_of_tags = mem_size/cache_size;

	validated_tags = (int*) malloc (number_of_tags*sizeof(int));

	int i;
	for (i = 0; i < number_of_tags; i++)
	{
	    validated_tags[i] = 0;
	}

	number_of_blocks = cache_size / block_size;
    allocate_memory(number_of_tags, number_of_blocks);
	return;
}

void print_parameters(int tag, int block, int word, int value)
{
	printf("-------------------------------------------\n");
	printf("|Tag%5d | Block:%5d | Word%5d (%3d) |\n",
            tag,block,word,value);
	printf("-------------------------------------------\n");
	return;
}

void read()
{
    int memory_address;
    printf("Enter main memory address to read: ");
	scanf("%d", &memory_address);

	int tag;
	tag = memory_address / cache_size;

	int block;
	block = (memory_address % cache_size) / block_size;

	int word;
	word = (memory_address % block_size );

    if (validated_tags[tag] == 0)
    printf("READ MISS!\n");
    else printf("READ HIT!\n");

    print_parameters( tag, block, word, initial_memory[memory_address] );

    return;
}

void write()
{
    int memory_address;
    printf("Enter main memory address to write to: ");
	scanf("%d", &memory_address);

    int value_to_write;
    printf("Enter value to write: ");
    scanf("%d", &value_to_write);

    initial_memory[memory_address] = value_to_write;

	int tag;
	tag = memory_address / cache_size;

	int block;
	block = (memory_address % cache_size) / block_size;

	int word;
	word = (memory_address % block_size );

    if (validated_tags[tag] == 0)
    {
        validated_tags[tag] = 1;
        printf("WRITE MISS!\n");
    }
    else printf("WRITE HIT!\n");

    cache_struct_array[tag].block[word] = value_to_write;

    print_parameters(tag, block, word,value_to_write );

    return;
}

void OPTION_2()
{
    printf("Entered selection 2: \n");

    printf("Select read (0) or write (1): ");
    int selected;
	scanf("%d", &selected);

	if (selected == 0)
        read();
    else if (selected == 1)
        write();
    return;
}

void de_allocate()
{
    free(validated_tags);
    if (cache_struct_array != NULL)
        free(cache_struct_array);
    return;
}

int main ()
{
    int x = 1;
    while (x == 1)
    {
        int selection;

        printf("\nCache memory allocation and mapping: \n");
        printf("--------------------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Access cache for reading/writing and transfer data\n");
        printf("3) Quit\n\n");
        printf("Enter Selection: \n");
        scanf("%d", &selection);

            if      (selection == 1)
            OPTION_1();
            else if (selection == 2)
            OPTION_2();
            else if (selection == 3)
            {
                de_allocate();
                x = 2;
            }
    }
    return 0;
}
