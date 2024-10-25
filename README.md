Purpose Of The Program:

    The purpose of the program is to implement a multi-threaded simulation involving five threads: four representing ghost hunters and
    one representing the ghost being pursued. The simulation takes place within a house structure, referred to as the in-game map,
    where the threads are distributed. The house consists of rooms organized as a LinkedList. The hunter threads start at the head node
    of the LinkedList, known as the Van, and move randomly to connected rooms. Similarly, the ghost thread is initially placed in a
    random node within the LinkedList and moves around the house in the same way as the hunters.
    
    Each hunter specializes in collecting a specific type of evidence that the ghost drops. The hunters' threads will only terminate
    under specific conditions: if all hunters collect three distinct pieces of evidence to identify the ghost, or if the hunters either
    become too bored from repeatedly failing to encounter the ghost or become too frightened due to encountering it too often.
    Likewise, the ghost’s thread terminates if it becomes bored from not encountering any hunters during its movement.

List of Files and Their Purposes:

    ∙ defs.h    : Header file that contains all the defined variables, all of the specified structs, all the libraries needed for the program and function prototypes.
    ∙ logger.c  : C file that contains all of the functions that log all of the activities of the threads to the terminal.
    ∙ utils.c   : C file that contains necessary pre-added helper methods.
    ∙ house.c   : C file that contains all of the needed helper methods for the HouseType struct.
    ∙ room.c    : C file that contains all of the needed helper methods for the RoomType struct.
    ∙ evidence.c: C file that contains all of the needed helper methods for the EvidenceType struct.
    ∙ ghost.c   : C file that contains all of the needed helper methods for the GhostType struct.
    ∙ hunter.c  : C file that contains all of the needed helper methods for the HunterType struct.
    ∙ Makefile  : Instructions to compile and run the program by typing one line into the terminal.

Instructions for Compiling the Program:

    Traverse to the folder directory that contains the program and compile the project by typing ```make``` into the terminal.

Instructions for Running the Program:

    Once after it compiles, Run the program by typing ```./fp``` in the same path into the terminal. Later, the object files and
    executable can be removed by typing ```make clean```.

    Furthermore, if you wish to run the program with input redirection then run it by typing: ```./fp < names.txt```.

Instructions for how to Use the Program Once it is Running:

    Once the program is run, it will ask the user to enter the names of the hunters, after doing so the multithreaded simulation will execute and then finally results will be printed.
