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

// ----テクスチャ座標（四角形）  ----
GLdouble texture_vertex[4][2];
// ----テクスチャ座標（三角形）  ----
GLdouble texture_triangle_vertex[3][2];

// ---- 海 ---
// 配置間隔
GLdouble ground_intvl;
// 配置数
int ground_num;
// 頂点座標
GLdouble ground_vertex[4][3];
// 海の法線
GLdouble ground_normal[3];
// 海の色
GLdouble ground_color[3];


// -------- 駅 --------
// ---- 駅の床 ----
GLdouble home_floor_intvl;
int home_floor_yoko;
int home_floor_tate;
// 駅の床の頂点座標
GLdouble home_floor_vertex[12][3];
// 駅の床の面
int home_floor_face[6][4];
// 駅の床の色情報
GLdouble home_floor_color[1][3];
// 駅の床のテクスチャ情報
GLdouble home_floor_texture[4][2];
// 駅の床の法線
GLdouble home_floor_normal[6][3];

// ---- 駅の建物 ----
GLdouble wall_intvl;
int wall_tate;
int wall_yoko;
GLdouble home_building_vertex[24][3];
// 駅の建物の面
int home_building_face[6][4];
// 駅の建物の色情報
GLdouble home_building_color[3];
// 駅の建物の面の法線
GLdouble home_building_normal[6][3];

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

// ---- 線路 ----
// 線路の下の石の写真の配置数
int stone_rail_num;
// 線路の下の石の間隔
GLdouble stone_rail_intvl;
// 線路の下の石の頂点座標
GLdouble stone_rail_vertex[4][3];
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
