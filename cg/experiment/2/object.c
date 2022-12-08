#include <GL/glut.h>

// -------- 各オブジェクトの座標などの定義 --------

// ---- カメラの視点、位置 ----
GLdouble look[3] = {15.0, 20.0, -10.0};
GLdouble camerapos[3] = {15.0, 20.0, 10.0};
GLdouble originlook[3] = {15.0, 20.0, -10.0};
GLdouble origincamerapos[3] = {15.0, 20.0, 10.0};

// ---- （テスト）座標軸 ----
// 頂点座標 
GLdouble axis_vertex[6][3] =
{
    // x軸
    {-300, 0, 0},
    {300, 0, 0},
    // y軸
    {0, -300, 0},
    {0, 300, 0},
    // z軸
    {0, 0, -300},
    {0, 0, 300},
};

// 辺 
int axis_edge[3][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
};

// 色情報
GLdouble axis_color[3][3] =
{
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
};

// ---- （テスト）立方体 ----
// 頂点座標
GLdouble cube_vertex[8][3] = {
    {-1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0},
    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, -1.0, 1.0},
};

int cube_edge[12][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 4},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
};

// ---- 緑の地面 ----
// 頂点座標
GLdouble ground_vertex[4][3] = {
    {300.0, 0.0, -300.0},
    {300.0, 0.0, 300.0},
    {-300.0, 0.0, 300.0},
    {-300.0, 0.0, -300.0},
};


// ---- 駅の床 ----
// 駅の床の頂点座標
GLdouble home_floor_vertex[8][3] = {
    {5.0, 10.0, -75.0},
    {40.0, 10.0, -75.0},
    {40.0, 10.0, 75.0},
    {5.0, 10.0, 75.0},
    {5.0, 0.0, -75.0},
    {40.0, 0.0, -75.0},
    {40.0, 0.0, 75.0},
    {5.0, 0.0, 75.0},
};

// 駅の床の辺
int home_floor_edge[12][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 0},
};

// 駅の床の色情報
GLdouble home_floor_color[1][3] = {
    {230.0 / 255.0, 224.0 / 255.0, 117.0 / 255.0},
};

// 駅の床のテクスチャ情報
GLdouble home_floor_texture[4][2] = {
    {0.0, 1.0},
    {1.0, 1.0},
    {1.0, 0.0},
    {0.0, 0.0},
};

// ---- 空 ----
// 空の頂点座標
GLdouble sky_vertex[4][3] = {
    {5000.0, 600.0, 5000.0},
    {5000.0, 600.0, -5000.0},
    {-5000.0, 600.0, -5000.0},
    {-5000.0, 600.0, 5000.0},
};

// 空のテクスチャの頂点座標
GLdouble sky_texture_vertex[4][2] = {
    {0.0, 0.0},
    {0.0, 1.0},
    {1.0, 1.0},
    {1.0, 0.0},
};

// テスト用テクスチャの情報
GLdouble texture_test_vertex[4][3] = {
    {2.0, 19.0, -5.0},
    {12.0, 19.0, -5.0},
    {12.0, 9.0, -5.0},
    {2.0, 9.0, -5.0},
};


// ---- 線路 ----
// 線路の下敷きの頂点座標
GLdouble rail_base_intvl = 4.0;
GLdouble rail_base_vertex[8][3] = {
    {0, 0, 0},
    {0, 0, 2},
    {-13, 0, 2},
    {-13, 0, 0},
    {0, 0.5, 0},
    {0, 0.5, 2},
    {-13, 0.5, 2},
    {-13, 0.5, 0},
};

// 線路の下敷きの辺
int rail_base_edge[12][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 0},
};

// 色情報
GLdouble rail_base_color[3] = {192.0/255.0, 128.0/255.0, 0.0};

// レールの頂点座標
GLdouble rail_vertex[8][3] = {
    {0.5, 0.5, -300},
    {0.5, 0.5, 300},
    {1.5, 0.5, 300},
    {1.5, 0.5, -300},
    {0.5, 1.5, -300},
    {0.5, 1.5, 300},
    {1.5, 1.5, 300},
    {1.5, 1.5, -300},
};

// レールの辺
int rail_edge[12][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 0},
};

// 色情報
GLdouble rail_color[3] = {231.0, 234.0, 248.0};
