       #include "fatal.h"
       #include "hashsep.h"
       #include <stdlib.h>
	   #include <string.h>
       
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
			int Elements_no;
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
			while (*Key != '\0')
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

/* START: fig5_9.txt */
        Position
        Retrieve( ElementType* key, HashTable H ,char mode)///Retrieve Function
        {
            Position P;
            List L;
			int check = 0;//counts matched queries
/* 1*/      L = H->TheLists[ Hash( key, H->TableSize ) ];
/* 2*/      P = L->Next;
			char search = 'j';
/* 3*/      while( P != NULL)
		{
				if (strcmp(P->first_name, key) == 0) {
					if (!check)
					{
						printf("First Name\tLast Name\tMobile\t\tHome\t\tCompany\n");
					}
					printf("%d.%s\t%s\t\t0%d\t0%d\t%s\n", check++, P->first_name, P->last_name,P->mobile,P->home,P->company_name);
					check++;
					if (mode != 'r')
					{
						printf("Search further (n to stop): ");
						scanf_s("%c", &search,1);
						getchar();
						if (search == 'n' || search == 'N')
							break;
					}
				}
				P = P->Next;
			}

		if (!check)
			puts("No matched queries");
/* Probably need strcmp!! */
/* 5*/		return P;
        }


        void
        Insert( Position Input, HashTable H ) /// Create Function ,upadate it to not allow duplicate contacts
        {
            Position NewCell;
            List L;
/* 1*/      //Pos = Find( Input->first_name, H );
/* 2*/      //if( Pos == NULL )   /* Key is not found */
            //{
/* 3*/          NewCell = malloc( sizeof( struct ListNode ) );
/* 4*/          if( NewCell == NULL )
/* 5*/              FatalError( "Out of space!!!" );
                else
                {
/* 6*/              L = H->TheLists[ Hash(Input->first_name, H->TableSize ) ];
/* 7*/              NewCell->Next = L->Next;
/* 8*/              strcpy_s(NewCell->first_name, constant, Input->first_name);  /* Probably need strcpy! */
					strcpy_s(NewCell->last_name, constant, Input->last_name);
					strcpy_s(NewCell->company_name, constant, Input->company_name);
					NewCell->mobile = Input->mobile;
					NewCell->home = Input->home;
/* 9*/              L->Next = NewCell;
                }
          //  }
*(&H->Elements_no) +=1;
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

			/* 1*/      Prev = L;
			/* 2*/      while (Prev->Next != NULL && Prev->Next != P)
				/* 3*/          Prev = Prev->Next;

			/* 4*/      return Prev;
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
			if (P == NULL)
			{
				puts("Contact not found");
			}
			else 
			{
				int choice;
				puts("what to edit\n1. mobile\n2.home\n3.work");
				scanf_s("%d", &choice);
				switch (choice)
				{
				case 3:
					printf("Enter the company name\n");
					scanf_s("%s", &P->company_name, constant);
					getchar();
				case 1:
					printf("Enter the mobile number\n");
					scanf_s("%d", &P->mobile);
					getchar();
				case 2:
					printf("Enter the home number\n");
					scanf_s("%d", &P->home);
					getchar();
				default:
					break;
				} 
				printf("First name = %s ", P->first_name);
				printf("Last Name = %s ", P->last_name);
				printf("Company name = %s ", P->company_name);
				printf("Mobile = 0%d ", P->mobile);
				printf("Home = 0%d\n", P->home);
			}

		}

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
					fprintf(fptr, "%d,%d\n", P->mobile, P->home);
					P = P->Next;
				}
			}

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

		/*void Load(char *path,HashTable H) {
			FILE *fptr;
			
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
			Position P = malloc(sizeof(struct ListNode));
			

			while (!feof(fptr))
			{
					fscanf_s(fptr, "%[^," "\n]", P->first_name,constant);
					fscanf_s(fptr, "%[^," "] ", P->last_name,constant);
					fscanf_s(fptr, "%[^," "] ", P->company_name,constant);
					fscanf_s(fptr, "%u%*c%u ", &P->mobile, &P->home);
					Insert(P, H);
				}
			}
	*/