#pragma once
#ifndef LCONF_H_INCLUDED
#define LCONF_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EMPTY 0
#define NOEMPTY 1

#define READ_ONLY 0
#define WRITE_ONLY 1

#define PATH1 0

#define UPDATE 255

typedef struct TypeConfig* ConfPTR;
typedef struct TypeConfig{
	char path1[200];
	int NAFolder1;
	int hideMessages;
	FILE *configFile;
}TypeConfig;

int openConfigFile(ConfPTR config);
void writeConfig(ConfPTR config, int empty);
void readConfig(ConfPTR config);
void ChangeNAFolderUsage(ConfPTR config);
void remakeFolders(ConfPTR config);
void turnMessages(ConfPTR config);
void MakeDirOneTime(char *path);

int mkdir(const char *pathname);

#endif //LCONF_H_INCLUDED
