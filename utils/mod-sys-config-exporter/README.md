## mod-sys-config-exporter

Just a small mod to dump *system.ltx* configuration


### Installation

Copy **config-exporter.script** in **<path/to/Anomaly>/gamedata/scripts/**


### Usage

Run Anomaly with the `-dbg` command argument and start a game (new game or saved game)


Once the map loaded, press F7, go to the Action section and run "Export System Config",
this should create a file (*outfile.ini*) in the current dir with all the section / keys created by **system.ltx**

*Export Sys. Config Ext.* action can also be used to dump extra keys:

* <anm_name>_mlength: Time (in ms) to run the animation
