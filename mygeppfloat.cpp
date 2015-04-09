/*
*   Name Removed for CPSC 450 Students to figure out ALGORITHM 6.2
*
*   To solve the n by n linear system
*
*   E1:  A[1,1] X[1] + A[1,2] X[2] +...+ A[1,n] X[n] = A[1,n+1]
*   E2:  A[2,1] X[1] + A[2,2] X[2] +...+ A[2,n] X[n] = A[2,n+1]
*   :
*   .
*   EN:  A[n,1] X[1] + A[n,2] X[2] +...+ A[n,n] X[n] = A[n,n+1]
*
*   INPUT:   number of unknowns and equations n; augmented
*            matrix A = (A(I,J)) where 1<=I<=n and 1<=J<=n+1.
*
*   OUTPUT:  solution x(1), x(2),...,x(n) or a message that the
*            linear system has no unique solution.
*/

#include<stdio.h>
#include <fstream>
#include<math.h>
#include <iostream>
#include <vector>
#define ZERO 1.0E-10
#define ASIZE 10
#define true 1
#define false 0
using namespace std;

float absval(float);
void INPUT(int *OK, float **&A, int *nVal, float bVal);
void OUTPUT(int, int, int, int *, float *, float **&A);
void makeMultipliersFile(float **&A, int nVal, int * NROW);

int main()
{
   //float A[103][104], X[103];
   float X[(ASIZE*ASIZE)/2];
   float** A = new float*[ASIZE];
   for(int i = 0; i < ASIZE; ++i)
   {
       A[i] = new float[ASIZE+1];
   }



   float AMAX,XM,SUM;
   int NROW[ASIZE];
   int M,ICHG,I,NN,IMAX,J,JJ,IP,JP,NCOPY,I1,J1,N1,K,N2,KK,OK;
    OK = true;
    vector<float> multipliers;
    int N;
    float bValue;
    N = 7;//101;
    N = 3+N;
    bValue = 100;

   INPUT(&OK, A, &N, bValue);

   for(int i = 0; i < ASIZE; i++)
   {
       for(int j = 0; j < ASIZE+1; j++)
       {
           cout << A[i][j] << " ";
       }
       cout << endl;
   }
   if (OK) {
      M = N + 1;
      /* STEP 1 */
      for (I=1; I<=N; I++) NROW[I-1] = I;
      /* initialize row pointer */
      NN = N - 1;
      ICHG = 0;
      I = 1;
      /* STEP 2 */
      while ((OK) && (I <= NN)) {
         /* STEP 3 */
         IMAX = NROW[I-1];
         AMAX = absval(A[IMAX-1][I-1]);
         IMAX = I;
         JJ = I + 1;
         for (IP=JJ; IP<=N; IP++) {
            JP = NROW[IP-1];
            if (absval(A[JP-1][I-1]) > AMAX) {
               AMAX = absval(A[JP-1][I-1]);
               IMAX = IP;
            }
         }
         /* STEP 4 */
         if (AMAX <= ZERO) OK = false;
         else {
            /* STEP 5 */
            /* simulate row interchange */
            if ( NROW[I-1] != NROW[IMAX-1]) {
               ICHG = ICHG + 1;
               NCOPY = NROW[I-1];
               NROW[I-1] = NROW[IMAX-1];
               NROW[IMAX-1] = NCOPY;
            }
            I1 = NROW[I-1];
            /* STEP 6 */
            for (J=JJ; J<=N; J++) {
               J1 = NROW[J-1];
               /* STEP  7 */
               XM = A[J1-1][I-1] / A[I1-1][I-1];
               /* STEP 8 */
               for (K=JJ; K<=M; K++)
                  A[J1-1][K-1] = A[J1-1][K-1] - XM * A[I1-1][K-1];
               /* Multiplier XM could be saved in A[J1-1,I-1]  */
               A[J1-1][I-1] = XM;
               cout << XM << " ";
               multipliers.push_back(XM);
            }
         }
         I++;
      }
      if (OK) {
         /* STEP 9 */
         N1 = NROW[N-1];
         if (absval(A[N1-1][N-1]) <= ZERO) OK = false;
         /* system has no unique solution */
         else {
            /* STEP 10 */
            /* start backward substitution */
            X[N-1] = A[N1-1][M-1] / A[N1-1][N-1];
            /* STEP 11 */
            for (K=1; K<=NN; K++) {
               I = NN - K + 1;
               JJ = I + 1;
               N2 = NROW[I-1];
               SUM = 0.0;
               for (KK=JJ; KK<=N; KK++) {
                  SUM = SUM - A[N2-1][KK-1] * X[KK-1];
               }
               X[I-1] = (A[N2-1][N] + SUM) / A[N2-1][I-1];
            }
            /* STEP 12 */
            /* procedure completed successfully */
            OUTPUT(N, M, ICHG, NROW, X, A);
         }
      }
      if (!OK) printf("System has no unique solution\n");
   }
   int row = 1;
   for(int i = 0; i < ASIZE; i++)
   {
       for(int j = 0; j < ASIZE+1; j++)
       {
           if(i == NROW[j]-1)
            {
               for(int k = 0; k < row; k++)
               {
                   cout << A[i][k] << " ";
               }
               row++;
               cout << endl;
            }
       }
   }
   cout << "before Multipliers" << endl;
    makeMultipliersFile(A, N, NROW);
   cout << "END" << endl;
   return 0;
}

