/**********************************************************************

  メディア情報学実験「音声認識」

  recogd: HMMによるパターン認識実験

    使用法: recogd datalist

        入力    datalist: 認識用データファイル一覧ファイル


                                               2013年10月23日 高木一幸

***********************************************************************/
/*---------------------------------------------------------------------

 include files

---------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <values.h>
#include <string.h>





/*---------------------------------------------------------------------

 macros

---------------------------------------------------------------------*/
#define L               2                /* HMMの種類数              */
#define N               2                /* HMMの状態数              */
#define M               2                /* 出力シンボル種類数       */
#define T               50               /* 観測シンボル長T          */
#define NDATA           100              /* 認識用データ数           */
#define FNAMELEN        256         /* パス名,ファイル名の最大文字数 */




/*---------------------------------------------------------------------

 data definitions

---------------------------------------------------------------------*/
/* 初期状態確率 */
double pi[N] = {1.0,0.0};


/* 出力シンボル */
int V[M] = {0,1};


/* 状態遷移確率 */
double a[L][N][N] = 
  {                                      /* HMM 1 */
    {
      {0.211938, 0.821584},
      {0.799315, 0.220692},
      //{0.5, 0.5},                        /* ここに0.5の代わりにBaum-Welch */
      //{0.5, 0.5},                        /* アルゴリズムで学習した値を設定 */
    },
    {   
      {0.714125, 0.290938}, 
      {0.278728, 0.729975},                    /* HMM 2 */
      //{0.5, 0.5},                        /* ここに0.5の代わりにBaum-Welch */
      //{0.5, 0.5}                         /* アルゴリズムで学習した値を設定 */
    }
  };

/* シンボル出力確率 */
double b[L][N][M] = 
  {                                      /* HMM 1 */
    {
      {0.801838, 0.198162}, 
      {0.173149, 0.826851}, 
      //{0.5, 0.5},                        /* ここに0.5の代わりにBaum-Welch */
      //{0.5, 0.5},                        /* アルゴリズムで学習した値を設定 */
    },
    {
      {0.813771, 0.186229}, 
      {0.165128, 0.834872},                                     /* HMM 2 */
      //{0.5, 0.5},                        /* ここに0.5の代わりにBaum-Welch */
      //{0.5, 0.5}                         /* アルゴリズムで学習した値を設定 */
    }
  };





/*----------------------------------------------------------------------

 function prototype

----------------------------------------------------------------------*/
double forward(int O[T],                 /* 観測記号列                */
               double a[N][N],           /* HMM状態遷移確率           */
               double b[N][M],           /* HMMシンボル出力確率       */
               double pi[N],             /* HMM初期状態確率           */
               double alpha[T][N]        /* forward変数α             */
               );





/*----------------------------------------------------------------------


  main


----------------------------------------------------------------------*/
int main(int argc, char	*argv[])
{
  char progname[FNAMELEN];          /* このプログラムの実行ファイル名 */
  int i, j, k;
  int t;
  int O[T];                              /* 観測データ                */
  char fname_list[FNAMELEN];            /* データファイル一覧ファイル */
  FILE *fp_list;                /* データファイル一覧ファイルハンドル */
  char fname_data[FNAMELEN];             /* データファイル名          */
  FILE *fp_data;                         /* データファイルハンドル    */
  int i_data;                            /* データindex               */
  double alpha[T][N];                    /* forward変数α             */
  double prob1, prob2;                   /* HMM1とHMM2の尤度          */
  int n1;                           /* カテゴリ1と認識されたデータ数  */
  int n2;                           /* カテゴリ2と認識されたデータ数  */



  /*------------------------------------
   コマンドライン引数の処理
  ------------------------------------*/
  strcpy(progname,argv[0]);
  if(2 == argc) {
    strcpy(fname_list,argv[1]);
  }
  else {
    exit (EXIT_FAILURE);
  }


  /* 学習データファイルの一覧ファイルを開く */
  if(NULL==(fp_list=fopen(fname_list,"r"))) {
    fprintf(stderr,"%s: error in opening %s\n",progname,fname_list);
    exit(EXIT_FAILURE);
  }

  /*-------------------------------------
     認識
  -------------------------------------*/
  n1 = n2 = 0;
  for(i_data=0; i_data<NDATA; i_data++) {
    /* データの読み込み */
    if(NULL==(fgets(fname_data,FNAMELEN,fp_list))) {
      fprintf(stderr,"%s: error in reading %s\n",progname,fname_list);
      exit(EXIT_FAILURE);
    }
    fname_data[strlen(fname_data)-1] = '\0';
    if(NULL==(fp_data=fopen(fname_data,"r"))) {
      fprintf(stderr,"%s: error in opening %s\n",progname,fname_data);
      exit(EXIT_FAILURE);
    }
    for(t=0; t<T; t++)
      fscanf(fp_data,"%d",O+t);
    /* forward確率を計算し表示 */
    prob1 = log(forward(O,a[0],b[0],pi,alpha)); /* HMM1 */
    prob2 = log(forward(O,a[1],b[1],pi,alpha)); /* HMM2 */
    printf("%f\t%f\n",prob1,prob2);

    /* 各カテゴリに認識されたデータ数を集計 */
    if(prob1 >= prob2) n1++;
    if(prob1 < prob2) n2++;

    fclose(fp_data);
  }

  /* 各カテゴリに認識されたデータ数を表示 */
  printf("n1= %d\n",n1);
  printf("n2= %d\n",n2);
  fprintf(stderr,"n1= %d\n",n1);
  fprintf(stderr,"n2= %d\n",n2);

  fclose(fp_list);

  exit(0);
}


/*---------------------------------------------------------------------

 forward

----------------------------------------------------------------------*/
double forward(int O[T],                 /* 観測記号列                */
	       double a[N][N],           /* HMM状態遷移確率           */
	       double b[N][M],           /* HMMシンボル出力確率       */
	       double pi[N],             /* HMM初期状態確率           */
	       double alpha[T][N]        /* forward変数α             */
	       )
{
  int i,j;                               /* 状態index                 */
  int t;                                 /* 時間index                 */
  double sum;                            /* 積和計算用変数            */
  double prob;                           /* forward確率               */
 

  /*------------------------------------
   初期化 (式5.5)
  ------------------------------------*/
  t = 0;
  for(i=0; i<N; i++) {
    alpha[t][i] = pi[i] * b[i][O[t]]; /* ここを穴埋め （済） */
  }
    
  /*------------------------------------
   再帰計算 (式5.6)
  ------------------------------------*/
  for(t=0; t<T-1; t++) {
    for(j=0; j<N; j++) {
      //sum = 0;
      sum = 0.0;
      for(i=0; i<N; i++) {
	sum += alpha[t][i] * a[i][j]; /* ここを穴埋め（済） */
      }
      alpha[t+1][j] = sum * b[j][O[t+1]] /* ここを穴埋め（済） */;
    }
  }

  /*------------------------------------
    forward確率の計算 (式5.7)
  ------------------------------------*/
  prob = 0.0;
  for(i=0; i<N; i++) {
    prob += alpha[T-1][i]; /* ここを穴埋め（済） */
  }

  return prob;
}
