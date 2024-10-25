#include "defs.h"
 
/*
    Intializes a Hunter struct.
    in: house        - Intializes the sharedEvidence and residingRoom and sharedReason fields in the Hunter structs with a pointer to the sharedEvidenceList in House struct and the head node of its room list and a pointer to the sharedReason in the House struct respectively.
    out: hunter   - The struct that will be intialized.
    in: evidenceType - Intializes the collectibleEvidence field in the hunter Struct with this value.
*/
void hunterInit(struct House* house, struct Hunter* hunter, enum EvidenceType evidenceType) {
    hunter->collectibleEvidence = evidenceType;
    hunter->sharedEvidence      = &house->sharedEvidenceList;
    hunter->residingRoom        = house->rooms.head->data;
    hunter->residingRoom->numHunters++;
    hunter->boredomTicker       = 0;
    hunter->fearTicker          = 0;
    hunter->reason              = LOG_UNKNOWN;
}


/*
    Moves the hunter to a random connected room relative to its former residing room.
    in/out: hunter - Pointer to the Hunter struct in order to change its current residingRoom and simulate it moving around the house.
*/
void hunterMove(struct Hunter* hunter) {
    
    struct Room* currentRoom = hunter->residingRoom;

    sem_wait(&hunter->residingRoom->mutex);
    hunter->residingRoom->numHunters--;
    sem_post(&hunter->residingRoom->mutex);
    
    struct Rooms* connectedRooms = &currentRoom->connectedRooms;
    hunter->residingRoom = iteRooms(connectedRooms);

    sem_wait(&hunter->residingRoom->mutex);
    hunter->residingRoom->numHunters++;
    sem_post(&hunter->residingRoom->mutex);

    l_hunterMove(hunter->name, hunter->residingRoom->name);

    if(strcmp(hunter->residingRoom->name, "Van") == 0) 
    {
        hunter->collectibleEvidence = randEquipment();
        l_hunterChangeEquip(hunter->name, hunter->collectibleEvidence);
    }
}

/*
    Simulates the hunter collecting evidence that matches the collectibleEvidence in the struct in its residingRoom evidenceList.
    in/out: hunter - Pointer to the Hunter struct in order to remove the evidence picked by the hunter in the evidenceList on the residing room and adding it to the sharedEvidence shared by all hunters structs.
*/
void hunterCollect(struct Hunter* hunter) {

    RoomType* residingRoom = hunter->residingRoom;
    EvidenceListType* evidenceList = &residingRoom->evidenceList;

    EvidenceNodeType* currNode = evidenceList->head;

    while(currNode->data->name != hunter->collectibleEvidence) {
        currNode = currNode->next;
        if(currNode == NULL) return;
    }

    if(!isEvidenceInList(hunter->sharedEvidence, currNode->data->name)) {

        addEvidence(hunter->sharedEvidence, currNode->data);

        l_hunterCollect(hunter->name, currNode->data->name, hunter->residingRoom->name);

        removeEvidence(evidenceList, currNode->data);
        
    }
    

   

}

/*
    Simulates the hunter reviewing its sharedEvidence whether its sufficient or not.
    in/out: hunter - Pointer to the Hunter struct to change its sharedReason, which is shared between all hunters, if the evidences are sufficient else nothing happens before being logged as an event into the terminal.
*/
void hunterReview(struct Hunter* hunter) {

    if(hunter == NULL) return;

    if(hunter->sharedEvidence->size == NUM_EVIDENCE) {
        hunter->reason  = LOG_SUFFICIENT;
        l_hunterReview(hunter->name, hunter->reason);
    } else  {
        l_hunterReview(hunter->name, LOG_INSUFFICIENT);
    }  
}

/*
    Simulates the hunter exiting the simulation if its either afraid, bored or has sufficient evidences.
    in/out: hunter - Pointer to the Hunter struct inorder to log it event if it ever exits.
*/
void hunterExit(struct Hunter* hunter) {
    if(hunter->reason == LOG_SUFFICIENT) {
        l_hunterExit(hunter->name, LOG_EVIDENCE);
        sem_wait(&hunter->residingRoom->mutex);
        hunter->residingRoom->numHunters--;
        sem_post(&hunter->residingRoom->mutex);
    }

               
}



