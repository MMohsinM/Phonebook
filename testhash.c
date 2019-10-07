#define SepChain    
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
#include <string.h>
#include <time.h>


#define constant 25

 struct ListNode
        {
            unsigned long int mobile;
			unsigned long int home;
			char first_name[constant];
			char last_name[constant];
			char company_name[constant];
            Position    Next;
        };


int main( )
{
	clock_t start, end;
    HashTable H;
    Position P=NULL;
	int i = 0;
    int j = 0;
    int CurrentSize;
	int options = 0;
	char c_opt[5];
	char num[constant];
	double runtime;
	struct ListNode f;
	char *path = "C:\\zmyFIles\\UET_SEMESTERS\\semester4\\data_structures_and_algorithms\\Project\\contacts.csv";
	H = InitializeTable(CurrentSize = 70);
	start = clock();
	Load(path, H);
	end = clock();
	runtime = (end - start) / (double)CLOCKS_PER_SEC;
	printf("runTime = %.20f\n", runtime);
	while (options != 6)
	{
		puts("1. Retrieve\n2. Insertions\n3. Deletion\n4. Edit\n5. Print\n6. Exit");
		printf("Your Choice: ");
		scanf_s("%s", c_opt,5);
		options = atoi(c_opt);
		getchar();
		if (options == 1)//Retrieve options
		{
			puts("Enter name of person");
			scanf_s("%s", f.first_name,constant);
			getchar();
			start = clock();
			Retrieve(f.first_name, H, 'r');
			end = clock();
			runtime = (end - start) / (double)CLOCKS_PER_SEC;
			printf("runTime = %.20f\n", runtime);
			getchar();
		}
		else if (options == 2) // Insert Options
		{
			do
			{
				puts("Enter first name of person"); 
				scanf_s("%s", f.first_name, constant); 
				getchar();
				//_strlwr_s(f.first_name = strdup(f.first_name), strlen(f.first_name)
				puts("Enter second name of person");
				scanf_s("%s", f.last_name , constant);
				getchar();
				P=Find(f.first_name, f.last_name, H); // finds duplicates
				if (P != NULL)
					puts("Contact already present");
			} while (P != NULL);
			puts("Enter work place");
			scanf_s("%s", f.company_name, constant);
			getchar();
			do
			{
				puts("Enter mobile number");
				scanf_s("%s", num,constant); // mobile number does not accepts characters
				getchar();
				if (j = hasAlphabets(num)) {
					puts("Invalid Number");
				}
				else
					break;
			} while (j);
			f.mobile = atoi(num);
			do
			{
				puts("Enter home number");
				scanf_s("%s", num,constant);  // phone number does not accepts characters
				getchar();
				if (j = hasAlphabets(num)) {
					puts("Invalid Number");
				}
				else
					break;
			} while (j = 1);
			f.home = atoi(num);
			start = clock();
			Insert(&f, H);
			end = clock();
			runtime = (end - start) / (double)CLOCKS_PER_SEC;
			printf("runTime = %.20f\n", runtime);


			getchar();
		}
		else if (options == 3)
		{
			puts("Enter first name of person");
			scanf_s("%s", f.first_name, constant); // DELETE
			getchar();
			Delete(f.first_name, H);
			getchar();
		}
		else if (options == 4)
		{
			puts("Enter first name of person");
			scanf_s("%s", f.first_name, constant);  // edit
			getchar();
			update(f.first_name, H);
			getchar();
		}
		else if (options == 5)
		{
			start = clock();
			Sort(H);
			end = clock();
			runtime = (end - start) / (double)CLOCKS_PER_SEC;
			printf("runTime = %.20f\n", runtime);
			getchar();  // Prints sorted list
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
		if (TableElements(H) > 2 * TableSize(H)) // Adjusts Load factor
			H = Rehash(H);
	}
	path = "C:\\zmyFIles\\UET_SEMESTERS\\semester4\\data_structures_and_algorithms\\Project\\contacts1.csv";
	write(path, H);
	printf( "End of program.\n" );
	getchar();
    return 0;
}

	