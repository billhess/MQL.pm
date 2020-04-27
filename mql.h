//----------------------------------------------------------------------
// MQL SWIG Interface and Header File
//----------------------------------------------------------------------

#ifdef SWIG
%module MQL
%{
   int errno;  /* Added here since it was not added to _wrap.c */
   
   char *MQL_output;  /* 5 MB default */
   char *MQL_error;   /* 1 MB default */
%}
#endif


#ifndef _MQL_H_
#define _MQL_H_


//----------------------------------------------------------------------
// Define preprocessor vars for compiling MQLIO API only
//----------------------------------------------------------------------
#ifndef SWIG

#if defined (_UNICODE) && (!defined(UNICODE))
#define UNICODE
#endif

#ifdef WIN32
#define STATIC static
#else
#define STATIC      
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// #include <process.h>
// #include <time.h>

#ifdef WIN32
#include <tchar.h>
#include <time.h>
#endif

#include "mqlio.h"

#endif



//----------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------
extern char *MQL_output;  /* 5 MB default */
extern char *MQL_error;   /* 1 MB default */





//----------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------
extern int  MQL_Open(char*, char*, char*);
extern int  MQL_Close(int);
extern int  MQL_OpenLog(char *path);
extern int  MQL_CloseLog(void);
extern int  MQL_Execute(int, char*);
extern void MQL_SetBuffers(int, int);
extern void MQL_ClearBuffers(void);
extern void MQL_SetBufferSize(int, int);
extern int  outputCallback(void *outData);
extern int  errorCallback(void *errData);


#endif // _MQL_H_




//----------------------------------------------------------------------
// Matrix One MQLIO API Constants
//----------------------------------------------------------------------
#ifdef SWIG


#endif



//----------------------------------------------------------------------
// Perl wrapper functiosn
//----------------------------------------------------------------------
#ifdef SWIG
%pragma(perl5) include="mql.ipl"
#endif

