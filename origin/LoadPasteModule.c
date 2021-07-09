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
    int x = 0,y = 0, i = 0 , files = 0;
    char temp[208]; //Base Folder and then Reboot Folder
    char temp2[208]; // Reboot+ Folder;
    int NGSfiles = 0, minNGS = 0;
    char textBF[208]; //Buffer Text for the GUI
    DIR *d = NULL;
    DIR *r = NULL;
	struct dirent *dir;
	struct dirent *NGSdir;

    int j = getFolderRestriction(config);
    if(j == 0)
    {
        //printf("what");
        stringMixing(textBF, 208, "Invalid Path, please insert a valid path on Configurations.", NULL, NULL, 0);
        pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        return;
    }

	stringMixing(temp, 208, config->path1, "\\MLoader\\win32", NULL, PATHCONV);
    //strncpy(temp, config->path1,size);
    //strcat(temp, "\\MLoader");

    files = getFileAmount(config, temp, d);  //Get the amount of files on the folder

    if(files == 0)
    {
        stringMixing(textBF, 208, "No Base Files Found\n", NULL, NULL, 0);
    }
    else
    {
        stringMixing(textBF, 208, NULL, " Base Files found!\n", NULL, files);
    }

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

                    if(((50.00/files) * (x-2)) >= ((1 * i)))
                    {
                        progressBarChange((1*i), buffers->progressBar);
                        i++;
                    }
                    LoadPasteBackupModule(config,temp, dir->d_name, (strlen(config->path1)- 1), buffers, &pos, 0, NULL);
                }
		    }
		    x++;
		}
		closedir(d);
		progressBarChange(50, buffers->progressBar);
        pos = GUIPosInsert("Base Done!\n", buffers->terminalTextBuffer, pos);
	}


	//NGS files go here
    stringMixing(temp, 208, config->path1, "\\MLoader\\win32reboot", NULL, PATHCONV);
    x = 0;
	d = opendir(temp);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
                y = 0;
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    stringMixing(temp2, 208, temp, "\\", dir->d_name, 0);
                    NGSfiles += getFileAmount(config, temp2, r);
                }
		    }
		    x++;
        }
		closedir(d);
	}

    if(files == 0)
    {
        stringMixing(textBF, 208, "No Reboot Files Found", NULL, NULL, 0);
    }
    else
    {
        stringMixing(textBF, 208, NULL, " Reboot Files found!\n", NULL, NGSfiles);
    }

    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
    x = 0;
    d = opendir(temp);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
                y = 0;
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    stringMixing(temp2, 208, temp, "\\", dir->d_name, 0);
                    //printf("Temp2: %s\n",temp2);
                    r = opendir(temp2);

                    if(r)
                    {
                        while((NGSdir = readdir(r)) != NULL)
                        {
                            if(y > 1)
                            {
                                //printf("NGSDIR: %s\n", NGSdir->d_name);
                                if(checkProhibitions(NGSdir->d_name) == 1)
                                {
                                    //printf("NGSdir %s\n", NGSdir->d_name);
                                    while(gtk_events_pending()) gtk_main_iteration();
                                    if(((50.00/NGSfiles) * (minNGS-2)) >= ((1 * i)))
                                    {
                                        progressBarChange(50 + (1*i), buffers->progressBar);
                                        i++;
                                    }
                                    LoadPasteBackupModuleNGS(config, temp2, NGSdir->d_name, (strlen(config->path1)- 1), buffers, &pos, dir->d_name);

                                }
                            }
                            y++;
                            minNGS++;
                        }
                    }
                    closedir(r);


                }
		    }
		    x++;
		}
		closedir(d);

		progressBarChange(100, buffers->progressBar);
        pos = GUIPosInsert("Reboot Done!\n", buffers->terminalTextBuffer, pos);
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

