## mod-sys-config-exporter

Just a small mod to dump *system.ltx* configuration

/!\ USAGE WARNING: Seems to cause corruption of GAMMA folder when use with ModOrganizer.
Maybe it's only my Linux install, my seteup or something really weird with ModOrganizer.

Don't plan to investigate further. You are warned.

### Installation

Copy **config_exporter.script** in **<path/to/Anomaly>/gamedata/scripts/**

### Usage

Run Anomaly with the `-dbg` command argument and start a game (new game or saved game)


Once the map loaded, press F7, go to the Action section and run "Export System Config",
this should create a file (*outfile-<unix-timestamp>.ini*) in the **appdata\logs** dir with all the section / keys created by **system.ltx**

*Export Sys. Config Ext.* action can also be used to dump extra keys:

* <anm_name>_mlength: Time (in ms) to run the animation
