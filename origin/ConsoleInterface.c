#include "../headers/ConsoleInterface.h"

void loadingMenu()
{
	char version[5] = "0.2";
	printf("Welcome to version %s of the PSO2 ModLoader made by Cat (GW)\n", version);
	printf("Now loading the program, please wait a little.\n");
	//Adicionar na memoria o arquivo de Configuração aqui ;-;
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
	    printf("|======================================|\n");
        printf("|       Configuration File Change      |\n");
        printf("| 1) Change Path1                      |\n");
        printf("| 2) Activate/Deactivate win32_na %s|\n", tempNA);
        printf("| 3) Remake all the folders            |\n");
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
            remakeFolders(config);
        }
		else
		{
			break;
		}
	}
	return;
}

void remakeFolders(ConfPTR config)
{
    char temp[208];
    int size = 0;
    printf("The program will attempt to create all folders again (Be aware that no folders or files will be deleted if they aleardy exist)\n");
    memset(temp,'\0',208);
    size = strlen(config->path1) - 1;
    strncpy(temp, config->path1,size);
    MakeDirOneTime(&temp);
    return;
}
