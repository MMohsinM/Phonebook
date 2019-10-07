#define SepChain    /* Define the appropriate hash algorithm */
// dont add duplicates  
// data formating	
// add comments

#ifdef SepChain
    #include "hashsep.h"
#endif

#ifdef QuadProb
    #include "hashquad.h"
#endif


#include <stdio.h>
#include <stdlib.h>

#define constant 25

struct ListNode
{
	unsigned long int m;
	unsigned long int h;
	char f_n[constant];
	char l_n[constant];
	char c_n[constant];
	Position Next;
};


main( )
{
    HashTable H;
    Position P=NULL;
	int i = 0;
    int j = 0;
    int CurrentSize;
	int options = 0;
	char c_opt[5];
	/*char f_n[constant];
	char s_n[constant];
	char w_n[constant];
	unsigned int m;
	unsigned int h;*/
	struct ListNode f;
	char *path = "C:\\zmyFIles\\UET_SEMESTERS\\semester4\\data_structures_and_algorithms\\Project\\contacts.csv";
	H = InitializeTable(CurrentSize = 12);
	Load(path, H);
	while (options != 6)
	{
		puts("1. Retrieve\n2. Insertions\n3. Deletion\n4. Edit\n5. Print\n6. Exit");
		printf("Your Choice: ");
		scanf_s("%d", &options);
		getchar();
		if (options == 1)
		{
			puts("Enter name of person");
			scanf_s("%s", f.f_n,constant);
			getchar();
			Retrieve(f.f_n, H, 'r');
			getchar();
		}
		else if (options == 2)
		{
			puts("Enter first name of person");
			scanf_s("%s", f.f_n, constant);
			getchar();
			puts("Enter second name of person");
			scanf_s("%s", f.l_n, constant);
			getchar();
			puts("Enter work place");
			scanf_s("%s", f.c_n, constant);
			getchar();
			puts("Enter mobile number");
			scanf_s("%u", &f.m);
			getchar();
			puts("Enter home number");
			scanf_s("%u", &f.h);
			getchar();
			Insert(&f, H);
			getchar();
		}
		else if (options == 3)
		{
			puts("Enter first name of person");
			scanf_s("%s", f.f_n, constant);
			getchar();
			Delete(f.f_n, H);
			getchar();
		}
		else if (options == 4)
		{
			puts("Enter first name of person");
			scanf_s("%s", f.f_n, constant);
			getchar();
			update(f.f_n, H);
			getchar();
		}
		else if (options == 5)
		{
			Sort(H);
			getchar();
		}
		else if (options == 6)
		{
			break;
		}
		else
		{
			puts("Invalid Choice\nPress any Key to continue");
			getchar();
		}
		system("cls");
		PrintTable(H);
		if (TableElements(H) > 2 * TableSize(H))
			H = Rehash(H);
		
	}
	printf( "End of program.\n" );
	getchar();
    return 0;
}

	