void INPUT(int *OK, float **&A, int *nVal, float bVal)
{
   int I, J;
   char AA;
   char NAME[ASIZE];
   FILE *INP;
   //float bVal;
   float cVal = bVal-2;

    //first n rows
   for(int i = 0; i+1 < *nVal; i++)
    {
        if(i < *nVal -2)
        {
            for(int j = 0; j < *nVal+1; j++)//j+1<
            {
                if(i == j)
                {
                    A[i][j] = -1;
                    //newInFile << " ";
                    A[i][j+1] = bVal;
                    //newInFile << " ";
                    A[i][j+2] = -1;
                    j+=2;
                    //newInFile << " ";
                }
                else if(j == *nVal)
                {
                    A[i][j] = cVal;
                    //newInFile << "\n";
                }
                else
                {
                    A[i][j] = 0;
                    //newInFile << " ";
                }
            }
        }
        //Last two rows in the pattern
        else if(i < *nVal-1)
        {
            //newInFile << "-1 0 1 ";
            A[i][0] = -1;
            A[i][1] = 0;
            A[i][2] = 1;

            for(int x = 0; x < *nVal - 6; x++)
            {
                A[i][x+3] = 0;
                //newInFile << " ";
            }

            A[i][*nVal-3] = 1;
            A[i][*nVal-2] = 0;
            A[i][*nVal-1] = -1;
            A[i][*nVal] = 0;
            A[i][*nVal+1] = 0;
            //newInFile << "0 1 ";
            A[i+1][0] = 0;
            A[i+1][1] = 1;
            for(int x = 0; x < *nVal - 4; x++)
            {
                A[i+1][x+2] = 0;
              //  newInFile << 0;
               // newInFile << " ";
            }
            A[i+1][*nVal-2] = -1;
            A[i+1][*nVal-1] = 0;
            A[i+1][*nVal] = 0;
            //newInFile << "-1 0 0 ";
        }

    }
    /*
    for(int i = 0; i < *nVal; i++)
    {
        for(int j = 0; j < *nVal+1; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "NVAL:" << endl;
    cout << *nVal << endl;
    */

   printf("This is Gauss Elimination modified somehow -- your job to figure out how.\n");
   printf("The array will be input from a text file in the order:\n");
   printf("A(1,1), A(1,2), ..., A(1,N+1), A(2,1), A(2,2), ..., A(2,N+1),\n");
   printf("..., A(N,1), A(N,2), ..., A(N,N+1)\n\n");
   printf("Place as many entries as desired on each line, but separate ");
   printf("entries with\n");
   printf("at least one blank.\n\n\n");
   printf("Has the input file been created? - enter Y or N.\n");
   //cin.clear();
   //cin.ignore(INT_MAX);
   ///fflush(stdin);
   ///scanf("%c",&AA);
   /*
   if ((AA == 'Y') || (AA == 'y')) {
        cout <<"HHH"<<endl;
      printf("Input the file name in the form - drive:name.ext\n");
      printf("for example:   A:DATA.DTA\n");
      scanf("%s", NAME);
      INP = fopen(NAME, "r");
      *OK = false;
      while (!(*OK)) {
         printf("Input the number of equations - an integer.\n");
            cin.clear();
            cin.ignore(INT_MAX);
            scanf("%d", nVal);
         if (*nVal > 0) {
            for (I=1; I<=*nVal; I++) {
               for (J=1; J<=*nVal+1; J++) fscanf(INP, "%f", &A[I-1][J-1]);
               fscanf(INP, "\n");
            }
            *OK = true;
            fclose(INP);
         }
         else printf("The number must be a positive integer.\n");
      }
   }
   else {
      printf("The program will end so the input file can be created.\n");
      *OK = false;
   }*/
}