void LoadPasteBackupModuleNGS(ConfPTR config,char *path, char *filename, int SIZE, gVar *buffers, int *pos, char* NGSPath)
{
    //Backup Part
    int er = 0;
    char textBF[208];
    //Go to PSO2_bin -> data -> win32 -> GET FILE NAME -> open in write mode -> Open another file and paste on Path
    char modFile[250]; //Mod File to be get
    char backups[250]; //Mod Folder, Backups usage (First for Normal, then for NGS)
    char backupsNA[250]; //Mod Folder, Backups NA usage (First for Normal, then for NGS)
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250]; //Straight into the win32_na Folder it goes.
    FILE* modded;

    stringMixing(backups, 250, config->path1, "\\MLoader\\backup\\path1\\win32reboot\\", NGSPath, PATHCONV);
    mkdir(backups);
    strcat(backups, "\\");
    strcat(backups, filename);
    stringMixing(backupsNA, 250, config->path1, "\\MLoader\\backup\\path1\\win32reboot_na\\", NGSPath, PATHCONV);
    mkdir(backupsNA);
    strcat(backupsNA, "\\");
    strcat(backupsNA, filename);

    stringMixing(data, 250, config->path1, "\\data\\win32reboot\\", NGSPath, PATHCONV);
    strcat(data, "\\");
    strcat(data, filename);
    stringMixing(dataNA, 250, config->path1, "\\data\\win32reboot_na\\", NGSPath, PATHCONV);
    strcat(dataNA, "\\");
    strcat(dataNA, filename);

    modded = fopen(data, "rb");
    if(modded != NULL)
    {
        fclose(modded);
        er = CopyFile(data,backups,TRUE);
        if(er == 0)
        {
            if(config->hideMessages == 0)
            {
                stringMixing(textBF, 208, "Reboot File ", filename, " failed to backup.\n", 0);
            }
        }
        else
        {
            stringMixing(textBF, 208, "Reboot File ", filename, " backed up successfully.\n", 0);
        }
        if(strlen(textBF) != 0)
        {
            *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
            memset(textBF, '\0', 208);
        }
    }


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
                    stringMixing(textBF, 208, "Reboot NA File ", filename, " failed to backup.\n", 0);
                }
            }
            else
            {
                stringMixing(textBF, 208, "Reboot NA File ", filename, " backed up successfully.\n\0", 0);
            }
        }

        if(strlen(textBF) != 0)
        {
            pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, *pos);
            memset(textBF, '\0', 208);
        }

    }

    //Get Mod and Paste on the win32 folder Part

    strcpy(modFile, path);
    strcat(modFile, "\\");
    strcat(modFile, filename);
    modded = fopen(data, "rb");


    if(modded != NULL)
    {
        fclose(modded);
        er = CopyFile(modFile,data,FALSE);
        if(er == 0)
        {
            stringMixing(textBF, 208, "Error Modding Reboot File ", filename, "!\n", 0);
        }
        else
        {
            if(config->hideMessages == 0)
            {
                *pos = GUIPosInsert("Reboot File Modded with Success!\n", buffers->terminalTextBuffer, pos);
            }
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
                *pos = GUIPosInsert("Error Modding Reboot File!\n\0", buffers->terminalTextBuffer, pos);
            }
            else
            {
                if(config->hideMessages == 0)
                {
                    *pos = GUIPosInsert("NA Reboot File Modded with Success!\n\0", buffers->terminalTextBuffer, pos);
                }
            }
        }


    }


}

