#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "count.h"

struct bstnode {
	int key;
    int val;
	struct bstnode *left;
	struct bstnode *right;
};

struct count{
    int total;
    int uniques;
    int freq;
    int freqnum;
 	struct bstnode *root;   
};

//see .h file for documentation
Count create_Count(void){
 	struct count *new = malloc(sizeof(struct count));
    new->root = NULL;
    new->total = 0;
    new->uniques = 0;
    new->freq = 0;
    new->freqnum = 0;
    return new;
}

void destroy_node(struct bstnode *node) {
	if (NULL == node) {return;}
	destroy_node(node->left);
	destroy_node(node->right);
	free(node);
}


// see bst.h documentation
void destroy_Count(Count c){
   destroy_node(c->root);
   free(c);
}

struct bstnode *make_bstnode(int key, int val, struct bstnode *l, struct bstnode *r) {
	struct bstnode *new = malloc(sizeof(struct bstnode));
	new->key = key;
    new->val = val;
	new->left = l;
	new->right = r;
	return new;
}

// next(c, i) add an occurrence of i to the Count ADT 
//   PRE:  c is a valid Count
//         [part A] 1 <= i <= 100
//   POST: value of count(c,i) is incremented by 1
//   TIME: [part A] O(1)
//         [part B] O(log n), where n = unique(c)


void next(Count c, int i){
   struct bstnode *k = c->root;
   
   while(1){
      if(k == NULL){
          c->root = make_bstnode(i, 1, NULL, NULL);
          c->uniques++;
          c->total++;
          if(c->freq == 0){
          	c->freq = 1; 
            c->freqnum = i;    
          }
         break;
      }else if(k->key == i){
          k->val++;
          c->total++;
          if(k->val > c->freq){
          	c->freq = k->val;
           	c->freqnum = k->key;   
          }
          break;
      }else if(i < k->key){
         if(k->left != NULL){
            k = k->left;
         }else{
            k->left = make_bstnode(i, 1, NULL, NULL);
            c->uniques++;
            c->total++;
          	if(c->freq == 0){
          		c->freq = 1; 
            	c->freqnum = k->key;    
          	}
         	break;
         }
      }else if(i > k->key){
         if(k->right != NULL){
            k = k->right;
         }else{
            k->right = make_bstnode(i, 1, NULL, NULL);
            c->uniques++;
            c->total++;
          	if(c->freq == 0){
          		c->freq = 1; 
            	c->freqnum = k->key;    
          	}
         	break;
         }
      }
   } 
}


//see .h file for documentation
int total(Count c){
 	return c->total;   
}

//see .h file for documentation
int unique(Count c){
 	return c->uniques;   
}

//see .h file for documentation
int count(Count c, int i){
 	struct bstnode *t = c->root;
    
    while(1){
        if(t == NULL){
        	return 0;  
        }else if(t->key == i){
        	return t->val;    
        }else if(i < t->key){
         	t = t->left;   
        }else{
         	t = t->right;   
        }
    }
    return 0;
}

int mostfreq(Count c){
 	return c->freqnum;   
}

void print_count(struct bstnode *t){
	if(!t) return;
    print_count(t->left);
   	printf("%d: %d\n", t->key, t->val);
    print_count(t->right); 	   
}

void stats(Count c){
    print_count(c->root);
}
