//BT20CSE070
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    bool mark;
    int referenceCount;
    struct node *next_1;
    struct node *next_2;
    struct node *next_3;
    
    
}Node;

 Node *pointer_array[10];

void display_node(int i)
{
	printf("value=%d\t reference_count=%d freedupSize=%d\n",pointer_array[i]->data,pointer_array[i]->referenceCount,sizeof(Node));
}

void set_edge(int no,int no1,int no2,int no3)
{
	if(no1!=-1)
	{
		pointer_array[no]->next_1=pointer_array[no1];
		pointer_array[no1]->referenceCount+=1;
	}
	if(no2!=-1)
	{
		pointer_array[no]->next_2=pointer_array[no2];
		pointer_array[no2]->referenceCount+=1;
	}
	if(no3!=-1)
	{
		pointer_array[no]->next_3=pointer_array[no3];
		pointer_array[no3]->referenceCount+=1;
	}
	
}

void display_all_nodes(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:referenceCount=%d\n",root->data,root->referenceCount);
	}
	if(root==NULL)
	{
		return;
	}
	display_all_nodes(root->next_1);
	display_all_nodes(root->next_2);
	display_all_nodes(root->next_3);
}

void adjacency_list()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]!=NULL)
		{
			printf("Value=%d: ",pointer_array[i]->data);
			if(pointer_array[i]->next_1!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_1->data);
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_2->data);
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_3->data);
			}
			printf("NULL\n");
		}
	}
}

int root_is_present(Node* root1,Node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	
	if(root_is_present(root1->next_1,temp))
	{
		return 1;
	}
	
	if(root_is_present(root1->next_2,temp))
	{
		return 1;
	}
	if(root_is_present(root1->next_3,temp))
	{
		return 1;
	}
 return 0;
}


void garbage_collection_referenceCounting(Node* root)
{
	int i=0;
	while(i<8)
	{
		if(root_is_present(root,pointer_array[i])==0 )
		{		
			if(pointer_array[i]->next_1!=NULL)
			{
				pointer_array[i]->next_1->referenceCount-=1;
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				pointer_array[i]->next_2->referenceCount-=1;
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				pointer_array[i]->next_3->referenceCount-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
		 i++;		
	}
	 
}

void adjacency_Matrix()
{
	int adm[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)	
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(pointer_array[j]!=NULL&&pointer_array[i]!=NULL)
		{
			
			if(pointer_array[i]->next_1!=NULL)
			{
				if(pointer_array[i]->next_1->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				if(pointer_array[i]->next_2->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				if(pointer_array[i]->next_3->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);
		}
		printf("\n");
	}
}

void mark_the_Nodes(Node*root,int i,int j)
{
    Node *current, *pre;

    current = root;
        
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_2;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_2 != NULL) && (pre->next_2 != current))
            {
            	pre = pre->next_2;
			}
                
            if (pre->next_2 == NULL) 
            {
                pre->next_2 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_2 = NULL;
                current->mark=true;
                current = current->next_2;
            } 
        }
    }   
    
    current = root;
        
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_3;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_3 != NULL) && (pre->next_3 != current))
            {
            	pre = pre->next_3;
			}
                
            if (pre->next_3 == NULL) 
            {
                pre->next_3 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_3 = NULL;
                current->mark=true;
                current = current->next_3;
            } 
        }
    }  
    
}

void mark_method(Node* root)
{
	
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	mark_method(root->next_1);
	mark_method(root->next_2);
	mark_method(root->next_3);
}

void sweep_method()
{
	int i;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]->mark==false)
		{
			if(pointer_array[i]->next_1!=NULL)
			{
				pointer_array[i]->next_1->referenceCount-=1;
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				pointer_array[i]->next_2->referenceCount-=1;
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				pointer_array[i]->next_3->referenceCount-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
	}
}

int main()
{

	int val[]={1,5,7,8,9,10,13,14};
	
	
	int i;
	
	for( i=0;i<8;i++)
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->data=val[i];
		newNode->next_1=NULL;
		newNode->next_2=NULL;
		newNode->next_3=NULL;
		newNode->referenceCount=0;
		newNode->mark=false;		
		pointer_array[i]=newNode;
	}
	
	Node*root1=pointer_array[3];
	pointer_array[3]->referenceCount+=1;
	Node*root2=pointer_array[0];
	pointer_array[0]->referenceCount+=1;
	
	set_edge(0,1,3,7);
	set_edge(2,5,7,-1);
	set_edge(3,0,-1,-1);
	set_edge(4,0,8,-1);
	set_edge(5,7,-1,-2);

	
	printf("\nAll nodes through root-1:\n");
	display_all_nodes(root1);
	
		
	printf("\nAll nodes through root-2:\n");
	display_all_nodes(root2);
	
	printf("\n\nAdjacency list :\n");
	adjacency_list();
    printf("\n\nAdjacency matrix:\n");
	adjacency_Matrix();	
	printf("\nCalling the mark and sweep garbage collector\n");
	mark_method(root1);
	sweep_method();	
	printf("\n\nAdjacency list after removal of garbage:\n");
	adjacency_list();
	
	printf("\n\nAdjacency matrix after removal of garbage:\n");
	adjacency_Matrix();
	
}
