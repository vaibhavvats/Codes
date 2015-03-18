#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

int maxi(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
        //tg
}

int height(struct node *N)
{
    if (N == NULL)
        return 2;
    return N->height;

}


struct node* newNode(int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxi(height(y->left), height(y->right))+1;
    x->height = maxi(height(x->left), height(x->right))+1;

    return x;
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;
    x->height = maxi(height(x->left), height(x->right))+1;
    y->height = maxi(height(y->left), height(y->right))+1;
    return y;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
   if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    node->height = maxi(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int main()
{
 FILE *fp;
int x;
 struct node *root = NULL;

    //printf("\n\nThe numbers: \n");
    fp=fopen("datab.txt","rb");
    if(fp==NULL)
    {
        printf("Sorry the file cannot be opened\n");
        exit(0);
    }


    while(fscanf(fp, "%d,", &x)==1)
    {
      //printf("Number : %d\n",x);
      root = insert(root, x);
    }

    printf("In order traversal of the constructed AVL tree is \n");
    inOrder(root);

    fclose(fp);
    return 0;
}
