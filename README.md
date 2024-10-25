Purpose Of The Program:

    The purpose of the program is to work with a multi-threaded simulation. Furthermore, this simulation contains 5 threads of which there will be 4 threads that represent ghost hunters and the other one represent the ghost that is being hunted. In this simulation there will be a house structure (A.K.A the in-game Map) that the threads will be placed in, it will contain rooms that are represented as a LinkedList, the hunter threads will be placed at the head node of the room LinkedList (A.K.A the Van) and move to a random connected room relative to the room they are in while the ghost thread will be placed in a random node in the room LinkedList and move around the house like the hunters do. Moreover, each hunter will each be specialized in a certian evidence type that the ghost will drop to be able to collect it and their threads will only exit if all hunters either collect three distinct evidences to identify the ghost or will do so if each hunter becomes too bored of not encountering the ghost multiple times sequentially or afraid because they encountered the ghost too much, likewise the ghost only exits if it becomes too bored of not encountering any hunters while it moves.

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

    Once after it compiles, Run the program by typing ```./fp``` in the same path into the terminal. Later, the object files and executable can be removed by typing ```make clean```.

Instructions for how to Use the Program Once it is Running:

    Once the program is run, it will ask the user to enter the names of the hunters, after doing so the multithreaded-simulation will execut and then finally results will be printed.
