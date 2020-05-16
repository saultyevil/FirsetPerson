/* Terminal.c */
void TerminalRevert(void);
void TerminalInit(void);
int TerminalGetCursorPosition(int *nrows, int *ncols);
int TerminalGetWindowSize(int *ncols, int *nrows);
void TerminalUpdateSize(int unused);
/* Utilities.c */
void UtilResetDisplay(void);
void UtilExit(char *s);
/* Map.c */
void MapInit(void);
/* Input.c */
int ReadKeypress(void);
void ControlPlayer(int key, float TimeDifference);
/* Render.c */
void RefreshScreen(void);
