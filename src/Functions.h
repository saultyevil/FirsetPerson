/* Terminal.c */
void TerminalInit(void);
void TerminalRevert(void);
void TerminalUpdateSize(int sig);
/* Utilities.c */
void UtilResetDisplay(void);
void UtilExit(char *s);
/* Map.c */
void MapInit(void);
/* Input.c */
void ControlPlayer(float TimeDifference);
/* Render.c */
void RefreshScreen(void);
