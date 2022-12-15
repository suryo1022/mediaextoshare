// マウスやキーボードなどの入力機構に関するヘッダファイル

// ---- 座標軸を表示するか否かのフラグ ----
int axis_flag;

// ---- カメラのの視点、位置 ----
GLdouble look[3];
GLdouble camerapos[3];
// ----  デフォルト（開いたとき）のカメラの視点、位置 ----
GLdouble originlook[3];
GLdouble origincamerapos[3];

// ---- マウスの座標保存用 ----
GLdouble mousepos[2];

// -------- マウス操作をする --------
void mouse(int button, int state, int x, int y);

// -------- マウスドラッグ --------
void motion(int x, int y);

// -------- キーボード操作をする --------
void keyboard(unsigned char key, int x, int y);