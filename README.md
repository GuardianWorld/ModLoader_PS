	Changelog Mod Loader, made by CAT (EE).

 Version 0.4:
 - GUI made, the Terminal-Only interface is gone. The program is eating a little more memory, but almost nothing (25MB RAM maximum i saw on my side).
 - GUI has some bugs... i think... I still don't understand how that code of mine is working, that thing is cursed.. xD
 - Things are working fine~ And the way to find the PSO2_Bin folder is way better than before.
 - The program will check if the files are "ok" (Aka: Interface files are intact" before booting up completly. Please dont touch the interface folder.
 - The GUI is made in GTK 3 and Glade on Windows (Using MSYS2), it works quite well to be honest~
 - The interface is as clean as i could make, sadly it's not too big, need to enlarge i think.
 - The Config System is still on V3, did not do any changes to it on the outside, just optimizations on the code.
 
 As always, any crashes, tell me!

 Version 0.3:
 - Cleaned more of the program code, removing unused references about Path2 that stayed there.
 - The program now hides the unecessary Log Messages when printing, those can be enable on the configuration menu if wanted.
 - Added an Ex-cube Icon to look more clean.
 - Updated the configuration file, but this time it will auto-convert anything from version V2 to V3 automatically, so no need to worry about remaking the file.
 - Some more cleaniness of the printed messages.
 - Adding an Icon adds the size of that to the program itself, so now the program is 207 KB, 170 KB of that is just the icon file.
 
  Version 0.2:
 - Removed the option for using Path2, the mode was incomplete and i think it's just better to copy and paste the program on another folder.
 - Cleaned a little of the code (most was the above). Still need to clean some references and variables not used, but should be fine.
 - Made the program create the MLoader by itself on the first boot time, together with any necessary folders inside of it.
 - The program will only try to create the folders one time when it's first initialized or when config is corrupted.
 - If the config from another version with less/more stuff is found, it will declare it corrupted and start the first time initialization again!
 
 Bugs Found: Aparently sometimes it does not save the path, i don't have any steps on how to replicate that, if found, please do a bug report with how to re-do the bug.
 
 Version 0.1:
Release of ModLoader, you need to make the MLoader folder, but it can make the rest by itself without any issues. Very useful.

Bugs found: None so far!
