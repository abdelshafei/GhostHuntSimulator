#include "defs.h"

int main()
{   
    // Initialize the random number generator
    srand(time(NULL));

    // Create the house: You may change this, but it's here for demonstration purposes
    // Note: This code will not compile until you have implemented the house functions and structures
    HouseType house;
    initHouse(&house);
    populateRooms(&house);

    pthread_t ghost, hunter1, hunter2, hunter3, hunter4;
    GhostType  ghostStruct;
    HunterType hunter1Struct;
    HunterType hunter2Struct;
    HunterType hunter3Struct;
    HunterType hunter4Struct;

    /* Intializing ghost struct */

    ghostInit(&house, &ghostStruct);
    l_ghostInit(ghostStruct.ghostType, ghostStruct.residingRoom->name);

    /* Intializing hunter structs */

        //intialization of the 1st hunter
    printf("Enter the name of hunter 1: ");
    fgets(hunter1Struct.name, MAX_STR, stdin);
    hunter1Struct.name[strlen(hunter1Struct.name) -  1] = 0;
    hunterInit(&house, &hunter1Struct, EMF);
    l_hunterInit(hunter1Struct.name, hunter1Struct.collectibleEvidence);

        //intialization of the 2nd hunter
    printf("Enter the name of hunter 2: ");
    fgets(hunter2Struct.name, MAX_STR, stdin);
    hunter2Struct.name[strlen(hunter2Struct.name) -  1] = 0;
    hunterInit(&house, &hunter2Struct, TEMPERATURE);
    l_hunterInit(hunter2Struct.name, hunter2Struct.collectibleEvidence);

        //intialization of the 3rd hunter
    printf("Enter the name of hunter 3: ");
    fgets(hunter3Struct.name, MAX_STR, stdin);
    hunter3Struct.name[strlen(hunter3Struct.name) -  1] = 0;
    hunterInit(&house, &hunter3Struct, FINGERPRINTS);
    l_hunterInit(hunter3Struct.name, hunter3Struct.collectibleEvidence);

        //intialization of the 4th hunter
    printf("Enter the name of hunter 4: ");
    fgets(hunter4Struct.name, MAX_STR, stdin);
    hunter4Struct.name[strlen(hunter4Struct.name) -  1] = 0;
    hunterInit(&house, &hunter4Struct, SOUND);
    l_hunterInit(hunter4Struct.name, hunter4Struct.collectibleEvidence);



    pthread_create(&ghost, NULL, ghostPlay, &ghostStruct);
    pthread_create(&hunter1, NULL, hunterPlay, &hunter1Struct);
    pthread_create(&hunter2, NULL, hunterPlay, &hunter2Struct);
    pthread_create(&hunter3, NULL, hunterPlay, &hunter3Struct);
    pthread_create(&hunter4, NULL, hunterPlay, &hunter4Struct);

    pthread_join(ghost,   NULL);
    pthread_join(hunter1, NULL);
    pthread_join(hunter2, NULL);
    pthread_join(hunter3, NULL);
    pthread_join(hunter4, NULL);

    l_printResults(&house, &ghostStruct, &hunter1Struct, &hunter2Struct, &hunter3Struct, &hunter4Struct);

    cleanupHouse(&house);
    cleanupGhost(&ghostStruct);



    return 0;
}

/*
    The start routine of the ghost thread.
    in/out: args - intially passed as a Ghost struct pointer.
*/
void* ghostPlay(void* args) {

    GhostType* ghost = (GhostType*)args;
    int randNo;

    while(1) {
        

        if (ghost->residingRoom->numHunters > 0) {
            randNo = randInt(2, 4);
        } else {
            randNo = randInt(1, 4);
        }

        if(ghost->residingRoom->numHunters == 0) {
            ghost->boredomTicker++;
        } else {
            ghost->boredomTicker = 0;
        }

        if(ghost->boredomTicker == BOREDOM_MAX) {
            ghost->reason = LOG_BORED;
        }

        if(randNo == 1) {
            ghostMove(ghost);
            l_ghostMove(ghost->residingRoom->name);
        } else if(randNo == 2) {
            ghostEvidence(ghost);
            l_ghostEvidence(ghost->residingRoom->evidenceList.tail->data->name, ghost->residingRoom->name);
        }

        if(ghost->reason == LOG_BORED) {
            l_ghostExit(ghost->reason);
            return NULL;
        }

        usleep(GHOST_WAIT);

    }

    l_ghostExit(LOG_UNKNOWN);
    return NULL;

}

/*
    The start routine of the hunter threads.
    in/out: args - intially passed as a Hunter struct pointer.
*/
void* hunterPlay(void* args) {
    

    HunterType* hunter = (HunterType*) args;
    int randNo;

    while(1) {

        if(hunter->residingRoom->evidenceList.head != NULL && isEvidenceInList(&hunter->residingRoom->evidenceList, hunter->collectibleEvidence) == C_TRUE) {
            randNo = randInt(1, 5);
        } else {
            randNo = randInt(1, 4);
        }

        if(hunter->residingRoom->ghost != NULL) {
            hunter->fearTicker++;
            hunter->boredomTicker = 0;
        } else {
            hunter->boredomTicker++;
        }

        if(hunter->boredomTicker == BOREDOM_MAX) {
            hunter->reason = LOG_BORED;
        } else if(hunter->fearTicker == FEAR_MAX) {
            hunter->reason = LOG_FEAR;
        }
        
        if(randNo == 1) {
            hunterMove(hunter);
        } else if(randNo == 2) {
            hunterExit(hunter);
            if (hunter->reason == LOG_SUFFICIENT) {
                return NULL;
            }
        }else if(randNo == 3) {
            hunterReview(hunter);
        }else {
            hunterCollect(hunter);
        }

        if(hunter->reason == LOG_FEAR || hunter->reason == LOG_BORED) {
            l_hunterExit(hunter->name, hunter->reason);
            sem_wait(&hunter->residingRoom->mutex);
            hunter->residingRoom->numHunters--;
            sem_post(&hunter->residingRoom->mutex);
            return NULL;
        }

        usleep(HUNTER_WAIT);
         
    }

    l_hunterExit(hunter->name, LOG_UNKNOWN);
    return NULL;
}
