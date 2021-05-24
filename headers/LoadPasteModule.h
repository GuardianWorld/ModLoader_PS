#pragma once
#ifndef LPM_H_INCLUDED
#define LPM_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "dirent.h"
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <winbase.h>
#include "Callbacks.h"
#include <gtk/gtk.h>
#include "LoaderConfig.h"

#define PATHCONV -99

int CheckFile();
int checkProhibitions(char* dirName);
int getFileAmount(ConfPTR config, char *temp, DIR *d);
void ListModInsert(ConfPTR config, gVar *buffers, int pos);
void ListModRemoval(ConfPTR config, gVar *buffers, int pos);
void LoadPasteBackupModule(ConfPTR config, char *path, char *filename, int SIZE, gVar *buffers, int *pos);
void returnBeckups(ConfPTR config, char *path, char *filename,char *purePath, gVar *buffers, int *pos);
void returnBeckupsNAFolder(ConfPTR config, char *path, char *filename, char *purePath, gVar *buffers, int *pos);

#endif //LPM_H_INCLUDED
