#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "matrix.h"
#include "texture.h"
#include "objects.h"

int STAIR_RANGE = 100;
double STAIR_WIDTH = 3.0;
double STAIR_RUN = 0.34;
double STAIR_RISE = 0.34;

int TORII_INTERVAL = 5;
int TORII_RANGE = 20;

int HASHIRA_NUM = 16;
double HASHIRA_RADIUS = 0.1;
double HASHIRA_HEIGHT = 3.2;
double HASHIRA_X = 1.2;
double HASHIRA_Z = -0.17;

double NUKI_SIZE[3] = { 2.4, 0.2, 0.1 };
double NUKI_OFFSET[3] = { 0.0, 2.6, -0.17 };

double KASAGI_SIZE[3] = { 3.2, 0.2, 0.3 };
double KASAGI_OFFSET[3] = { 0.0, 3.2, -0.17 };

int SMOKE_RANGE = 60;
int SMOKE_NUM = 100;
double smokePos[100][3];
double SMOKE_WIDTH = 4.0;
double SMOKE_HEIGHT = 4.0;
double SMOKE_INTERVAL = 0.41;
double SMOKE_RANGE_X = 40.0;
double SMOKE_RANGE_Y = 10.0;

double CUBE_VERTEX[][3] = {
  { -0.5, -0.5, -0.5 },
  { 0.5, -0.5, -0.5 },
  { 0.5, 0.5, -0.5 },
  { -0.5, 0.5, -0.5 },
  { -0.5, -0.5, 0.5 },
  { 0.5, -0.5, 0.5 },
  { 0.5, 0.5, 0.5 },
  { -0.5, 0.5, 0.5 }
};

int CUBE_FACE[][4] = {
  { 3, 2, 1, 0 },
  { 2, 6, 5, 1 },
  { 6, 7, 4, 5 },
  { 7, 3, 0, 4 },
  { 0, 1, 5, 4 },
  { 7, 6, 2, 3 }
};

