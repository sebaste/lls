# lls

A custom implementation of the `ls` command. It supports various flags similar to the original `ls` command.

## Features

These flags are supported:
  - `-a`: Include hidden files.
  - `-d`: List directory names instead of their contents.
  - `-g`: Exclude owner information.
  - `-G`: Exclude group information.
  - `-h`: Human-readable file sizes.
  - `-l`: Provide a long listing format.
  - `-r`: Reverse the order of the sort.
  - `-R`: Recursively list subdirectories.
  - `-t`: Sort by modification time.

## Prerequisite(s)

* gcc

## Build

```
make
```
This will generate the `lls` executable.

To clean up object files generated during the build process, run:
```
make clean
```

# Run

```
./lls <flags>
```
