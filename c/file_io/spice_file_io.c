/**
 * @file spice_file_io.c
 * @author CW2 Kyle Spicer
 * @brief library that contains functions for file input/output operations.
 * 
 * @date 2023-01-09
 * 
 * @copyright Copyright (c) 2023
 * 
 * @cite 1. Utilized the following link to understand how to properly implement 
 * 		 sys/stat.h to capture file information : 
 * 		 https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/sys/stat.h
 * 
 */

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "spice_file_io.h"

static int file_verify_not_empty(FILE * fp)
{
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	// file is empty
	if (0 == size) {
		printf("File is empty.\n");
		return 0;
	}

	else if (0 < size) {
		return 1;
	}
	return 0;
}

FILE *file_open_and_verify(char *file_name)
{
	// ABCs 
	if (!file_name) {
		return NULL;
	}

	FILE *file = fopen(file_name, "r");
	if (!file) {
		return NULL;
	}

	int file_size = file_verify_not_empty(file);

	if (0 == file_size) {
		return NULL;
	} else {
		return file;
	}
}

/**
 * @brief function to determine the size of the file in bytes.
 * 
 * @param file_name 
 * @return int - returns size of bytes or -1 on error.
 */
int file_size_bytes(char *file_name)
{
	if (!file_name) {
		return -1;
	}

	struct stat file_stats;

	// stat() returns 0 on successful operation
	if (0 == stat(file_name, &file_stats)) {
		return file_stats.st_size;
	}

	return -1;
}

int file_line_count(char *file_name)
{
	if (!file_name) {
		return -1;
	}

	char buff[256];
	int line_count = 0;

	FILE *fp = fopen(file_name, "r");

	if (!fp) {
		return -1;
	}
	// using fgets to determine number of lines within file
	while (NULL != fgets(buff, 256, fp)) {
		line_count++;
	}

	fclose(fp);

	return line_count;
}

/**
 * @brief find
 * 
 * @param filename 
 * @return int 
 */
int file_line_integers_begin(char *filename)
{

	if (!filename) {
		return -1;
	}

	char buff[256];
	int line_count = 0;

	FILE *fp = fopen(filename, "r");
	while (NULL != fgets(buff, 256, fp)) {
		line_count++;
		if (isdigit(*buff)) {
			break;
		}
	}
	fclose(fp);
	return line_count;

}

/**
 * @brief function that reads the size (in bytes) of only the first line in a file
 * 
 * @param file_name 
 * @return int - returns size of first line in file, in bytes
 */
int size_of_first_line(char *file_name)
{
	if (!file_name) {
		return -1;
	}

	int c = 0;

	FILE *fp = fopen(file_name, "r");
	if (!fp) {
		return -1;
	}
	while ((c = fgetc(fp)) != '\n' && c != EOF) {
		c++;
	}

	fclose(fp);
	return c;

}

/**
 * @brief displays informative usage message to user
 * 
 */
void display_usage_statement(void)
{
	const char *message = "\n---------- Program Help Menu ----------\n"
	    "\nUsage: ./bacon -f [file] -args [argument format] \n"
	    "\nCommand Line Arguments:\n"
	    "\n\tCOMMAND \t   ARGUMENT FORMAT \t DESCRIPTION\n"
	    "\t-f / --file \t   \"input file\" \t (alternate input file)\n"
	    "\t-c / --cast \t   \"Movie Title\" YEAR \t (shows cast of movie)\n"
	    "\t-m / --movieinfo   \"Movie Title\" YEAR \t (show rating/genre of movie)\n"
	    "\t-r / --roles \t   \"Actor\" \t\t (displays films actor has been in)\n"
	    "\t-s / --stats \t   \"Actor\" \t\t (connectivity of actor)\n"
	    "\t-d / --distance    \"Actor A\" \"Actor B\" \t (displays actor->movie->actor relationship)\n"
	    "\n\t-f / --help \t (shows informative help menu)\n"
	    "\nExample Usages:\n"
	    "\t ./bacon -f file.txt -c \"The Hangover\" 2008 \n"
	    "\t ./bacon -f file.txt --roles \"Adam Sandler\" \n"
	    "\t ./bacon -f file.txt -d \"Adam Sandler\" \"Kevin Bacon\" \n"
	    "\n------------ End Help Menu ------------\n\n";

	fprintf(stdout, "%s", message);
}

/**
 * @brief Accepts a string of potential year and verifies it is a legitimate
 * four digit year within a specified range.
 * 
 * @param string_of_int - string of potential year
 * @return true - if good year
 * @return false - if bad year
 */
bool check_good_year(char *string_of_int)
{
	if (!string_of_int) {
		return false;
	}
	if (!isdigit(*string_of_int)) {
		return false;
	}
	if (4 != strlen(string_of_int)) {
		return false;
	}
	char *remaining = NULL;
	long year = 0;
	year = strtol(string_of_int, &remaining, 10);
	if (1825 > year || 2023 < year) {
		return false;
	}
	return true;
}

/* end of file */
