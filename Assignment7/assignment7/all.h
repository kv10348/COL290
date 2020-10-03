#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

#define WASTE_WORD_COUNT  61
struct value
{
	char word[20];
};


struct datafile
{
	struct value data[5000];	
};

struct value_freq
{
	int fre;
};
struct datafile_freq
{
	struct value_freq data_[5000];	
};