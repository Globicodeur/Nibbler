# Nibbler
Yet another snake

![demo](https://cloud.githubusercontent.com/assets/2079561/12066016/1d37cd74-afe1-11e5-9d15-8e7d8e27ac81.gif)

## Principle
This project aims to familiarize with Unix's dynamic library API: `libdl`  
In this rework of the famous game [`Snake`](http://www.wikiwand.com/en/Snake_(video_game)), we give to the player the ability to change, in real time, the graphics library used to display the game. This is done by implementing different dynamic libraries which export an interface specialization.  
The core of the program will handle the dynamic switching between those implementations:

![Core concept](https://cloud.githubusercontent.com/assets/2079561/12064829/155ed08e-afcd-11e5-836c-265cbf48b672.png)

It makes this project easily extendable with custom [graphics](https://github.com/Globidev/Nibbler/blob/master/gui/spec.hpp#L46-L59) / [audio](https://github.com/Globidev/Nibbler/blob/master/audio%2Fspec.hpp#L10-L20) implementations (there is also a [network specification](https://github.com/Globidev/Nibbler/blob/master/network%2Fspec.hpp#L36-L65) but it not currently possible to dynamically switch between network libraries).

## Building
With docker:
```sh
docker build -t nibbler-builder .
docker run --rm -it -v $PWD:/app -w /app nibbler-builder make -j$(nproc)
```

Then run it with X-Forwarding:
```sh
xhost +
docker run --rm -it \
    -v $PWD:/app \
    -w /app \
    -e DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --net host \
    nibbler-builder ./nibbler
```
Note that the use of `--net host` is just to ease the usage for network games

## Usage
The following options are available:
```
--help                Show this help message
-w [ --width ] arg    The width of the game arena
-h [ --height ] arg   The height of the game arena
-t [ --torus ]        Torus mode
-o [ --obstacles ]    Add obstacles on the map
-s [ --snakes ] arg   Number of snakes
-p [ --players ] arg  Number of players
--script arg          Python script file for AIs
--client              Join a multiplayer game
--server              Host a multiplayer game
--host arg            The host address of the multiplayer game to join
--port arg            The port of the multiplayer game to host/join
```

### AIs
The number of snakes (`--snakes`) minus the number of players (`--players`) determines the number of AIs that will be used.  
AIs are run by python scripts (thanks to [boost python](http://www.boost.org/doc/libs/1_60_0/libs/python/doc/html/index.html)).  
There are [four available scripts](https://github.com/Globidev/Nibbler/tree/master/ai) which are currently not very advanced but you can of course roll your own. See the [exposed module](https://github.com/Globidev/Nibbler/blob/master/game%2Fpython%2Fsnake_module.cpp#L16-L51) for more details on how to write AI scripts.

### Network games
Running the program with the `--server` flag will only start a TCP server.  
The server is responsible for managing the game options and will wait until the number of players specified by `--players` are connected before starting a game.  
When a player leaves prematurely, his snake will be replaced by an AI.  
Additional people can also connect to the server in order to *observe* a game.
