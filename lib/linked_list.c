/**
 * Singly linked list implementation.
 *
 * @author: Karina Quenta
 * @class: CS 5008
 * @term: Fall 2025
 */

#include <stdlib.h>
#include <stdbool.h>
#include "movie.h"
#include "linked_list.h"


/** 
 * Creates a new linked list node.
*/
Node * __ll__new_node(Movie *movie) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->movie = movie;
    new_node->next = NULL;
    return new_node;
}

/**
 * Creates a new linked list.
 * 
 * @return a pointer to the new linked list
 */
LinkedList *new_linked_list() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * Frees the memory associated with a linked list.
 * 
 * Frees just the linked list and nodes, the movies
 * stored are not freed. 
 * @param list the linked list to free
 */
void free_linked_list(LinkedList *list) {
    Node *curr = list->head;
    Node *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Frees the memory, including memory allocated
 * to movies stored in the link list. 
 * 
 * @param list the linked list to free
*/
void clear_and_free_linked_list(LinkedList *list) {
    Node *curr = list->head;
    Node *next;
    while (curr != NULL) {
        next = curr->next;
        free_movie(curr->movie);
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Adds a movie to the front of a linked list.
 * 
 * Don't forget to update the tail pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 * 
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_front(LinkedList *list, Movie *movie) {
    if (!list || !movie){
        return;
    }

    Node *new_node = __ll__new_node(movie);

    if(list->head == NULL){
        list->head = new_node;
        list->tail=new_node;
    }else{
        new_node->next = list-> head;
        list->head = new_node;
    }
    list->size++;
}

/**
 * Adds a movie to the back of a linked list.
 *
 * Don't forget to update the head pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 *
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_back(LinkedList *list, Movie *movie) {
    if (!list || !movie){
        return;
    }
    Node *new_node = __ll__new_node(movie);

    if (list->head==NULL){
        list->head=new_node;
        list->tail=new_node;
    }else{
        list->tail->next=new_node;
        list->tail=new_node;
    }
    list->size++;
}


/**
 * Inserts a movie into a linked list at a given index.
 * 
 * if n == 0, safe to call ll_add_front, if n == list->size, safe to call ll_add_back
 * 
 * if n is out of bounds, do nothing (return early)
 * 
 * @param list the linked list to insert into
 * @param movie the movie to insert
 * @param n the index to insert at
 */
void ll_insert(LinkedList *list, Movie *movie, int n) {
   if (!list || !movie || n <0){
        return;
   }
   if (n==0){
        ll_add_front(list, movie);
        return;
   }
   if (n==list->size){
        ll_add_back(list,movie);
        return;
   }

   Node *current = list->head;
   for (int i = 0; i < n - 1 && current != NULL;i++){
        current=current->next;
   }
   if (!current)return;

   Node *new_node=__ll__new_node(movie);
   if (!new_node)return;

   new_node->next=current->next;
   current->next=new_node;

   list->size++;
}


/**
 * Removes the first movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the tail pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_front(LinkedList *list) {
    Movie *movie = NULL;
    
    if (!list || list->head == NULL){
        return NULL;
    }

    Node *old_head = list->head;
    movie = old_head->movie;

    if (list->head == list->tail){
        list->head=NULL;
        list->tail=NULL;
    }else{
        list->head=old_head->next;
    }
    free(old_head);
    list->size--;
    return movie;
}

/**
 * Removes the last movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the head pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_back(LinkedList *list) {
    Movie* movie = NULL;
    
    if(!list || list->head ==NULL){
        return NULL;
    }
    Node *old_tail = list->tail;
    movie=old_tail->movie;

    if(list->head == list->tail){
        list->head=NULL;
        list->tail=NULL;
        free(old_tail);
        list->size--;
        return movie;
    }
    Node *current=list->head;
    while(current->next != list->tail){
        current = current->next;
    }
    current->next=NULL;
    list->tail=current;

    free(old_tail);
    list->size--;

    return movie;
}

/**
 * Removes a movie from a linked list at a given index.
 * 
 * if n == 0, safe to call ll_remove_front, if n == list->size - 1, safe to call ll_remove_back
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to remove from
 * @param n the index to remove at
 * @return the movie that was removed
 */
Movie * ll_remove(LinkedList *list, int n) {
    Movie * movie = NULL;
    
    if (!list || n<0 || list->head ==NULL){
        return NULL;
    }
    if(n>= list->size){
        return NULL;
    }
    if (n==0){
        return ll_remove_front(list);
    }
    if (n == list->size - 1){
        return ll_remove_back(list);
    }
    Node *current = list->head;
    for (int i=0;i < n -1 && current != NULL; i++){
        current = current->next;
    }

    if (!current || !current->next){
        return NULL;
    }
    Node *target = current -> next;
    movie = target->movie;
    current->next = target->next;
    free(target);
    list->size--;

    return movie;
}

/**
 * Gets a movie from a linked list at a given index.
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to get from
 * @param n the index to get at
 * @return the movie at the given index
 */
Movie* ll_get(LinkedList *list, int n) {
    if(!list || n < 0 || n >= list->size){
        return NULL;
    }
    Node *curr = list->head;
    for (int i = 0; i < n; i++) {
        curr = curr->next;
    }
    return curr->movie;
}

/**
 * Checks if a linked list contains a given movie.
 * 
 * Rare if a linked list contains a movie more than once, but
 * if so, just immediately return true.
 * 
 * @param list the linked list to check
 * @param movie the movie to check for
 * @return true if the linked list contains the movie, false otherwise
 */
bool ll_contains(LinkedList *list, Movie *movie) {
    Node *curr = list->head;
    while (curr != NULL) {
        if (curr->movie == movie) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/**
 * Checks if a linked list is empty.
 * 
 * @param list the linked list to check
 * @return true if the linked list is empty, false otherwise
 */
bool ll_is_empty(LinkedList *list) {
    return list->size == 0;
}

/**
 * Converts a linked list to a string representation.
 * 
 * @param list the linked list to convert
 * @return a string representation of the linked list
 */
char* ll_to_str(LinkedList *list) {
    
    char *str = (char *)malloc(sizeof(char) * (MAX_MOVIE_STR_LEN + 3) * list->size);
    if (list->size == 0) {
        strcpy(str, "[]");
        return str; // early exit
    }
    // implied else
    strcpy(str, "[");
    Node *curr = list->head;
    while (curr != list->tail) {
        char *movie_str = movie_to_str(curr->movie);
        strcat(str, movie_str);
        strcat(str, ", ");
        free(movie_str);
        curr = curr->next;
    }
    // now add the tail
    char *movie_str = movie_to_str(curr->movie);
    strcat(str, movie_str);
    free(movie_str);
    strcat(str, "]");

    return str;
}

