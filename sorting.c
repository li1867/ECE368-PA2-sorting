#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

Node * sequence(int * length, int size);
Node * find_position(Node * list, int m);
int power(int base, int temp);
void reverse(Node ** head_ref);
void freeNode(Node * list);

void freeNode(Node * list)
{
	while(list != NULL)
	{
		Node *temp = list;
		list = list -> next;
		free(temp);
	}
}

Node *Load_From_File(char * Filename)
{

	FILE * fp = fopen(Filename, "rb");
	if(fp == NULL)
	{
		printf("unable to open file");
		fclose(fp);
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	int fp_size = ftell(fp) / sizeof(long);
	Node * node = malloc(sizeof(*node));  
	fseek(fp, 0, SEEK_SET);
	node -> next = NULL;
	if(fread(&(node -> value), sizeof(long), 1, fp)!= 1)
	{
		printf("1");
	}
	Node * temp = node;
	int i;
	for(i = 0; i < (fp_size - 1); i++)
	{
		Node* newNode = malloc(sizeof(*newNode));
		newNode -> next = NULL;
		fread(&(newNode -> value), sizeof(long), 1, fp);
		temp -> next = newNode;
		temp = newNode;
	}
	fclose(fp);

	return node;
}

int Save_To_File(char * Filename, Node * list)
{
	FILE* fp = fopen(Filename, "wb");
	if(fp == NULL)
	{
		return 0;
	}
	int size = 0;
	Node * temp = list;
	while(temp != NULL)
	{
		size++;
		temp = temp -> next;
	}
	temp = list;
	int i;
	for(i = 0; i < size; i++)
	{
		fwrite(&(temp -> value), sizeof(long), 1, fp);
		temp = temp -> next;
	}
	fclose(fp);

	return size;
}

Node * Shell_Sort(Node * list)
{
	int size = 0;
	Node * head = list;

	while(head != NULL)
	{
		size++;
		head = head -> next;
	}

	int length = 0;
	Node * seq = sequence(&length, size);

	Node * empty_node = malloc(sizeof(*empty_node));
	empty_node -> value = 0;
	empty_node -> next = list;
	list = empty_node;
	Node* seq_temp = seq; 

	while(seq_temp -> next != NULL)
	{
		long k_val = seq_temp -> value;  //gap
		int iterate = size - k_val;

		int j;
		if (k_val != 1){
			Node * prev_begin = NULL;
			Node * begin = NULL;
			Node * prev_end = NULL;
			Node * end = NULL;
			for(j = 0; j < (iterate +1 ); j++)
			{
				if (j == 0){
					prev_begin = list;
					begin = prev_begin -> next;
					prev_end = find_position(prev_begin, k_val+1);
					end = prev_end -> next;
				}
				else{
					begin = begin -> next;
					end = end -> next;
					prev_begin = prev_begin -> next;
					prev_end = prev_end -> next;
				}
				if(end == NULL)
				{
					break;
				}
				if(begin -> value > end -> value)
				{
					prev_begin -> next = end;
					Node* temp_swap = end -> next;
					end -> next = begin -> next;
					prev_end -> next = begin;
					begin -> next = temp_swap;
					begin = prev_begin -> next;
					end = prev_end -> next;

				}
			}
			seq_temp = seq_temp -> next;
		}
		else{
			Node* slave = list;
			Node* temp_s = list -> next;
			Node* temp_f = temp_s -> next;
			while(temp_f != NULL){
				if(temp_f -> value < temp_s -> value){
					Node* temp = temp_f -> next;
					slave -> next = temp_f;
					temp_f -> next = temp_s;
					temp_s -> next = temp;
					temp_s = slave -> next;
					temp_f = temp_s -> next;
				}
				slave = slave -> next;
				temp_f = temp_f -> next;
				temp_s = temp_s -> next;
			}
		}
	}
	list = list -> next;
	free(empty_node);
	freeNode(seq);	
	return list;
}

Node * find_position(Node * head, int k)
{
	Node * temp = head;
	int i = 0;
	while(i < k)
	{
		temp = temp -> next;
		if(temp == NULL)
		{
			return NULL;
			break;
		}
		i++;
	}
	return temp;
}

Node * sequence(int * length, int size)
{
	if(size == 0)
	{
		return NULL;
	}
	if(size == 1)
	{
		return NULL;
	}

	int base = 2;
	int height = 0;
	while(base < size)
	{
		base = base * 2;
		height++;
	}
	Node * seq = malloc(sizeof(*seq));
	Node * seq1 = seq;
	int i, p, q;
	for(i = 0; i <= height; i++)
	{
		p = i;
		q = 0;
		while(p >= 0)
		{
			int num = power(2, p) * power(3, q);
			if(num < size)
			{
				if(*length == 0)
				{
					seq1 -> value = num;
					seq1 -> next = NULL;
				}
				else{
					Node * temp = malloc(sizeof(*temp));
					temp -> value = num;
					temp -> next = NULL;
					seq1 -> next = temp;
					seq1 = seq1 -> next;
				}
				(*length)++;
				p = p - 1;
				q = q + 1;
			}
			else
			{
				break;
			}
		}
	}
	reverse(&seq);
	return seq;
}

void reverse(Node ** head_ref)
{
	Node * prev = NULL;
	Node * current = * head_ref;
	Node * next;
	while(current != NULL)
	{
		next = current -> next;
		current -> next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

int power(int base, int temp)
{
	int count = 1;
	int result = 1;
	if(temp == 0)
	{
		return result;
	}
	else
	{
		while(count <= temp)
		{
			result *= base;
			count++;
		}
	}
	return result;
}













