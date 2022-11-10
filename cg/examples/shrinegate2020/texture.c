#include <stdio.h>
#include <GL/glut.h>
#include "texture.h"

void tInit(TextureP texture) {
	FILE* fp;

	// read file
	if ((fp = fopen(texture->fname, "rb")) != NULL) {
    fread(texture->buf, sizeof texture->buf, 1, fp);
    fclose(fp);
  }
  else {
    perror(texture->fname);
  }

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH, TEXHEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, texture->buf);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glAlphaFunc(GL_GREATER, 0.5);

	glBindTexture(GL_TEXTURE_2D, 0);
}