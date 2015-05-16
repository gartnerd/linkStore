//
//  main.c
//  linkStore
//
//  Created by David M Gartner on 2015-05-16.
//  Copyright (c) 2015 David. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct icmpCount {
    int totalRecv;
    int rtt;
    int minRtt;
    int maxRtt;
    char *remIp;
    struct icmpCount *link;
};

typedef struct icmpCount ic;
char **str_split(char*, const char);

int main(int argc, const char * argv[]) {
    int c;
    char *remoteHost;
    extern char *optarg;
    extern int optind, optopt, opterr;
    char** tokens;
    
    // insert code here...
    printf("Hello, World!\n");
    
    //create a list of locations to ping
    //from command line arguments
    while ((c = getopt(argc, argv, ":h:")) != -1) {
        switch (c) {
            case 'h':
                remoteHost = optarg;
                break;
            case ':':
                printf(" -%c requires ip address\n", optopt);
                break;
            case '?':
                printf("unknown arg %c\n", optopt);
                break;
        }
    }
    
    printf("remote host addresses %s\n", optarg);
    
    tokens = str_split(optarg, ',');
    
    if (tokens){
        int i;
        for (i = 0; *(tokens + i); i++){
            printf("month=[%s]\n", *(tokens + i));
            free(*(tokens + i));
        }
        printf("\n");
        free(tokens);
    }
    
    return 0;
}
    //parse the IP addresses and put them into the record structs
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
        
    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
        
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
        
    /* Add space for terminating null string so caller
    knows where the list of returned strings ends. */
    count++;
        
    result = malloc(sizeof(char*) * count);
        
    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
            
        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
        
    return result;
}