#include "defs.h"

/*
    Intializes the Rooms struct.
    out: list - Pointer to the list Rooms struct to be intialized.
*/
void initRooms(struct Rooms* list) 
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/*
    Dynamically allocates memory for a Room struct and returns it.
    in: name - Intializes this to the name field in the to be created Room struct.
    returns: pointer to the newly created Room struct.
*/
struct Room* createRoom(char* name) 
{

    RoomType* intializedRoom = malloc(sizeof(RoomType));

    strcpy(intializedRoom->name, name);
    intializedRoom->ghost      = NULL;
    initRooms(&intializedRoom->connectedRooms);
    initEvidenceList(&intializedRoom->evidenceList);
    intializedRoom->numHunters = 0;
    sem_init(&intializedRoom->mutex, 0, 1);

    return intializedRoom;
}

/*
    Adds the room struct room to the back of the list of a Rooms structure in parameter list.
    in/out: list - The Rooms struct list that the Room struct room will be added to.
    in: room     - The Room struct room that will be added.
*/
void addRoom(struct Rooms* list, struct Room* room) 
{

    RoomNodeType* currNode = list->head;

    if(room == NULL) return;
    
    //if the list is empty
    if (currNode == NULL) {
        RoomNodeType *newNode = malloc(sizeof(RoomNodeType)); 

        newNode->data = room;
        newNode->next = NULL; 
        list->head    = newNode;
        list->tail    = newNode;
        list->size++;

    } else {
        RoomNodeType *newNode = malloc(sizeof(RoomNodeType)); 

        newNode->data    = room;
        newNode->next    = NULL;
        list->tail->next = newNode;
        list->tail       = newNode;
        list->size++;

    }
    
}

/*
    Adds the given dest and src Room structs to each others connectedRooms LinkedList field in both of their structs.
    in/out: dest - The dest room to be added.
    in/out: src  - The src room to be added.
*/
void connectRooms(struct Room* dest, struct Room* src) 
{
    addRoom(&dest->connectedRooms, src);
    addRoom(&src->connectedRooms, dest);
}

/*
    gets a random Room struct from a given rooms LinkedList.
    in: list - The given Rooms struct to be used to find a random room.
    returns: pointer to the random choosen struct Room data.
*/
RoomType* iteRooms(struct Rooms* list) {

    int randNo = randInt(0, list->size);

    RoomNodeType* currNode = list->head;
    RoomNodeType* nextNode = NULL;

    for(int i = 0; i != randNo; i++) {
        nextNode = currNode->next;
        currNode = nextNode;
    }

    return currNode->data;

}

/*
    Cleans up the data of the given Rooms struct by freeing them.
    in/out: list - The Rooms struct that will have its data freed.
*/
void cleanupRoomData(struct Rooms* list) {

    RoomNodeType* currNode = list->head;
    RoomNodeType* nextNode = NULL;

    while (currNode != NULL)
    {
        nextNode = currNode->next;

        free(currNode->data);

        currNode = nextNode;
    }

}

/*
    Cleans up the node of the given Rooms struct by freeing them.
    in/out: list - The Rooms struct that will have its nodes freed.
*/
void cleanupRoomNodes(struct Rooms* list) {

    RoomNodeType* currNode = list->head;
    RoomNodeType* nextNode = NULL;

    while (currNode != NULL)
    {
        nextNode = currNode->next;

        free(currNode);

        currNode = nextNode;
    }

}