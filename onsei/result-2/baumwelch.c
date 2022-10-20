/**********************************************************************

  baumWelch.c: BaumWelchプログラム

    使用法: baumWelch < file.txt
      

***********************************************************************/
/*---------------------------------------------------------------------

 include files

---------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <values.h>
#include <string.h>
#include <float.h>





/*---------------------------------------------------------------------

 macros

---------------------------------------------------------------------*/
#define N               2                /* HMMの状態数              */
#define M               2                /* 出力シンボル種類数       */
#define T               1000             /* 観測シンボル長T          */
#define EPSILON         1.0e-06          /* 再推定終了の閾値         */





/*---------------------------------------------------------------------

 data definitions

---------------------------------------------------------------------*/
/* 初期状態確率 */
double pi[N] = {1.0,0.0};


/* 状態遷移確率 */
double a[N][N] = 
  {                                      /* 初期値 */
    {0.5, 0.5},
    {0.5, 0.5}
  };

/* 出力シンボル */
int V[M] = {0,1};

/* シンボル出力確率 */
double b[N][M] = 
  {                                      /* 初期値 */
    {0.5,0.5},
    {0.5,0.5}
  };





/*----------------------------------------------------------------------

 function prototype

----------------------------------------------------------------------*/
int baumWelch(int O[T],                  /* 観測記号列                */
	      double a[N][N],            /* HMM状態遷移確率           */
	      double b[N][M],            /* HMMシンボル出力確率       */
	      double pi[N]);

double forward(int O[T],                 /* 観測記号列                */
               double a[N][N],           /* HMM状態遷移確率           */
               double b[N][M],           /* HMMシンボル出力確率       */
               double pi[N],             /* HMM初期状態確率           */
               double alpha[T][N]        /* forward変数α             */
               );

double backward(int O[T],                /* 観測記号列                */
                double a[N][N],          /* HMM状態遷移確率           */
                double b[N][M],          /* HMMシンボル出力確率       */
                double pi[N],            /* HMM初期状態確率           */
                double beta[T][N]        /* backward変数β            */
                );

void printHMM(double a[N][N],            /* HMM状態遷移確率           */
	      double b[N][M],            /* HMMシンボル出力確率       */
	      double pi[N]               /* HMM初期状態確率           */
	      );





/*----------------------------------------------------------------------


  main


----------------------------------------------------------------------*/
int main(int argc, char	*argv[])
{
  int i, j, k;
  int t;
  int O[T];                               /* 観測シンボル "abba"      */



  /*------------------------------------
   学習データを読み込む
  ------------------------------------*/
  for(t=0; t<T; t++)
    fscanf(stdin,"%d",O+t);

  /*------------------------------------
   HMMパラメータを表示
  ------------------------------------*/
  fprintf(stderr,"Before Training ---------------\n");
  printHMM(a,b,pi);
  fprintf(stderr,"\n");

  /*------------------------------------
   BaumWelchアルゴリズムを実行
  ------------------------------------*/
  (void)baumWelch(O,a,b,pi);
  
  /*------------------------------------
   HMMパラメータを表示
  ------------------------------------*/
  fprintf(stderr,"After Training ----------------\n");
  printHMM(a,b,pi);
  fprintf(stderr,"\n");


  exit(0);
}





