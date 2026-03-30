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
    /* TODO: traversare post-ordine pentru eliberarea fiecărui BSTNode */
    (void)node;
}

/* Inserare recursivă; returnează rădăcina (posibil nouă) a subarbore. */
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
    __attribute__((unused));
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
{
    /* TODO: compară numele, recursie stânga/dreapta, alocă la NULL */
    (void)node;
    (void)gn;
    return NULL;
}

/* Căutare recursivă; returnează GraphNode* sau NULL. */
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
    __attribute__((unused));
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
{
    /* TODO: compară name, recursie stânga/dreapta */
    (void)node;
    (void)name;
    return NULL;
}

/* Traversare inordine pentru afișare. */
static void bst_inorder_recursive(const BSTNode *node)
    __attribute__((unused));
static void bst_inorder_recursive(const BSTNode *node)
{
    /* TODO: stânga -> vizitare -> dreapta */
    (void)node;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și inițializează un BST gol. Returnează NULL la eșec. */
BST *bst_create(void)
{
    /* TODO: alocă structura BST și inițializează root-ul cu NULL */
    return NULL;
}

/* Eliberează recursiv toți nodii BST, apoi structura BST. */
void bst_free(BST *tree)
{
    /* TODO: traversare post-ordine pentru eliberarea memoriei */
    (void)tree;
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int bst_insert(BST *tree, GraphNode *graph_node)
{
    /* TODO: deleghează la helper-ul recursiv, actualizează tree->root */
    (void)tree;
    (void)graph_node;
    return -1;
}

/* ----------------------------------------------------------
 * Interogare
 * ---------------------------------------------------------- */

GraphNode *bst_search(const BST *tree, const char *name)
{
    /* TODO: deleghează la helper-ul recursiv */
    (void)tree;
    (void)name;
    return NULL;
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void bst_inorder_print(const BST *tree)
{
    /* TODO: deleghează la helper-ul recursiv */
    (void)tree;
}
