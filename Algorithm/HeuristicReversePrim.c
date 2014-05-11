//
//  cluster.c
//  google_code_for_india
//
//  Created by Huzefa on 5/10/14.
//  Copyright (c) 2014 Huzefa. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NO_OF_BUSES 2 /// No of clusters reqd
#define NO_OF_SCHOOLS 3
int flag[NO_OF_SCHOOLS]={0};

int GetNodeWithMaxDistance(int distanceFromKitchen[NO_OF_SCHOOLS]){
    int max_distance=0;
    int id=0;
    for(int i=0;i<NO_OF_SCHOOLS;i++){
        if(distanceFromKitchen[i]>max_distance){
            max_distance = distanceFromKitchen[i];
            id =i;
        
        }
    }
    return id;
}
typedef struct dist_Weight{
    int nodeNumber;
    int distance;
    struct dist_Weight *main;
    struct dist_Weight *next;
}dist_weight;

void getAnotherFarthestNode(dist_weight **headNode,int distanceFromKitchen[NO_OF_SCHOOLS]){
    int isGreater=0;
    int max_distance=0;
    dist_weight *current;
    dist_weight *head = *headNode;
    int id=0;
    for(int i=0;i<NO_OF_SCHOOLS;i++){
        if(flag[i]==0){
            if(distanceFromKitchen[i]>max_distance){
                current=head;
                while(current->next!=NULL){
                    if(distanceFromKitchen[i]<current->distance){
                        isGreater=1;
                        break;
                    }
                    current=current->next;
                }
                if(isGreater){
                    isGreater=0;
                    continue;
                }
                current=head;
                while(current->next!=NULL){
                    current=current->next;
                }
                current->next=malloc(sizeof(dist_weight));
                current->next->nodeNumber = i;
                current->next->distance = distanceFromKitchen[i];
                current->next->next=NULL;
                flag[i]=1;
            }
            //flag[i]=1;
        }
    }
}

dist_weight *searchForNode(dist_weight *head, int maxID){
    dist_weight *current = head;
    while(current!=NULL){
        if(current->nodeNumber==maxID)
            return current;
        current=current->next;
    }
    return  NULL;
}

void startFormCluster(dist_weight **headNode,int distanceFromKitchen[NO_OF_SCHOOLS]){
    struct dist_Weight *head=*headNode;
    struct dist_Weight *current;
    dist_weight *internalMain;
    int maxDistance=0;
    int maxID=0;
    for(int i=0;i<NO_OF_SCHOOLS;i++){
        current=head;
        if(flag[i]==0){
            while(current!=NULL){
                if(current->distance<distanceFromKitchen[i]){
                    maxID=current->nodeNumber;
                }
                current=current->next;
            }
        }
        current = searchForNode(head,maxID);
        if(current->main==NULL){
            current->main=malloc(sizeof(dist_weight));
            internalMain=current->main;
        }else{
            internalMain = current->main;
            while(internalMain->next!=NULL){
                internalMain=internalMain->next;
            }
            internalMain->next=malloc(sizeof(dist_weight));
            internalMain=internalMain->next;
        }
        internalMain->next=NULL;
        internalMain->nodeNumber=i;
        flag[i]=1;
    }
    return;
}
int main(){
    int farthestNode=-1;
    dist_weight *head=NULL;
    dist_weight *current=NULL;
    printf("Clustering starting\n");
    int distanceFromKitchen[NO_OF_SCHOOLS]={1,4,5};
    int distanceBetweenSchool[NO_OF_SCHOOLS][NO_OF_SCHOOLS]={
        {0,2,8},
        {2,0,9},
        {8,9,0},
//        {2,0,3,8,5,0},
//        {0,3,0,0,7,0},
//        {6,8,0,0,9,0},
//        {0,5,7,9,0,0},
//        {5,0,0,0,0,0},
    };
    
    farthestNode =  GetNodeWithMaxDistance(distanceFromKitchen);
    head=malloc(sizeof(dist_weight));
    head->nodeNumber = farthestNode;
    head->distance = distanceFromKitchen[farthestNode];
    head->next=NULL;
    flag[farthestNode]=1;
    for(int j=0;j<NO_OF_BUSES-1;j++){
        getAnotherFarthestNode(&head,distanceFromKitchen);
    }
    
    startFormCluster(&head,distanceFromKitchen);
    current=head;
    while(current!=NULL){
        printf("Node number : %d\n",current->nodeNumber);
        while(current->main!=NULL){
            printf("Inside: %d\n\n",current->main->nodeNumber);
            current->main=current->main->next;
        }
        current=current->next;
    }
    return 0;
}