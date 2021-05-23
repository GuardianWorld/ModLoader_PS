#include "../headers/Callbacks.h"

//Called when the mainWindow is closed

void initializeUI(GtkBuilder *builder,UI *gui)
{

    //Initialize Main Window
    gui->mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
    //mainImage = GTK_WIDGET(gtk_builder_get_object(builder, "MainImage"));


    //Main Window Text
    gui->scrolledWindow = GTK_WIDGET(gtk_builder_get_object(builder, "WindowScroll"));
    gui->textView =  GTK_WIDGET(gtk_builder_get_object(builder, "textView"));
    gui->edt.terminalTextBuffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "TerminalText"));
    gui->edt.progressBar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "ProgressBar"));

    //Main Window buttons
    gui->edt.btt.load = GTK_WIDGET(gtk_builder_get_object(builder, "LoadMods"));
    gui->edt.btt.restore = GTK_WIDGET(gtk_builder_get_object(builder, "RestoreFiles"));
    gui->edt.btt.easterEgg = GTK_WIDGET(gtk_builder_get_object(builder, "Easter"));


    //Initialize Menus
    gui->edt.mn.configMenu = GTK_WIDGET(gtk_builder_get_object(builder, "Config"));
    gui->edt.mn.utilMenu = GTK_WIDGET(gtk_builder_get_object(builder, "Util"));
    gui->edt.mn.aboutMenu = GTK_WIDGET(gtk_builder_get_object(builder, "About"));
    gui->edt.mn.quitMenu = GTK_WIDGET(gtk_builder_get_object(builder, "Quit"));

    //Initalize configOptions
    gui->opt.chPath = GTK_WIDGET(gtk_builder_get_object(builder, "ChPath"));
    gui->opt.win32NAEnable = GTK_WIDGET(gtk_builder_get_object(builder, "Win32na"));
    gui->opt.confLogs = GTK_WIDGET(gtk_builder_get_object(builder, "Logs"));
    gui->opt.redFolder = GTK_WIDGET(gtk_builder_get_object(builder, "Redo"));


    //Initialize EndWindow
    //endW.endWindow = GTK_WIDGET(gtk_builder_get_object(builder, "EndWindow"));
    //gtk_builder_connect_signals(builder, NULL);


    if(gui->edt.pConfig->NAFolder1 == 1)
    {
          gtk_check_menu_item_set_active(gui->opt.win32NAEnable, 1);
    }
    if(gui->edt.pConfig->hideMessages == 0)
    {
        gtk_check_menu_item_set_active(gui->opt.confLogs, 1);
    }
}

void initializeRequests(UI *gui)
{
    gtk_widget_set_size_request(gui->scrolledWindow, 470,100);
    gtk_widget_set_size_request(gui->textView, 470,100);
    gtk_text_buffer_create_tag (gui->edt.terminalTextBuffer, "fill_justify","justification", GTK_JUSTIFY_FILL, NULL);
}

void signalConnections(UI *gui)
{
    //Quit Signals
    g_signal_connect(G_OBJECT(gui->mainWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL); //Main Window Destroy
    g_signal_connect(G_OBJECT(gui->edt.mn.quitMenu), "activate", G_CALLBACK(gtk_main_quit), NULL);  //Quit Button for now
     g_signal_connect(G_OBJECT(gui->edt.mn.aboutMenu), "activate", G_CALLBACK(about), &gui->edt); //Easter Egg

    //Button Signals
    g_signal_connect(G_OBJECT(gui->edt.btt.load), "clicked", G_CALLBACK(modFiles), &gui->edt); //Load button
    g_signal_connect(G_OBJECT(gui->edt.btt.restore), "clicked", G_CALLBACK(restoreFiles), &gui->edt);  //Restore button
    g_signal_connect(G_OBJECT(gui->edt.btt.easterEgg), "clicked", G_CALLBACK(easter), &gui->edt); //Easter Egg

    //Config Menu Signals
    g_signal_connect(G_OBJECT(gui->opt.redFolder), "activate", G_CALLBACK(redoFolder), &gui->edt); //Redo Folders button
    g_signal_connect(G_OBJECT(gui->opt.win32NAEnable), "toggled", G_CALLBACK(win32na_toggled), &gui->edt);  //Win32NA enable button
    g_signal_connect(G_OBJECT(gui->opt.confLogs), "toggled", G_CALLBACK(logs_toggled), &gui->edt); //Easter Egg
    g_signal_connect(G_OBJECT(gui->opt.chPath), "activate", G_CALLBACK(changePath), gui); //Easter Egg
}


void start(gVar *buffers, int NAFolderMode)
{
    GtkTextIter iter;
    GtkTextBuffer *buffer = buffers->terminalTextBuffer;

    gtk_text_buffer_set_text(buffer, "\0", -1);
    gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
    gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,"Program Started! \n", -1,"fill_justify", NULL);
    gtk_text_buffer_get_iter_at_offset (buffer, &iter, 18);
    if(NAFolderMode == 0)
    {
        gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,"NA Folder modding is currently disabled \n", -1,"fill_justify", NULL);
    }
    else
    {
        gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,"NA Folder modding is currently enabled \n", -1,"fill_justify", NULL);
    }
}

