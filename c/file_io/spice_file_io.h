/**
 * @file spice_file_io.h
 * @author CW2 Kyle Spicer
 * @brief header file that contains declarations and doc strings for functions
 * within spice_file_io.c
 * @version 0.1
 * @date 2023-01-09
 * @cite - if there are citations, they are located within the doc string for 
 * specific function
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SPICE_FILE_IO
#define SPICE_FILE_IO

#include <stdio.h>

/**
 * @brief opens and checks file for the following: if file exists, open file, 
 * verify file isn't empty by retrieving file size. Responsibility of user to
 * properly close file.
 * 
 * 
 * @param file_name 
 * @return FILE* - returns file pointer
 */
FILE *file_open_and_verify(char *file_name);

/**
 * @brief utilizes sys/stat.h to check file size in bytes
 * file is closed prior to function terminating
 * 
 * @param file_name 
 * @return int 
 */
int file_size_bytes(char *file_name);

/**
 * @brief cycles through all lines in file and returns the count found
 * file is closed prior to function terminating
 * 
 * @param file_name 
 * @return int 
 */
int file_line_count(char *file_name);

/**
 * @brief specific function to determine first line in file that has integers
 * 
 * @param filename 
 * @return int - returns line number that has integers (ex. coordinates in csv)
 */
int file_line_integers_begin(char *filename);

/**
 * @brief prints informative usage statement
 * 
 */
void display_usage_statement(void);

/**
 * @brief reads the first line of a CSV file and returns the amount of bytes
 * 
 * @param file_name 
 * @return int 
 */
int size_of_first_line(char *file_name);

/**
 * @brief Accepts a string of potential year and verifies it is a legitimate
 * four digit year within a specified range.
 * 
 * @param string_of_int - string of potential year
 * @return true - if good year
 * @return false - if bad year
 */
bool check_good_year(char *string_of_int);

#endif				/* SPICE_FILE_IO */
/* end of file */
