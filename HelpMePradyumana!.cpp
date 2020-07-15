/*
Help Me Pradyumana!

Pradyumn is tired of using auto - correct feature in his smartphone. He needs to correct his auto - correct more times than the auto - correct corrects him. Pradyumn is thinking to make his own app for mobile which will restrict auto - correct feature, instead it will provide auto - completion. Whenever Pradyumn types factorial, auto - correct changes it to fact. Pradyumn's App will show options such as fact, factorial, factory. Now, he can chose from any of these options. As Pradyumn is busy with his front - end work of his App. He asks you to help him. He said "You will be given set of words(words may repeat too but counted as one only). Now, as user starts the app, he will make queries(in lowercase letters only). So, you have to print all the words of dictionary which have the prefix same as given by user as input. And if no such words are available, add this word to your dictionary." As you know, Pradyumn want this app to be as smart as him :P So, implement a program for him such that he can release it on Fun Store.
INPUT CONSTRAINTS
1=N=30000
sum(len(string[i]))=2*10^5
1=Q=10^3
INPUT FORMAT
Single integer N which denotes the size of words which are input as dictionary
N lines of input, where each line is a string of consisting lowercase letter
Single integer Q which denotes the number of queries.
Q number of lines describing the query string on each line given by user
OUTPUT FORMAT
If auto - completions exists, output all of them in lexicographical order else output "No suggestions" without quotes

NOTE: All strings are lowercase
SAMPLE INPUT
3
fact
factorial
factory
2
fact
pradyumn
SAMPLE OUTPUT
fact
factorial
factory
No suggestions
*/

#include<stdio.h>
#include<stdlib.h>
 
char ans[200001];
 
typedef struct trie_t {
	struct trie_t* child[26];
	int leaf;
} trie_t;
 
int myStrlen(char* str) {
	int len = 0;
	while(str[len])
		len++;
	return len;
}
 
trie_t* getNode() {
	trie_t* newNode;
	int i;
 
	newNode = (trie_t*) malloc(sizeof(trie_t));
	newNode->leaf = 0;
 
	for(i=0; i<26; i++)
		newNode->child[i] = NULL;
 
	return newNode;
}
 
void insert(trie_t* root, char* str) {
	int len = myStrlen(str), i;
	trie_t* pcrawl = root;
 
	for(i=0; i<len; i++) {
		int x;
		if(str[i] >= 'A' && str[i] <= 'Z') {
			x = str[i] - 'A';
		}
		else
			x = str[i] - 'a';
 
		if(pcrawl->child[x] == NULL) {
			pcrawl->child[x] = getNode();
		}
		pcrawl = pcrawl->child[x];
	}
 
	pcrawl->leaf = 1;
}
 
void triePrint(trie_t* pcrawl, int idx) {
	int i;
 
	if(pcrawl->leaf) {
		ans[idx] = '\0';
		puts(ans);
	}
 
	for(i=0; i<26; i++) {
		if(pcrawl->child[i] == NULL)
			continue;
 
		ans[idx] = 'a' + i;
		triePrint(pcrawl->child[i], idx+1);
	}
}
 
int search(trie_t* root, char* str) {
	int len = myStrlen(str), i;
	trie_t* pcrawl = root;
 
	for(i=0; i<len; i++) {
		int x;
		if(str[i] >= 'A' && str[i] <= 'Z') {
			x = str[i] - 'A';
		}
		else
			x = str[i] - 'a';
 
		if(pcrawl->child[x] == NULL)
			return 0;
		ans[i] = str[i];
		pcrawl = pcrawl->child[x];
	}
	triePrint(pcrawl, i);
	return 1;
}
 
int main() {
 
	int n, i=0, q;
	char str[200001];
	trie_t* root = getNode();
 
	scanf("%d", &n);
 
	for(i=0; i<n; i++) {
		scanf("%s", str);
		insert(root, str);
	}
 
	scanf("%d", &q);
 
	for(i=0; i<q; i++) {
		scanf("%s", str);
		if(!search(root, str)) {
			insert(root, str);
			puts("No suggestions");
		}
	}
 
	return 0;
}
