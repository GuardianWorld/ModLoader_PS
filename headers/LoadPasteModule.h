#pragma once
#ifndef LPM_H_INCLUDED
#define LPM_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <winbase.h>
#include "LoaderConfig.h"

int CheckFile();
void ListModInsert(ConfPTR config);
void ListModRemoval(ConfPTR config);
void LoadPasteBackupModule(ConfPTR config, char *path, char *filename, int SIZE);
void returnBeckups(ConfPTR config, char *path, char *filename,char *purePath);
void returnBeckupsNAFolder(ConfPTR config, char *path, char *filename, char *purePath);

#endif //LPM_H_INCLUDED
