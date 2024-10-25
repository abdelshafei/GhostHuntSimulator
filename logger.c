#include "defs.h"

/* 
    Logs the hunter being created.
    in: hunter    - the hunter name to log
    in: equipment - the hunter's equipment
*/
void l_hunterInit(char* hunter, enum EvidenceType equipment) 
{
    if (!LOGGING) return;
    char ev_str[MAX_STR];
    evidenceToString(equipment, ev_str);
    printf("[HUNTER INIT] [%s] is a [%s] hunter\n", hunter, ev_str);    
}

/*
    Logs the hunter moving into a new room.
    in: hunter - the hunter name to log
    in: room   - the room name to log
*/
void l_hunterMove(char* hunter, char* room) 
{
    if (!LOGGING) return;
    printf("[HUNTER MOVE] [%s] has moved into [%s]\n", hunter, room);
}

/* 
    Logs the hunter being changing equipments.
    in: hunter    - the hunter name to log
    in: equipment - the hunter's new choosen equipment
*/
void l_hunterChangeEquip(char* hunter, enum EvidenceType equipment) 
{
    if (!LOGGING) return;
    char ev_str[MAX_STR];
    evidenceToString(equipment, ev_str);
    printf("[HUNTER CHANGE] [%s] is changing to being a [%s] hunter\n", hunter, ev_str); 
}

/*
    Logs the hunter exiting the house.
    in: hunter - the hunter name to log
    in: reason - the reason for exiting, either LOG_FEAR, LOG_BORED, or LOG_EVIDENCE
*/
void l_hunterExit(char* hunter, enum LoggerDetails reason) 
{
    if (!LOGGING) return;
    printf("[HUNTER EXIT] [%s] exited because ", hunter);
    switch (reason) {
        case LOG_FEAR:
            printf("[FEAR]\n");
            break;
        case LOG_BORED:
            printf("[BORED]\n");
            break;
        case LOG_EVIDENCE:
            printf("[EVIDENCE]\n");
            break;
        default:
            printf("[UNKNOWN]\n");
    }
}

/*
    Logs the hunter reviewing evidence.
    in: hunter - the hunter name to log
    in: result - the result of the review, either LOG_SUFFICIENT or LOG_INSUFFICIENT
*/
void l_hunterReview(char* hunter, enum LoggerDetails result) 
{
    if (!LOGGING) return;
    printf("[HUNTER REVIEW] [%s] reviewed evidence and found ", hunter);
    switch (result) {
        case LOG_SUFFICIENT:
            printf("[SUFFICIENT]\n");
            break;
        case LOG_INSUFFICIENT:
            printf("[INSUFFICIENT]\n");
            break;
        default:
            printf("[UNKNOWN]\n");
    }
}

/*
    Logs the hunter collecting evidence.
    in: hunter   - the hunter name to log
    in: evidence - the evidence type to log
    in: room     - the room name to log
*/
void l_hunterCollect(char* hunter, enum EvidenceType evidence, char* room) 
{
    if (!LOGGING) return;
    char ev_str[MAX_STR];
    evidenceToString(evidence, ev_str);
    printf("[HUNTER EVIDENCE] [%s] found [%s] in [%s] and [COLLECTED]\n", hunter, ev_str, room);
}

/*
    Logs the ghost moving into a new room.
    in: room - the room name to log
*/
void l_ghostMove(char* room) 
{
    if (!LOGGING) return;
    printf("[GHOST MOVE] Ghost has moved into [%s]\n", room);
}

/*
    Logs the ghost exiting the house.
    in: reason - the reason for exiting, either LOG_FEAR, LOG_BORED, or LOG_EVIDENCE
*/
void l_ghostExit(enum LoggerDetails reason) 
{
    if (!LOGGING) return;

    printf("[GHOST EXIT] Exited because ");
    switch (reason) {
        case LOG_FEAR:
            printf("[FEAR]\n");
            break;
        case LOG_BORED:
            printf("[BORED]\n");
            break;
        case LOG_EVIDENCE:
            printf("[EVIDENCE]\n");
            break;
        default:
            printf("[UNKNOWN]\n");
    }

}

