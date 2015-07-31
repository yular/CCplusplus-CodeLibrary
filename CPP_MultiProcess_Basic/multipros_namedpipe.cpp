/*
* Read from Named Pipe
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

//mkfifo("myfifo","rw");

int main(){
	FILE *in_file;
	int cnt = 1;
	char buf[80];
	in_file = fopen("mypipe","r");
	if(in_file == NULL){
		printf("Error in fopen.\n");
		exit(1);
	}
	while((cnt = fread(buf, 1, 80, in_file)) > 0)
		printf("Receive from pipe: %s\n",buf);
	fclose(in_file);
	return 0;
}

/*
* Write to Named Pipe
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

//mkfifo("myfifo","rw");

int main(){
        FILE *out_file;
        int cnt = 1;
        char buf[80];
        out_file = fopen("mypipe","r");
        if(out_file == NULL){
                printf("Error in fopen.\n");
                exit(1);
        }
	sprintf(buf, "this is test data for the named pipe example\n");
	fwrite(buf, 1, 80, out_file);
        fclose(out_file);
        return 0;
}

