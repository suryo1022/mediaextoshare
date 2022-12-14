#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define TEXWIDTHSTONE 256
#define TEXHEIGHTSTONE 256
#define TEXWIDTHGRASS1 128
#define TEXHEIGHTGRASS1 128
#define TEXWIDTHGRASS2 256
#define TEXHEIGHTGRASS2 256
#define TEXWIDTHWALL1 512
#define TEXHEIGHTWALL1 512
#define TEXWIDTHROOF 256
#define TEXHEIGHTROOF 256
#define TEXWIDTHFLOOR 1024
#define TEXHEIGHTFLOOR 1024
#define TEXWIDTHWINDOW 512
#define TEXHEIGHTWINDOW 512

GLuint texname[6];

static const char nametexturestone[] = "stone_rail-256x256.raw";
static const char nametexturegrass1[] = "water-128x128.raw";
static const char nametexturegrass2[] = "grass-256x256-2.raw";
static const char nametexturewall1[] = "wall-512x512.raw";
static const char nametextureroof[] = "roof-256x256.raw";
static const char nametexturefloor[] = "floor-1024x1024.raw";
static const char nametexturewindow[] = "window-512x512.raw";


void init_texture(void) {
    GLubyte texturestone[TEXHEIGHTSTONE][TEXWIDTHSTONE][3];
    GLubyte texturegrass1[TEXHEIGHTGRASS1][TEXWIDTHGRASS1][3];
    GLubyte texturegrass2[TEXHEIGHTGRASS2][TEXWIDTHGRASS2][3];
    GLubyte texturewall1[TEXWIDTHWALL1][TEXHEIGHTWALL1][3];
    GLubyte textureroof[TEXWIDTHROOF][TEXHEIGHTROOF][3];
    GLubyte texturefloor[TEXWIDTHFLOOR][TEXHEIGHTFLOOR][3];
    GLubyte texturewindow[TEXWIDTHWINDOW][TEXHEIGHTWINDOW][3];

    FILE *fp;

    if ((fp = fopen(nametexturestone, "rb")) != NULL) {
        fread(texturestone, sizeof texturestone, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturestone);
    }

    if ((fp = fopen(nametexturegrass1, "rb")) != NULL) {
        fread(texturegrass1, sizeof texturegrass1, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturegrass1);
    }

    if ((fp = fopen(nametexturegrass2, "rb")) != NULL) {
        fread(texturegrass2, sizeof texturegrass2, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturegrass2);
    }

    if ((fp = fopen(nametexturewall1, "rb")) != NULL) {
        fread(texturewall1, sizeof texturewall1, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturewall1);
    }

    if ((fp = fopen(nametextureroof, "rb")) != NULL) {
        fread(textureroof, sizeof textureroof, 1, fp);
        fclose(fp);
    } else {
        perror(nametextureroof);
    }

    if ((fp = fopen(nametexturefloor, "rb")) != NULL) {
        fread(texturefloor, sizeof texturefloor, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturefloor);
    }

    if ((fp = fopen(nametexturewindow, "rb")) != NULL) {
        fread(texturewindow, sizeof texturewindow, 1, fp);
        fclose(fp);
    } else {
        perror(nametexturewindow);
    }

    // テクスチャ画像はバイト単位に詰め込まれている
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // テスト用テクスチャのID生成
    // いつか配列にまとめ、for文で記述したい
    glGenTextures(1, &texname[0]);
    glBindTexture(GL_TEXTURE_2D, texname[0]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHSTONE, TEXHEIGHTSTONE, GL_RGB, GL_UNSIGNED_BYTE, texturestone);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(2, &texname[1]);
    glBindTexture(GL_TEXTURE_2D, texname[1]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHGRASS1, TEXHEIGHTGRASS1, GL_RGB, GL_UNSIGNED_BYTE, texturegrass1);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(3, &texname[2]);
    glBindTexture(GL_TEXTURE_2D, texname[2]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHGRASS2, TEXHEIGHTGRASS2, GL_RGB, GL_UNSIGNED_BYTE, texturegrass2);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(4, &texname[3]);
    glBindTexture(GL_TEXTURE_2D, texname[3]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHSTONE, TEXHEIGHTSTONE, GL_RGB, GL_UNSIGNED_BYTE, texturewall1);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(5, &texname[4]);
    glBindTexture(GL_TEXTURE_2D, texname[4]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHSTONE, TEXHEIGHTSTONE, GL_RGB, GL_UNSIGNED_BYTE, textureroof);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(6, &texname[5]);
    glBindTexture(GL_TEXTURE_2D, texname[5]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHSTONE, TEXHEIGHTSTONE, GL_RGB, GL_UNSIGNED_BYTE, texturefloor);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(7, &texname[6]);
    glBindTexture(GL_TEXTURE_2D, texname[6]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTHSTONE, TEXHEIGHTSTONE, GL_RGB, GL_UNSIGNED_BYTE, texturewindow);
    glBindTexture(GL_TEXTURE_2D, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