/*
    Logs the ghost leaving evidence in a room.
    in: evidence - the evidence type to log
    in: room     - the room name to log
*/
void l_ghostEvidence(enum EvidenceType evidence, char* room) 
{
    if (!LOGGING) return;
    char ev_str[MAX_STR];
    evidenceToString(evidence, ev_str);
    printf("[GHOST EVIDENCE] Ghost left [%s] in [%s]\n", ev_str, room);
}

/*
    Logs the ghost being created.
    in: ghost - the ghost type to log
    in: room  - the room name that the ghost is starting in
*/
void l_ghostInit(enum GhostClass ghost, char* room) 
{
    if (!LOGGING) return;
    char ghost_str[MAX_STR];
    ghostToString(ghost, ghost_str);
    printf("[GHOST INIT] Ghost is a [%s] in room [%s]\n", ghost_str, room);
    
}

/*
    Logs the results of the simulations.
    in: house         -  The House struct to log the evidences shared between all hunters 
    in: ghostStruct   -  The Ghost struct to log the identity of the ghost
    in: hunter1Struct -  The first Hunter Struct to log its reason of exiting the simulation
    in: hunter2Struct -  The second Hunter struct to log its reason of exiting the simulation
    in: hunter3Struct -  The third Hunter struct to log its reason of exiting the simulation
    in: hunter4Struct -  The fourth Hunter struct to log its reason of exiting the simulation
*/
void l_printResults(struct House* house, struct Ghost* ghostStruct, struct Hunter* hunter1Struct, struct Hunter* hunter2Struct, struct Hunter* hunter3Struct, struct Hunter* hunter4Struct) 
{

    printf("%s\n", "==============================================");
    printf("%s\n", "All done! Let's tally the results...");
    printf("%s\n", "==============================================");

    int result       = C_FALSE;
    int fearCounter  = 0;
    int boredCounter = 0;

    if(hunter1Struct->reason == LOG_FEAR) {

        printf("%10s %s %s\n", "*", hunter1Struct->name, "has run away in fear");
        result = C_TRUE;
        fearCounter++;

    } else if(hunter1Struct->reason == LOG_BORED) {

        printf("%10s %s %s\n", "*", hunter1Struct->name, "has become bored");
        result = C_TRUE;
        boredCounter++;

    }

    if(hunter2Struct->reason == LOG_FEAR) {

        printf("%10s %s %s\n", "*", hunter2Struct->name, "has run away in fear");
        result = C_TRUE;
        fearCounter++;

    } else if(hunter2Struct->reason == LOG_BORED) {

        printf("%10s %s %s\n", "*", hunter2Struct->name, "has become bored");
        result = C_TRUE;
        boredCounter++;

    }

    if(hunter3Struct->reason == LOG_FEAR) {

        printf("%10s %s %s\n", "*", hunter3Struct->name, "has run away in fear");
        result = C_TRUE;
        fearCounter++;

    } else if(hunter3Struct->reason == LOG_BORED) {

        printf("%10s %s %s\n", "*", hunter3Struct->name, "has become bored");
        result = C_TRUE;
        boredCounter++;

    }

    if(hunter4Struct->reason == LOG_FEAR) {

        printf("%10s %s %s\n", "*", hunter4Struct->name, "has run away in fear");
        result = C_TRUE;
        fearCounter++;

    } else if(hunter4Struct->reason == LOG_BORED) {

        printf("%10s %s %s\n", "*", hunter4Struct->name, "has become bored");
        result = C_TRUE;
        boredCounter++;

    }

    if(result == C_TRUE) {
        printf("%s\n", "----------------------------------------------");
    }

    if(hunter1Struct->reason == LOG_SUFFICIENT || hunter2Struct->reason == LOG_SUFFICIENT || hunter3Struct->reason == LOG_SUFFICIENT|| hunter4Struct->reason == LOG_SUFFICIENT || house->sharedEvidenceList.size == 3) {
        printf("%s\n", "It seems the ghost has been discovered!");
        printf("%s\n", "The hunters have won the game!");
        char ghostype[MAX_STR];
        ghostToString(ghostStruct->ghostType, ghostype);
        printf("%s%s\n", "Using the evidence they found, they correctly determined that the ghost is ", ghostype);
        printf("%s\n", "The hunters collected the following evidence:");
        char evidence1[MAX_STR];
        char evidence2[MAX_STR];
        char evidence3[MAX_STR];
        evidenceToString(house->sharedEvidenceList.head->data->name, evidence1);
        evidenceToString(house->sharedEvidenceList.head->next->data->name, evidence2);
        evidenceToString(house->sharedEvidenceList.tail->data->name, evidence3);
        printf("%5s %s\n%5s %s\n%5s %s\n\n", "*", evidence1, "*", evidence2, "*", evidence3);
    } else if(fearCounter == 4) {
        printf("%s\n", "All the hunters have run away in fear!");
        printf("%s\n", "The ghost has won!");
        printf("%s\n", "The hunters have failed!");
        char ghosttypeun[MAX_STR];
        ghostToString(GH_UNKNOWN, ghosttypeun);
        char ghostype[MAX_STR];
        ghostToString(ghostStruct->ghostType, ghostype);
        printf("%s%s\n", "Using the evidence they found, they incorrectly determined that the ghost is ", ghosttypeun);
        printf("%s%s\n", "The ghost is actually a ", ghostype);
        printf("%s\n", "The hunters collected the following evidence:");
        char evidence[MAX_STR];
        EvidenceNodeType* currNode = house->sharedEvidenceList.head;
        while(currNode != NULL) {
            evidenceToString(currNode->data->name, evidence);
            printf("%5s %s\n", "*", evidence);
            currNode = currNode->next;
        }
        printf("\n");
    } else if(boredCounter == 4) {
        printf("%s\n", "All the hunters have became bored.");
        printf("%s\n", "The ghost has won!");
        printf("%s\n", "The hunters have failed!");
        char ghosttypeun[MAX_STR];
        ghostToString(GH_UNKNOWN, ghosttypeun);
        char ghostype[MAX_STR];
        ghostToString(ghostStruct->ghostType, ghostype);
        printf("%s%s\n", "Using the evidence they found, they incorrectly determined that the ghost is ", ghosttypeun);
        printf("%s%s\n", "The ghost is actually a ", ghostype);
        printf("%s\n", "The hunters collected the following evidence:");
        char evidence[MAX_STR];
        EvidenceNodeType* currNode = house->sharedEvidenceList.head;
        while(currNode != NULL) {
            evidenceToString(currNode->data->name, evidence);
            printf("%5s %s\n", "*", evidence);
            currNode = currNode->next;
        }
        printf("\n");
    } else {
        printf("%s\n", "All the hunters have exited for some reason or another.");
        printf("%s\n", "The ghost has won!");
        printf("%s\n", "The hunters have failed!");
        char ghosttypeun[MAX_STR];
        ghostToString(GH_UNKNOWN, ghosttypeun);
        char ghostype[MAX_STR];
        ghostToString(ghostStruct->ghostType, ghostype);
        printf("%s%s\n", "Using the evidence they found, they incorrectly determined that the ghost is ", ghosttypeun);
        printf("%s%s\n", "The ghost is actually a ", ghostype);
        printf("%s\n", "The hunters collected the following evidence:");
        char evidence[MAX_STR];
        EvidenceNodeType* currNode = house->sharedEvidenceList.head;
        while(currNode != NULL) {
            evidenceToString(currNode->data->name, evidence);
            printf("%5s %s\n", "*", evidence);
            currNode = currNode->next;
        }
        printf("\n");
    }

}