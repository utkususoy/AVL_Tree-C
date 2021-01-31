#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_TREE_AVL_NODE_s *LINKED_TREE_AVL_NODE;
typedef struct LINKED_TREE_AVL_NODE_s{
    LINKED_TREE_AVL_NODE right;
    LINKED_TREE_AVL_NODE left;
    void *data;
    int height;
} LINKED_TREE_AVL_NODE_t[1];

typedef struct LINKED_TREE_AVL_s *LINKED_TREE_AVL;
typedef struct LINKED_TREE_AVL_s{
    LINKED_TREE_AVL_NODE root;
} LINKED_TREE_AVL_t[1];

typedef struct LINKED_STACK_NODE_s *LINKED_STACK_NODE;
typedef struct LINKED_STACK_NODE_s{
	LINKED_STACK_NODE next;
	void *data;
}LINKED_STACK_NODE_t[1];

typedef struct LINKED_STACK_s *LINKED_STACK;
typedef struct LINKED_STACK_s{
	LINKED_STACK_NODE head;
}LINKED_STACK_t[1];




void *linked_stack_top(LINKED_STACK stack);
void push(LINKED_STACK stack,void *data);
void *pop(LINKED_STACK stack);
int linked_stack_is_empty(LINKED_STACK stack);
LINKED_TREE_AVL_NODE Left_Rotate(LINKED_TREE_AVL_NODE node);
LINKED_TREE_AVL_NODE Right_Rotate(LINKED_TREE_AVL_NODE node);
int Getheight(LINKED_TREE_AVL_NODE node);
LINKED_TREE_AVL linked_tree_init();
int static compare_data(int d1, int d2);
LINKED_TREE_AVL_NODE init_node(void *data);
void Recursive_insert_Main(LINKED_TREE_AVL tree,void *data);
void Recursive_insert(LINKED_TREE_AVL_NODE node,void *data, LINKED_TREE_AVL tree);
void linked_tree_insert(LINKED_TREE_AVL tree, void *data , LINKED_STACK stack);
void linked_tree_avl_iterative_delete(LINKED_TREE_AVL tree, void *data, LINKED_STACK stack);
void linked_tree_Recursive_delete_Main(LINKED_TREE_AVL tree, void *data);
LINKED_TREE_AVL_NODE delete_recursive(LINKED_TREE_AVL_NODE node, void *data, LINKED_TREE_AVL tree);
LINKED_TREE_AVL_NODE Left_Rotate_Mines_Two(LINKED_TREE_AVL_NODE node);
LINKED_TREE_AVL_NODE Right_Rotate_Mines_Two(LINKED_TREE_AVL_NODE node);

LINKED_TREE_AVL linked_tree_init() {
	LINKED_TREE_AVL new = (LINKED_TREE_AVL) malloc(sizeof(LINKED_TREE_AVL_t));
	new->root = NULL;
	return new;
}


int linked_stack_is_empty(LINKED_STACK stack){
	if(stack->head == NULL){
		return 0;
	}else{
		return 1;
	}
}

void push(LINKED_STACK stack,void *data){
	LINKED_STACK_NODE node2 = (LINKED_STACK_NODE)malloc(sizeof(LINKED_STACK_NODE_t));
	if(node2 != NULL){
		node2->data=data;
		node2->next = stack->head;
		stack->head = node2;
	}else{
		printf("ERROR @@: Can not Allocate Memory!!\n");
	}
}

void *pop(LINKED_STACK stack){
	LINKED_STACK_NODE node;
	void *res;
	if(stack->head != NULL){
		node = stack->head; // node a stack head in g�sterdi�i nodu at�yo.
		res = node->data;
		stack->head = node->next;
		free(node);
	}else{
		printf("ERROR @@: Stack is Empty!!");
	}
	return res;
}

LINKED_STACK linked_stack_init() {
	LINKED_STACK new1 = (LINKED_STACK)malloc(sizeof(LINKED_STACK_t));
	new1->head = NULL;
	return new1;
}

void *linked_stack_top(LINKED_STACK stack){

    if(stack->head != NULL){
        return stack->head->data;
    }
    else{
        return 0;
    }

}

void Recursive_insert_Main(LINKED_TREE_AVL tree,void *data){
		if(tree->root == NULL){
			tree->root = init_node(data);
		}else{
			Recursive_insert(tree->root,data, tree);
		}	
}

LINKED_TREE_AVL_NODE init_node(void *data){
	LINKED_TREE_AVL_NODE new_node = (LINKED_TREE_AVL_NODE)malloc(sizeof(LINKED_TREE_AVL_NODE_t));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = data;
	return new_node;
}


