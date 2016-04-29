#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
   char* username;
   int len;
   if (argc != 2)
   {
	  fprintf(stderr, "Usage: %s <name>\n", argv[0]);
	  return -1;
   }
   username = malloc(250);
   username[0] = '\0';
   
   len = strlen(argv[1]);

   if (len > 250)
   {
	  username = realloc(username, len);
   }

   strcat(username, "Hello ");
   strcat(username, "user : ");
   strcat(username, argv[1]);
   strcat(username, "\n");

   printf("%s", username);

   free(username);
   return 0;
}
