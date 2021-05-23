#include "../headers/LoaderConfig.h"


int openConfigFile(ConfPTR config)
{
    FILE** configFile = &config->configFile;
	*configFile = fopen("ModLoaderConfig.txt", "r");
	if (*configFile == NULL)
	{
		writeConfig(config, EMPTY);
		fclose(*configFile);
		return 0;
	}
	else
	{
		readConfig(config);
	}
	fclose(*configFile);
	return 1;
}

void MakeDirOneTime(char *path)
{
    //printf("Making folders\n");
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
    //printf("Done!\n");
}


void writeConfig(ConfPTR config, int empty)
{
    FILE** configFile = &config->configFile;
    char temp[208];
    int size = 0;
	if (empty == EMPTY)
	{
		strcpy(config->path1, "NO PATH\n");

        config->NAFolder1 = 1;
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
void readConfig(ConfPTR config)
{
    FILE** configFile = &config->configFile;
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
        writeConfig(config, EMPTY);
        return;
    }
    if(x == UPDATE)
    {
        fclose(*configFile);
        printf("\nOutdated file found, updating configuration file to new version.\n");
        writeConfig(config, UPDATE);
        printf("\nDone updating config file!\n");
        return;
    }

	return;
}

void ChangeNAFolderUsage(ConfPTR config)
{
    if (config->NAFolder1 == 1)
    {
        config->NAFolder1 = 0;
    }
    else
    {
        config->NAFolder1 = 1;
    }
    writeConfig(config, NOEMPTY);
}

void remakeFolders(ConfPTR config)
{
    char temp[208];
    int size = 0;
    memset(temp,'\0',208);
    size = strlen(config->path1) - 1;
    strncpy(temp, config->path1,size);
    MakeDirOneTime(temp);
    return;
}

void turnMessages(ConfPTR config)
{
    if (config->hideMessages == 0)
    {
        config->hideMessages = 1;
    }
    else
    {
        config->hideMessages = 0;
    }
    writeConfig(config, NOEMPTY);
}



