#include "headers/ConsoleInterface.h"
#include "headers/LoaderConfig.h"
#include "headers/LoadPasteModule.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x = -1;
	FILE* configFILE;
    loadingMenu();
	TypeConfig configuration;
	openConfigFile(&configuration, &configFILE);
	while (1)
	{
		DefaultMenu(&configuration);
		//printf("%s\n", configuration.path1);
		scanf("%d", &x);
		if (x == 1)
		{
			//Check mod folder for now
            ListModInsert(&configuration);
		}
		if (x == 2)
		{
            ListModRemoval(&configuration);
		}
		if(x == 3)
        {
            printf("*Headpats*\n");
        }
        if(x == 4)
        {
            printf("Boop :3\n");
        }
            if (x == 404)
        {
            printf("Made by: CAT (EE)\n");
        }
		if (x == 9)
		{
			ConfigMenu(&configuration, &configFILE);
		}
		if (x == 0)
        {
            break;
        }
		getchar();
	}
	return 0;
}
