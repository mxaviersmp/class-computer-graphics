#ifndef MODEL3DS_H
#define MODEL3DS_H

#include <GL/glut.h>
#include <lib3ds/file.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#include <string.h>
#include <iostream>
#include <math.h>
//#include <SDL/SDL_image.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define	TEX_XSIZE	1024
#define	TEX_YSIZE	1024

//#define USE_SDL

struct _player_texture
{
  int valid; // was the loading attempt successful ?
#ifdef	USE_SDL
  SDL_Surface *bitmap;
#else
  void *bitmap;
#endif
  GLuint tex_id; //OpenGL texture ID
  float scale_x, scale_y; // scale the texcoords, as OpenGL thinks in TEX_XSIZE and TEX_YSIZE
};
typedef struct _player_texture Player_texture;


class Model3DS
{
private:
    Player_texture *pt;
    int tex_mode; // Texturing active ?
    Lib3dsFile *file;

    void render_node(Lib3dsNode *node);

public:
    Model3DS(const char *name);
    ~Model3DS();

    void draw();
};

#endif // MODEL3DS_H
