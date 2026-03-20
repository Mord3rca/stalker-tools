## Utils


A collection of utilities to help for dev / testing


### mod-config-exporter.lua

Copy this file in **<path/to/Anomaly>/gamedata/script/config-exorter.script**

Then, run Anomaly with the -dbg option and start a game (saved or new game)

Once the map loaded, press F7, go to the Action section and run "Export System Config"

This should create a file (*outfile.ini*) in the current dir with all the section / keys created by **system.ltx**
