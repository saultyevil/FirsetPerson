/* Terminal.c */
void terminalInit (void);
void terminalRevert (void);
void terminalUpdateSize (int sig);
/* Utilities.c */
void utilResetDisplay (void);
void utilExit (char *s);
/* Map.c */
void mapInit (void);
/* Input.c */
void controlPlayer (float TimeDifference);
/* Render.c */
void refreshScreen (void);
