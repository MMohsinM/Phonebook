       #include "fatal.h"
       #include "hashsep.h"
       #include <stdlib.h>
	   #include <string.h>
	   #include <time.h>
       
       #define MinTableSize (10)
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
		

        typedef Position List;

        /* List *TheLists will be an array of lists, allocated later */
        /* The lists use headers (for simplicity), */
        /* though this wastes space */
        struct HashTbl
        {
            int TableSize;
            List *TheLists;
			int Elements_no; // keeps contacts number
        };

        /* Return next prime; assume N >= 10 */
        static int
        NextPrime( int N )
        {
            int i;

            if( N % 2 == 0 )
                N++;
            for( ; ; N += 2 )
            {
                for( i = 3; i * i <= N; i += 2 )
                    if( N % i == 0 )
                        goto ContOuter;  /* Sorry about this! */
                return N;
              ContOuter: ;
            }
        }

        /* Hash function for ints */
		Index
		Hash(const char *Key, int TableSize)
		{
			unsigned int HashVal = 0;
			while (*Key != '\0')  // sum of ascii values of chars mod tablesize
				HashVal += *Key++;
			return HashVal % TableSize;
		}


/* START: fig5_8.txt */
        HashTable
        InitializeTable( int TableSize )
        {
            HashTable H;
            int i;

/* 1*/      if( TableSize < MinTableSize )
            {
/* 2*/          Error( "Table size too small" );
/* 3*/          return NULL;
            }

            /* Allocate table */
/* 4*/      H = malloc( sizeof( struct HashTbl ) );
/* 5*/      if( H == NULL )
/* 6*/          FatalError( "Out of space!!!" );

/* 7*/      H->TableSize = NextPrime( TableSize );

            /* Allocate array of lists */
/* 8*/      H->TheLists = malloc( sizeof( List ) * H->TableSize );
/* 9*/      if( H->TheLists == NULL )
/*10*/          FatalError( "Out of space!!!" );

            /* Allocate list headers */
/*11*/      for( i = 0; i < H->TableSize; i++ )
            {
/*12*/          H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
/*13*/          if( H->TheLists[ i ] == NULL )
/*14*/              FatalError( "Out of space!!!" );
                else
/*15*/              H->TheLists[ i ]->Next = NULL;
            }
			H->Elements_no = 0;
/*16*/      return H;
        }
/* END */

		//  FUNCTION FIND
		//  DESCRIPTION 
		//		Returns pointer to contact based on first name and 
		//		second name
			   
		Position Find(ElementType* fn, ElementType* sn, HashTable H)
		{
			Position P;
			List L;
			int check = 0;
			L = H->TheLists[Hash(fn, H->TableSize)];
			P = L->Next;
			while (P != NULL)
			{
				if (strcmp(P->first_name, fn) == 0)
					if (strcmp(P->last_name, sn) == 0)
						return P;
				P = P->Next;
			}
			return P;
		}

/* START: fig5_9.txt */
        Position
        Retrieve( ElementType* key, HashTable H ,char mode)///Retrieve Function
        {
            Position P;
            List L;
			int check = 0;//counts matched queries
/* 1*/      L = H->TheLists[ Hash( key, H->TableSize ) ];
/* 2*/      P = L->Next;
			char found = 'j';
/* 3*/      while( P != NULL)
		{
				if (strcmp(P->first_name, key) == 0) {
					if (!check)
					{
					//	printf("First Name\tLast Name\tMobile\t\tHome\t\tCompany\n");
					}
					printf("%s\t%s\t",P->first_name ,P->last_name);
					printf("0%u\t0%u\t%s\n", P->mobile, P->home, P->company_name);
					check++;
					if (mode != 'r')
					{
						printf("Is this your required contact (y to stop): ");
						scanf_s("%c", &found,1);
						getchar();
						if (found == 'y' || found == 'Y')
							break;
					}
				}
				P = P->Next;
			}

		if (!check)
			puts("No matched contacts");
/* Probably need strcmp!! */
/* 5*/		return P;
        }


        void
        Insert( Position Input, HashTable H ) /// Inserts contacts into the hashtable
        {
			Position NewCell = NULL;
			Position Pos = NULL;
            List L;

			//_strlwr_s(Input->first_name = strdup(Input->first_name), strlen(Input->first_name));
/* 1*/      Pos = Find( Input->first_name,Input->last_name, H );
			
/* 2*/      if( Pos == NULL )   /* Key is not found */
            //{
/* 3*/          NewCell = malloc( sizeof( struct ListNode ) );
/* 4*/          if( NewCell == NULL )
/* 5*/              FatalError( "Out of space!!!" );
                else
                {
/* 6*/              L = H->TheLists[ Hash(Input->first_name, H->TableSize ) ];
/* 7*/              NewCell->Next = L->Next;
/* 8*/              strcpy_s(NewCell->first_name, constant, Input->first_name);  
					strcpy_s(NewCell->last_name, constant, Input->last_name);
					strcpy_s(NewCell->company_name, constant, Input->company_name);
					NewCell->mobile = Input->mobile;
					NewCell->home = Input->home;
/* 9*/              L->Next = NewCell;
                }
          //  }
				H->Elements_no +=1;
        }
