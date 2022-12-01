// 各オブジェクトの情報に関するヘッダファイル 

// ---- （テスト）座標軸 ----
// 頂点座標 
GLdouble axis_vertex[6][3];

// 辺 
int axis_edge[3][2];

// 色情報
GLdouble axis_color[3][3];

// ---- （テスト）立方体 ----
// 頂点座標
GLdouble cube_vertex[8][3];

int cube_edge[12][2];

// ---- 緑の地面 ----
// 頂点座標
GLdouble ground_vertex[4][3];


// ---- 駅の床 ----
// 駅の床の頂点座標
GLdouble home_floor_vertex[8][3];

// 駅の床の辺
int home_floor_edge[12][2];

// 駅の床の色情報
GLdouble home_floor_color[1][3];

// 駅の床のテクスチャ情報
GLdouble home_floor_texture[4][2];


// ---- 空 ----
// 空の頂点座標
GLdouble sky_vertex[4][3];

// 空のテクスチャの頂点座標
GLdouble sky_texture_vertex[4][2];

// （テスト）テクスチャのテスト用
GLdouble texture_test_vertex[4][3];