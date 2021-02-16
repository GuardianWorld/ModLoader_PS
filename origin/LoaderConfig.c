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

void MakeDirOneTime(char *path)
{
    printf("Making folders\n");
    char temporary[250]; //Mod Folder, Backups usage
    char temporary2[250];
    strcpy(temporary, path);
    strcat(temporary, "\\MLoader");
    mkdir(temporary);
    strcat(temporary, "\\backup");
    mkdir(temporary);
    strcat(temporary, "\\path1");
    mkdir(temporary);
    strcpy(temporary2, temporary);
    strcat(temporary, "\\win32");
    strcat(temporary2, "\\win32_na");
    mkdir(temporary);
    mkdir(temporary2);
    printf("Done!\n");
}


void writeConfig(ConfPTR config, FILE **configFile, int empty)
{
    char option[2];
    char temp[208];
    int size = 0;
	if (empty == EMPTY)
	{
		printf("Welcome to the Setup of the PSO2 Mod Loader!\n");
		printf("First, lets get some information to get it working.\n");
		printf("Please input the full path to the PSO2_bin you using.\n");
		printf("Keep in mind a MLoader folder will be made inside it.\n");
		printf("pso2_bin folder path: ");
		memset(config->path1, '\0', 200);
		fgets(config->path1, 200, stdin);
        printf("Allow the Mod Loader to change files in the win32_na folder? (For PSO2 Global only) \n (This configuration can be changed at any time in the main menu).\n");
        printf("Please select Y/N: ");
        fgets(option, 2, stdin);
        if(option[0] == 'y' || option[0] == 'Y')
        {
            config->NAFolder1 = 1;
        }
        else
        {
            config->NAFolder1 = 0;
        }
        config->hideMessages = 1;
	}

    if(empty == UPDATE)
    {
        if(config->hideMessages != 0 && config->hideMessages != 1) //If it's being updated, and it's trash values, then it must be re-done.
        {
            config->hideMessages = 1;
        }
    }

	*configFile = fopen("ModLoaderConfig.txt", "w");
	fprintf(*configFile, config->path1);
    fprintf(*configFile, "%d\n", config->NAFolder1);
    fprintf(*configFile, "%d\n", config->hideMessages);
    fprintf(*configFile, "V3");
    if (empty == EMPTY)
    {
        memset(temp,'\0',208);
        size = strlen(config->path1) - 1;
        strncpy(temp, config->path1,size);
        MakeDirOneTime(temp);
    }
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
		else if (x == 1)
        {
            config->NAFolder1 = atoi(tempPath);
        }
        else if(x == 2)
        {
            //Backwards updatability
            if(strcmp(tempPath, "V2") == 0) //If it finds V2 here, the file is aleardy over, so it needs to be updated!
            {
                x = UPDATE;
                break;
            }
            else
            {
                config->hideMessages = atoi(tempPath);
                //printf("%s", tempPath);
            }
        }
        else if(x == 3)
        {
            if(strcmp(tempPath, "V3") != 0)
            {
                x = 99;
                break;
            }
        }
		x++;

	}

	if(x == 99)
    {
        fclose(*configFile);
        printf("\nError detected on the configuration file, remaking file.\n");
        writeConfig(config, configFile, EMPTY);
        return;
    }
    if(x == UPDATE)
    {
        fclose(*configFile);
        printf("\nOutdated file found, updating configuration file to new version.\n");
        writeConfig(config, configFile, UPDATE);
        printf("\nDone updating config file!\n");
        return;
    }

	return;
}
void changeConfig(ConfPTR config, FILE **configFile)
{
	char x[2];
	printf("Do you want to change the current path?\n");
    printf("The current location is: %s\n", config->path1);
	printf("Y/N: ");
	scanf("\n%s", x);
	if (x[0] == 'y' || x[0] == 'Y')
	{
		printf("Changing path location, please enter the location of the pso2_bin.\n");
		printf("Location: ");
        fgets(config->path1, 208, stdin);
		writeConfig(config, configFile, 0);
	}

}

void ChangeNAFolderUsage(ConfPTR config, FILE **configFile)
{
    printf("Changing NA Folder Modding.\n");
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

void remakeFolders(ConfPTR config)
{
    char temp[208];
    int size = 0;
    printf("The program will attempt to create all folders again. (Be aware that no folders or files will be deleted if they aleardy exist)\n");
    memset(temp,'\0',208);
    size = strlen(config->path1) - 1;
    strncpy(temp, config->path1,size);
    MakeDirOneTime(temp);
    return;
}

void turnMessages(ConfPTR config, FILE **configFile)
{
    if(config->hideMessages == 0)
    {
        printf("Disabling load/restore messages.\n");
    }
    else
    {
        printf("Enabling load/restore messages.\n");
    }

    if (config->hideMessages == 0)
    {
        config->hideMessages = 1;
    }
    else
    {
        config->hideMessages = 0;
    }
    writeConfig(config, configFile, 0);
}
