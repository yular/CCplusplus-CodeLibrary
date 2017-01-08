#include <my_global.h>
#include <mysql.h>


void finish_with_error(MYSQL *con){

  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void finish_with_result(MYSQL_RES *result){

  MYSQL_ROW row;

  int i, num_fields = mysql_num_fields(result);

  while ((row = mysql_fetch_row(result)))
  {
      for(i = 0; i < num_fields; i++)
      {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
      puts("");
  }

  mysql_free_result(result);

}


int main(int argc, char **argv){

  printf("MySQL client version: %s\n", mysql_get_client_info());

  MYSQL *con = mysql_init(NULL);
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;
  
  int i, mysql_num_fields;

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "host_ip", "user_name", "password", NULL, 0, NULL, 0) == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      mysql_close(con);
      exit(1);
  }

  if (mysql_query(con, "use towergirl"))
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "show tables"))
  {
      finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  finish_with_result(result);

  if (mysql_query(con, "select * from user_account"))
  {
      finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  finish_with_result(result);

  mysql_close(con);
  return 0;
}