/*----------------------------------------------------------------------

 baumWelch

----------------------------------------------------------------------*/
int baumWelch(int O[],                  /* 観測記号列                 */
	      double a[N][N],           /* HMM状態遷移確率            */
	      double b[N][M],           /* HMMシンボル出力確率        */
	      double pi[N])
{
  int t;
  int i, j, k;
  double alpha[T][N];                   /* forward変数α              */
  double beta[T][N];                    /* backward変数β             */
  double prob, prob_old=-DBL_MAX;       /* 尤度(パラメータ更新後,前)  */
  double prob_forward, prob_backward;   /* forward, backward 確率     */
  double sum1,sum2;
  int n_reest = 0;                      /* 再推定回数                 */


  while(n_reest<=1000) {
    /*------------------------------------
      forward確率αを計算
    ------------------------------------*/
    prob_forward = forward(O,a,b,pi,alpha);
    prob = prob_forward;

    /*------------------------------------
      収束したら再推定を終了
    ------------------------------------*/
    if(log(prob)-log(prob_old) < EPSILON) goto END;

    /* P(λ)の値を記憶 */
    prob_old = prob;

    /* 再推定回数をインクリメント */
    n_reest++;

    /*------------------------------------
      backward確率βを計算
    ------------------------------------*/
    prob_backward = backward(O,a,b,pi,beta);

    /*------------------------------------
      πi を再推定
    ------------------------------------*/
    for(i=0; i<N; i++)
      pi[i] = (alpha[0][i] * beta[0][i]) / prob; /* ここを穴埋め(Algorithm 1の第17行)（済） */


    /*------------------------------------
      A (a_ij) を再推定
    ------------------------------------*/
    for(i=0; i<N; i++) {
      for(j=0; j<N; j++) {
	sum1 = sum2 = 0.0;
         /* 
          ここを穴埋め（済）
          (Algorithm 1の第21行)
          ...実際の行数はこの穴埋欄の行数と一致するとは限らない 
        */
        for(t = 0; t < T-1; ++t) {
          sum1 += alpha[t][i] * a[i][j] * b[j][O[t+1]] * beta[t+1][j];
          sum2 += alpha[t][i] * beta[t][j];
        }
        a[i][j] = sum1 / sum2;

      }
    }

    /*------------------------------------
      B (b_jk) を再推定
    ------------------------------------*/
    for(j=0; j<N; j++) {
      for(k=0; k<M; k++) {
	sum1 = sum2 = 0.0;
        /* 
          ここを穴埋め
          (Algorithm 1の第26行)
          ...実際の行数はこの穴埋欄の行数と一致するとは限らない
          ...Knonecker deltaの意味に注意。
        */
        //int delta[2] = {0, 1};
        for(t = 0; t < T; ++t) {
          if(V[k] == O[t]) 
            sum1 += 1 * alpha[t][j] * beta[t][j];
          else
            sum1 += 0 * alpha[t][j] * beta[t][j];
          sum2 += alpha[t][j] * beta[t][j];
        }
        b[j][k] = sum1 / sum2;
      }
    }
  }
  
 END: fprintf(stderr,"Baum-Welch estimation converged.\n");
  
  return 0;
}





/*-----------------------------------------------------------------------

 printHMM: HMMパラメータを表示

-----------------------------------------------------------------------*/
void printHMM(double a[N][N],           /* HMM状態遷移確率            */
	      double b[N][M],           /* HMMシンボル出力確率        */
	      double pi[N]              /* HMM初期状態確率            */
	      )
{
  int i, j, k;


  fprintf(stderr,"pi= ");
  for(i=0; i<N; i++) {
    fprintf(stderr,"%f ",pi[i]);
  }
  fprintf(stderr,"\n");
  
  fprintf(stderr,"A=\n");
  for(i=0; i<N; i++) {
    for(j=0; j<N; j++) {
      fprintf(stderr,"%f ",a[i][j]);
    }
    fprintf(stderr,"\n");
  }

  fprintf(stderr,"B=\n");
  for(i=0; i<N; i++) {
    for(k=0; k<M; k++) {
      fprintf(stderr,"%f ",b[i][k]);
    }
    fprintf(stderr,"\n");
  }
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



/*---------------------------------------------------------------------

 backward

---------------------------------------------------------------------*/
double backward(int O[T],                /* 観測記号列               */
		double a[N][N],          /* HMM状態遷移確率          */
		double b[N][M],          /* HMMシンボル出力確率      */
		double pi[N],            /* HMM初期状態確率          */
		double beta[T][N]        /* backward変数β           */
		)
{
  int i,j;                               /* 状態index                */
  int t;                                 /* 時間index                */
  double prob;                           /* backward確率             */


  /*------------------------------------
    初期化 (式5.8)
  ------------------------------------*/
  t = T-1;
  for(i=0; i<=N-1; i++) {
    beta[t][i] = 1.0; /* ここを穴埋め（済） */
  }
    
  /*------------------------------------
    再帰計算 (式5.9)
  ------------------------------------*/
  for(t=T-2; t>=0; t--) {
    for(i=0; i<N; i++) {
      beta[t][i] = 0.0;
      for(j=0; j<N; j++) {
	beta[t][i] += a[i][j] * b[j][O[t+1]] * beta[t+1][j] ;/* ここを穴埋め（済） */
      }
    }
  }

  /*------------------------------------
    backward確率の計算 (式5.10)
  ------------------------------------*/
  prob = 0.0;
  for(i=0; i<N; i++) {
    prob += pi[i] * b[i][0] * beta[0][i]; /* ここを穴埋め（済） */
  }

  return prob;
}
