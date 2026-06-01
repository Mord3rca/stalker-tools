# STalker FileSystem

A hook library to expose Stalker file structure to another program

## Usage

Preload this lib with **LD_PRELOAD** env. variable to hook system call functions of glibc

```sh
$ LD_PRELOAD=/path/to/libstfs.so <program> [args]
```
