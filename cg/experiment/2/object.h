// 各オブジェクトの情報に関するヘッダファイル

// カメラの位置や視点に関する情報
GLdouble look[3];
GLdouble camerapos[3];
GLdouble originlook[3];
GLdouble origincamerapos[3];

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


// -------- 駅 --------
// ---- 駅の床 ----
// 駅の床の頂点座標
GLdouble home_floor_vertex[8][3];

// 駅の床の面
int home_floor_face[6][4];

// 駅の床の色情報
GLdouble home_floor_color[1][3];

// 駅の床のテクスチャ情報
GLdouble home_floor_texture[4][2];

// ---- 駅の建物 ----
GLdouble home_building_vertex[8][3];

// 駅の建物の面
int home_building_face[6][4];

// 駅の建物の色情報
GLdouble home_building_color[3];

// ---- 駅の建物の屋根 ----
// 駅の建物の屋根の頂点情報
GLdouble home_building_roof_vertex[5][3];

// 駅の建物の屋根の面
int home_building_roof_face[5][4];

// 駅の建物の屋根の色情報
GLdouble home_building_roof_color[3];


// ---- 空 ----
// 空の頂点座標
GLdouble sky_vertex[4][3];

// 空のテクスチャの頂点座標
GLdouble sky_texture_vertex[4][2];

// （テスト）テクスチャのテスト用
GLdouble texture_test_vertex[4][3];

// ---- 線路 ----
// 線路の下敷きの頂点座標
GLdouble rail_base_intvl;
int num_of_base;
GLdouble rail_base_vertex[8][3];

// 線路の下敷きの面
int rail_base_face[6][4];

// 線路の下敷きの色情報
GLdouble rail_base_color[3];

// レールの頂点座標
GLdouble rail_vertex[16][3];

// レールの面
int rail_face[12][4];

// レールの色情報
GLdouble rail_color[3];
