#include "sdt_list.h"
#include <cstdlib>

struct sdt_list *sdt_list_create()
{
    struct sdt_list *list = (struct sdt_list *)malloc(sizeof(struct sdt_list));
    list->max_size = 0;
    list->size = 0;
    list->first_node = NULL;
    list->last_node = NULL;
    return list;
}

void sdt_list_set_max_size(struct sdt_list *list, int max_size)
{
    list->max_size = max_size;
}

int sdt_list_add(struct sdt_list *list, void *data)
{
    // Check the size limitted
    if (list->max_size > 0 && list->max_size < list->size)
        return -1; // Failed to add a new node

    sdt_node *new_node = (sdt_node *)malloc(sizeof(sdt_node));
    new_node->data = data;
    new_node->next_node = NULL;

    // Reset the last node of the list to the new node
    if (list->last_node)
        list->last_node->next_node = new_node;
    list->last_node = new_node;

    // Check to set the first node of the list
    if (!list->first_node)
        list->first_node = new_node;

    // Increase the size
    ++list->size;
    return list->size;
}

struct sdt_node *sdt_list_get_node_at(struct sdt_list *list, int index)
{
    if (index < 0 || index >= list->size)
        return NULL;

    sdt_node *node = list->first_node;
    while (node && index != 0) {
        node = node->next_node;
        --index;
    }
    return node;
}

void *sdt_list_get_data_at(struct sdt_list *list, int index)
{
    sdt_node *node = sdt_list_get_node_at(list, index);
    if (node)
        return node->data;
    return NULL;
}

int sdt_list_remove_first_node(struct sdt_list *list)
{
    sdt_node *node = list->first_node;
    if (node) {
        list->first_node = node->next_node;
        free(node);
        node = NULL;
        --list->size;
        return list->size;
    }

    return -1;
}

int sdt_list_destroy_first_node(struct sdt_list *list)
{
    sdt_node *node = list->first_node;
    if (list->first_node) {
        list->first_node = node->next_node;
        sdt_list_destroy_node_data(node);
        --list->size;
        return list->size;
    }

    return -1;
}

void sdt_list_destroy_node_data(struct sdt_node *node)
{
    void *data = node->data;
    if (data) {
        free(data);
        data = NULL;
    }
    free(node);
    node = NULL;
}

void sdt_list_destroy_list(struct sdt_list *list)
{
    sdt_node *node, *tmp_node;
    node = list->first_node;
    while (node) {
        tmp_node = node;
        node = node->next_node;
        // Release the node
        free(tmp_node);
        tmp_node = NULL;
    }
    // Release the list
    free(list);
    list = NULL;
}

void sdt_list_destroy_list_data(struct sdt_list *list)
{
    sdt_node *node, *tmp_node;
    node = list->first_node;
    while (node) {
        tmp_node = node;
        node = node->next_node;
        // Release the node and node's data
        sdt_list_destroy_node_data(tmp_node);
    }
    // Release the list
    free(list);
    list = NULL;
}