void linked_tree_insert(LINKED_TREE_AVL tree, void *data , LINKED_STACK stack) {
	LINKED_TREE_AVL_NODE node;
	LINKED_TREE_AVL_NODE iter;
	iter = tree->root;
	if(tree->root == NULL){
		node = init_node(data);
		tree->root = node;	
	}else{
		int loop = 0;
		while(loop == 0){
			if(compare_data(*(int *)iter->data,*(int *)data) == -1){
				if(iter->right == NULL){
					push(stack, iter);
					node = init_node(data);
					iter->right = node;
					loop++;
				}else{
					push(stack, iter);
					iter = iter->right;
				}			
			}else if(compare_data(*(int *)iter->data,*(int *)data) == 1){
				if(iter->left == NULL){
					push(stack, iter);
					node = init_node(data);
					iter->left = node;
					loop++;
				}else{
					push(stack, iter);
					iter = iter->left;
				}				
			}else{
				printf("Data Can Not Allocated");
				loop++;
			}
		}
		while(linked_stack_is_empty(stack) && loop == 1){
			node = pop(stack);
			if(node != NULL) {
				node->height = Getheight(node->left) - Getheight(node->right);
				if(node->height == 2){
					if(node->left->height == 0 || node->left->height == 1){
						if(node == tree->root){
							tree->root = Right_Rotate(node);
						}else{ 	//done
							iter = linked_stack_top(stack);
							if(compare_data(*(int *)iter->data,*(int *)node->data) == -1){
								iter->right = Right_Rotate(node);
							}else	iter->left = Right_Rotate(node);
						 }
					}else if(node->left->height == -1){
						if(node == tree->root){
							tree->root = Right_Rotate(Left_Rotate(node));
						}else{	//done
							iter = linked_stack_top(stack);
							if(compare_data(*(int *)iter->data,*(int *)node->data) == -1){
								iter->right = Right_Rotate(Left_Rotate(node));
							}else	iter->left = Right_Rotate(Left_Rotate(node));
						}
					}

				}else if(node->height == -2){
					if(node->right->height == 1){
						if(node == tree->root){
							tree->root = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(node));
						}else{	//done
							iter = linked_stack_top(stack);
							if(compare_data(*(int *)iter->data,*(int *)node->data) == -1){
								iter->right = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(node));
							}else	iter->left = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(node));
						}
					 }else if(node->right->height == 0 || node->right->height == -1){
						if(node == tree->root){
							tree->root = Left_Rotate_Mines_Two(node);
						}else{		//done
							iter = linked_stack_top(stack);
							if(compare_data(*(int *)iter->data,*(int *)node->data) == -1){
								iter->right = Left_Rotate_Mines_Two(node);
							}else	iter->left = Left_Rotate_Mines_Two(node);
						 }
					 }
				}
			}
		}
	}
}



void Recursive_insert(LINKED_TREE_AVL_NODE node,void *data, LINKED_TREE_AVL tree){
		

		int compare_result = 0;
		compare_result = compare_data(*(int *)node->data,*(int *)data);
			
		if(compare_result < 0){
			if(node->right == NULL){

				node->right = init_node(data);
			}else{
				Recursive_insert(node->right,data,tree);
				
			}
		}else if(compare_result > 0){
			if(node->left == NULL){

				node->left = init_node(data);
			}else{
				Recursive_insert(node->left,data, tree);
			}
			
		}else{
			printf("dublicate data");
		}
	
}

