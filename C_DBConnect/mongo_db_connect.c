#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

int main (int argc, char *argv[])
{
   mongoc_client_t      *client;
   mongoc_database_t    *database;
   mongoc_collection_t  *collection;
   mongoc_cursor_t      *cursor;
   bson_t               *command, reply, *insert, *query;
   const bson_t         *doc;
   bson_error_t         error;
   char                 *str;
   bool                 retval;

   /*
    *
    * Required to initialize libmongoc's internals
    *
    */
   mongoc_init ();

   /*
    *
    * Create a new client instance
    *
    */
   client = mongoc_client_new ("mongodb://0.0.0.0:29000");

   /*
    *
    * Register the application name so we can track it in the profile logs
    *
    * on the server. This can also be done from the URI (see other examples).
    *
    */
   mongoc_client_set_appname (client, "mongodb-connection-status");

 /*
 *
 *      Get a handle on the database "db_name" and collection "coll_name"
 *       
 */
   database = mongoc_client_get_database (client, "database_name");
   collection = mongoc_client_get_collection (client, "database_name", "table_name");
   
   /*
 *
 *       Do work. This example pings the database, prints the result as JSON and
 *       performs an insert        
 */
   command = BCON_NEW ("ping", BCON_INT32 (1));

   retval = mongoc_client_command_simple (client, "admin", command, NULL, &reply, &error);

   if (!retval) {
      fprintf (stderr, "%s\n", error.message);
      return EXIT_FAILURE;
   }

   str = bson_as_json (&reply, NULL);
   printf ("Message %s\n", str);

   bson_destroy (&reply);
   bson_destroy (command);
   
   /*
    * 
    *      Insert one document into given database and collection
    *
    */
    query = bson_new ();
   cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);
   while (mongoc_cursor_next (cursor, &doc)) {
      str = bson_as_json (doc, NULL);
      printf ("%s\n", str);
      bson_free (str);
   }


 /*
 *
 *        Release our handles and clean up libmongoc
 *        
 */
   mongoc_collection_destroy (collection);
   mongoc_database_destroy (database);
   mongoc_client_destroy (client);
   mongoc_cursor_destroy (cursor);
   mongoc_cleanup ();

   return 0;
  }
