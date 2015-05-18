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
#include <ctype.h>

struct icmpCount {
    int totalRecv;
    int rtt;
    int minRtt;
    int maxRtt;
    char remIp[24];
    struct icmpCount *link;
};

typedef struct icmpCount ic;
ic *str_split(char*, const char);

int main(int argc, const char * argv[]) {
    int c;
    char *remoteHost;
    extern char *optarg;
    extern int optind, optopt, opterr;
    ic *addrs;
    const char delim = ',';
    
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
    
    addrs = str_split(optarg, delim);
    
    while (addrs) {
        printf("remote host is:%s\n", addrs->remIp);
        addrs = addrs->link;
    }
    return 0;
}
    //parse the IP addresses and put them into the record structs
ic* str_split(char* a_str, const char a_delim)
{
    ic *addrs;
    ic *head = NULL;
    char *token = NULL;
    while ((token = strtok(a_str, &a_delim))) {
        while (isspace(*token)) {
            token++;
        }
        addrs = (ic*)malloc(sizeof(struct icmpCount));
        strcpy(addrs->remIp, token);
        addrs->link = NULL;
        
        if (head == NULL) {
            head = addrs;
        }
        else {
            addrs->link = head;
            head = addrs;
        }
        a_str = NULL;
    }
    return head;
}