void linked_tree_avl_iterative_delete(LINKED_TREE_AVL tree, void *data, LINKED_STACK stack){
	if(tree->root == NULL){
		printf("Tree is already Empty");
	}else{
		int loop = 0;
		LINKED_TREE_AVL_NODE iter = tree->root;
		LINKED_TREE_AVL_NODE iterPrev = tree->root;
		while(loop == 0){
			if(compare_data(*(int *)iter->data,*(int *)data) == -1){
						push(stack, iter);
						iterPrev = iter;
						iter = iter->right;
					}else if(compare_data(*(int *)iter->data,*(int *)data) == 1){
						push(stack, iter);
						iterPrev = iter;
						iter = iter->left;
					}else{
						if(iter->left == NULL && iter->right == NULL){
							if(iter == tree->root){
								tree->root = NULL;
								free(iter);
								iter = NULL;
								loop++;
							}else{
								if(iterPrev->left == iter){
									iterPrev->left = NULL;
									free(iter);
									iter = NULL;
									loop++;
								}else{
									iterPrev->right = NULL;
									free(iter);
									iter = NULL;
									loop++;
								}

							}
						}else if(iter->left != NULL && iter->right != NULL){
							LINKED_TREE_AVL_NODE iter2;
							LINKED_TREE_AVL_NODE iterPrev2;
							iter2 = iter->left;
							iterPrev2 = iter2;
							while(iter2->right != NULL ){
								iterPrev2 = iter2;
								iter2 = iter2->right;
							}
							iter->data = iter2->data;
							if(iterPrev2 != iter2){
								iterPrev2->right = iter2->left;
							}else{
								iter->left = iterPrev2->left;
							}
							free(iter2);
							iter2 = NULL;
							loop++;
						}else{
							LINKED_TREE_AVL_NODE temp;
							if(iter->left != NULL && iter->right == NULL){//done
								iter->data = iter->left->data;
								free(iter->left);
								iter->left = NULL;
								loop++;
							}else if(iter->left == NULL || iter->right != NULL){ //done
								iter->data = iter->right->data;
								free(iter->right);
								iter->right = NULL;
								loop++;
							}else{
								printf("Error@@");
								loop++;
							}
						}
					}
		}
		LINKED_TREE_AVL_NODE iter2;
		while(linked_stack_is_empty(stack) && loop == 1){
			iter = pop(stack);
			if(iter != NULL) {
				iter->height = Getheight(iter->left) - Getheight(iter->right);
							 if(iter->height == 2){
								 if(iter->left->height == 0 || iter->left->height == 1){
									 if(iter == tree->root){
									 	 tree->root = Right_Rotate(iter);
						 			 }else{  // done
						 				 iter2 = linked_stack_top(stack);
										 if(compare_data(*(int *)iter2->data,*(int *)iter->data) == -1){
										 	iter2->right = Right_Rotate(iter);
										}else	iter2->left = Right_Rotate(iter);
						 			 }
							 		}else if(iter->left->height == -1){
							 			if(iter == tree->root){
							 				tree->root = Right_Rotate(Left_Rotate(iter));
							 			}else{ // done
							 				iter2 = linked_stack_top(stack);
											 if(compare_data(*(int *)iter2->data,*(int *)iter->data) == -1){
											 	iter2->right = Right_Rotate(Left_Rotate(iter));
											}else	iter2->left = Right_Rotate(Left_Rotate(iter));
							 			}
							 		}
							 }else if(iter->height == -2){
								 if(iter->right->height == 1){
									 if(iter == tree->root){
										tree->root = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(iter));
									 }else{  //done
										iter2 = linked_stack_top(stack);
										if(compare_data(*(int *)iter2->data,*(int *)iter->data) == -1){
											iter2->right = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(iter));
										}else	iter2->left = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(iter));
									 }
								 }else if(iter->right->height == 0 || iter->right->height == -1){
									 if(iter == tree->root){
										 tree->root = Left_Rotate_Mines_Two(iter);
									 }else{ // done
										 iter2 = linked_stack_top(stack);
										 if(compare_data(*(int *)iter2->data,*(int *)iter->data) == -1){
										 	iter2->right = Left_Rotate_Mines_Two(iter);
										}else	iter2->left = Left_Rotate_Mines_Two(iter);
									 }
								 }

							 }


						}
		}

	}
}

void linked_tree_Recursive_delete_Main(LINKED_TREE_AVL tree, void *data){
	if(tree->root == NULL){
		printf("Tree is already Empty  ");
	}else{
		delete_recursive(tree->root,data , tree);
	}
}

LINKED_TREE_AVL_NODE delete_recursive(LINKED_TREE_AVL_NODE node, void *data, LINKED_TREE_AVL tree){
	LINKED_TREE_AVL_NODE  temp;
	int compare = compare_data(*(int *)node->data,*(int *)data);
	if(compare == -1){
		node->right = delete_recursive(node->right,data, tree);
	}else if(compare == 1){
		node->left = delete_recursive(node->left,data, tree);
	}else{
		if(node->left == NULL && node->right == NULL){ //done			
			free(node);
			node = NULL;
		}else if(node->left != NULL && node->right != NULL){ // ???
			LINKED_TREE_AVL_NODE iter;
			LINKED_TREE_AVL_NODE iterPrev;
			iter = node->left;
			iterPrev = iter;
			while(iter->right != NULL ){
					iterPrev = iter;
					iter = iter->left;
			}			
				node->data = iter->data;				
				if(iterPrev != iter){
					iterPrev->right = iter->left;
				}else{
					node->left = iterPrev->left;
				}				
			free(iter);
			iter = NULL;
		}else{
			if(node->left != NULL || node->right != NULL){
				if(node->left != NULL && node->right == NULL){//done
					temp = node->left;
					free(node);
					node = temp;
				}else if(node->left == NULL || node->right != NULL){ //done
					temp = node->right;
					free(node);					
					node = temp;
				}
			}
		} 	
	}

	if(node != NULL) {

		 node->height = Getheight(node->left) - Getheight(node->right);

		 if(node->height == 2){

			 if(node->left->height == 0 || node->left->height == 1){
				 if(node == tree->root){
				 	 tree->root = Right_Rotate(node);
	 			 }else node = Right_Rotate(node);

		 		}else if(node->left->height == -1){
		 			if(node == tree->root){
		 				tree->root = Right_Rotate(Left_Rotate(node));
		 			}else{
		 				node = Right_Rotate(Left_Rotate(node));
		 			}
		 		}

		 }else if(node->height == -2){

			 if(node->right->height == 1){
				 if(node == tree->root){
					tree->root = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(node));
				 }else{
					node = Left_Rotate_Mines_Two(Right_Rotate_Mines_Two(node));

				 }
			 }else if(node->right->height == 0 || node->right->height == -1){
				 if(node == tree->root){
					 tree->root = Left_Rotate_Mines_Two(node);
				 }else{
					 node = Left_Rotate_Mines_Two(node);
				 }
			 }

		 }

	}
	return node;
	
}

