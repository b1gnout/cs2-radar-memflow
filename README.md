# cs2-radar-memflow

Radar hack for CS2 using memflow & qemu plugin.  

All libs are precompiled, proper build script to come...

To compile, install required libs (proper build process to come) using below:

[Radar in-use video](https://youtu.be/_fAjWSg8nkg)

```bash
mkdir bin
g++ main.cpp memory.cpp render.cpp game.cpp -o bin/cs2-radar -lSDL2 -lSDL2_image  -lSDL2_gfx -std=c++17 -lmemflow_ffi
sudo ./bin/cs2-radar 
```

![Screenshot from 2025-02-02 00-42-55](https://github.com/user-attachments/assets/76c44788-b036-4a66-a730-20e4175ee0dd)
