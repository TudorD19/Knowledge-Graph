#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bst.h"

/* =========================================================
 * bst.c
 * BST indexat după numele entității; nodurile conțin pointeri
 * în tabloul de noduri al grafului (fără duplicarea datelor).
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții auxiliare interne (statice, neexportate)
 * ---------------------------------------------------------- */

/* Eliberează recursiv nodii BSTNode (nu GraphNode-urile spre care
 * pointează — acelea aparțin Grafului). */
static void bst_free_recursive(BSTNode *node)
    __attribute__((unused));
static void bst_free_recursive(BSTNode *node)
{
    if(node == NULL)
        return;
    
    bst_free_recursive(node->left);
    bst_free_recursive(node->right);
    free(node);
}

/* Inserare recursivă; returnează rădăcina (posibil nouă) a subarbore. */
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
    __attribute__((unused));
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
{   
    // daca ajunge la null, insereaza noul nod
    if(node == NULL) {
        BSTNode *new_node = malloc(sizeof(BSTNode));

        if(new_node == NULL)
            return NULL;

        new_node->graph_node = gn; //copia la nodul din graph
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }
    // criteriul de comparatie
    int cmp = strcmp(gn->entity.name, node->graph_node->entity.name);

    if(cmp < 0)
        node->left = bst_insert_recursive(node->left, gn);
    else if(cmp > 0)
        node->right = bst_insert_recursive(node->right, gn);

    // daca numele e egal, nu insereaza duplicat (proprietate bst)

    return node;
}

/* Căutare recursivă; returnează GraphNode* sau NULL. */
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
    __attribute__((unused));
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
{   
    // nu a gasit numele sau numele este invalid
    if(node == NULL || name == NULL)
        return NULL;

    int cmp = strcmp(name, node->graph_node->entity.name);

    // daca am gasit nodul
    if(cmp == 0)
        return node->graph_node;
    // decide directia
    else if(cmp < 0)
        return bst_search_recursive(node->left, name);
    
    else 
        return bst_search_recursive(node->right, name);
    
}

/* Traversare inordine pentru afișare. */
static void bst_inorder_recursive(const BSTNode *node)
    __attribute__((unused));
static void bst_inorder_recursive(const BSTNode *node)
{
    if(node == NULL)
        return;
    
    bst_inorder_recursive(node->left); //parcurgere stanga
    entity_print(&node->graph_node->entity); // nodul curent
    bst_inorder_recursive(node->right); // parcurgere dreapta
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și inițializează un BST gol. Returnează NULL la eșec. */
BST *bst_create(void)
{
    BST *tree = malloc(sizeof(BST));

    if(tree == NULL)
        return NULL;

    tree->root = NULL;

    return tree;
}

/* Eliberează recursiv toți nodii BST, apoi structura BST. */
void bst_free(BST *tree)
{
    if(tree == NULL)
        return;
    //eliberam recursiv pornind de la root
    bst_free_recursive(tree->root);

    free(tree);
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int bst_insert(BST *tree, GraphNode *graph_node)
{
    BSTNode *new_root = NULL;

    if(tree == NULL || graph_node == NULL)
        return -1;
    
    // daca arborele e gol, new_root devine nodul inserat
    new_root = bst_insert_recursive(tree->root , graph_node);
    
    if(new_root == NULL)
        return -1;
    
    tree->root = new_root;
    return 0;
}

/* ----------------------------------------------------------
 * Interogare
 * ---------------------------------------------------------- */

GraphNode *bst_search(const BST *tree, const char *name)
{
    if(tree == NULL || name == NULL)
        return NULL;

    return bst_search_recursive(tree->root, name);
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void bst_inorder_print(const BST *tree)
{
    if(tree == NULL)
        return;
    
    bst_inorder_recursive(tree->root);
}
