#include "../headers/LoaderConfig.h"


void openConfigFile(ConfPTR config, FILE **configFile)
{
	*configFile = fopen("ModLoaderConfig.txt", "r");
	if (*configFile == NULL)
	{
		writeConfig(config, configFile, EMPTY);
	}
	else
	{
		readConfig(config, configFile);
	}
	fclose(*configFile);
	return;
}
void writeConfig(ConfPTR config, FILE **configFile, int empty)
{
	if (empty == EMPTY)
	{
		printf("Welcome to the Setup of the PSO2 Mod Loader!\n");
		printf("First, lets get some information to get it working.\n");
		printf("Please input the full path to the PSO2_bin you using.\n");
		printf("Remember to create a MLoader folder inside PSO2, so the mods will be get automatically!.\n");
		printf("Keep in mind a Backup folder will be made.\n");
		printf("pso2_bin folder path: ");
		memset(config->path1, '\0', 200);
		fgets(config->path1, 200, stdin);
		strcpy(config->path2, config->path1);
        config->TwoPath = 0;
		config->NAFolder1 = 0;
	}
	*configFile = fopen("ModLoaderConfig.txt", "w");
	fprintf(*configFile, config->path1);
	fprintf(*configFile, config->path2);
	fprintf(*configFile, "%d\n", config->TwoPath);
    fprintf(*configFile, "%d\n", config->NAFolder1);

	fclose(*configFile);
	return;
}
void readConfig(ConfPTR config, FILE **configFile)
{
	int x = 0;
	char tempPath[200];
	memset(tempPath, '\0', 200);
	while (fgets(tempPath, 200, *configFile))
	{
		if (x == 0)
		{
			strcpy(config->path1, tempPath);
		}
		else if(x == 1)
		{
			strcpy(config->path2, tempPath);
		}
		else if(x == 2)
		{
			config->TwoPath = atoi(tempPath);
		}
		else
        {
            config->NAFolder1 = atoi(tempPath);
        }
		x++;
	}
	return;
}
void changeConfig(ConfPTR config, FILE **configFile, int path)
{
	char x;
	printf("Do you want to change Path %d?\n", path);
	if (path == PATH1)
	{
		printf("The current location is: %s\n", config->path1);
	}
	else
	{
		printf("The current location is: %s\n", config->path2);
	}
	printf("Y/N: ");
	scanf("\n%c", &x);
	if (x == 'y' || x == 'Y')
	{
		printf("Changing path %d location, please enter the location of the pso2_bin\n");
		printf("Location: ");
		if (path == PATH1)
		{
			fgets(config->path1, 200, stdin);
		}
		else
		{
			fgets(config->path2, 200, stdin);
		}
		writeConfig(config, configFile, 0);
	}

}

void ChangePath2Usage(ConfPTR config, FILE **configFile)
{
    printf("Changing Path2 Usage\n");
    if (config->TwoPath == 1)
    {
        config->TwoPath = 0;
    }
    else
    {
        config->TwoPath = 1;
    }
    writeConfig(config, configFile, 0);
}

void ChangeNAFolderUsage(ConfPTR config, FILE **configFile)
{
    printf("Activating NA Folder Modding\n");
    if (config->NAFolder1 == 1)
    {
        config->NAFolder1 = 0;
    }
    else
    {
        config->NAFolder1 = 1;
    }
    writeConfig(config, configFile, 0);
}

