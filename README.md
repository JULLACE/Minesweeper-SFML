# Minesweeper-SFML
A basic Minesweeper C++ application using the SFML graphics library.
Has the ability to read custom boards made from 0s and 1s.

# Requirements
[SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) using [GCC 7.3.0 MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download)


# Board Layout

On top of having randomized board layouts, you can use 0s and 1s in a regular txt file to create a custom board.

```
0000100000000000000000000
0000100000000000000000000
0000101000000000000000000
1111100000000000000000000
0000000000000100000000000
0000000000000000000000000
0000000000000000000000000
0100000010000000000000001
0000000000000000000000000
0000010000000000000000000
0000000000000000000000000
0000000000000000100000000
0000000000000000000000000
0000000000000000000000000
0000000000000000000000000
1000000000000001000000000
```

The text above will turn into:

![image](https://github.com/JULLACE/Minesweeper-SFML/assets/88823380/182131a8-01ff-4e14-8573-45e23a8bc46b)
