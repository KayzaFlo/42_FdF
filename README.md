# FdF

<p align="center">
  <img src="/screenjulia.png" width="50%" />
  <img src="/screenmars.gif" width="50%" />
</p>

## Description

Project from 42 School
A program that create a wireframe view of a map parsed in a .fdf file like :
```
    1 0 0 -1 -1 0 1 1 0 0 
    -1 0 0 0 1 0 0 0 0 0 
    -1 1 0 0 -1 1 0 0 0 1 
    1 -1 0 1 1 -1 0 0 -1 0 
    1 -1 -1 0 -1 0 0 0 -1 -1 
```
Created with a graphical library provided by school: 'Minilibx', working only on MacOS for now

## Installation

```
    git clone git@github.com:KayzaFlo/42_FdF.git
    make *or* make bonus
```

## Features

##### Mandatory
- Read and process any .fdf valid file
- Draw the map associated in orthographic view with correct height values
- ESC or close window exit the program properly
##### Bonus
- Dynamic Rendering
- Gradient colored height
- Dynamic Translation
- Dynamic Rotation
- Dynamic Zoom
- Dynamic Height Value

## Usage

```
    ./fdf [.fdf file]
```
[ESC] - Exit<br>
[+] : Increase Height (bonus)<br>
[-] : Decrease Height (bonus)<br>
[Left Click] : Translation (bonus)<br>
[Right Click] : Rotation (bonus)<br>
[Mouse Wheel] : Zoom (bonus)<br>

## Credits

[fgeslin](https://github.com/KayzaFlo)</br>

https://harm-smits.github.io/42docs/libs/minilibx</br>
