<h1 align="center"> push_swap </h1>
<h4 align="center"> My first RayCaster with miniLibX </h4>

<h5 align="center">
  <a href="#description_id">Description</a> - 
  <a href="#usage_id">Usage</a> - 
  <a href="#scene_id">Scene</a> -
  <a href="#control_id">Controls</a> -
  <a href="#tester_id">Tester</a>
</h5>

---

### Warning: The version of 42's graphic library has change since I make this project so there are some double free because of that


<h2 id="description_id"> Description of the project: </h2>

The goal of this project is to code a 3D environnement using raycasting and 42's graphic library, like the first fps games, doom or wolfenstein.

<h2 id="usage_id"> Usage of the project: </h2>

#### Compilation: (in the folder that contain the makefile)

```shell
make
```

### How to run it:

```shell
./Cub3D (scene)
```

<h2 id="scene_id"> How scene are builded: </h2>

Each file must have a ```.cub``` extension.

Each scene contain a map composed of 7 differents characters and must be closed by walls:

- ```N```/```S```/```E```/```W```: player starting position and his orientation
- ```1```: Wall
- ```0```: Empty space
- ```2```: Object

You have also to specify the texture for the wall depending of the orientation:

- ```SO path_to_the_south_texure```
- ```NO path_to_the_north_texure```
- ```WE path_to_the_west_texure```
- ```EA path_to_the_east_texure```

And for the object texture:

```S path_to_object_texture```

All texture must have ```.xpm``` extension

You also have to set the window resolution:

```R width height```

And finaly the color of Ceiling and floor, with a rgb code (range 0-255):

```C red_value,green_value,blue_value``` for the ceiling

```F red_value,green_value,blue_value``` for the floor

You have a valid example in ```maps_test/good_map_1.cub```

<h2 id="control_id"> Controls: </h2>

- ```A``` or ```Q```: strafe left
- ```D```: strafe right
- ```W``` or ```Z```: move forward
- ```S```: move backward
- ```left arrow```: rotate left
- ```right arrow```: rotate right

<h2 id="tester_id"> Tester for incorrect maps: </h2>

```shell
sh test.sh
```

You have differents settings:

- ```M```: Test incorrect maps (non closed / double player position)
- ```C```: Bad texture path
- ```V```: Empty line in the map
- ```F```: Wrong value (negative or more than 255) for ceilling and floor
- ```P```: Strings or characters who doesn't belong here 
- ```R```: Resolution error (missing argument / negative)
- ```E```: no .cub extension
- ```G```: valid file
- ```I```: Non existant file or multiple files
- ```L```: Leaks
- ```T```: All tests