void LoadPasteBackupModule(ConfPTR config,char *path, char *filename, int SIZE, gVar *buffers, int *pos, int NGS, char* NGSPath)
{
    //Backup Part
    int er = 0;
    char textBF[208];
    //Go to PSO2_bin -> data -> win32 -> GET FILE NAME -> open in write mode -> Open another file and paste on Path
    char modFile[250]; //Mod File to be get
    char backups[250]; //Mod Folder, Backups usage (First for Normal, then for NGS)
    char backupsNA[250]; //Mod Folder, Backups NA usage (First for Normal, then for NGS)
    char data[250]; //Straight into the win32 Folder it goes.
    char dataNA[250]; //Straight into the win32_na Folder it goes.
    FILE* modded;

    //Go to the correct Path
    if(NGS == 0)
    {

        stringMixing(backups, 250, config->path1, "\\MLoader\\backup\\path1\\win32\\", filename, PATHCONV);
        stringMixing(backupsNA, 250, config->path1, "\\MLoader\\backup\\path1\\win32_na\\", filename, PATHCONV);

        stringMixing(data, 250, config->path1, "\\data\\win32\\", filename, PATHCONV);
        stringMixing(dataNA, 250, config->path1, "\\data\\win32_na\\", filename, PATHCONV);
    }
    else
    {

        stringMixing(backups, 250, config->path1, "\\MLoader\\backup\\path1\\win32reboot\\", NGSPath, PATHCONV);
        mkdir(backups);
        strcat(backups, "\\");
        strcat(backups, filename);
        stringMixing(backupsNA, 250, config->path1, "\\MLoader\\backup\\path1\\win32reboot_na\\", NGSPath, PATHCONV);
        mkdir(backupsNA);
        strcat(backupsNA, "\\");
        strcat(backupsNA, filename);

        stringMixing(data, 250, config->path1, "\\data\\win32reboot\\", NGSPath, PATHCONV);
        strcat(data, "\\");
        strcat(data, filename);
        stringMixing(dataNA, 250, config->path1, "\\data\\win32reboot_na\\", NGSPath, PATHCONV);
        strcat(dataNA, "\\");
        strcat(dataNA, filename);


    }

    //Check if the file aleardy exists on the BACKUP folder, if exist, do nothing, else, backup!
    modded = fopen(data, "rb");
    if(modded != NULL)
    {
        fclose(modded);
        er = CopyFile(data,backups,TRUE);
        if(er == 0)
        {
            if(config->hideMessages == 0)
            {
                if(NGS == 1)
                {
                    stringMixing(textBF, 208, "Reboot File ", filename, " failed to backup.\n", 0);
                }
                else
                {
                    stringMixing(textBF, 208, "File ", filename, " failed to backup.\n", 0);
                }
            }
        }
        else
        {
            if(NGS == 1)
            {
                stringMixing(textBF, 208, "Reboot File ", filename, " backed up successfully.\n", 0);
            }
            else
            {
                stringMixing(textBF, 208, "File ", filename, " backed up successfully.\n", 0);
            }
        }
        if(strlen(textBF) != 0)
        {
            *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
            memset(textBF, '\0', 208);
        }
    }



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
                    if(NGS == 1)
                    {
                        stringMixing(textBF, 208, "Reboot NA File ", filename, " failed to backup.\n", 0);
                    }
                    else
                    {
                        stringMixing(textBF, 208, "NA File ", filename, " failed to backup.\n", 0);
                    }
                }
            }
            else
            {
                if(NGS == 1)
                {
                    stringMixing(textBF, 208, "Reboot NA File ", filename, " backed up successfully.\n\0", 0);
                }
                else
                {
                    stringMixing(textBF, 208, "NA File ", filename, " backed up successfully.\n\0", 0);
                }
            }
        }

        if(strlen(textBF) != 0)
        {
            pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, *pos);
            memset(textBF, '\0', 208);
        }

    }

    //Get Mod and Paste on the win32 folder Part

    strcpy(modFile, path);
    strcat(modFile, "\\");
    strcat(modFile, filename);
    modded = fopen(data, "rb");


    if(modded != NULL)
    {
        fclose(modded);
        er = CopyFile(modFile,data,FALSE);
        if(er == 0)
        {
            if(NGS == 1)
            {
                stringMixing(textBF, 208, "Error Modding Reboot File ", filename, "!\n", 0);
            }
            else
            {
                stringMixing(textBF, 208, "Error Modding Reboot File ", filename, "!\n", 0);
            }
            //*pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, *pos);

        }
        else
        {
            if(config->hideMessages == 0)
            {
                if(NGS == 1)
                {
                   *pos = GUIPosInsert("Reboot File Modded with Success!\n", buffers->terminalTextBuffer, pos);
                }
                else
                {
                    *pos = GUIPosInsert("File Modded with Success!\n", buffers->terminalTextBuffer, pos);
                }


            }
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
                if(NGS == 1)
                {
                    *pos = GUIPosInsert("Error Modding Reboot File!\n\0", buffers->terminalTextBuffer, pos);
                }
                else
                {
                    *pos = GUIPosInsert("Error Modding File!\n\0", buffers->terminalTextBuffer, pos);
                }
            }
            else
            {
                if(config->hideMessages == 0)
                {
                    if(NGS == 1)
                    {
                      *pos = GUIPosInsert("NA Reboot File Modded with Success!\n\0", buffers->terminalTextBuffer, pos);
                    }
                    else
                    {
                      *pos = GUIPosInsert("NA File Modded with Success!\n\0", buffers->terminalTextBuffer, pos);
                    }
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
    char win32RFolder[230];
    char purePathR[230];
    char textBF[208];
    char temp2[208];
    //int size;
    int x = 0, i = 0, y = 0;
    int files = 0;
    int NGSFiles = 0, minNGS = 0;
    DIR *d = NULL;
    DIR *r = NULL;
	struct dirent *dir;
	struct dirent *NGSdir;

    int j = getFolderRestriction(config);
    if(j == 0)
    {
        //printf("what");
        stringMixing(textBF, 208, "Invalid Path, please insert a valid path on Configurations.", NULL, NULL, 0);
        pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        return;
    }


    stringMixing(win32BFolder, 230, config->path1, "\\MLoader\\backup\\path1\\win32", NULL, PATHCONV);
    stringMixing(purePath, 230, config->path1, "\\data\\win32", NULL, PATHCONV);

    stringMixing(win32RFolder, 230, config->path1, "\\MLoader\\backup\\path1\\win32reboot", NULL, PATHCONV);
    stringMixing(purePathR, 230, config->path1, "\\data\\win32reboot", NULL, PATHCONV);

    files = getFileAmount(config, win32BFolder, d);
    if(files == 0)
    {
        stringMixing(textBF, 208," No Base Files found! \n\0",NULL, NULL, files);
    }
    else
    {
        stringMixing(textBF, 208, NULL, " Base Files found! \n\0", NULL, files);
    }

    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
    //Base PSO2 Files
    d = opendir(win32BFolder);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    while(gtk_events_pending()) gtk_main_iteration();

                    if(((50.00/files) * (x-2)) >= (1 * i))
                    {
                        progressBarChange((1*i), buffers->progressBar);
                        i++;
                    }

                    returnBeckups(config, win32BFolder, dir->d_name, purePath, buffers, &pos, 0, 0, NULL);
                    if(config->NAFolder1 == 1)
                    {
                         returnBeckups(config, win32BFolder, dir->d_name, purePath, buffers, &pos, 1, 0, NULL);
                    }
                }
		    }
		    x++;
		}
		closedir(d);
		progressBarChange(50, buffers->progressBar);
        pos = GUIPosInsert("Base Done!\n\0", buffers->terminalTextBuffer, pos);
	}

    x = 0;
    d = opendir(win32RFolder);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(x > 1)
            {
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    stringMixing(temp2, 208, win32RFolder, "\\", dir->d_name, 0);
                    NGSFiles += getFileAmount(config, temp2, r);
                }
		    }
		    x++;
        }
		closedir(d);
	}

    if(files == 0)
    {
        stringMixing(textBF, 208, "No Reboot Files Found\0", NULL, NULL, 0);
    }
    else
    {
        stringMixing(textBF, 208, NULL, " Reboot Files found! \n\0", NULL, NGSFiles);
    }

    pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);


    //NGS files go here

    x = 0;
    d = opendir(win32RFolder);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if(x > 1)
		    {
                y = 0;
		        if(checkProhibitions(dir->d_name) == 1)
                {
                    stringMixing(temp2, 208, win32RFolder, "\\", dir->d_name, 0);
                    r = opendir(temp2);

                    if(r)
                    {
                        while((NGSdir = readdir(r)) != NULL)
                        {
                            if(y > 1)
                            {
                                if(checkProhibitions(NGSdir->d_name) == 1)
                                {
                                    //printf("NGSdir: %s\n", NGSdir->d_name);
                                    while(gtk_events_pending()) gtk_main_iteration();
                                    if(((50.00/NGSFiles) * (minNGS-2)) >= ((1 * i)))
                                    {
                                        progressBarChange(50 + (1*i), buffers->progressBar);
                                        i++;
                                    }
                                    returnBeckups(config, win32RFolder, NGSdir->d_name, purePathR, buffers, &pos,0, 1, dir->d_name);
                                    if(config->NAFolder1 == 1)
                                    {
                                        returnBeckups(config, win32RFolder, NGSdir->d_name, purePathR, buffers, &pos, 1, 1, dir->d_name);
                                    }
                                }
                            }
                            y++;
                            minNGS++;
                        }
                    }
                    closedir(r);
                }
		    }
		    x++;
		}
		closedir(d);
	}





    progressBarChange(100, buffers->progressBar);
    pos = GUIPosInsert("Reboot Done!\n", buffers->terminalTextBuffer, pos);

}