void modFiles(GtkWidget *widget, gVar *buffers)
{

    int pos = GUIPosInsert("Modding Files, please wait!\n", buffers->terminalTextBuffer, 0);
    diEn(buffers, 0);
    while(gtk_events_pending()) gtk_main_iteration();
    ListModInsert(buffers->pConfig, buffers, pos);
    diEn(buffers, 1);
}

void diEn(gVar *buffers, int active)
{
    gtk_widget_set_sensitive (buffers->btt.load, active);
    gtk_widget_set_sensitive (buffers->btt.restore, active);
    gtk_widget_set_sensitive (buffers->mn.quitMenu, active);
    gtk_widget_set_sensitive (buffers->mn.configMenu, active);
    gtk_widget_set_sensitive (buffers->mn.utilMenu, active);
    gtk_widget_set_sensitive (buffers->btt.easterEgg, active);
    gtk_widget_set_sensitive (buffers->mn.aboutMenu, active);
}

void restoreFiles(GtkWidget *widget, gVar *buffers)
{

    int pos = GUIPosInsert("Restoring Files, please wait!\n", buffers->terminalTextBuffer, 0);
    diEn(buffers, 0);
    while(gtk_events_pending()) gtk_main_iteration();
    ListModRemoval(buffers->pConfig, buffers, pos);
    diEn(buffers, 1);

}
void easter(GtkWidget *widget, gVar *buffers)
{
    char textFB[200];
    int value = rand() % 5;
    if(value == 0)
    {
        strcpy(textFB,"*Headpats*\n");
    }
    else if(value == 1)
    {
        strcpy(textFB, "Boop :3\n");
    }
    else if(value == 2)
    {
        strcpy(textFB, "Made by CAT (EE) \n");
    }
    else if(value == 3)
    {
        strcpy(textFB, "Have a great day!\n");
    }
    else if(value == 4)
    {
        strcpy(textFB, "I would like to thank my friends on PSO2.\nWithout them i would have not be here today <3\nI hope they have the best on their lives!\n");
    }
    int pos = GUIPosInsert(textFB, buffers->terminalTextBuffer, 0);
}

void changePath(GtkWidget *widget, UI *gui)
{
        char textTmp[240];
        stringMixing(textTmp,240,gui->edt.pConfig->path1, NULL, NULL, PATHCONV);
        GtkWidget *window;
        GtkWidget *folder;
        GtkWidget *YBT;
        GtkWidget *cPath;
        GtkWidget *applyPath;
        GtkBuilder *builder;


        builder = gtk_builder_new();
        gtk_builder_add_from_file (builder, "interface/PSO2MLLoad.interface", NULL);

        //Initialize ChangePath
        window = GTK_WIDGET(gtk_builder_get_object(builder, "StarterWindow"));
        folder = GTK_WIDGET(gtk_builder_get_object(builder, "Choose"));
        YBT = GTK_WIDGET(gtk_builder_get_object(builder, "Yes"));
        cPath = GTK_WIDGET(gtk_builder_get_object(builder, "PathText"));
        applyPath = GTK_WIDGET(gtk_builder_get_object(builder, "applyPath"));


        gui->tempEntry = folder;
        gui->tempEntry2 = cPath;

        //Signals
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_window_close), window); //Window Destroy
        g_signal_connect(G_OBJECT(YBT), "clicked", G_CALLBACK(gtk_window_close), window);  //Quit Button (YES)
        g_signal_connect(G_OBJECT(applyPath), "clicked", G_CALLBACK(on_folder_set), gui);  //Quit Button (YES)

        //Other
        gtk_widget_set_size_request(folder, 410, 35);
        gtk_entry_set_text(GTK_ENTRY(cPath), textTmp);

        g_object_unref(builder);
        gtk_widget_show_all (window);
}