void OUTPUT(int N, int M, int ICHG, int *NROW, float *X, float **&A)
{
   int I, J, FLAG;
   char NAME[ASIZE];
   FILE *OUP;

   printf("Choice of output method:\n");
   printf("1. Output to screen\n");
   printf("2. Output to text file\n");
   printf("Please enter 1 or 2.\n");
   scanf("%d", &FLAG);
   if (FLAG == 2) {
      printf("Input the file name in the form - drive:name.ext\n");
      printf("for example:   A:OUTPUT.DTA\n");
      scanf("%s", NAME);
      OUP = fopen(NAME, "w");
   }
   else OUP = stdout;
   fprintf(OUP, "GAUSSIAN ELIMINATION - WITH MYSTERY MODIFICATION\n\n");
   fprintf(OUP, "The reduced system - output by rows:\n");
   ///This was here before:
   /*
   for (I=1; I<=N; I++) {
      for (J=1; J<=N; J++) fprintf(OUP, " %11.8f", A[I-1][J-1]);
      fprintf(OUP, "\n");
   }
   */
   fprintf(OUP, "\n\nHas solution vector \n");
   for (I=3; I<=N-2; I+=5) {
      fprintf(OUP, "%12.6f    %12.6f    %12.6f    %12.6f    %12.6f\n", X[I-1], X[I], X[I+1],X[I+2],X[I+3]);
   }
   fprintf (OUP, "\nwith %d row interchange(s)\n", ICHG);
   /*
   fprintf(OUP, "\nThe rows have been logically re-ordered to:\n");
   for (I=1; I<=N; I++)
   {
        fprintf(OUP, " %2d", NROW[I-1]); fprintf(OUP,"\n");
   }*/
}

/* Absolute Value Function */
float absval(float val)
{
   if (val >= 0) return val;
   else return -val;
}


void makeMultipliersFile(float **&A, int nVal, int * NROW)
{
    FILE *newInFile;
    newInFile = fopen("multipliers.dat","w");
    bool space;
    bool prevspace;

    int row = 1;
    for(int i = 0; i < ASIZE; i++)
    {
        for(int j = 0; j < ASIZE+1; j++)
        {
            //find the correct row, in the correct order
            if(i == NROW[j]-1)
            {
                //multipliers, which is the lower-triangular region
                for(int k = 0; k < row; k++)//(int k = (ASIZE+1)*i + j; k <= row + (ASIZE+1)*i + j; k++)
                {
                    fprintf(newInFile, "%1.8f ",A[i][k]);
                }
                fprintf(newInFile, "\n");
                row += 1;

            }
        }
    }

}
