#include "defs.h"

/*
    Intializes the EvidenceList struct.
    out: list - Pointer to the EvidenceList struct to be intialized.
*/
void initEvidenceList(struct EvidenceList* list) {
    list->head = NULL;
    list->tail = NULL;
    sem_init(&list->mutex, 0, 1);
    list->size = 0;
}

/*
    Dynamically allocates memory for an Evidence struct and returns it.
    in: name - Intializes this to the enum name field in the to be created room struct.
    returns: pointer to the newly created Evidence struct.
*/
EvType* createEvidence(enum EvidenceType name) {
    EvType* ev = malloc(sizeof(EvType));
    ev->name = name;
    return ev;
}

/*
    Adds the Evidence struct ev to the back of the list of an EvidenceList structure in parameter list.
    in/out: list - The EvidenceList struct list that the Evidence struct ev will be added to.
    in: ev       - The Evidence struct ev that will be added.
*/
void addEvidence(struct EvidenceList* list, struct Evidence* ev) {

    EvidenceNodeType* currNode = list->head;
    
    //if the list is empty
    if (currNode == NULL) {
        sem_wait(&list->mutex);
        EvidenceNodeType *newNode = malloc(sizeof(EvidenceNodeType)); 

        newNode->data = ev;
        newNode->next = NULL; 
        list->head    = newNode;
        list->tail    = newNode;
        list->size++;
        sem_post(&list->mutex);
    } else {
        sem_wait(&list->mutex);
        EvidenceNodeType *newNode = malloc(sizeof(EvidenceNodeType));

        newNode->data    = ev;
        newNode->next    = NULL;
        list->tail->next = newNode;
        list->tail       = newNode;
        list->size++;
        sem_post(&list->mutex);
    }

}

/*
    Removes the Evidence struct ev from the list of an EvidenceList structure in parameter list.
    in/out: list - The EvidenceList struct list that the Evidence struct ev will be removed from.
    in: ev       - The Evidence struct ev that will be removed.
*/
void removeEvidence(struct EvidenceList* list, struct Evidence* ev) {

    EvidenceNodeType* currNode = list->head;
    EvidenceNodeType* prevNode = NULL;

    if(ev == NULL) return;
    

    while(currNode->data != ev) {

        prevNode = currNode;
        currNode = currNode->next;

    }

    sem_wait(&list->mutex);

    if (prevNode == NULL) list->head = currNode->next;
    else              prevNode->next = currNode->next;

    free(currNode);

    sem_post(&list->mutex);

}

/*
    Checks if a given Evidence struct ev is in the given EvidenceList struct list, by returning C_FALSE if not otherwise it returns C_TRUE.
    in: list - The given EvidenceList struct to check whether ev is in th list or not.
    in: ev   - The given Evidence struct to check whether it exists in the list or not.
    return: an int definition of C_FALSE if it does not exist, or a definition of C_TRUE if it does.
*/
int isEvidenceInList(struct EvidenceList* list, enum EvidenceType ev) {

    EvidenceNodeType* currNode = list->head;

    while(currNode != NULL) {

        if(currNode->data->name == ev) {
            return C_TRUE;
        }

        currNode = currNode->next;

    }

    return C_FALSE;
}

/*
    Gets a random Evidence struct from a given  EvidenceList struct LinkedList.
    in: list - The given EvidenceList struct to be used to find a random Evidence.
    returns: Pointer to the random choosen Evidence struct data.
*/
struct Evidence* iteEvidence(struct EvidenceList* list) {

    int randNo = randInt(0, list->size);
    
    EvidenceNodeType* currNode = list->head;
    EvidenceNodeType* nextNode;

    for(int i = 0; i != randNo; i++) {
        nextNode = currNode->next;
        currNode = nextNode;
    }

    return currNode->data;

}

/*
    Cleans up the data of the given EvidenceList struct by freeing them.
    in/out: list - The EvidenceList struct that will have its data freed.
*/
void cleanupEvidenceListData(struct EvidenceList* list) {

    EvidenceNodeType* currNode = list->head;
    EvidenceNodeType* nextNode = NULL;

    while (currNode != NULL)
    {
        nextNode = currNode->next;

        free(currNode->data);

        currNode = nextNode;
    }

}

/*
    Cleans up the node of the given EvidenceList struct by freeing them.
    in/out: list - The EvidenceList struct that will have its nodes freed.
*/
void cleanupEvidenceListNodes(struct EvidenceList* list) {
    
    EvidenceNodeType* currNode = list->head;
    EvidenceNodeType* nextNode = NULL;

    while (currNode != NULL)
    {
        nextNode = currNode->next;

        free(currNode);

        currNode = nextNode;
    }

}