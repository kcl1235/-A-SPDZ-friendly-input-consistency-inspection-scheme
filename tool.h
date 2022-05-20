#include "stdio.h"
#include "gmp.h"
#include "time.h"
#include <string.h>
#include <stdlib.h>
//#include <openssl/sha.h>
#pragma comment(lib,"libgmp-10.lib")

typedef struct Basic
{
    mpz_t p;
    mpz_t h;
    mpz_t g;
}Basic;


typedef struct Commit
{
    mpz_t r;
    mpz_t Commit_Value;
} Commit;

//原paillier key
typedef struct Key
{
	mpz_t one;
	mpz_t two;
}Key;

typedef struct Check_Compute
{
    mpz_t V[3];
    mpz_t W;
    mpz_t R;
    mpz_t r;
}Check_Compute;

typedef  struct Check_Value
{
    mpz_t S[3];
    mpz_t C;
    mpz_t T;
    mpz_t Y;
    mpz_t P;
}Check_Value;

//可分布paillier key
typedef struct New_Paillier_Key
{
	mpz_t N;
	mpz_t G;
    mpz_t theta;
    mpz_t SK;
}New_Paillier_Key;

// 返回一个大数 rand_value
int Get_Big_Number(mpz_t rand_value,int len);

//返回一个不大于big_number的数 rand_vlue
int Get_Big_Number2(mpz_t rand_value,mpz_t big_number);

//判断是否为素数
int Is_Prime(mpz_t rand_value);

//得到一个大素数 prime_number
int Get_Prime_Number(mpz_t prime_number,int len);

//寻找下一个素数 prime_number
int Next_Prime(mpz_t prime_number);

//生成阶为p的群G Group_g
int Get_Group_G(mpz_t Group_g,int len,mpz_t prime_number_p,mpz_t big_number_q);

//计算commit_values = g^m * h^r mod p 
int Compute_Values(mpz_t commit_values,mpz_t Group_g,mpz_t m,mpz_t commt_h,mpz_t r,mpz_t mod_p);

//将int转换为string string
int Int_To_String(mpz_t data ,char* string);

//将string转换为int data
int String_To_Int(char* string,mpz_t data);

//初始化Commit
int Init_Commit(Commit*  Commit);

//清除commit
int Clear_Commit(Commit*  Commit);

//生成alpha i alpha
int Get_Alpha(mpz_t alpha,int len);

//计算形如H = g^alpha 
int Compute_Glpha(mpz_t Value,mpz_t g,mpz_t alpha,const mpz_t q);

//计算形如Value = glpha1 * glpha2 mod p
int Compute_G_Mul(mpz_t Value,mpz_t glpha1,mpz_t glpha2,mpz_t p);

//用于测试生成Pedersen承诺 Pedersen(单个Pedersen)
//int Pedersen(int len,mpz_t  m,commit* Pedersen,mpz_t r);


/********************************************************************
-------------------------------Paillier----------------------------------
********************************************************************

//获得公钥和私钥    PK(n,g)   SK(lambda,Mu)
int Get_Key(Key*  PK,Key*  SK,int len);
int Init_Key(Key*  Key_Key);
int Clear_Key(Key*  Key_Key);
    //新版
int Init_New_Key(New_Paillier_Key* Key_Key);
int Clear_New_Key(New_Paillier_Key*  Key_Key);
//加密以及解密 m , c
int Encrypt(Key*  PK,mpz_t m);
int Decrypt(Key * PK,Key*  SK,mpz_t c);
    //新版
int Encypt_New( New_Paillier_Key *Key,mpz_t c,mpz_t m);
int Decypt_New( New_Paillier_Key *Key,mpz_t c,mpz_t Ci);


//得到Fi
int Get_Fxi(mpz_t F1,mpz_t F2,mpz_t N,mpz_t m,mpz_t beitam);
//相加 m0
int Paillier_ADD(mpz_t Value,mpz_t m0,mpz_t m1,mpz_t N);

//计算数乘 m0
int Paillier_MUL(Key*  PK,mpz_t Value,mpz_t m0,mpz_t m1);

//用于群生成的小函数
int Lx(mpz_t x,mpz_t n);

//将key秘密共享 SK,SKU
int Share_Key(Key*  SK,Key*  SKU);

//将Key连接起来 sendbuff
int Contruct_Key(Key * key,char * sendbuff);

//将key分开 key
int Slipt_Key(Key * key,char *recievebuff);

//Reshare函数
int Reshare(Key * PK,Key* SK,Key*  SKU,mpz_t C_Alpha_ONE,mpz_t C_Alpha_TWO,mpz_t C_Omega);

//新的Reshare
int New_Reshare(mpz_t C_Alpha_One,mpz_t C_Alpha_Two,mpz_t C_Omiga_One,mpz_t C_Omiga_Two,mpz_t N,mpz_t theta);
//计算hash值
int Get_Hash(mpz_t C,mpz_t CommitValue,char *buff); 

//重组密文（两方）
int Construct_Ci(mpz_t M,mpz_t C1,mpz_t C2, mpz_t N,mpz_t theta);*/

/*****************************************************************************
 * *********************check
******************************************************************************/

//生成Vi
int Get_Vi(Check_Compute*  Check,int len);

//生成Si和t
int Get_T(Check_Value*  Value,Check_Compute* Check, mpz_t g,mpz_t glpha, mpz_t h);

//生成Eta
int Get_Eta(mpz_t Eta,int len);

//分别计算等式两边的数据
int Compute_TEta(mpz_t mul_all,Check_Value Check[],mpz_t Eta[],int number);

int Compute_GsEta(mpz_t gsEta,Check_Value Check[],mpz_t Eta[],mpz_t g,mpz_t h,mpz_t glpha,int number);

int Compute_YnEta(mpz_t ynEta,Check_Value Check[],mpz_t Eta[],int number);

//判断teta = gseta * yneta mod p?
int Check_Equal(mpz_t tEta,mpz_t gsEta,mpz_t ynEta,mpz_t p);

//初始化以及清除
int Init_Check_Compute(Check_Compute*  Check);

int Clear_Check_Compute(Check_Compute*  Check);

int Init_Check_Value(Check_Value*  Check);

int Clear_Check_Value(Check_Value*  Check);

int Init_Basic(Basic * Basic_Value);

int Clear_Basic(Basic * Basic_Value);

//得到g，h，p
int Get_Bisic_Value(Basic * Basic_Value,int len);

//生成Pedersen承诺
int Pedersen(Basic *  Basic_Value,Commit * Commit_Value,mpz_t m);

//用于生成Y
int Compute_Y(Check_Value* Value,Commit* Commit,Basic* Basic_Value,mpz_t Gdelta2);

//用于Sever计算g^delta1 * h ^ R mod p
int Compute_Gwlpha(Commit* Commit,Basic* Basic_Value,mpz_t Delta1);

//用于Client计算g^delta2 mod p
int Compute_Gdelta(mpz_t Gdelta,Basic * Basic_Value,mpz_t Delta2);

//用于计算g ^ alpha mod p
int Get_Glpha(mpz_t glpha,mpz_t Glpha1,mpz_t Glpha2,Basic * Basic_Value);

//用于Client验证
int Client_Check(Check_Value Value[],mpz_t Eta[],mpz_t glpha,Basic Basic_Value,int len);