/* END */

        /*ElementType
        Retrieve( Position P )
        {
            return P->Element;
        }
		*/


        void
        DestroyTable( HashTable H )
        {
            int i;

            for( i = 0; i < H->TableSize; i++ )
            {
                Position P = H->TheLists[ i ];
                Position Tmp;

                while( P != NULL )
                {
                    Tmp = P->Next;
                    free( P );
                    P = Tmp;
                }
            }

            free( H->TheLists );
            free( H );
        }


		Position FindPrevious(Position P, List L)
		{
			Position Prev;

			      Prev = L;
			      while (Prev->Next != NULL && Prev->Next != P)
				          Prev = Prev->Next;

			      return Prev;
		}


		void Delete(ElementType* fname,HashTable H) {// update this
			Position P =Retrieve(fname, H,'d');
			if (P == NULL) {
				puts("Contact not found");
			}
			else 
			{
				Position Prev = FindPrevious(P, H->TheLists[Hash(P->first_name, H->TableSize)]);
				Prev -> Next = P -> Next;
				free(P);
				puts("Delete Successful");
			}
		}

		void update(ElementType* fname, HashTable H)
		{
			Position P = Retrieve(fname, H, 'd');
			char num[constant];
			if (P == NULL)
			{
				puts("Contact not found");
			}
			else 
			{
				int choice;
				struct ListNode f;
				clock_t start, end;
				double runtime;
				puts("what to edit\n1. mobile\n2.home\n3.work\n4. First Name\n5. Second Name\nAny other key to exit");
				scanf_s("%d", &choice);
				getchar();
				if (choice == 3)
				{
					printf("Enter the company name\n");
					scanf_s("%s", &P->company_name, constant);
					getchar();
				}
				else if (choice == 1)
				{
					do
					{
						puts("Enter mobile number");
						scanf_s("%s", num, constant);
						getchar();
						if ( hasAlphabets(num)) {
							puts("Invalid Number");
						}
						else
							break;
					} while (1);
					P->mobile = atoi(num);
				}
				else if (choice == 2)
				{
					do
					{
						puts("Enter home number");
						scanf_s("%s", num,constant);
						getchar();
						if (hasAlphabets(num)) 
							puts("Invalid Number");
						else
							break;
					} while (1);
					P->home = atoi(num);
				}
				else if (choice == 4)
				{
					f = *P;
					Position Prev = FindPrevious(P, H->TheLists[Hash(P->first_name, H->TableSize)]);
					Prev->Next = P->Next;
					free(P);
					
					printf("Enter first name\n");
					scanf_s("%s", &f.first_name, constant);
					getchar();
					Insert(&f, H);
					
					P = &f;
				}
				else if (choice == 5)
				{
					printf("Enter second name\n");
					scanf_s("%s", &P->last_name, constant);
					getchar();
				}
				printf("First name = %s\n", P->first_name);
				printf("Last Name = %s\n", P->last_name);
				printf("Company name = %s\n", P->company_name);
				printf("Mobile = 0%u\n", P->mobile);
				printf("Home = 0%u\n", P->home);
			}

		}

		
		// Sorts the table in descending order


		void Sort(HashTable H) {
			int i;
			int  j = 0;
			SearchTree T = MakeEmpty(NULL);
			for (i = 0; i < H->TableSize; i++)
			{
				Position P = H->TheLists[i]->Next;
				while (P != NULL) 
				{
					T= TreeInsert(P, T);
					P = P->Next;
				}
				j = 0;
			}
			puts("First Name\tSecond Name\tMoblile Number\tPhone Number\tWork");
			PrintAscend(T);
			
		}


		//for file reading

		void Load(char *path,HashTable H)
		{
			FILE *fptr;
			char line[150]; //for lines in file
			const char delimeter[3] = ","; // delimiter for fields in file
			char *token = NULL;
			char *next_token = NULL;

			//give path for the file
			fopen_s(&fptr, path, "r");

			//check if file is opening successfully
			if (fptr == NULL)
			{
				perror("error ");
				exit(1);
			}
			else
				printf("success!\n");
			///////My variables////
			int term;
			Position f = malloc(sizeof(struct ListNode));
			//read data from file
			while (!feof(fptr))
			{
				if (fgets(line, 150, fptr) != NULL)
				{
					term = 1;
					char *ptr;
					//separate data fields using delimiter
					token = strtok_s(line, delimeter, &next_token);
					strcpy_s(f->first_name,constant,token);
					
					// walk through other tokens 
					while (token != NULL) {
						token = strtok_s(NULL, delimeter, &next_token);
						term++;
						if (token == NULL)
							break;
						if (term % 4 == 0)
						{
							f->mobile = strtoul(token,&ptr,10);
						}
						else if (term % 2 == 0) 
						{
							strcpy_s(f->last_name, constant, token);
						}	
						else if (term % 3 == 0)
						{
							strcpy_s(f->company_name, constant, token);
						}
						else if (term % 5 == 0)
						{
							f->home = strtol(token,&ptr,10);
						}
					}
					Insert(f, H);
				}
			}

			fclose(fptr); // close file

		}
		

		//writing data to hard disk in a file 
		void write(char *path,HashTable H) {
			FILE *fptr;
			fopen_s(&fptr, path, "w");
			if (fptr == NULL)
				Error("Cannot open file");
			int i = 0;
			List L;
			Position P;
			for (i = 0; i < H->TableSize; i++) {
				L = H->TheLists[i];
				P = L->Next;
				while (P != NULL) {
					fprintf(fptr, "%s,", P->first_name);
					fprintf(fptr, "%s,", P->last_name);
					fprintf(fptr, "%s,",P->company_name);
					fprintf(fptr, "%u,%d\n", P->mobile, P->home);
					P = P->Next;
				}
			}
			fclose(fptr);
		}


		
		HashTable Rehash(HashTable H)
		{
			int i, OldSize;
			List* OldLists;
			Position P;
			OldLists = H->TheLists;
			OldSize = H->TableSize;
			H = InitializeTable(2 * OldSize);
			for (i = 0; i < OldSize; i++) 
			{
				P = OldLists[i]->Next;
				while (P != NULL)
				{
					Insert(P, H);
					P = P->Next;
				}
			}
			free(OldLists);
			return H;
		}


		int TableElements(HashTable H)
		{
			return H->Elements_no;
		}

		int TableSize(HashTable H)
		{
			return H->TableSize;
		}

		// Prints The table index wise

		void PrintTable(HashTable H) {
			int i;
			int  j = 0;
			for (i = 0; i < H->TableSize; i++) {
				printf("Index = %d", i);
				Position P = H->TheLists[i]->Next;
				while (P != NULL) {
					printf(" Value %d = %s", j++, P->first_name);
					P = P->Next;
				}
				if (P != NULL)
					printf("%s", "Empty");
				puts("");
				j = 0;
			}
		}

		//hasAlphabets is used to check whether a string has alphabets in it or not

		int hasAlphabets(ElementType* x) 
		{
			int len = strlen(x);
			for (int i = 0; i < len; i++) 
			{
				if (*x<'0' || *x>'9')
				{
					return 1;
				}
				x++;
			}
			return 0;
		}

		