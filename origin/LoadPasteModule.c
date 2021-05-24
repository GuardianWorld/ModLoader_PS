#include "../headers/LoadPasteModule.h"

// Made By Cat (EE)

int getFileAmount(ConfPTR config, char *temp, DIR *d)
{
    struct dirent *dir;
    int x = 0;
    d = opendir(temp);
	if (d)
	{
	    while ((dir = readdir(d)) != NULL)
		{
		    //printf("%s\n", dir->d_name);
		    if(checkProhibitions(dir->d_name) == 1)
		    {
                x++;
		    }
		}
		closedir(d);
	}
    //printf("%d Files found!\n", x-2);
	return x-2;
}

void ListModInsert(ConfPTR config, gVar *buffers, int pos)
{
    int x = 0, i = 0 , files = 0;
    char temp[208];
    char textBF[208]; //Buffer Text for the GUI
    DIR *d = NULL;
	struct dirent *dir;

    int j = getFolderRestriction(config);
    if(j == 0)
    {
        printf("what");
        stringMixing(textBF, 208, "Invalid Path, please insert a valid path on Configurations.", NULL, NULL, 0);
        pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        return;
    }

	stringMixing(temp, 208, config->path1, "\\MLoader", NULL, PATHCONV);
    //strncpy(temp, config->path1,size);
    //strcat(temp, "\\MLoader");

    files = getFileAmount(config, temp, d);  //Get the amount of files on the folder

    stringMixing(textBF, 208, NULL, " Files found! \n", NULL, files);

    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);

    d = opendir(temp);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    while(gtk_events_pending()) gtk_main_iteration();

                    if(((100.00/files) * (x-2)) >= (1 * i))
                    {
                        progressBarChange((1*i), buffers->progressBar);
                        i++;
                    }
                    LoadPasteBackupModule(config, temp, dir->d_name, (strlen(config->path1)- 1), buffers, &pos);
                }
		    }
		    x++;
		}
		closedir(d);
		progressBarChange(100, buffers->progressBar);
        pos = GUIPosInsert("Done!\n", buffers->terminalTextBuffer, pos);
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

void LoadPasteBackupModule(ConfPTR config, char *path, char *filename, int SIZE, gVar *buffers, int *pos)
{
    //Backup Part
    int er = 0;
    char textBF[208];
    //Go to PSO2_bin -> data -> win32 -> GET FILE NAME -> open in write mode -> Open another file and paste on Path
    char modFile[250]; //Mod File to be get
    char backups[250]; //Mod Folder, Backups usage
    char backupsNA[250]; //Mod Folder, Backups NA usage
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250]; //Straight into the win32_na Folder it goes.

    //Go to the correct Path
    stringMixing(backups, 250, path, "\\backup\\path1\\win32\\", filename, 0);
    stringMixing(backupsNA, 250, path, "\\backup\\path1\\win32_na\\", filename, 0);

    stringMixing(data, 250, config->path1, "\\data\\win32\\", filename, PATHCONV);
    stringMixing(dataNA, 250, config->path1, "\\data\\win32_na\\", filename, PATHCONV);


    //Check if the file aleardy exists on the BACKUP folder, if exist, do nothing!
    er = CopyFile(data,backups,TRUE);
    if(er == 0)
    {
        if(config->hideMessages == 0)
        {
            stringMixing(textBF, 208, "File ", filename, " failed to backup.\n", 0);
        }
    }
    else
    {
        stringMixing(textBF, 208, "File ", filename, " backed up successfully.\n", 0);
    }
    if(strlen(textBF) != 0)
    {
        *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        memset(textBF, '\0', 208);
    }


    FILE* modded;
    if(config->NAFolder1)
    {
        modded = fopen(dataNA, "rb");
        if(modded != NULL)
        {
            fclose(modded);
            er = CopyFile(dataNA,backupsNA,TRUE);
            if(er == 0)
            {
                if(config->hideMessages == 0)
                {
                    stringMixing(textBF, 208, "NA File ", filename, " failed to backup.\n", 0);
                }
            }
            else
            {
                stringMixing(textBF, 208, "NA File ", filename, " backed up successfully.\n", 0);
            }
        }

        if(strlen(textBF) != 0)
        {
            *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
            memset(textBF, '\0', 208);
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
        stringMixing(textBF, 208, "Error Modding File ", filename, "!\n", 0);
        *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
    }
    else
    {
        if(config->hideMessages == 0)
        {
            *pos = GUIPosInsert("File Modded with Success!\n", buffers->terminalTextBuffer, pos);
        }
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
                *pos = GUIPosInsert("Error Modding File!\n", buffers->terminalTextBuffer, pos);
            }
            else
            {
                if(config->hideMessages == 0)
                {
                    *pos = GUIPosInsert("NA File Modded with Success!\n", buffers->terminalTextBuffer, pos);
                }
            }
        }


    }

    return;
}

