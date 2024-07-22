
#define numOfBytes 16
#define sizeOfByte 8
#define numOfBits (numOfBytes * sizeOfByte)
#define numsInLine 16
#define maxNumbers 128
#define maxInputSize 1000  
#define numOfSets 6
#define numOfCommands 7

typedef struct set
{
    char bitsArray[numOfBytes];
} set;

void updateBits (set *s, int num);
int checkBit (set *s, int num);
set * creatSet ();
void read_set(set *s, int *num, int n);
void print_set(set *s);
void union_set(set *set1, set *set2, set *unionSet);
void intersect_set(set *set1, set *set2, set *intersectionSet);
void sub_set(set *set1, set *set2, set *subSet);
void symdiff_set(set *set1, set *set2, set *symdiffSet);
int stop (void);


void problem (int x);
int numOfDigits (int num);
int numIsValid (char * ptr);
int commandIsValid (char * ptr);
int nameIsValid (char * ptr);
int allLineIsValid (char * ptr);



