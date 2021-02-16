#include "../headers/ConsoleInterface.h"

void loadingMenu()
{
	printf("Welcome to version 0.3 of the PSO2 ModLoader made by Cat.\n");
	printf("Now loading the program, please wait a little.\n");
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

void ConfigMenu(ConfPTR config, FILE **configFile)
{
	char tempNA[6];
	char tempMessages[6];
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
        if (config->hideMessages == 0)
        {
            strcpy(tempMessages, "(on) \0");
        }
        else
        {
            strcpy(tempMessages, "(off)\0");
        }
	    printf("|======================================|\n");
        printf("|       Configuration File Change      |\n");
        printf("| 1) Change Path1                      |\n");
        printf("| 2) Activate/Deactivate win32_na %s|\n", tempNA);
        printf("| 3) Turn On/Off Log Messages %s    |\n", tempMessages);
        printf("| 9) Remake all the folders            |\n");
        printf("| 0) Back                              |\n");
        printf("|======================================|\n");
		printf("Option: ");
		scanf("%d", &y);
		if (y == 1)
		{
			changeConfig(config, configFile);
		}
		else if (y == 2)
        {
            ChangeNAFolderUsage(config, configFile);
        }
        else if(y == 3)
        {
            turnMessages(config, configFile);
        }
        else if(y == 9)
        {
            remakeFolders(config);
        }
		else
		{
			break;
		}
	}
	return;
}