double CUBE_NORMAL[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

double CUBE_TEXTURE[][3] = {
	{ 0.0, 0.0 },
	{ 1.0, 0.0 },
	{ 1.0, 1.0 },
	{ 0.0, 1.0 },
};

int CUBE_TEXSIZE[][2] = {
	{ 0, 1 },
	{ 2, 1 },
	{ 0, 1 },
	{ 2, 1 },
	{ 0, 2 },
	{ 0, 2 },
};

Texture stoneTexture, toriiTexture, smokeTextures[5];
char* stoneTextureFileName = "stone.raw";
char* toriiTextureFileName = "torii.raw";
char* smokeTextureFileNames[5] = {
	"smoke1.raw",
	"smoke2.raw",
	"smoke3.raw",
	"smoke4.raw",
	"smoke5.raw"
};

double stoneTextureScale = 0.5;
double toriiTextureScale = 0.5;
double toriiTextureOffset = 1.2;

void initTextures(void) {
	int i;
	stoneTexture.fname = stoneTextureFileName;
	toriiTexture.fname = toriiTextureFileName;
	tInit(&stoneTexture);
	tInit(&toriiTexture);
	for (i = 0; i < 5; i++) {
		smokeTextures[i].fname = smokeTextureFileNames[i];
		tInit(&smokeTextures[i]);
	}
}

void hashira(int texI, double x, double z) {
	int i;
	double theta, dTheta, lTheta, rTheta, lTex, rTex, tTex, bTex;
	dTheta = 2 * M_PI / HASHIRA_NUM;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, toriiTexture.id);
	glBegin(GL_QUADS);
	for (i = 0; i < HASHIRA_NUM; i++) {
		theta = dTheta * i;
		lTheta = theta - dTheta / 2;
		rTheta = theta + dTheta / 2;
		lTex = (x * texI * toriiTextureOffset + HASHIRA_RADIUS * lTheta) * toriiTextureScale;
		rTex = (x * texI * toriiTextureOffset + HASHIRA_RADIUS * rTheta) * toriiTextureScale;
		tTex = (texI * toriiTextureOffset + HASHIRA_HEIGHT) * toriiTextureScale;
		bTex = texI * toriiTextureOffset * toriiTextureScale;
		glNormal3d(sin(theta), 0.0, cos(theta));
		glTexCoord2d(rTex, bTex);
		glVertex3d(HASHIRA_RADIUS * sin(rTheta) + x, HASHIRA_HEIGHT, HASHIRA_RADIUS * cos(rTheta) + z);
		glTexCoord2d(lTex, bTex);
		glVertex3d(HASHIRA_RADIUS * sin(lTheta) + x, HASHIRA_HEIGHT, HASHIRA_RADIUS * cos(lTheta) + z);
		glTexCoord2d(lTex, tTex);
		glVertex3d(HASHIRA_RADIUS * sin(lTheta) + x, 0.0, HASHIRA_RADIUS * cos(lTheta) + z);
		glTexCoord2d(rTex, tTex);
		glVertex3d(HASHIRA_RADIUS * sin(rTheta) + x, 0.0, HASHIRA_RADIUS * cos(rTheta) + z);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void cube(int texI, double size[3], double offset[3]) {
	int i, j;
	double pos[3], texSize[2], tex[2];

	double texOffset[2] = { texI * toriiTextureOffset, texI * toriiTextureOffset };

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, toriiTexture.id);
	glBegin(GL_QUADS);
	for (j = 0; j < 6; ++j) {
		glNormal3dv(CUBE_NORMAL[j]);
		for (i = 0; i < 4; ++i) {
			texSize[0] = size[CUBE_TEXSIZE[j][0]] * toriiTextureScale;
			texSize[1] = size[CUBE_TEXSIZE[j][1]] * toriiTextureScale;
			mMultiply(2, CUBE_TEXTURE[i], texSize, tex);
			mAdd(2, tex, texOffset, tex);
			glTexCoord2dv(tex);
			mMultiply(3, CUBE_VERTEX[CUBE_FACE[j][i]], size, pos);
			mAdd(3, pos, offset, pos);
			glVertex3dv(pos);
		}
	}
	glEnd();
}

void nuki(int texI) {
	cube(texI, NUKI_SIZE, NUKI_OFFSET);
}

void kasagi(int texI) {
	cube(texI, KASAGI_SIZE, KASAGI_OFFSET);
}

void torii(int i) {
	glPushMatrix();
	glTranslated(0.0, STAIR_RISE * i * TORII_INTERVAL, -STAIR_RUN * i * TORII_INTERVAL);
	hashira(i, -HASHIRA_X, HASHIRA_Z);
	hashira(i, HASHIRA_X, HASHIRA_Z);
	nuki(i);
	kasagi(i);
	glPopMatrix();
}

void toriis(double z) {
	int i, c = -z / STAIR_RUN / TORII_INTERVAL;
	for (i = c- TORII_RANGE; i < c+ TORII_RANGE; i++) {
		torii(i);
	}
}

void stair(int i) {
	double lTex, rTex, tTex, bTex;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stoneTexture.id);
	glBegin(GL_QUADS);

	lTex = 0.0;
	rTex = STAIR_WIDTH * stoneTextureScale;
	tTex = ((STAIR_RISE + STAIR_RUN) * i + STAIR_RISE) * stoneTextureScale;
	bTex = (STAIR_RISE + STAIR_RUN) * i * stoneTextureScale;

	// riser
	glNormal3d(0.0, 0.0, 1.0);
	glTexCoord2d(rTex, tTex);
	glVertex3d(STAIR_WIDTH / 2, i * STAIR_RISE, -i * STAIR_RUN);
	glTexCoord2d(lTex, tTex);
	glVertex3d(-STAIR_WIDTH / 2, i * STAIR_RISE, -i * STAIR_RUN);
	glTexCoord2d(lTex, bTex);
	glVertex3d(-STAIR_WIDTH / 2, (i - 1.0) * STAIR_RISE, -i * STAIR_RUN);
	glTexCoord2d(rTex, bTex);
	glVertex3d(STAIR_WIDTH / 2, (i - 1.0) * STAIR_RISE, -i * STAIR_RUN);

	tTex = ((STAIR_RISE + STAIR_RUN) * i + STAIR_RISE + STAIR_RUN) * stoneTextureScale;
	bTex = ((STAIR_RISE + STAIR_RUN) * i + STAIR_RISE) * stoneTextureScale;

	// tread
	glNormal3d(0.0, 1.0, 0.0);
	glTexCoord2d(rTex, tTex);
	glVertex3d(STAIR_WIDTH / 2, i * STAIR_RISE, -(i + 1.0) * STAIR_RUN);
	glTexCoord2d(lTex, tTex);
	glVertex3d(-STAIR_WIDTH / 2, i * STAIR_RISE, -(i + 1.0) * STAIR_RUN);
	glTexCoord2d(lTex, bTex);
	glVertex3d(-STAIR_WIDTH / 2, i * STAIR_RISE, -i * STAIR_RUN);
	glTexCoord2d(rTex, bTex);
	glVertex3d(STAIR_WIDTH / 2, i * STAIR_RISE, -i * STAIR_RUN);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void stairs(double z) {
	int i, c = -z / STAIR_RUN;
	for (i = c - STAIR_RANGE; i < c + STAIR_RANGE; i++) {
		stair(i);
	}
}

void smoke(double sPos[3], int tex) {
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, smokeTextures[tex].id);
	glBegin(GL_QUADS);
	// omote +z gawa
	glNormal3d(0.0, 0.0, 1.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(sPos[0] + SMOKE_WIDTH / 2, sPos[1] + SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(sPos[0] - SMOKE_WIDTH / 2, sPos[1] + SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(sPos[0] - SMOKE_WIDTH / 2, sPos[1] - SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(sPos[0] + SMOKE_WIDTH / 2, sPos[1] - SMOKE_HEIGHT / 2, sPos[2]);
	// ura -z gawa
	glNormal3d(0.0, 0.0, -1.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(sPos[0] - SMOKE_WIDTH / 2, sPos[1] + SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(sPos[0] + SMOKE_WIDTH / 2, sPos[1] + SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(sPos[0] + SMOKE_WIDTH / 2, sPos[1] - SMOKE_HEIGHT / 2, sPos[2]);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(sPos[0] - SMOKE_WIDTH / 2, sPos[1] - SMOKE_HEIGHT / 2, sPos[2]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}

void smokeInit(int smokeSeed) {
	int i;
	srand(smokeSeed);
	for (i = 0; i < SMOKE_NUM; i++) {
		smokePos[i][0] = rand() * SMOKE_RANGE_X / RAND_MAX - SMOKE_RANGE_X / 2.0;
		smokePos[i][1] = rand() * SMOKE_RANGE_Y / RAND_MAX - SMOKE_RANGE_Y / 2.0;
	}
}


void smokes(double z, double theta) {
	int i, j, c = z / SMOKE_INTERVAL;
	for (i = c - SMOKE_RANGE; i < c + SMOKE_RANGE; i++) {
		j = abs(i % SMOKE_NUM);
		double sPos[3] = { smokePos[j][0] + sin(theta + smokePos[j][2] / 3), smokePos[j][1] + -i * SMOKE_INTERVAL, i * SMOKE_INTERVAL };
		int tex = abs(i % 5);
		smoke(sPos, tex);
	}
}