void on_folder_set(GtkWidget *widget, UI *gui)
{
    char textTmp[240];
    if(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gui->tempEntry)) != NULL)
    {
        strcpy(gui->edt.pConfig->path1, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gui->tempEntry)));
        strcat(gui->edt.pConfig->path1, "\n");
        //printf("folder name = %s\n", gui->edt.pConfig->path1);
        writeConfig(gui->edt.pConfig, NOEMPTY);
        stringMixing(textTmp,240,gui->edt.pConfig->path1, NULL, NULL, PATHCONV);
        gtk_entry_set_text(GTK_ENTRY(gui->tempEntry2), textTmp);
    }
}

void win32na_toggled(GtkWidget *widget, gVar *buffers)
{
    if(buffers->pConfig->NAFolder1 == 1)
    {
        int pos = GUIPosInsert("De-activating NA Folder modding\n", buffers->terminalTextBuffer, 0);
    }
    else
    {
        int pos = GUIPosInsert("Activating NA Folder modding\n", buffers->terminalTextBuffer, 0);
    }
    diEn(buffers, 0);

    while(gtk_events_pending()) gtk_main_iteration();
    ChangeNAFolderUsage(buffers->pConfig);

    diEn(buffers, 1);
}

void logs_toggled(GtkWidget *widget, gVar *buffers)
{
    if(buffers->pConfig->hideMessages == 0)
    {
        int pos = GUIPosInsert("De-activating Terminal Logs\n", buffers->terminalTextBuffer, 0);
    }
    else
    {
        int pos = GUIPosInsert("Activating Terminal Logs\n", buffers->terminalTextBuffer, 0);
    }
    diEn(buffers, 0);

    while(gtk_events_pending()) gtk_main_iteration();
    turnMessages(buffers->pConfig);
    diEn(buffers, 1);
}


void redoFolder(GtkWidget *widget, gVar *buffers)
{
    int pos = GUIPosInsert("The program will attempt to create all folders again.\nBe aware that nothing is gonna be deleted!\n", buffers->terminalTextBuffer, 0);
    diEn(buffers, 0);
    while(gtk_events_pending()) gtk_main_iteration();
    remakeFolders(buffers->pConfig);
    pos = GUIPosInsert("Done!\n", buffers->terminalTextBuffer, pos);
    diEn(buffers, 1);
}
void about(GtkWidget *widget, gVar *buffers)
{
    char textFB[400];
    strcpy(textFB, "Made by (Cat).\nVersion 4\n");
    int pos = GUIPosInsert(textFB, buffers->terminalTextBuffer, 0);
}

void stringMixing(char *rText, int cleanSize, char *string1, char* string2, char* string3, int conversion)
{
    memset(rText, '\0',cleanSize);
    int size = 0;
    if(conversion == -99)
    {
        size = strlen(string1) - 1;
    }
    else if(conversion > 0)
    {
        sprintf(rText, "%d", conversion);
    }
    else
    {
        size = strlen(string1);
    }

    if(string1 != NULL && conversion <= 0)
    {
        strncpy(rText, string1, size);
    }
    if(string2 != NULL)
    {
        strcat(rText, string2);
    }
    if(string3 != NULL)
    {
        strcat(rText, string3);
    }

    return;
}

int GUIPosInsert(char *stringBF, GtkTextBuffer *buffer, int pos)
{
    if(pos == 0)
    {
        gtk_text_buffer_set_text(buffer, "\0", -1);
    }
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, pos); //Gets Pointer Position
    gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, stringBF, strlen(stringBF) ,"fill_justify", NULL); //Sets text at pointer position
    pos = pos + strlen(stringBF); // gives the pointer position back;
    return pos;

}

void progressBarChange(int value, GtkProgressBar *progressBar)
{
    char cValue[5];
    memset(cValue,'\0', 5);
    sprintf(cValue, "%d", value);
    strcat(cValue, "%");
    gtk_progress_bar_set_fraction (progressBar , (float)value/100);
    gtk_progress_bar_set_text (progressBar, cValue);
    return;
}
