#include "defs.h"

/*
    To intialize the ghost struct with all of its given fields.
    in: house - Getting a random room from a pointer to a house struct and ensuring its not a van in order to spawn the ghost in it
    in/out: ghost - Pointer to the Ghost struct to be intialized.
*/
void ghostInit(struct House* house, struct Ghost* ghost) {

    RoomType* spawnRoom = iteRooms(&house->rooms);

    while(spawnRoom == house->rooms.head->data) 
    {
        spawnRoom = iteRooms(&house->rooms);
    }

    ghost->residingRoom  = spawnRoom;
    ghost->residingRoom->ghost = ghost;
    ghost->ghostType     = randomGhost();
    ghost->boredomTicker = 0;

    initEvidenceList(&ghost->evidences);

    if(ghost->ghostType == POLTERGEIST) {
        addEvidence(&ghost->evidences, createEvidence(EMF));
        addEvidence(&ghost->evidences, createEvidence(TEMPERATURE));
        addEvidence(&ghost->evidences, createEvidence(FINGERPRINTS));
    }
    else if(ghost->ghostType == BANSHEE) {
        addEvidence(&ghost->evidences, createEvidence(EMF));
        addEvidence(&ghost->evidences, createEvidence(TEMPERATURE));
        addEvidence(&ghost->evidences, createEvidence(SOUND));
    }
    else if(ghost->ghostType == BULLIES) {
        addEvidence(&ghost->evidences, createEvidence(EMF));
        addEvidence(&ghost->evidences, createEvidence(FINGERPRINTS));
        addEvidence(&ghost->evidences, createEvidence(SOUND));
    }
    else if(ghost->ghostType == PHANTOM) {
        addEvidence(&ghost->evidences, createEvidence(TEMPERATURE));
        addEvidence(&ghost->evidences, createEvidence(FINGERPRINTS));
        addEvidence(&ghost->evidences, createEvidence(SOUND));
    }

    ghost->reason = LOG_UNKNOWN;

}

/*
    Moves the ghost to a random connected room relative to its former residing room.
    in/out: ghost - Pointer to the Ghost struct in order to change its current residingRoom and simulate it moving around the house.
*/
void ghostMove(struct Ghost* ghost) {

    sem_wait(&ghost->residingRoom->mutex);
    ghost->residingRoom->ghost = NULL;
    sem_post(&ghost->residingRoom->mutex);

    RoomType* newresidingRoom = iteRooms(&ghost->residingRoom->connectedRooms);
    ghost->residingRoom = newresidingRoom;

    sem_wait(&newresidingRoom->mutex);
    newresidingRoom->ghost = ghost;
    sem_post(&newresidingRoom->mutex);
}

/*
    Simulates the ghost dropping evidence in its current residing room.
    in/out: ghost - Pointer to the Ghost struct inorder to modify evidencelists field in its residingRoom struct field.
*/
void ghostEvidence(struct Ghost* ghost) {

    addEvidence(&ghost->residingRoom->evidenceList, iteEvidence(&ghost->evidences));

}

/*
    Cleans up the Evidence nodes and its data of the evidences field of the given Ghost struct by freeing them.
    in/out: ghost - The Ghost struct that will cleaned up.
*/
void cleanupGhost(struct Ghost* ghost) {
    cleanupEvidenceListData(&ghost->evidences);
    cleanupEvidenceListNodes(&ghost->evidences);
}