LINKED_TREE_AVL_NODE Right_Rotate_Mines_Two(LINKED_TREE_AVL_NODE node){
	LINKED_TREE_AVL_NODE gp = node;
	LINKED_TREE_AVL_NODE p = node->right;
	LINKED_TREE_AVL_NODE c = node->right->left;
//	printf("%d %d %d\n",*(int *)gp->data, *(int *)p->data, *(int *)c->data);
	gp->right = c;
	p->left = c->right;
	c->right = p;

	if(p->left == gp || p->right == gp) return p;
	else return gp;
}

LINKED_TREE_AVL_NODE Left_Rotate_Mines_Two(LINKED_TREE_AVL_NODE node){
	LINKED_TREE_AVL_NODE gp = node;
	LINKED_TREE_AVL_NODE p = node->right;
	LINKED_TREE_AVL_NODE c = node->right->left;
//	printf("%d %d %d\n",*(int *)gp->data, *(int *)p->data, *(int *)c->data);
	gp->right = c;
	p->left = gp;

	if(p->left == gp || p->right == gp) return p;
	else return gp;

}

LINKED_TREE_AVL_NODE Right_Rotate(LINKED_TREE_AVL_NODE node){
	LINKED_TREE_AVL_NODE gp = node;
	LINKED_TREE_AVL_NODE p = node->left;
	LINKED_TREE_AVL_NODE c = node->left->right;
	gp->left = p->right;
	p->right = gp;
	if(p->left == gp || p->right == gp) return p;
	else return gp;
}

LINKED_TREE_AVL_NODE Left_Rotate(LINKED_TREE_AVL_NODE node){
	LINKED_TREE_AVL_NODE gp = node;
	LINKED_TREE_AVL_NODE p = node->left;
	LINKED_TREE_AVL_NODE c = node->left->right;
	gp->left = c;
	p->right = c->left;
	c->left = p;
	if(p->left == gp || p->right == gp) return p;
	else return gp;
}


void print_tree(LINKED_TREE_AVL_NODE node,int l){ //note mainde l ye s�f�r ata
	int i;
	if(node != NULL){
		print_tree(node->right,l+1);
		for(i=0; i<l; i++){
			printf("\t");
		}
		node->height = Getheight(node->left) - Getheight(node->right);
		printf("%d , ( %d )",*(int *)node->data , node->height);
		printf("\n");
		print_tree(node->left,l+1);
	}
	
}

int ballanceHeight(int leftHeight , int rightHeight){
	return (leftHeight - rightHeight);
}

int Getheight(LINKED_TREE_AVL_NODE node){
	int	left_height = 0;
	int	right_height = 0;
	if ( node == NULL){
		return 0;
	}
	left_height = Getheight(node->left);
	right_height = Getheight(node->right);
	if(left_height > right_height){
		return  left_height + 1 ;
	}else{
		return  right_height + 1 ;
	}
}


int static compare_data(int d1, int d2) {
	int c;
	if (d1 < d2) {
		c = -1;
	} else if (d1 > d2) {
		c = 1;
	} else {
		c = 0;
	}
	return c;
}

int main(){
	int l = 0;
	LINKED_TREE_AVL tree = linked_tree_init();
	LINKED_STACK stack = linked_stack_init();
//	int arrx[] = {55,43,74,15,52,68,88,5,17,51,54,70,80,92,8,16,30,53,78,25,12,18,40,35,79};
	int arrx[] = {23, 26 ,44,9,4,15,30,17,14,11,2,3,7};
//	int arrx[] = {10,9,7,6,5,4,3,2,1,0}; //10
//	int arrx[] = {55,46,74,14,52,68,49};
//	int arrx[] = {55,49,74,46,52,68,88,15,51,54,70,50,53};

	int i = 0;
	for(i = 0; i<13; i++){
		linked_tree_insert(tree,&arrx[i] , stack);
		printf("\n------------------------------\n");
		LINKED_TREE_AVL_NODE x = tree->root;
		print_tree(x,l);
	}

}
