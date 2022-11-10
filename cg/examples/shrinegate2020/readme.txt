# コンパイル方法

gcc main.c texture.c matrix.c objects.c trackball.c -lglut -lGL -lGLU -lm
または
./compile.sh

# 操作方法

視点操作: マウスドラッグ
リセット: r
終了: q

通常モード: r
  移動: w,a,s,d (前左後右)

フリーモード: f
  移動: w,a,s,d (前左後右)
  上昇: SPACE
  下降: c
