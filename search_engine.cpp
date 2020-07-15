/*
Search Engine

Let us see how search engines work. Consider the following simple auto complete feature. When you type some characters in the text bar, the engine automatically gives best matching options among it's database. Your job is simple. Given an incomplete search text, output the best search result.
Each entry in engine's database has a priority factor attached to it. We consider a result / search suggestion best if it has maximum weight and completes the given incomplete search query. For each query in the input, print the maximum weight of the string in the database, that completes the given incomplete search string. In case no such string exists, print -1.
INPUT
First line contains two integers n and q, which represent number of database entries and number of search queries need to be completed. Next n lines contain a string s and an integer weight, which are the database entry and it's corresponding priority.

Next q lines follow, each line having a string t, which needs to be completed.
OUTPUT
Output q lines, each line containing the maximum possible weight of the match for given query, else -1, in case no valid result is obtained.
CONSTRAINTS
1 = n, weight, len(s), len(t) = 10^6
1 = q = 10^5
total length of all strings in database entries = 10^6
total length of all query strings = 10^6
SAMPLE INPUT
2 1
hackerearth 10
hackerrank 9
hacker
SAMPLE OUTPUT
10
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define newTrie (Trie*) calloc(1, sizeof(Trie))
typedef struct node {
						bool isWord;
						int max;
						struct node *next[26];
					}Trie;
 
void insert(char*, Trie*, int);
void print(Trie , char, int);
int main(void )
{
 
	int n, w, q, i = 0;
	char string[1234];
	
	scanf("%i %i", &n,&q);
	Trie *t = newTrie, *ptr; 
	while(n--)
	{
		scanf("%s %i", string,&w);
		insert(string, t, w);
	}
    while(q--)
    {    
        scanf("%s",string);
        w=1,i=0;
        ptr = t;
        while( string[i] != '\0' )
        {
            if(ptr)
                ptr = ptr->next[string[i]-'a'];
            else
                break;
            i++;
        }    
        printf("%i\n",ptr?ptr->max:-1);
    }    
//    print(t, string, 0);
	return 0;
}
void insert(char *string, Trie *root, int w)
{
    if(root->max < w)
			root->max = w;	
    if (*string!='\0')
	{
		if (root->next[*string - 'a'] == NULL)
			root->next[*string - 'a'] = newTrie;
    	insert(string + 1, root->next[*string - 'a'], w);		
	}
	else
	{
		
		root->isWord = true;
	}
}
void print(Trie *root, char *string, int level)
{
 
	if(root->isWord == true)
	{	string[level] = '\0';
		printf("%i\n",root->max);
        puts(string);
	}
	int i;
	for( i = 0; i < 26; i++)
	{
		if (root->next[i])
		{
			string[level] = i + 'a';
			print(root->next[i], string, level + 1);
		}			
	}		
	
}
