#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void save(int file, char *input){
    
    write(file, input, strlen(input)); 

}


void main(int argc, char *argv[]){
    if(argc<3){
        printf(1,"Incorrect Usage!\nUsage: %s %s",argv[0],"<filename> sentance to be written");
        exit();
    }


    int file = open(argv[1], O_CREATE | O_WRONLY);
    char *newline = (char*) "\n";
    char *space = (char*) " ";

    for(int i=2;i<argc;i++){
        save(file,argv[i]);
        if(i<argc-1)
            save(file,space);
    }
    save(file,newline);
    close(file);

    

    exit();
}