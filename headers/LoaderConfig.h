#pragma once
#ifndef LCONF_H_INCLUDED
#define LCONF_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EMPTY 1

#define READ_ONLY 0
#define WRITE_ONLY 1

#define PATH1 0

typedef struct TypeConfig* ConfPTR;
typedef struct TypeConfig{
	char path1[200];
	int NAFolder1;
}TypeConfig;

void openConfigFile(ConfPTR config, FILE **configFile);
void writeConfig(ConfPTR config, FILE **configFile, int empty);
void readConfig(ConfPTR config, FILE **configFile);
void changeConfig(ConfPTR config, FILE **configFile);
void ChangeNAFolder(ConfPTR config, FILE **configFile);
void MakeDirOneTime(char *path);

#endif //LCONF_H_INCLUDED
