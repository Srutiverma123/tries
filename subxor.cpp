/*
SUBXOR

A straightforward question. Given an array of positive integers you have to print the number of subarrays whose XOR is less than K. Subarrays are defined as a sequence of continuous elements Ai, Ai+1, ..., Aj . XOR of a subarray is defined as Ai ^ Ai+1 ^ ... ^ Aj. Symbol ^ is Exclusive Or.
Input Format
First line contains T, the number of test cases. 
Each of the test case consists of N and K in one line, followed by N space separated integers in next line.
Output Format
For each test case, print the required answer.
Constraints:
1 = T = 5
1 = N = 10^5
1 = A[i] = 10^5
1 = K = 10^6
Sample Input
1
5 2
4 1 3 2 7   
Sample Output
3
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 20;
#define lli long long int 

struct node{
   node* left = NULL;
   node* right = NULL;
   lli countl = 0;
   lli countr = 0; 
};

node* root;

void insert(node* root,int x,int l){
    if(l == N + 1) return;         
    if( x & ( 1<<(N-l) )){ root->countr++;
         if(root->right == NULL) root->right = new node;
         insert(root->right,x,l+1);
    }
    else{ root->countl++;
         if(root->left == NULL) root->left = new node;
         insert(root->left,x,l+1);
    } 
}

lli query(int x,int k){
    node* temp =root;
    lli res = 0; 
    
    for(int i=N;i>=0;i--){
        if(temp == NULL) break;
        if(k & (1<<i)) {
            if(x & (1<<i)){
                 res += temp->countr;
                 temp = temp->left;
            }
            else{
                 res += temp->countl;
                 temp = temp->right;
            }
        }    
        else{
            if(x & (1<<i)){
                 temp = temp->right;
            }
            else{
                 temp = temp->left;
            }
        } 
    }
    
  return res;
}

int main(){
 int t;
 scanf("%d", &t);
    
    while(t--){
        root = new node;
        int n,k;
        scanf("%d%d", &n, &k);

        int x = 0,a;
        node* temp = root;
        insert(temp,x,0);
        
        lli cnt = 0; 
        for(int i=1;i<=n;i++){scanf("%d", &a); 
           x ^= a; 
           cnt += query(x,k); 
           insert(temp,x,0);
        }
        
        cout<<cnt<<endl;  
    }
    
 return 0;
}

