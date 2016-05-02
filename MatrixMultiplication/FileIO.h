/*
 * Copyright (c) 2011-2014 Abelardo Lopez Lagunas
 *
 * File name: FileIO.c
 *
 * Author:  Abelardo Lopez Lagunas
 *
 * Purpose: Support routines that handle reading ASCII files
 *
 * References:
 *          Based on my own code, but won't be surprised if it is
 *          similar to other code out there
 *
 * Restrictions:
 *          All functions return (-1) in case something went wrong
 *
 * Revision history:
 *          Feb  4 15:15 2011 -- File created
 *
 *          May 22 09:13 2012 -- Added recognition of negative numbers.
 *
 *          Jan 30 15:44 2014 -- Added recognition of strings
 *
 * Error handling:
 *          None
 *
 * Notes:
 *          Support routine that reads an ASCII file and returns an
 *          integer value skiping over non-numeric data.
 *
 */

/**************************************************************
 *             Declare the function prototypes                *
 **************************************************************/

int    GetInt    (FILE *fp);
char * GetString (FILE *fp);

