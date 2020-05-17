/* terminal.c */
void terminalInit(void);
void terminalRevert(void);
void terminalUpdateSize(int sig);
/* utilities.c */
void sortBoundaryTest(struct bTest *boundaryTest);
void utilExit(char *s);
/* map.c */
void mapInit(void);
/* input.c */
void controlPlayer(float timeDifference);
/* render.c */
void refreshScreen(void);
/* main.c */
void gameInit(void);
int main(void);
