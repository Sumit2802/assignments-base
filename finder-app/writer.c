#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <stdint.h>

int main(int argc, char *argv[]){
openlog("writer", LOG_PID | LOG_NDELAY, LOG_USER); //setup syslog logging
if(argc !=3){
	fprintf(stderr, "Usage: %s <string> <file>\n", argc[0]);
	exit(EXIT_FAILURE);
}

//Open the file for writing
FILE *file = fopen(argv[2], "w");
if(file==NULL){
syslog(LOG_ERR, "Failed to open file: %s", argv[2]);
perror("fopen");
exit(EXIT_FAILURE);
}
//write string to the file
if(fprintf(file, %s, argv[1])<0)){
syslog(LOG_ERR, "Failed to write to file: %s", argv[2]);
perror("fprintf");
fclose(file);
exit(EXIT_FAILURE)
}

//Close the file
fclose(file);

//Log the successful write operation
syslog(LOG_DEBUG, "Writing \"%s\" to %s", argv[1], argv[2]);
return EXIT_SUCCESS;
}
