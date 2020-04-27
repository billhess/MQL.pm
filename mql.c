#include "mql.h"

#define LINEBUFFERSIZE       65536
#define DEFAULT_OUTPUT_SIZE  5242880
#define DEFAULT_ERROR_SIZE   1048576


int MQL_output_size = DEFAULT_OUTPUT_SIZE;
int MQL_error_size  = DEFAULT_ERROR_SIZE;


int  current_session;
int  have_output;
int  have_error;



int MQL_Open(char *path, char *exe, char *bootstrap) {
   int session;
   session = mqlOpen2(path, exe, bootstrap);
   return session;
}


int MQL_Close(int session) {
   return mqlClose2(session);
}


int MQL_OpenLog(char *path) {
   return mqlOpenLog(path);
}


int MQL_CloseLog(void) {
   return mqlCloseLog();
}


int MQL_Execute(int session, char *mql)
{
   int rc;

   have_output = 0;
   have_error  = 0;

   
   MQL_SetBuffers(MQL_output_size, MQL_error_size);
   
   current_session = session;
   
   rc = mqlExecute2(session, mql);

   if(rc != MQLERROR) {
      rc = mqlCallback2(session,
                        outputCallback, NULL,
                        errorCallback,  NULL);
   }

   
   return rc;
}



int outputCallback(void *outData)
{
   char  buffer[LINEBUFFERSIZE] = "";
   int rc = 0;
   
   if(mqlOutput2(current_session, buffer, LINEBUFFERSIZE)) {

      if(MQL_output_size < (strlen(MQL_output) + LINEBUFFERSIZE)) {
         printf("ERROR: MQL output buffer too small - %d\n",
                MQL_output_size);

         return MQLERROR;
      }

      
      if(! have_output) {
         strcpy(MQL_output, buffer);
         have_output = 1;
      }
      else {
         strcat(MQL_output, buffer);
      }
   }
   
   return MQLOK;
}



int errorCallback(void *errData)
{
   char  buffer[LINEBUFFERSIZE] = "";

   if(mqlError2(current_session, buffer, LINEBUFFERSIZE)) {

      if(MQL_error_size < (strlen(MQL_error) + LINEBUFFERSIZE)) {
         printf("ERROR: MQL error buffer too small - %d\n",
                MQL_error_size);

         return MQLERROR;
      }

       
      if(! have_error) {
         strcpy(MQL_error, buffer);
         have_error = 1;
      }
      else {
         strcat(MQL_error, buffer);
      }
   }   
   
   return MQLOK;
}




void MQL_SetBuffers(int output_size, int error_size)
{
   if(! MQL_output || (MQL_output_size != output_size)) {
      MQL_output_size = output_size;

      if(MQL_output)
         free(MQL_output);
    
      MQL_output = (char *)malloc(sizeof(char) * MQL_output_size);
  }


  if(! MQL_error || (MQL_error_size != error_size)) {
     MQL_error_size = error_size;
    
     if(MQL_error)
       free(MQL_error);
    
     MQL_error = (char *)malloc(sizeof(char) * MQL_error_size);    
  }


  MQL_ClearBuffers();
}



void MQL_ClearBuffers(void)
{
   memset(MQL_output, 0, MQL_output_size);
   memset(MQL_error,  0, MQL_error_size);
}



void MQL_SetBufferSize(int output_size, int error_size)
{
    if(output_size > 0)
        MQL_output_size = output_size;
    else
        MQL_output_size = DEFAULT_OUTPUT_SIZE;
    

    if(error_size > 0)
        MQL_error_size = error_size;
    else
        MQL_error_size = DEFAULT_ERROR_SIZE;
}
