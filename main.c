#include "headers/LoaderConfig.h"
#include "headers/Callbacks.h"
#include "headers/LoadPasteModule.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
    int x = 0;
    //Backbone
	TypeConfig configuration;

    //UI
    GtkBuilder *builder;
    UI gui;
    gtk_init(&argc, &argv); //Starts GTK

    //Initialize Builder
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "interface/PSO2MLMain.interface", NULL);

    //Initialize Configuration
    x = openConfigFile(&configuration);
    gui.edt.pConfig = &configuration;

    //Initialize UI
    initializeUI(builder,&gui);
    initializeRequests(&gui);
    signalConnections(&gui);

    //Finish Initialization of UI
    g_object_unref(builder);
    gtk_widget_show_all(gui.mainWindow);
    start(&gui.edt, configuration.NAFolder1);

    //Checks
    if(gui.mainWindow == NULL)
    {
        return 1;
    }
    if(x == 0)
    {
        changePath(NULL, &gui);
    }
    //getFolderRestriction(&configuration);
    //changePath(NULL, &gui);
    gtk_main(); //Loops GTK
	return 0;
}
