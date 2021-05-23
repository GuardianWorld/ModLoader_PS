#pragma once
#include <stdio.h>
#include <gtk/gtk.h>
#include "LoaderConfig.h"
#include <stdlib.h>

/*
    //GtkWidget *mainGrid;
    //GtkWidget *menubar;

    //GtkWidget *terminalText;
    //GtkWidget *buttonBox;

    //GtkWidget *vboxEnd;
    //GtkWidget *buttonBoxEnd;

    //GtkWidget *mainImage;
    //GtkWidget *mainText;

    //End Window
    //endBlock endW;
*/

typedef struct uMenu{
    GtkWidget *chPath;
    GtkCheckMenuItem *win32NAEnable;
    GtkCheckMenuItem *confLogs;
    GtkWidget *redFolder;
}uMenu;

typedef struct mBlocks{
    GtkWidget *configMenu;
    GtkWidget *utilMenu;
    GtkWidget *aboutMenu;
    GtkWidget *quitMenu;
}mBlocks;

typedef struct mwButton{
    GtkWidget *load;
    GtkWidget *restore;
    GtkWidget *easterEgg;
}mwButton;

typedef struct gVar{
    GtkProgressBar *progressBar;
    GtkTextBuffer *terminalTextBuffer;
    mBlocks mn;
    mwButton btt;
    ConfPTR pConfig;
}gVar;

typedef struct UI{
    GtkWidget *mainWindow;
    GtkWidget *textView;
    GtkWidget *scrolledWindow;
    gVar edt;
    uMenu opt;

    GtkWidget *tempEntry2;
    GtkWidget *tempEntry;
}UI;

#include "LoadPasteModule.h"

//Config
void changePath(GtkWidget *widget, UI *gui);
void on_folder_set(GtkWidget *widget, UI *gui);
void changePathDestroy(GtkWidget *widget, UI *gui);
void win32na_toggled(GtkWidget *widget, gVar *buffers);
void logs_toggled(GtkWidget *widget, gVar *buffers);


//Utilities
void redoFolder(GtkWidget *widget, gVar *buffers);
void about(GtkWidget *widget, gVar *buffers);

void stringMixing(char *rText, int cleanSize, char *string1, char* string2, char* string3, int conversion);
int GUIPosInsert(char *stringBF, GtkTextBuffer *buffer, int pos);
void progressBarChange(int value, GtkProgressBar *progressBar);

//Main Functions
void initializeUI(GtkBuilder *builder,UI *interface);
void initializeRequests(UI *gui);
void signalConnections(UI *gui);
void start(gVar *buffers, int NAFolderMode);
void modFiles(GtkWidget *widget, gVar *buffers);
void diEn(gVar *buffers, int active);
void restoreFiles(GtkWidget *widget, gVar *buffers);
void easter(GtkWidget *widget, gVar *buffers);
