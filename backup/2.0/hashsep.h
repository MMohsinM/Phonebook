/* Interface for separate chaining hash table */
typedef char ElementType;

/* START: fig5_2.txt */
        typedef unsigned int Index;
/* END */

/* START: fig5_7.txt */
        #ifndef _HashSep_H
        #define _HashSep_H

        struct ListNode;
        typedef struct ListNode *Position;
		typedef Position List;
        struct HashTbl;
        typedef struct HashTbl *HashTable;
        HashTable InitializeTable( int TableSize );
        void DestroyTable( HashTable H );
		Index Hash(const char *Key,int TableSize);
		Position FindPrevious(Position P, List L);
		Position Find(ElementType* fn, ElementType* sn, HashTable H);
        Position Retrieve( ElementType *key, HashTable H,char mode);	
        void Insert( Position Ptrstruct, HashTable H );
        //Position Retrieve( char str[] );
		void Delete(ElementType* fname, HashTable H);
		void Sort(HashTable H);
		void Load(char *path, HashTable H);
		void update(ElementType* fname, HashTable H);
		int TableElements(HashTable H);
		int TableSize(HashTable H);
		HashTable Rehash(HashTable H);
		void PrintTable(HashTable H);
        /* Routines such as Delete are MakeEmpty are omitted */
		////////TREE FUNCTIONS//////////////
		typedef struct TreeNode* SearchTree;
		struct TreeNode;
		SearchTree	MakeEmpty(SearchTree T);
		SearchTree TreeInsert(Position X, SearchTree T);
		void PrintAscend(SearchTree T);
        #endif  /* _HashSep_H */
/* END */
