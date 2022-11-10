#pragma once

#define TEXWIDTH 512
#define TEXHEIGHT 512

typedef struct tex {
	GLuint id;
	char* fname;
	GLubyte buf[TEXHEIGHT][TEXWIDTH][4];
} Texture, * TextureP;

extern void tInit(TextureP texture);