/**
  * @file sdt_list.h
  * @brief A simple list implementation
  * @author Nguyen Truong Duong (Raycad)
  * @contact Email: seedotech@gmail.com
  * @contact Skype: raycadrb
  */
#ifndef SDT_LIST_H
#define SDT_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

// Define the node structure of the list's element
struct sdt_node {
    void *data; // Data holder
    struct sdt_node *next_node; // The next node's pointer
};

// Define the list structure of the list
struct sdt_list {
    struct sdt_node *first_node; // The first node of the list
    struct sdt_node *last_node; // The last node of the list

    int max_size; // The limitted size of the list
    int size; // The current size of the list
};

/**
 * @brief Create a new list
 * @return The list pointer
 */
struct sdt_list *sdt_list_create();
/**
 * @brief Set the limitted size of the list
 * @param list: the specific sdt_list pointer
 * @param max_size: the limitted size of the list
 */
void sdt_list_set_max_size(struct sdt_list *list, int max_size);
/**
 * @brief Add new node to the list
 * @param list: the specific sdt_list pointer
 * @param data: the data pointer of the new node
 * @return The new size of the list. Returns -1 if failed, otherwise returns the current size of the list
 */
int sdt_list_add(struct sdt_list *list, void *data);
/**
 * @brief Get the node at the specific index of the list
 * @param list: the specific sdt_list pointer
 * @param index: the specific position need to retrieve the element
 * @return the node at that position. Returns NULL if not success, otherwise returns the node pointer
 */
struct sdt_node *sdt_list_get_node_at(struct sdt_list *list, int index);
/**
 * @brief Get the node at the specific index of the list
 * @param list: the specific sdt_list pointer
 * @param index: the specific position need to retrieve the element
 * @return the node's data at that position. Returns NULL if not success, otherwise returns the node's data pointer
 */
void *sdt_list_get_data_at(struct sdt_list *list, int index);

/**
 * @brief Remove the first node of the list. Note that this just removes the element but does not
 *          remove the node's pointer so you need handle the node pointer to avoid the memory leak
 * @param list: the specific sdt_list pointer
 * @return the current size of the list if success, otherwise returns -1
 */
int sdt_list_remove_first_node(struct sdt_list *list);
/**
 * @brief Destroy the first node of the list. Note that this just removes both the element and the node's pointer
 * @param list: the specific sdt_list pointer
 * @return the current size of the list if success, otherwise returns -1
 */
int sdt_list_destroy_first_node(struct sdt_list *list);
/**
 * @brief Release both the node pointer and the its data
 * @param list: the specific sdt_node pointer
 */
void sdt_list_destroy_node_data(struct sdt_node *node);
/**
 * @brief Release all node pointers of the list and itself. Note that if the node data of the list are pointers you have to
 *          manage those pointers to avoid the memory leak. You can use function sdt_list_destroy_list_data to release all
 * @param list: the specific sdt_node pointer
 */
void sdt_list_destroy_list(struct sdt_list *list);
/**
 * @brief Release all data include node, node's data, list pointers of the given list
 * @param list: the specific sdt_node pointer
 */
void sdt_list_destroy_list_data(struct sdt_list *list);
#ifdef __cplusplus
}
#endif

#endif // SDT_LIST_H
