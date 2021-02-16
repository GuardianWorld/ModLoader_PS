#pragma once
#ifndef CINT_H_INCLUDED
#define CINT_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "LoadPasteModule.h"
#include "LoaderConfig.h"

void loadingMenu();
void chooseMenu(ConfPTR file);
void DefaultMenu(ConfPTR config);
void ConfigMenu(ConfPTR config, FILE **configFile);

#endif //CINT_H_INCLUDED
