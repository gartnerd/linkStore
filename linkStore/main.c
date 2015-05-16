//
//  main.c
//  linkStore
//
//  Created by David M Gartner on 2015-05-16.
//  Copyright (c) 2015 David. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

struct icmpCount {
    int totalRecv;
    int rtt;
    int minRtt;
    int maxRtt;
    char *remIp;
    struct icmpCount *link;
};

typedef struct icmpCount ic;

int main(int argc, const char * argv[]) {
    int c;
    char *remoteHost;
    extern char *optarg;
    extern int optind, optopt, opterr;
    
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
    
    //parse the IP addresses and put them into the record structs
    
    return 0;
}
