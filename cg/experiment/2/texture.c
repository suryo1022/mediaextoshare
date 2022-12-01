#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define TEXWIDTH1 225
#define TEXHEIGHT1 225
#define TEXWIDTHSKY 600
#define TEXHEIGHTSKY 360

GLuint texname[2];

static const char nametexturetest[] = "floor-225x225.raw";
static const char nametexturesky[] = "sky-600x360.raw";


void init_texture(void) {
    GLubyte texturetest[TEXHEIGHT1][TEXWIDTH1][3];
    GLubyte texturesky[TEXHEIGHTSKY][TEXWIDTHSKY][3];

    FILE *fp;

    if ((fp = fopen(nametexturetest, "rb")) != NULL) {
        fread(texturetest, sizeof texturetest, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturetest);
    }

    if ((fp = fopen(nametexturesky, "rb")) != NULL) {
        fread(texturesky, sizeof texturesky, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturesky);
    }

    // テクスチャ画像はバイト単位に詰め込まれている
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    // テスト用テクスチャのID生成
    glGenTextures(1, &texname[0]);
    glBindTexture(GL_TEXTURE_2D, texname[0]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTH1, TEXHEIGHT1, GL_RGB, GL_UNSIGNED_BYTE, texturetest);
    glBindTexture(GL_TEXTURE_2D, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
