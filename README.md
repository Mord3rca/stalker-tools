# Stalker Tools

A set of tools used for S.T.A.L.K.E.R.'s gamefile manipulation

## dltx-reader

Parse a S.T.A.L.K.E.R. DLTX file and spit it out on stdout a ConfigParser.

The result can be parsed by Python with:

```python
from configparser import ConfigParser

ini = ConfigParser()
ini.read('/path/to/file')
```

### Limitation

For now, case sensitivity is an issue and depend of your filesystem ...


## TODO

Here a list of shit to do for this is usefull:

* lib: DLTX
  * [x] Override at the end of buffer processing
  * [x] Support for SafeOverride (create if not exist)
  * [x] Support for section delete
  * [x] Support for key without value (= may not be present)
  * [ ] Better error report
  * [x] Trace support

* utils: Modding LUA definition file
  * [ ] Create a LUA LS Def. file for XRay Monolith LUA Engine
  * [ ] Document it ... Cauz' reading engine's code to create a mod was annoying.

* exec: STALKER like DLTX Loader
  * [ ] Script to prepare FS for parsing (Decompress XDB, GAMMA standalone, ...)
  * [ ] Support of mod_* files

* exec: DLTX Linter
  * [ ] Why not ? Can be done by moving DLTXParser to the public API and tweeking it a bit.

* lib: Gamefiles
  * [ ] Parse gamefile structure (chunk type etc)
  * [ ] Read them all (xdb, omf, ...)
