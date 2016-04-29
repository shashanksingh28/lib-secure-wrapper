#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 500

struct user
{
   int userid;
   int permissions;
   char username[SIZE];
};

int main(int argc, char** argv)
{
   struct user* new_user;

   if (argc != 4)
   {
	  fprintf(stderr, "Usage: %s <name> <userid> <permissions>\n", argv[0]);
	  return -1;
   }
   new_user = malloc(sizeof(struct user));

   new_user->userid = atoi(argv[2]);
   new_user->permissions = atoi(argv[3]);
   strcpy(new_user->username, argv[1]);

   printf("New user created:\n");

   printf("User id: %d\n", new_user->userid);
   printf("Permissions: %d\n", new_user->permissions);
   printf("User Name: %s\n", new_user->username);

   free(new_user);
   return 0;
}
