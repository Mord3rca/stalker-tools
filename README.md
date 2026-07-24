# Stalker Tools

A set of tools used for S.T.A.L.K.E.R.'s gamefile manipulation

## dltx-resolver

Parse & resolve a S.T.A.L.K.E.R. DLTX file and spit it out
on stdout as a ConfigParser compatible INI file.

The result can be parsed by Python with:
```python
from configparser import ConfigParser

ini = ConfigParser()
ini.read('/path/to/file')
```

## stfsmount

Mount internal Stalker Filesystem with FUSE to a directory

Usage:

```sh
$ stfsmount -s --st_path=/path/to/stalker/dir <mountpoint>
```

Tested by running `dltx-resolver` on **<mountpoint>/gamedata/configs/system.ltx**

### Limitation

* Read only

* Only use `-s` since thread protection is not garanted for now

* Not so fast and do a lot of mem copy (bad)

## xdb

A tar-like executable to manipulate XDB archive (defined by a stalker gamefile containing a header, data & metadata chunks)

Only support **GNU-style** usage (no plan to change that.)

### Limitation

Don't support one-file decompression (aka: `xdb [OPTIONS] -- <FILES>` is tolerated but not supported yet)

Don't support XDB creation (`-c`) for now
