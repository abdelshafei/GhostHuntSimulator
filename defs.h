#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_STR         64
#define MAX_RUNS        50
#define BOREDOM_MAX     100
#define C_TRUE          1
#define C_FALSE         0
#define HUNTER_WAIT     5000
#define GHOST_WAIT      600
#define NUM_EVIDENCE    3
#define NUM_HUNTERS     4
#define FEAR_MAX        10
#define MAX_HUNTERS     4
#define LOGGING         C_TRUE

typedef enum EvidenceType EvidenceType;
typedef enum GhostClass GhostClass;

enum EvidenceType { EMF, TEMPERATURE, FINGERPRINTS, SOUND, EV_COUNT, EV_UNKNOWN };
enum GhostClass { POLTERGEIST, BANSHEE, BULLIES, PHANTOM, GHOST_COUNT, GH_UNKNOWN };
enum LoggerDetails { LOG_FEAR, LOG_BORED, LOG_EVIDENCE, LOG_SUFFICIENT, LOG_INSUFFICIENT, LOG_UNKNOWN };

typedef   struct EvidenceNode EvidenceNodeType;
typedef   struct RoomNode     RoomNodeType;
typedef   struct Room         RoomType;
typedef   struct Evidence     EvType;
typedef   struct Rooms        RoomsType;
typedef   struct EvidenceList EvidenceListType;
typedef   struct Hunter       HunterType;
typedef   struct Ghost        GhostType;
typedef   struct House        HouseType;

struct Rooms {
  RoomNodeType *head;
  RoomNodeType *tail;
  int           size;
};

struct EvidenceList {
  EvidenceNodeType *head;
  EvidenceNodeType *tail;
  sem_t            mutex;
  int               size;
};

struct Room {
  char                 name[MAX_STR];
  struct  Ghost*       ghost;
  struct  Rooms        connectedRooms;
  struct  EvidenceList evidenceList;
  int                  numHunters;
  sem_t                mutex;
};

struct House {
  struct Rooms         rooms; 
  struct EvidenceList  sharedEvidenceList; 
};

struct Evidence {
  enum    EvidenceType name;
};

struct Hunter {
  char                  name[MAX_STR];
  struct Room*          residingRoom;
  enum   EvidenceType   collectibleEvidence; //Each hunter can only carry one specific enumrated EvidenceType
  struct EvidenceList*  sharedEvidence;
  int                   boredomTicker;
  int                   fearTicker;
  enum   LoggerDetails  reason;
};

struct Ghost {
  enum   GhostClass    ghostType;
  struct Room*         residingRoom;
  int                  boredomTicker;
  struct EvidenceList  evidences;    
  enum   LoggerDetails reason; 
};

struct RoomNode {
  RoomType     *data; 
  RoomNodeType *next;
};

struct EvidenceNode {
  struct Evidence *data; 
  EvidenceNodeType *next;
};

void* ghostPlay(void*);
void* hunterPlay(void*);

void initHouse(struct House*);
void populateRooms(struct House*);
void cleanupHouse(struct House*);

void initRooms(struct Rooms*);
void connectRooms(struct Room*, struct Room*);
void addRoom(struct Rooms*, struct Room*);
struct Room* iteRooms(struct Rooms*);
void cleanupRoomData(struct Rooms*);
void cleanupRoomNodes(struct Rooms*);
struct Room* createRoom(char*);

void initEvidenceList(struct EvidenceList*);
void addEvidence(struct EvidenceList*, struct Evidence*);
void removeEvidence(struct EvidenceList*, struct Evidence*);
int isEvidenceInList(struct EvidenceList*, enum EvidenceType);
struct Evidence* iteEvidence(struct EvidenceList*);
void cleanupEvidenceListData(struct EvidenceList*);
void cleanupEvidenceListNodes(struct EvidenceList*);
struct Evidence* createEvidence(enum EvidenceType);

void hunterInit(struct House*, struct Hunter*, enum EvidenceType);
void hunterMove(struct Hunter*);
void hunterReview(struct Hunter*);
void hunterCollect(struct Hunter*);
void hunterExit(struct Hunter*);

void ghostInit(struct House*, struct Ghost*);
void ghostMove(struct Ghost*);
void ghostEvidence(struct Ghost*);
void cleanupGhost(struct Ghost*);

// Helper Utilies
int randInt(int,int);        // Pseudo-random number generator function
float randFloat(float, float);  // Pseudo-random float generator function
enum GhostClass randomGhost();  // Return a randomly selected a ghost type
void ghostToString(enum GhostClass, char*); // Convert a ghost type to a string, stored in output paremeter
void evidenceToString(enum EvidenceType, char*); // Convert an evidence type to a string, stored in output parameter
enum EvidenceType randEquipment();

// Logging Utilities
void l_hunterInit(char* name, enum EvidenceType equipment);
void l_hunterMove(char* name, char* room);
void l_hunterChangeEquip(char* hunter, enum EvidenceType equipment);
void l_hunterReview(char* name, enum LoggerDetails reviewResult);
void l_hunterCollect(char* name, enum EvidenceType evidence, char* room);
void l_hunterExit(char* name, enum LoggerDetails reason);
void l_ghostInit(enum GhostClass type, char* room);
void l_ghostMove(char* room);
void l_ghostEvidence(enum EvidenceType evidence, char* room);
void l_ghostExit(enum LoggerDetails reason);
void l_printResults(struct House*, struct Ghost*, struct Hunter*, struct Hunter*, struct Hunter*, struct Hunter*);