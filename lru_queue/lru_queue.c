#include <stdio.h> 
#include <stdlib.h> 

int no_of_page_faults = 0;  

typedef struct QNode 
{ 
    struct QNode *prev, *next; 
    unsigned pageNumber;
} QNode; 

typedef struct Queue 
{ 
    unsigned count;
    unsigned numberOfFrames;
    QNode *front, *rear; 
} Queue; 
  
typedef struct Hash 
{ 
    int capacity; 
    QNode* *array; 
} Hash; 

QNode* newQNode( unsigned pageNumber ) 
{ 
    QNode* temp = (QNode *)malloc( sizeof( QNode ) ); 
    temp->pageNumber = pageNumber; 
  
    temp->prev = temp->next = NULL; 
  
    return temp; 
} 
  
Queue* createQueue( int numberOfFrames ) 
{ 
    Queue* queue = (Queue *)malloc( sizeof( Queue ) ); 
  
    queue->count = 0; 
    queue->front = queue->rear = NULL; 
  
    queue->numberOfFrames = numberOfFrames; 
  
    return queue; 
} 
  
Hash* createHash( int capacity ) 
{ 
    Hash* hash = (Hash *) malloc( sizeof( Hash ) ); 
    hash->capacity = capacity; 
  
    hash->array = (QNode **) malloc( hash->capacity * sizeof( QNode* ) ); 
  
    int i; 
    for( i = 0; i < hash->capacity; ++i ) 
        hash->array[i] = NULL; 
  
    return hash; 
} 
  
int AreAllFramesFull( Queue* queue ) 
{ 
    return queue->count == queue->numberOfFrames; 
} 
  
int isQueueEmpty( Queue* queue ) 
{ 
    return queue->rear == NULL; 
} 
  
void deQueue( Queue* queue ) 
{ 
    if( isQueueEmpty( queue ) ) 
        return; 
  
    if (queue->front == queue->rear) 
        queue->front = NULL; 
  
    QNode* temp = queue->rear; 
    queue->rear = queue->rear->prev; 
  
    if (queue->rear) 
        queue->rear->next = NULL; 
  
    free( temp ); 
  
    queue->count--; 
} 
  
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber ) 
{ 
    if ( AreAllFramesFull ( queue ) ) 
    { 
        hash->array[ queue->rear->pageNumber ] = NULL; 
        deQueue( queue );
    } 
  
    QNode* temp = newQNode( pageNumber ); 
    temp->next = queue->front; 
  
    if ( isQueueEmpty( queue ) ) 
        queue->rear = queue->front = temp; 
    else
    { 
        queue->front->prev = temp; 
        queue->front = temp; 
    } 
  
    hash->array[ pageNumber ] = temp; 
  
    queue->count++; 
} 

int ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber ) 
{ 
    QNode* reqPage = hash->array[ pageNumber ]; 
	int isPagefault=0;  
    
    if ( reqPage == NULL ){ 
        isPagefault+=1;
        Enqueue( queue, hash, pageNumber ); 
    }
    
    else if (reqPage != queue->front) 
    { 
        reqPage->prev->next = reqPage->next; 
        if (reqPage->next) 
           reqPage->next->prev = reqPage->prev; 
  
        if (reqPage == queue->rear) 
        { 
           queue->rear = reqPage->prev; 
           queue->rear->next = NULL; 
        } 
  
        reqPage->next = queue->front; 
        reqPage->prev = NULL; 
  
        reqPage->next->prev = reqPage; 
  
        queue->front = reqPage; 
    } 
    return isPagefault;
} 
  

int main() 
{ 
    FILE *fin;
    FILE *fout;
    fin = fopen("Input.txt","r");
	fout = fopen("Output.txt","w");
	int no_of_frames;
	no_of_frames=3; 
    Queue* q = createQueue( no_of_frames );
    
    int no_of_pages;
    fprintf(fout, "The number of elements in the reference string are :");
    fscanf(fin,"%d",&no_of_pages);
    fprintf(fout, "%d\n",no_of_pages);
    
    Hash* hash = createHash( no_of_pages ); 
  
  	int no_of_page_faults=0;
    int pageValue;

    int i=0;
    fprintf(fout, "\nThe elements present in the string are\n");
	for(i=0;i<no_of_pages;i++){
    	fscanf(fin,"%d",&pageValue);
    	fprintf(fout, "%d ",pageValue);
		no_of_page_faults+=ReferencePage( q, hash, pageValue);
	}
	fprintf(fout, "\nFinal Queue: ");

    while(no_of_frames-- && q->front!=NULL){
    	fprintf (fout, "%d ", q->front->pageNumber);
    	q->front=q->front->next;
	}
	fprintf (fout, "\nThe number of page faults are: %d ", no_of_page_faults);

    return 0;
}

