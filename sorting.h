
typedef struct Node{
    long value;
    struct Node * next;
}Node;

Node * Load_From_File(char* Filename);
Node * Shell_Sort(Node * list);
int Save_To_File(char * Filename, Node * list);


