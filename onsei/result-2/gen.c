/**********************************************************************

  HMMによる記号列生成プログラム

  〜 『パターン認識と学習のアルゴリズム』上坂・尾関, pp.139--142 の
     HMMの学習実験実験用〜

  使用法: gen HMMMnum T
              HMMnum: 記号列生成に使うHMM番号 (1 or 2)
                   T: 出力記号列長 (正整数)

  変更履歴
  初版                                         2011年04月28日 高木一幸
  2014年度用に改訂：[0,1]-->[1,2]              2014年10月28日 高木一幸

**********************************************************************/
/*---------------------------------------------------------------------

 include files

---------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



/*---------------------------------------------------------------------

 macros

---------------------------------------------------------------------*/
#define L               2                /* HMMの種類数              */
#define N               2                /* HMMの状態数              */
#define M               2                /* 出力シンボル種類数       */



/*---------------------------------------------------------------------

 data definitions

---------------------------------------------------------------------*/
/* 状態遷移確率 */
double a[L][N][N] = 
  {
    {                                    /* HMM 1 */
      {0.2, 0.8},
      {0.8, 0.2},
    },
    {                                    /* HMM 2 */
      {0.8, 0.2},
      {0.2, 0.8}
    }
  };

/* シンボル出力確率 */
double b[L][N][M] = 
  {
    {                                    /* HMM 1 */
      {0.8,0.2},
      {0.2,0.8},
    },
    {                                    /* HMM 2 */
      {0.8,0.2},
      {0.2,0.8}
    }
  };



/*---------------------------------------------------------------------


 main


---------------------------------------------------------------------*/
int main(int argc,char *argv[])
{
  int k_state;                           /* 現在の状態               */
  int i_time;                            /* 離散時間カウンタ         */
  int HMMnum;                            /* 記号列生成に使うHMM番号  */
  int T;                                 /* 出力記号列長             */
  double a_rand, b_rand;         /* 遷移先と出力記号を決めるサイコロ */
  int symbol;                            /* 出力記号                 */


  /*------------------------------------
   コマンドラインオプションの処理
  ------------------------------------*/
  if(3 > argc) {
    fprintf(stderr,"文字列のDPマッチング\n");
    fprintf(stderr,"使用方法: %s HMMnum T\n",argv[0]);
    fprintf(stderr,"   HMMnum: 記号列生成に使うHMM番号 (1 or 2)\n");
    fprintf(stderr,"        T: 出力記号列長 (正整数)\n");
    exit (EXIT_FAILURE);
  }
  HMMnum = atoi(argv[1])-1;
  T = atoi(argv[2]);

  /*-------------------------------------
   乱数初期化(時刻によって乱数種を決定)
  -------------------------------------*/
  srand(time(NULL));

  /*-------------------------------------
   乱数生成(T個)
  -------------------------------------*/
  for(i_time=0; i_time<T; i_time++) {
    if(0 == i_time) {                   /* 初期状態 */
      k_state = 0;
    }
    /* 記号を出力 */
    b_rand = (double)rand()/RAND_MAX;
    if(b_rand <= b[HMMnum][k_state][0])
      symbol = 0;
    else
      symbol = 1;
    printf("%d\n",symbol);
    
    /* 次の状態を決める */
    a_rand = (double)rand()/RAND_MAX;
    if(a_rand <= a[HMMnum][k_state][0])
      k_state = 0;
    else
      k_state = 1;
  }
}