#include "linked_list.h"
#include "iterator.h"

link_t *link_create(int element, link_t *next)
{
    link_t *new = calloc(1,sizeof(link_t));
    new->element = element;
    new->next = next;
    return new;
}

ioopm_list_t *ioopm_linked_list_create()
{
    ioopm_list_t *lista = calloc(1,sizeof(ioopm_list_t)); // allokerar plats för en tom lista
    lista->last = NULL;
    lista->first =NULL;
    lista->size = 0; // sätter liststorleken till 0
    return lista;
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
   
    link_t *newlast = link_create(value, NULL); // gör nya länken
    if(list->first == NULL) // om listan är tom måste vi oxå peka om firstpekaren
    {
        list->last = newlast;
        list->first = list->last;
        
    }
    else // om den inte är tom
    {
        list->last->next = newlast; //lägg till newlast på sista platsen
        list->last = newlast; //peka om last pekaren
    }
    list->size++;
}
    

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    link_t *newfirst = link_create(value, list->first);
    if (list->last == NULL) // om listan är tom så vi oxå flytta om lastpekaren
    {
        list->last = newfirst;
        list->first = list->last;
    }
    else
    {
        newfirst->next =list->first; // gör att nya elem pekar på gammla first
        list->first = newfirst; // pekar om firstpekaren
    }
    list->size++;
}

link_t *find_link(ioopm_list_t *item, int index) // hittar länken på givet index
{
    link_t *current = item->first;
    while (index > 0)
    {
    current = current->next;
    index--;
    }
   return current;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{   
    
    if (index < 0 || index > list->size)
    {
        printf("index out of range, insert\n");
    }
    else if (index == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else if (index == list->size)
    {
        ioopm_linked_list_append(list, value);
    }
    else
    {   link_t *prev = find_link(list, index-1); // hittar länk på index innan länken vi vill inserta
        prev->next= link_create(value, prev->next); // skapar en ny länk där vi vill hitta den
        list->size++;
    }
    
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
   
    if(index < 0 || index > list->size)
    {
        printf("index out of range,remove\n");
        return 0;

    }
    if(index == 0) //remove first item
    {   
        link_t *first = list->first;
        link_t *new_first = list->first->next; // pekare till nya första
        int value = list->first->element;
        list->first = new_first;
        free(first);
        list->size--;
        return value;
    }
    if(index == (list->size - 1)) // sista elem
    {
        link_t *newlast = find_link(list, index-1); // hitta elem innan den vi vill ta bort
        link_t *last = list->last;
        list->last = newlast;
        int value = last->element;
        free(last);
        list->size--;
        return value;
    }
    else
    {
        link_t *link_before = find_link(list, index-1);
        link_t *link_remove = link_before->next;
        link_t *link_after = link_remove->next;
        int value = link_remove->element;
        link_before->next = link_after;
        free(link_remove);
        list->size--;
        return value;
    }
    
    
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    
    if(index < 0 || index > list->size)  
    {
        printf("index out of range\n");
        return 0;

    }
    if(index == 0) //första elem
    {
        return list->first->element;
    }
    if (index == (list->size-1)) //sista elem
    {
        return list->last->element;
    }
    else
    {
        link_t *wanted = find_link(list, index); // hitta länken på givet index
        return wanted->element;
    }
    
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    link_t *current = list->first; // ställer mig i första länken

    while (current != NULL) 
    {
    if(current->element == element)
    {
        return true;
    }
    else
    {
        current = current->next; // gå till nästa
    }
    }
    
    return false;
}   

int32_t ioopm_linked_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    if(list->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    link_t *current = list->first; // ställer oss i första elementet
    while(current != NULL) 
    {
        link_t *temp = current; // gör en temp som vi sätter till current
        current = current->next; // sätter current till nästa elem
        free(temp); // gör free på next
    }
    list->size = 0;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    ioopm_linked_list_clear(list);
    free(list);
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    link_t *current = list->first;
    int index = 0;
    while (current != NULL) 
    {
        if (prop(index, current->element, extra))
        {
            return false;
        }
        current= current->next;
        index++;
    }
    return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    link_t *current = list->first;
    int index = 0;
    while (current != NULL)
    {
        if (prop(index, current->element, extra))
        {
            return true;
        }
        current= current->next;
        index++;
    }
    return false;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    link_t *current = list->first;
    int index = 0;
    while (current != NULL)
    {
        fun(index, &current->element, extra);
        current = current->next;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// iterator
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ioopm_list_iterator_t *list_iterator(ioopm_list_t *list)
{
  ioopm_list_iterator_t *result = calloc(1, sizeof(ioopm_list_iterator_t));

  result->current = list->first;
  result->list = list; /// Iterator remembers where it came from

  return result; 
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
  iter->current = iter->list->first;
}

int ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{
  link_t *to_remove = iter->current; /// Cache result

  iter->current->next = to_remove->next;  /// Move forward
  int result = to_remove->element;

  free(to_remove); /// Remove link

  return result;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
 if(iter->current)
    {
        return iter->current->next != NULL; 
    }
 return false;
}

bool ioopm_iterator_next(ioopm_list_iterator_t *iter, int *value) // venne om funkar
{
    if(ioopm_iterator_has_next(iter))
    {
        iter->current = iter->current->next;
        *value = iter->current->element;
        return true;
    }
   return false; 
}

int call_ioopm_iterator_next(ioopm_list_iterator_t *iter) // venne om funkar
{
    int value = 0;
    bool sucsess = ioopm_iterator_next(iter, &value);

    if(sucsess)
    {
        return value;
    }
    printf("Has no next");
    return 0;
    
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
  free(iter);
}

int ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  return iter->current->element; 
}