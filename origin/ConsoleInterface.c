#include "../headers/ConsoleInterface.h"

void loadingMenu()
{
	char version[5] = "0.1a";
	printf("Welcome to version %s of the PSO2 ModLoader made by Cat\n", version);
	printf("Now loading the program, please wait a little.\n");
	//Adicionar na memoria o arquivo de Configuração aqui ;-;
}

void chooseMenu(ConfPTR config)
{
	if (config->TwoPath == 1)
	{
		DefaultMenu2Path();
	}
	else
	{
		DefaultMenu(config);
	}
}

void DefaultMenu(ConfPTR config)
{
    char temp[4];
    if (config->NAFolder1 == 1)
    {
        strcpy(temp, "(on) ");
    }
    else
    {
        strcpy(temp, "(off)");
    }
	printf("|============== PATH 1 ================|\n");
	printf("| NA Folder modding is currently %s |\n",temp);
	printf("| 1) Load the mods from the MLoader    |\n");
	printf("| 2) Restore Backup files              |\n");
	printf("| 9) Configuration                     |\n");
	printf("| 0) Exit Program                      |\n");
	printf("|======================================|\n");
}

void DefaultMenu2Path()
{
	printf("|============== PATH 2 ================|\n");
	printf("| 1) Load the mods from the MLoader    |\n");
	printf("| 2) Restore Backup files              |\n");
	printf("| 9) Configuration                     |\n");
	printf("| 0) Exit Program                      |\n");
	printf("|======================================|\n");
}

void ConfigMenu(ConfPTR config, FILE **configFile)
{
	char tempPATH2[6];
	char tempNA[6];
	int y = 0;
	while (1)
	{
        if (config->NAFolder1 == 1)
        {
            strcpy(tempNA, "(on) \0");
        }
        else
        {
            strcpy(tempNA, "(off)\0");
        }

        if (config->TwoPath == 1)
        {
            strcpy(tempPATH2, "(on) ");
        }
        else
        {
            strcpy(tempPATH2, "(off)");
        }
	    printf("|======================================|\n");
        printf("|       Configuration File Change      |\n");
        printf("| 1) Change Path1                      |\n");
        printf("| 2) Change Path2                      |\n");
        printf("| 3) Activate/Deactivate Path2    %s|\n",tempPATH2);
        printf("| 4) Activate/Deactivate win32_na %s|\n", tempNA);
        printf("| 0) Back                              |\n");
        printf("|======================================|\n");
		printf("Option: ");
		scanf("%d", &y);
		if (y == 1 || y == 2)
		{
			changeConfig(config, configFile, y-1);
		}
		else if (y == 3)
		{
			ChangePath2Usage(config, configFile);
		}
		else if (y == 4)
        {
            ChangeNAFolderUsage(config, configFile);
        }
		else
		{
			break;
		}
	}
	return;
}
