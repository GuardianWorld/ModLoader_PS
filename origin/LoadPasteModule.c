#include "../headers/LoadPasteModule.h"

// Made By Cat (EE)

/*
TO-DO:
Make a new Void ListModRemoval, that will do the same as ListModInsert, the only difference is the folder it's
reading.

*/

void ListModInsert(ConfPTR config)
{
    char temp[208];
    int size;
    int x = 0;
    memset(temp,'\0',208);
    size = strlen(config->path1) - 1;
    strncpy(temp, config->path1,size);
    strcat(temp, "\\MLoader");
	DIR *d;
	struct dirent *dir;
	d = opendir(temp);
	if (d)
	{
	   //MakeDirOneTime(&temp);
	    printf("\n");
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
		        //printf("%s\n", dir->d_name);
		        if(checkProhibitions(&dir->d_name) == 1)
                {
                    //printf("Path %d\n", path);
                    LoadPasteBackupModule(config, &temp, &dir->d_name, size);
                    printf("\n");
                }
		    }
		    x++;
		}
		closedir(d);
	}
}

int checkProhibitions(char* dirName)
{
    if(strcmp(dirName, "backup") == 0)
    {
        return 0;
    }
    return 1;
}

void LoadPasteBackupModule(ConfPTR config, char *path, char *filename, int SIZE)
{
    //Backup Part
    int er = 0;
    //Go to PSO2_bin -> data -> win32 -> GET FILE NAME -> open in write mode -> Open another file and paste on Path
    char modFile[250]; //Mod File to be get
    char backups[250]; //Mod Folder, Backups usage
    char backupsNA[250]; //Mod Folder, Backups NA usage
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250]; //Straight into the win32_na Folder it goes.
    memset(data,'\0',250);
    memset(dataNA, '\0',250);
    char pathTemp[8];

    //Go to the correct Path
    strcpy(backups, path);
    strcpy(backupsNA, path);
    strcat(backups, "\\backup\\path1\\win32\\"); //Go to the Path1 backup folder win32
    strcat(backupsNA, "\\backup\\path1\\win32_na\\");
    strncpy(data, config->path1,SIZE);
    strncpy(dataNA, config->path1,SIZE);

    strcat(backups, filename);
    strcat(backupsNA, filename);
    //strcat(backupsNA, filename);
    strcat(data, "\\data\\win32\\"); //Go to the win32 folder in pso2 data
    strcat(dataNA, "\\data\\win32_na\\"); //Go to the win32 folder in pso2 data
    strcat(data, filename);
    strcat(dataNA, filename);
    //printf("DataNA Folder: %s\n", dataNA);
    //printf("Backup Folder: %s\n", backups);

    //Check if the file aleardy exists on the BACKUP folder, if exist, do nothing!
    er = CopyFile(data,backups,TRUE);
    if(er == 0)
    {
        printf("Backup of File %s not made, aleardy exists in Backups folder\n", filename);
    }
    else
    {
        printf("File %s made backup with success\n", filename);
    }

    FILE* modded;

    //printf("Path %d\n", P);
    if(config->NAFolder1)
    {
        modded = fopen(dataNA, "rb");
        if(modded != NULL)
        {
            fclose(modded);
            er = CopyFile(dataNA,backupsNA,TRUE);
            if(er == 0)
            {
                printf("Backup of NA File %s not made, aleardy exists in Backups folder\n",filename);
            }
            else
            {
                printf("NA File %s made backup with success\n", filename);
            }
        }

    }

    //Get Mod and Paste on the win32 folder Part
    strcpy(modFile, path);
    strcat(modFile, "\\");
    strcat(modFile, filename);
    //printf("modFile: %s\n", modFile);
    er = CopyFile(modFile,data,FALSE);

    if(er == 0)
    {
        printf("Error Modding File! Maybe the file is aleardy in use?\n");
    }
    else
    {
        printf("File Modded with Success!\n");
    }

    if(config->NAFolder1 == 1)
    {
        modded = fopen(dataNA, "rb");
        if(modded != NULL)
        {
            fclose(modded);
            er = CopyFile(modFile,dataNA,FALSE);
            if(er == 0)
            {
                printf("Error Modding File! Maybe the file is aleardy in use?\n");
            }
            else
            {
                printf("NA File Modded with Success!\n");
            }
        }


    }

    return;
}

void ListModRemoval(ConfPTR config)
{
//List that will go straight to the Path1 or Path2 Backup folders (and their respective Win32 and Win32_na)
    char win32BFolder[230];
    char purePath[230];
    int size;
    int x = 0;
    memset(win32BFolder,'\0',230);
    memset(purePath,'\0',230);

    size = strlen(config->path1) - 1;
    strncpy(win32BFolder, config->path1,size);
    strncpy(purePath, config->path1, size);
    strcat(win32BFolder, "\\MLoader\\backup\\path1\\win32");

    strcat(purePath, "\\data\\win32");
    //printf("%s\n",purePath);
	DIR *d;
	struct dirent *dir;
	d = opendir(win32BFolder);
	if (d)
	{
        printf("\n");
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
		        //printf("%s\n", dir->d_name);
		        if(checkProhibitions(&dir->d_name) == 1)
                {
                    returnBeckups(config, &win32BFolder, &dir->d_name, &purePath);
                    if(config->NAFolder1 == 1)
                    {
                        returnBeckupsNAFolder(config, &win32BFolder, &dir->d_name, &purePath);
                    }
                    printf("\n");
                }
		    }
		    x++;
		}
		closedir(d);
	}


}
void returnBeckups(ConfPTR config, char *path, char *filename, char *purePath)
{
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250];
    char modFile[250]; //Mod File to be get
    int er = 0;
    strcpy(data, purePath);//Go to the win32 folder in pso2 data
    strcat(data, "\\");
    strcat(data, filename);
    //printf("Data: %s\n", data);
    //Get Mod and Paste on the win32 folder Part
    strcpy(modFile, path);
    strcat(modFile, "\\");
    strcat(modFile, filename);
    //printf("Backup: %s\n", modFile);
    er = CopyFile(modFile,data,FALSE);

    if(er == 0)
    {
        printf("Error Restoring File! Maybe the file is aleardy in use?\n");
    }
    else
    {
        printf("File %s Restored with Success!\n",filename);
    }

    return;
}

void returnBeckupsNAFolder(ConfPTR config, char *path, char *filename, char *purePath)
{
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250];
    char modFile[250]; //Mod File to be get
    int er = 0;
    strcpy(data, purePath);//Go to the win32 folder in pso2 data
    strcat(data, "_na\\");//Add the NA to the win32
    strcat(data, filename);
    //printf("Data: %s\n", data);
    //Get Mod and Paste on the win32 folder Part
    strcpy(modFile, path);
    strcat(modFile, "_na\\");
    strcat(modFile, filename);
    //printf("Backup: %s\n", modFile);

    //differences start here
    FILE* modded;
    modded = fopen(data, "rb");

    if(modded != NULL)
    {
        //printf("Starting NA folder Restoration\n");
        fclose(modded);
        er = CopyFile(modFile,data,FALSE);
        if(er == 0)
        {
            printf("Error Restoring NA File! Maybe the file is aleardy in use?\n");
        }
        else
        {
            printf("NA File %s Restored with Success!\n",filename);
        }
    }

    return;
}
