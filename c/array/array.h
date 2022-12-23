#ifndef SPICE_LLIST_H
#define SPICE_LLIST_H

char **create_char_matrix(int rows, int cols);

void print_char_matrix(char **matrix, int rows, int cols);

void destroy_matrix(char **matrix, int rows);

#endif				/* SPICE_LLIST_H */