void returnBeckups(ConfPTR config, char *path, char *filename, char *purePath, gVar *buffers, int *pos, int NA, int NGS, char* NGSPath)
{
    char data[250]; //Straight into the win32 Folder it goes.
    char textBF[208];
    char modFile[250]; //Mod File to be get
    int er = 0;
    if(NA == 0)
    {
        if(NGS == 1)
        {
            stringMixing(data, 250, purePath, "\\", NGSPath, 0);
            stringMixing(modFile, 250, path, "\\", NGSPath, 0);

            strcat(data, "\\");
            strcat(data, filename);
            strcat(modFile, "\\");
            strcat(modFile, filename);
        }
        else
        {
            stringMixing(data, 250, purePath, "\\", filename, 0);
            stringMixing(modFile, 250, path, "\\", filename, 0);
        }
    }
    else
    {
        if(NGS == 1)
        {
            stringMixing(data, 250, purePath, "_na\\", NGSPath, 0);
            stringMixing(modFile, 250, path, "_na\\", NGSPath, 0);

            strcat(data, "\\");
            strcat(data, filename);
            strcat(modFile, "\\");
            strcat(modFile, filename);
        }
        else
        {
            stringMixing(data, 250, purePath, "_na\\", filename, 0);
            stringMixing(modFile, 250, path, "_na\\", filename, 0);
        }

    }

    FILE* modded;
    modded = fopen(data, "rb");

    if(modded != NULL)
    {
        fclose(modded);
        er = CopyFile(modFile,data,FALSE);
        if(er == 0)
        {
            if(NA == 0)
            {
                if(NGS == 1)
                {
                    stringMixing(textBF, 208, "Error Restoring Reboot File ", filename, ".\n\0", 0);
                }
                else
                {
                    stringMixing(textBF, 208, "Error Restoring Base File ", filename, ".\n\0", 0);
                }
            }
            else
            {
                if(NGS == 1)
                {
                    stringMixing(textBF, 208, "Error Restoring NA Reboot File ", filename, ".\n\0", 0);
                }
                else
                {
                    stringMixing(textBF, 208, "Error Restoring NA Base File ", filename, ".\n\0", 0);
                }
            }
            *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
        }
        else
        {
            if(config->hideMessages == 0)
            {
                if(NA == 0)
                {
                    if(NGS == 1)
                    {
                        stringMixing(textBF, 208, "Reboot File ", filename, " restored successfully!\n\0", 0);
                    }
                    else
                    {
                        stringMixing(textBF, 208, "Base File ", filename, " restored successfully!\n\0", 0);
                    }
                }
                else
                {
                    if(NGS == 1)
                    {
                        stringMixing(textBF, 208, "NA Reboot File ", filename, " restored successfully!\n\0", 0);
                    }
                    else
                    {
                        stringMixing(textBF, 208, "NA Base File ", filename, " restored successfully!\n\0", 0);
                    }
                }
                *pos = GUIPosInsert(textBF, buffers->terminalTextBuffer, pos);
            }
        }
    }

    return;
}