void ListModRemoval(ConfPTR config, gVar *buffers, int pos)
{
//List that will go straight to the Path1 or Path2 Backup folders (and their respective Win32 and Win32_na)
    char win32BFolder[230];
    char purePath[230];
    char textBF[208];
    //int size;
    int x = 0, i = 0;
    int files = 0;
    DIR *d = NULL;
	struct dirent *dir;

    int j = getFolderRestriction(config);
    if(j == 0)
    {
        printf("what");
        stringMixing(textBF, 208, "Invalid Path, please insert a valid path on Configurations.", NULL, NULL, 0);
        pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        return;
    }


    stringMixing(win32BFolder, 230, config->path1, "\\MLoader\\backup\\path1\\win32", NULL, PATHCONV);
    stringMixing(purePath, 230, config->path1, "\\data\\win32", NULL, PATHCONV);

    //strcat(purePath, "\\data\\win32");
    //printf("%s\n",purePath);

    files = getFileAmount(config, win32BFolder, d);

    stringMixing(textBF, 208, NULL, " Files found! \n", NULL, files);
    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);

    d = opendir(win32BFolder);
	if (d)
	{
        //pos = GUIPosInsert("Restoring files, please wait...\n", buffers->terminalTextBuffer, pos);
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    while(gtk_events_pending()) gtk_main_iteration();

                    if(((100.00/files) * (x-2)) >= (1 * i))
                    {
                        progressBarChange((1*i), buffers->progressBar);
                        i++;
                    }

                    returnBeckups(config, win32BFolder, dir->d_name, purePath, buffers, &pos);
                    if(config->NAFolder1 == 1)
                    {
                        returnBeckupsNAFolder(config, win32BFolder, dir->d_name, purePath, buffers, &pos);
                    }
                }
		    }
		    x++;
		}
		closedir(d);
		progressBarChange(100, buffers->progressBar);
        pos = GUIPosInsert("Done!\n", buffers->terminalTextBuffer, pos);
	}


}
void returnBeckups(ConfPTR config, char *path, char *filename, char *purePath, gVar *buffers, int *pos)
{
    char data[250]; //Straight into the win32 Folder it goes.
    char textBF[208];
    char modFile[250]; //Mod File to be get
    int er = 0;
    stringMixing(data, 250, purePath, "\\", filename, 0);
    //strcpy(data, purePath);//Go to the win32 folder in pso2 data
    //strcat(data, "\\");
    //strcat(data, filename);
    //printf("Data: %s\n", data);
    //Get Mod and Paste on the win32 folder Part
    stringMixing(modFile, 250, path, "\\", filename, 0);
    //strcpy(modFile, path);
    //strcat(modFile, "\\");
    //strcat(modFile, filename);
    //printf("Backup: %s\n", modFile);
    er = CopyFile(modFile,data,FALSE);

    if(er == 0)
    {
        stringMixing(textBF, 208, "Error Restoring File ", filename, ".\n", 0);
        //printf("\nError Restoring File! Maybe the file is aleardy in use?\n");
    }
    else
    {
        if(config->hideMessages == 0)
        {
            stringMixing(textBF, 208, "File ", filename, " restored successfully!\n", 0);
            //printf("\nFile %s restored successfully!\n",filename);
        }
    }
    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
    return;
}

void returnBeckupsNAFolder(ConfPTR config, char *path, char *filename, char *purePath, gVar *buffers, int *pos)
{
    char data[250]; //Straight into the win32 Folder it goes.
    char modFile[250]; //Mod File to be get
    char textBF[208];
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
            stringMixing(textBF, 208, "Error Restoring NA File ", filename, ".\n", 0);
        }
        else
        {
            if(config->hideMessages == 0)
            {
                stringMixing(textBF, 208, "NA File ", filename, " restored successfully!\n", 0);
                //printf("NA File %s Restored with Success!\n",filename);
            }
        }
        pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
    }

    return;
}

