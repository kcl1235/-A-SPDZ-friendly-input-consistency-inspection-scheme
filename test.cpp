#include <iostream>
#include <helib/helib.h>
#include <helib/EncryptedArray.h>
#include <helib/ArgMap.h>
#include <NTL/BasicThreadPool.h>
#include "tool.c"
#include<vector>
int main()
{

    unsigned long s = 131;
  //  unsigned long m = 130; 
    unsigned long r = 1;
    unsigned long bits = 1000;
    unsigned long c = 2;
    unsigned long nthreads = 1;
    unsigned long W1 = 3;
    unsigned long F = 4;
    bool debug = false;
    int len = 128;

/*

    HELIB_NTIMER_START(timer_Context);
    helib::Context context = helib::ContextBuilder<helib::BGV>()
                               .m(m)
                               .p(s)
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();

    helib::SecKey secret_key = helib::SecKey(context);
    secret_key.GenSecKey();
    helib::addSome1DMatrices(secret_key);
    const helib::PubKey& public_key = secret_key;
    const helib::EncryptedArray& ea = context.getEA();
    long nslots = ea.size();
    std::cout << "\nNumber of slots: " << nslots << std::endl;
    helib::Ctxt encrypted_numbers(public_key);
    helib::Ptxt<helib::BGV> ptxt(context);
    ptxt[0] = W1;
    public_key.Encrypt(encrypted_numbers,ptxt);
    helib::Ptxt<helib::BGV> ptxt1(context);
    ptxt1[0] = F;
    helib::Ctxt c_f(public_key);
    public_key.Encrypt(c_f,ptxt1);
    std::cout << "\nNumber of  ptxt: " <<  ptxt << std::endl;
    c_f.multiplyBy(encrypted_numbers);
    c_f +=  encrypted_numbers;
    helib::Ptxt<helib::BGV> new_plaintext_result(context);
    secret_key.Decrypt(new_plaintext_result, c_f);
    helib::Ptxt<helib::BGV> new_plaintext_result1(context);
    secret_key.Decrypt(new_plaintext_result1, encrypted_numbers);
    std::cout << "\nNumber of  ptxt: " <<  new_plaintext_result << std::endl;
    std::cout << "\nNumber of  ptxt1: " <<  new_plaintext_result1 << std::endl;
*/

//Create 8 prime numbers p len = 16
    mpz_t q[9];
    mpz_t M;
    unsigned long p[9];
    int i;
    mpz_init(M);
    mpz_set_ui(M,1);
    for(i = 0;i < 9;i++)
    {
        mpz_init(q[i]);
        Get_Prime_Number(q[i],32);
        mpz_mul(M,M,q[i]);
        p[i] = mpz_get_ui(q[i]);
       //gmp_printf("q is %Zd\n", q[i]);
    }

//get basic value to commit
    Basic Basic_Value;
    Init_Basic(&Basic_Value);
    Get_Bisic_Value(&Basic_Value,len);
    

//get W and Commit Value
    mpz_t W[10];
    Commit Commit[10];
    for(i = 0;i < 10;i++)
    {
        mpz_init(W[i]);
        Get_Big_Number(W[i],len);
	//gmp_printf("w is %Zd\n", W[i]);
        Init_Commit(&Commit[i]);
        Pedersen(&Basic_Value,&Commit[i],W[i]);
    }

    unsigned long m[9]; 
    for(i = 0;i < 9;i++)
    {
        m[i] = 130;
    }

clock_t start,finish;
	start = clock();
//create 8 SK and 8 PK

    //context0
    helib::Context context0 = helib::ContextBuilder<helib::BGV>()
                               .m(m[0])
                               .p(p[0])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();

    helib::SecKey secret_key0 = helib::SecKey(context0);
    secret_key0.GenSecKey();
    helib::addSome1DMatrices(secret_key0);
    const helib::PubKey& public_key0 = secret_key0;
  

    //context1
   helib::Context context1 = helib::ContextBuilder<helib::BGV>()
                               .m(m[1])
                               .p(p[1])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();

    helib::SecKey secret_key1 = helib::SecKey(context1);
    secret_key1.GenSecKey();
    helib::addSome1DMatrices(secret_key1);
    const helib::PubKey& public_key1 = secret_key1;
    

    //context2
    helib::Context context2 = helib::ContextBuilder<helib::BGV>()
                               .m(m[2])
                               .p(p[2])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key2 = helib::SecKey(context2);
    secret_key2.GenSecKey();
    helib::addSome1DMatrices(secret_key2);
    const helib::PubKey& public_key2 = secret_key2;                        

    //context3
   helib::Context context3 = helib::ContextBuilder<helib::BGV>()
                               .m(m[3])
                               .p(p[3])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key3 = helib::SecKey(context3);
    secret_key3.GenSecKey();
    helib::addSome1DMatrices(secret_key3);
    const helib::PubKey& public_key3 = secret_key3;

    //context4
    helib::Context context4 = helib::ContextBuilder<helib::BGV>()
                               .m(m[4])
                               .p(p[4])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key4 = helib::SecKey(context4);
    secret_key4.GenSecKey();
    helib::addSome1DMatrices(secret_key4);
    const helib::PubKey& public_key4 = secret_key4;

    //context5
   helib::Context context5 = helib::ContextBuilder<helib::BGV>()
                               .m(m[5])
                               .p(p[5])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key5 = helib::SecKey(context5);
    secret_key5.GenSecKey();
    helib::addSome1DMatrices(secret_key5);
    const helib::PubKey& public_key5 = secret_key5;

    //context6
    helib::Context context6 = helib::ContextBuilder<helib::BGV>()
                               .m(m[6])
                               .p(p[6])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key6 = helib::SecKey(context6);
    secret_key6.GenSecKey();
    helib::addSome1DMatrices(secret_key6);
    const helib::PubKey& public_key6 = secret_key6;

    //context7
   helib::Context context7 = helib::ContextBuilder<helib::BGV>()
                               .m(m[7])
                               .p(p[7])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key7 = helib::SecKey(context7);
    secret_key7.GenSecKey();
    helib::addSome1DMatrices(secret_key7);
    const helib::PubKey& public_key7 = secret_key7;
    
    helib::Context context8 = helib::ContextBuilder<helib::BGV>()
                               .m(m[8])
                               .p(p[8])
                               .r(r)
                               .bits(bits)
                               .c(c)
                               .build();
    helib::SecKey secret_key8 = helib::SecKey(context8);
    secret_key8.GenSecKey();
    helib::addSome1DMatrices(secret_key8);
    const helib::PubKey& public_key8 = secret_key8;
    
//we need w(alredy get) cw alpha1 calpha1 alpha2 calpha2 r1 cr1 r2 cr2 
    mpz_t alpha_one,alpha_two,r_one,r_two;//,rrr,alpha;
    mpz_init(alpha_one);
   // mpz_init(alpha);
    mpz_init(alpha_two);
    mpz_init(r_one);
    mpz_init(r_two);
   // mpz_init(rrr);

    Get_Big_Number(alpha_one,len);
    Get_Big_Number(alpha_two,len);
    Get_Big_Number(r_one,len);
    Get_Big_Number(r_two,len);

  //  mpz_add(alpha,alpha_one,alpha_two);
  //  mpz_add(rrr,r_one,r_two);


//let's start create ptxt and ctxt ; 
//use tep to store tepdata ; 
//use Dis_ to store dispersed data;

    //start to disperse W to Dis_W
    mpz_t tepm;
    mpz_init(tepm);
    unsigned long Dis_W[10][9];
    int j;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 9;j++)
        {
            mpz_mod(tepm,W[i],q[j]);
            Dis_W[i][j] = mpz_get_ui(tepm);
      
         //   printf("w[%d][%d] is %Zd\n",i,j,Dis_W[i][j]);
        //   gmp_printf("prime is %Zd\n",tepm);
            
        }
      //  gmp_printf("w[i] is %Zd\n",W[i]);
    }

    //start to disperse alpha_one to Dis_alpha_one
    unsigned long Dis_alpha_one[9];

    for(i = 0;i < 9;i++)
    {
        
        mpz_mod_ui(tepm,alpha_one,p[i]);
        Dis_alpha_one[i] = mpz_get_ui(tepm);
     //   gmp_printf("alpha one is %Zd\n",tepm);
    }

    //start to disperse alpha_two to Dis_alpha_two
    unsigned long Dis_alpha_two[9];
    for(i = 0;i < 9;i++)
    {
        mpz_mod_ui(tepm,alpha_two,p[i]);
        Dis_alpha_two[i] = mpz_get_ui(tepm);
      //  gmp_printf("alpha two is %Zd\n",tepm);
    }

    //start to disperse r_one to Dis_r_one
    unsigned long Dis_r_one[9];
    for(i = 0;i < 9;i++)
    {
        mpz_mod_ui(tepm,r_one,p[i]);
        Dis_r_one[i] = mpz_get_ui(tepm);
      //  gmp_printf("r one is %Zd\n",tepm);
    }

    //start to disperse r_two to Dis_r_two
    unsigned long Dis_r_two[9];
    for(i = 0;i < 9;i++)
    {
        mpz_mod_ui(tepm,r_two,p[i]);
        Dis_r_two[i] = mpz_get_ui(tepm);
     //   gmp_printf("r two is %Zd\n",tepm);
    }


   

    //create ptxt-i 

    helib::Ptxt<helib::BGV> ptxt0(context0);
    helib::Ptxt<helib::BGV> ptxt1(context1);
    helib::Ptxt<helib::BGV> ptxt2(context2);
    helib::Ptxt<helib::BGV> ptxt3(context3);
    helib::Ptxt<helib::BGV> ptxt4(context4);
    helib::Ptxt<helib::BGV> ptxt5(context5);
    helib::Ptxt<helib::BGV> ptxt6(context6);
    helib::Ptxt<helib::BGV> ptxt7(context7);
    helib::Ptxt<helib::BGV> ptxt8(context8);
     std::vector<helib::Ptxt<helib::BGV>> teep[10];
    //create ptxt to store Dis_W use vector test i means this is i-th W 
    std::vector<std::pair<int ,std::vector< helib::Ptxt<helib::BGV>>>> test;
    for(i = 0;i < 10;i++)
    {
       

        ptxt0[0] =  Dis_W[i][0];  
        ptxt1[0] =  Dis_W[i][1];
        ptxt2[0] =  Dis_W[i][2];
        ptxt3[0] =  Dis_W[i][3];
        ptxt4[0] =  Dis_W[i][4];
        ptxt5[0] =  Dis_W[i][5];
        ptxt6[0] =  Dis_W[i][6];  
        ptxt7[0] =  Dis_W[i][7];  
         ptxt8[0] =  Dis_W[i][8];  

        teep[i].emplace_back(ptxt0);
        teep[i].emplace_back(ptxt1);
        teep[i].emplace_back(ptxt2);
        teep[i].emplace_back(ptxt3);
        teep[i].emplace_back(ptxt4);
        teep[i].emplace_back(ptxt5);
        teep[i].emplace_back(ptxt6);
        teep[i].emplace_back(ptxt7);
        teep[i].emplace_back(ptxt8);
        test.emplace_back(i,teep[i]);
       // std::vector<helib::Ptxt<helib::BGV>>().swap(teep);
     //  std::cout << "Number of  ptxt: " << i <<" "<< test[i].second[1][0] << std::endl;
      //  printf("w[%d][1] is %Zd\n",i,Dis_W[i][1]);
    }

    //create ptxt to store Dis_alpha_one
    std::vector<helib::Ptxt<helib::BGV>> ptxt_Dis_alpha_one;
    
    ptxt0[0] =  Dis_alpha_one[0];  
    ptxt1[0] =  Dis_alpha_one[1];
    ptxt2[0] =  Dis_alpha_one[2];
    ptxt3[0] =  Dis_alpha_one[3];
    ptxt4[0] =  Dis_alpha_one[4];
    ptxt5[0] =  Dis_alpha_one[5];
    ptxt6[0] =  Dis_alpha_one[6];  
    ptxt7[0] =  Dis_alpha_one[7]; 
    ptxt8[0] =  Dis_alpha_one[8]; 

    ptxt_Dis_alpha_one.emplace_back(ptxt0);
    ptxt_Dis_alpha_one.emplace_back(ptxt1);
    ptxt_Dis_alpha_one.emplace_back(ptxt2);
    ptxt_Dis_alpha_one.emplace_back(ptxt3);
    ptxt_Dis_alpha_one.emplace_back(ptxt4);
    ptxt_Dis_alpha_one.emplace_back(ptxt5);
    ptxt_Dis_alpha_one.emplace_back(ptxt6);
    ptxt_Dis_alpha_one.emplace_back(ptxt7);
    ptxt_Dis_alpha_one.emplace_back(ptxt8);

   /* 
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[0][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[1][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[2][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[3][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[4][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[5][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[6][0] << std::endl;
    std::cout << "Number of  ptxt alpha: " << ptxt_Dis_alpha_one[7][0] << std::endl;
*/
    //create ptxt to store Dis_alpha_two
    std::vector<helib::Ptxt<helib::BGV>> ptxt_Dis_alpha_two;
    
    ptxt0[0] =  Dis_alpha_two[0];  
    ptxt1[0] =  Dis_alpha_two[1];
    ptxt2[0] =  Dis_alpha_two[2];
    ptxt3[0] =  Dis_alpha_two[3];
    ptxt4[0] =  Dis_alpha_two[4];
    ptxt5[0] =  Dis_alpha_two[5];
    ptxt6[0] =  Dis_alpha_two[6];  
    ptxt7[0] =  Dis_alpha_two[7]; 
    ptxt8[0] =  Dis_alpha_two[8]; 

    ptxt_Dis_alpha_two.emplace_back(ptxt0);
    ptxt_Dis_alpha_two.emplace_back(ptxt1);
    ptxt_Dis_alpha_two.emplace_back(ptxt2);
    ptxt_Dis_alpha_two.emplace_back(ptxt3);
    ptxt_Dis_alpha_two.emplace_back(ptxt4);
    ptxt_Dis_alpha_two.emplace_back(ptxt5);
    ptxt_Dis_alpha_two.emplace_back(ptxt6);
    ptxt_Dis_alpha_two.emplace_back(ptxt7);
    ptxt_Dis_alpha_two.emplace_back(ptxt8);

    /*
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[0][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[1][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[2][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[3][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[4][0] << std::endl;

    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[5][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[6][0] << std::endl;
    std::cout << "Number of  ptxt alpha t: " << ptxt_Dis_alpha_two[7][0] << std::endl;
    */
    //create ptxt to store Dis_r_one
    std::vector<helib::Ptxt<helib::BGV>> ptxt_Dis_r_one;
    
    ptxt0[0] =  Dis_r_one[0];  
    ptxt1[0] =  Dis_r_one[1];
    ptxt2[0] =  Dis_r_one[2];
    ptxt3[0] =  Dis_r_one[3];
    ptxt4[0] =  Dis_r_one[4];
    ptxt5[0] =  Dis_r_one[5];
    ptxt6[0] =  Dis_r_one[6];  
    ptxt7[0] =  Dis_r_one[7]; 
    ptxt8[0] =  Dis_r_one[8]; 

    ptxt_Dis_r_one.emplace_back(ptxt0);
    ptxt_Dis_r_one.emplace_back(ptxt1);
    ptxt_Dis_r_one.emplace_back(ptxt2);
    ptxt_Dis_r_one.emplace_back(ptxt3);
    ptxt_Dis_r_one.emplace_back(ptxt4);
    ptxt_Dis_r_one.emplace_back(ptxt5);
    ptxt_Dis_r_one.emplace_back(ptxt6);
    ptxt_Dis_r_one.emplace_back(ptxt7);
    ptxt_Dis_r_one.emplace_back(ptxt8);

    /*
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[0][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[1][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[2][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[3][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[4][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[5][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[6][0] << std::endl;
    std::cout << "Number of  ptxt r: " << ptxt_Dis_r_one[7][0] << std::endl;

    */
    //create ptxt to store Dis_r_two
    std::vector<helib::Ptxt<helib::BGV>> ptxt_Dis_r_two;
    
    ptxt0[0] =  Dis_r_two[0];  
    ptxt1[0] =  Dis_r_two[1];
    ptxt2[0] =  Dis_r_two[2];
    ptxt3[0] =  Dis_r_two[3];
    ptxt4[0] =  Dis_r_two[4];
    ptxt5[0] =  Dis_r_two[5];
    ptxt6[0] =  Dis_r_two[6];  
    ptxt7[0] =  Dis_r_two[7]; 
    ptxt8[0] =  Dis_r_two[8]; 


    ptxt_Dis_r_two.emplace_back(ptxt0);
    ptxt_Dis_r_two.emplace_back(ptxt1);
    ptxt_Dis_r_two.emplace_back(ptxt2);
    ptxt_Dis_r_two.emplace_back(ptxt3);
    ptxt_Dis_r_two.emplace_back(ptxt4);
    ptxt_Dis_r_two.emplace_back(ptxt5);
    ptxt_Dis_r_two.emplace_back(ptxt6);
    ptxt_Dis_r_two.emplace_back(ptxt7);
    ptxt_Dis_r_two.emplace_back(ptxt8);

    /*
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[0][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[1][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[2][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[3][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[4][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[5][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[6][0] << std::endl;
    std::cout << "Number of  ptxt r t: " << ptxt_Dis_r_two[7][0] << std::endl;
    */

//ready to encrypt

    helib::Ctxt encrypted_numbers0(public_key0);
    helib::Ctxt encrypted_numbers1(public_key1);
    helib::Ctxt encrypted_numbers2(public_key2);
    helib::Ctxt encrypted_numbers3(public_key3);
    helib::Ctxt encrypted_numbers4(public_key4);
    helib::Ctxt encrypted_numbers5(public_key5);
    helib::Ctxt encrypted_numbers6(public_key6);
    helib::Ctxt encrypted_numbers7(public_key7);
    helib::Ctxt encrypted_numbers8(public_key8);
//start to encrypt

    //create ctxt to store encrypt values C_W use vector C_W


   
    std::vector<std::pair<int,std::vector<helib::Ctxt>>> C_W;
    std::vector<helib::Ctxt> C_tep[10];

    for(i = 0;i < 10;i++)
    {
        
        public_key0.Encrypt(encrypted_numbers0,test[i].second[0]);
        public_key1.Encrypt(encrypted_numbers1,test[i].second[1]);
        public_key2.Encrypt(encrypted_numbers2,test[i].second[2]);
        public_key3.Encrypt(encrypted_numbers3,test[i].second[3]);
        public_key4.Encrypt(encrypted_numbers4,test[i].second[4]);
        public_key5.Encrypt(encrypted_numbers5,test[i].second[5]);
        public_key6.Encrypt(encrypted_numbers6,test[i].second[6]);
        public_key7.Encrypt(encrypted_numbers7,test[i].second[7]);
        public_key8.Encrypt(encrypted_numbers8,test[i].second[8]);


        C_tep[i].emplace_back(encrypted_numbers0);
        C_tep[i].emplace_back(encrypted_numbers1);
        C_tep[i].emplace_back(encrypted_numbers2);
        C_tep[i].emplace_back(encrypted_numbers3);
        C_tep[i].emplace_back(encrypted_numbers4);
        C_tep[i].emplace_back(encrypted_numbers5);
        C_tep[i].emplace_back(encrypted_numbers6);
        C_tep[i].emplace_back(encrypted_numbers7);
        C_tep[i].emplace_back(encrypted_numbers8);
     
        
        C_W.emplace_back(i,C_tep[i]);

        /*
        secret_key0.Decrypt(dptxt0, C_W[i].second[0]);
        secret_key1.Decrypt(dptxt1, C_W[i].second[1]);
        secret_key2.Decrypt(dptxt2, C_W[i].second[2]);
        secret_key3.Decrypt(dptxt3, C_W[i].second[3]);
        secret_key4.Decrypt(dptxt4, C_W[i].second[4]);
        secret_key5.Decrypt(dptxt5, C_W[i].second[5]);
        secret_key6.Decrypt(dptxt6, C_W[i].second[6]);
        secret_key7.Decrypt(dptxt7, C_W[i].second[7]);
        secret_key8.Decrypt(dptxt8, C_W[i].second[8]);
        */
       // std::cout << "Number of  ctxt: " << i <<" "<< test[i].second[1] << std::endl;
        //std::cout << "Number of  ctxt: " << i <<" "<< dptxt1 << std::endl;

    }

    //create ctxt to store encrypted values C_alpha_one use vector C_alpha_one

    std::vector<helib::Ctxt> C_alpha_one;
    public_key0.Encrypt(encrypted_numbers0,ptxt_Dis_alpha_one[0]);
    public_key1.Encrypt(encrypted_numbers1,ptxt_Dis_alpha_one[1]);
    public_key2.Encrypt(encrypted_numbers2,ptxt_Dis_alpha_one[2]);
    public_key3.Encrypt(encrypted_numbers3,ptxt_Dis_alpha_one[3]);
    public_key4.Encrypt(encrypted_numbers4,ptxt_Dis_alpha_one[4]);
    public_key5.Encrypt(encrypted_numbers5,ptxt_Dis_alpha_one[5]);
    public_key6.Encrypt(encrypted_numbers6,ptxt_Dis_alpha_one[6]);
    public_key7.Encrypt(encrypted_numbers7,ptxt_Dis_alpha_one[7]);
    public_key8.Encrypt(encrypted_numbers8,ptxt_Dis_alpha_one[8]);

    C_alpha_one.emplace_back(encrypted_numbers0);
    C_alpha_one.emplace_back(encrypted_numbers1);
    C_alpha_one.emplace_back(encrypted_numbers2);
    C_alpha_one.emplace_back(encrypted_numbers3);
    C_alpha_one.emplace_back(encrypted_numbers4);
    C_alpha_one.emplace_back(encrypted_numbers5);
    C_alpha_one.emplace_back(encrypted_numbers6);
    C_alpha_one.emplace_back(encrypted_numbers7);
    C_alpha_one.emplace_back(encrypted_numbers8);

    //create ctxt to store encrypted values C_alpha_two use vector C_alpha_two

    std::vector<helib::Ctxt> C_alpha_two;
    public_key0.Encrypt(encrypted_numbers0,ptxt_Dis_alpha_two[0]);
    public_key1.Encrypt(encrypted_numbers1,ptxt_Dis_alpha_two[1]);
    public_key2.Encrypt(encrypted_numbers2,ptxt_Dis_alpha_two[2]);
    public_key3.Encrypt(encrypted_numbers3,ptxt_Dis_alpha_two[3]);
    public_key4.Encrypt(encrypted_numbers4,ptxt_Dis_alpha_two[4]);
    public_key5.Encrypt(encrypted_numbers5,ptxt_Dis_alpha_two[5]);
    public_key6.Encrypt(encrypted_numbers6,ptxt_Dis_alpha_two[6]);
    public_key7.Encrypt(encrypted_numbers7,ptxt_Dis_alpha_two[7]);
    public_key8.Encrypt(encrypted_numbers8,ptxt_Dis_alpha_two[8]);

    C_alpha_two.emplace_back(encrypted_numbers0);
    C_alpha_two.emplace_back(encrypted_numbers1);
    C_alpha_two.emplace_back(encrypted_numbers2);
    C_alpha_two.emplace_back(encrypted_numbers3);
    C_alpha_two.emplace_back(encrypted_numbers4);
    C_alpha_two.emplace_back(encrypted_numbers5);
    C_alpha_two.emplace_back(encrypted_numbers6);
    C_alpha_two.emplace_back(encrypted_numbers7);
    C_alpha_two.emplace_back(encrypted_numbers8);

    //create ctxt to store encrypted values C_r_one use vector C_r_one

    std::vector<helib::Ctxt> C_r_one;
    public_key0.Encrypt(encrypted_numbers0,ptxt_Dis_r_one[0]);
    public_key1.Encrypt(encrypted_numbers1,ptxt_Dis_r_one[1]);
    public_key2.Encrypt(encrypted_numbers2,ptxt_Dis_r_one[2]);
    public_key3.Encrypt(encrypted_numbers3,ptxt_Dis_r_one[3]);
    public_key4.Encrypt(encrypted_numbers4,ptxt_Dis_r_one[4]);
    public_key5.Encrypt(encrypted_numbers5,ptxt_Dis_r_one[5]);
    public_key6.Encrypt(encrypted_numbers6,ptxt_Dis_r_one[6]);
    public_key7.Encrypt(encrypted_numbers7,ptxt_Dis_r_one[7]);
    public_key8.Encrypt(encrypted_numbers8,ptxt_Dis_r_one[8]);
    C_r_one.emplace_back(encrypted_numbers0);
    C_r_one.emplace_back(encrypted_numbers1);
    C_r_one.emplace_back(encrypted_numbers2);
    C_r_one.emplace_back(encrypted_numbers3);
    C_r_one.emplace_back(encrypted_numbers4);
    C_r_one.emplace_back(encrypted_numbers5);
    C_r_one.emplace_back(encrypted_numbers6);
    C_r_one.emplace_back(encrypted_numbers7);
C_r_one.emplace_back(encrypted_numbers8);
    //create ctxt to store encrypted values C_r_two use vector C_r_two



  

    std::vector<helib::Ctxt> C_r_two;
    public_key0.Encrypt(encrypted_numbers0,ptxt_Dis_r_two[0]);
    public_key1.Encrypt(encrypted_numbers1,ptxt_Dis_r_two[1]);
    public_key2.Encrypt(encrypted_numbers2,ptxt_Dis_r_two[2]);
    public_key3.Encrypt(encrypted_numbers3,ptxt_Dis_r_two[3]);
    public_key4.Encrypt(encrypted_numbers4,ptxt_Dis_r_two[4]);
    public_key5.Encrypt(encrypted_numbers5,ptxt_Dis_r_two[5]);
    public_key6.Encrypt(encrypted_numbers6,ptxt_Dis_r_two[6]);
    public_key7.Encrypt(encrypted_numbers7,ptxt_Dis_r_two[7]);
    public_key8.Encrypt(encrypted_numbers8,ptxt_Dis_r_two[8]);

    C_r_two.emplace_back(encrypted_numbers0);
    C_r_two.emplace_back(encrypted_numbers1);
    C_r_two.emplace_back(encrypted_numbers2);
    C_r_two.emplace_back(encrypted_numbers3);
    C_r_two.emplace_back(encrypted_numbers4);
    C_r_two.emplace_back(encrypted_numbers5);
    C_r_two.emplace_back(encrypted_numbers6);
    C_r_two.emplace_back(encrypted_numbers7);
  C_r_two.emplace_back(encrypted_numbers8);

//now we can compute (w*alpha)+r1+r2

    //first compute alpha = alpha1 + alpha2
    for(i = 0;i < 9;i++)
    {
        C_alpha_one[i] +=  C_alpha_two[i];
    }

    //second compute w * alpha
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 9;j++)
        {
            C_W[i].second[j].multiplyBy(C_alpha_one[j]);
        }     
    }

    //third compute r1 + r2
    for(i = 0;i < 9;i++)
    {
        C_r_one[i] +=  C_r_two[i];
    }

    //finally compute w * alpha + r1 + r2
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 9;j++)
        {
            C_W[i].second[j] +=  C_r_one[j];
        }
    }

    //now we can decrypt 
    std::vector<std::pair<int ,std::vector< helib::Ptxt<helib::BGV>>>> P_delta;
    
    helib::Ptxt<helib::BGV> dptxt0(context0);
    helib::Ptxt<helib::BGV> dptxt1(context1);
    helib::Ptxt<helib::BGV> dptxt2(context2);
    helib::Ptxt<helib::BGV> dptxt3(context3);
    helib::Ptxt<helib::BGV> dptxt4(context4);
    helib::Ptxt<helib::BGV> dptxt5(context5);
    helib::Ptxt<helib::BGV> dptxt6(context6);
    helib::Ptxt<helib::BGV> dptxt7(context7);
    helib::Ptxt<helib::BGV> dptxt8(context8);


std::vector<helib::Ptxt<helib::BGV>> stor_delta[i];
long sk;
    for(i = 0;i < 10;i++)
    {
        
        secret_key0.Decrypt(dptxt0, C_W[i].second[0]);
        secret_key1.Decrypt(dptxt1, C_W[i].second[1]);
        secret_key2.Decrypt(dptxt2, C_W[i].second[2]);
        secret_key3.Decrypt(dptxt3, C_W[i].second[3]);
        secret_key4.Decrypt(dptxt4, C_W[i].second[4]);
        secret_key5.Decrypt(dptxt5, C_W[i].second[5]);
        secret_key6.Decrypt(dptxt6, C_W[i].second[6]);
        secret_key7.Decrypt(dptxt7, C_W[i].second[7]);
        secret_key8.Decrypt(dptxt8, C_W[i].second[8]);

        stor_delta[i].emplace_back(dptxt0);
        stor_delta[i].emplace_back(dptxt1);
        stor_delta[i].emplace_back(dptxt2);
        stor_delta[i].emplace_back(dptxt3);
        stor_delta[i].emplace_back(dptxt4);
        stor_delta[i].emplace_back(dptxt5);
        stor_delta[i].emplace_back(dptxt6);
        stor_delta[i].emplace_back(dptxt7);
        stor_delta[i].emplace_back(dptxt8);

        P_delta.emplace_back(i,stor_delta[i]);
        //std::cout << "Number of  ptxt: " << i <<" "<< P_delta[i].second[1][0] << std::endl;
      //  std::vector<helib::Ptxt<helib::BGV>>().swap(stor_delta);
    }
   

//now we can compute delta use CRT x[i] is delta i delta = w * alpha + r1 + r2
    mpz_t Mi[9];
    mpz_t ti[9];
   
   for(i = 0;i < 9;i++)
    {
        mpz_init(Mi[i]);
        mpz_init(ti[i]);
        mpz_cdiv_q(Mi[i],M,q[i]); 
        mpz_invert(ti[i],Mi[i],q[i]); 
      //gmp_printf("prime is %Zd\n", M);
        
    }


    


    int k = 0;
    mpz_t x[10],y;
    mpz_init(y);
    long ss;
    mpz_set_ui(y,1);
    for(i = 0;i < 10;i++)
    {
        mpz_init(x[i]);
        for(j = 0;j < 9;j++)
        {
          
            ss = long(P_delta[i].second[j][0]);

            mpz_mul_ui(y,ti[j],ss);
            mpz_mul(y,y,Mi[j]);
            mpz_add(x[i],y,x[i]);  
         //  std::cout << "Number of  ptxt: " << i <<" "<< ss<< std::endl;
          // std::cout << "Number of  ptxt: " << i <<" "<< P_delta[i].second[j][0] << std::endl;
           // std::cout << "\nNumber of  ptxt: " << i <<" "<< ss<< std::endl;
         //  printf("p_delta :%d\n",P_delta[i].first);
        }
        mpz_mod(x[i],x[i],M);
     //   mpz_mul(tepm,W[i],alpha);
     //   mpz_add(tepm,rrr,tepm);

       
        //mpz_mod(tepm,tepm,M);
      //  gmp_printf("X[%d] is %Zd\n", i,x[i]);
      //  gmp_printf("X[%d] is %Zd\n",i, tepm);
      //  gmp_printf("M is %Zd\n",M);

    }

//now we get delta1 and delta2
    mpz_t delta_one[10],delta_two[10],delta[10];
    for(i = 0;i < 10;i++)
    {
        mpz_init(delta_one[i]);
        mpz_init(delta_two[i]);
        mpz_init(delta[i]);
        mpz_sub(delta_one[i],x[i],r_one);
        mpz_set(delta_two[i],r_two);
        mpz_neg(delta_two[i],delta_two[i]);

      //  mpz_add(tepm,delta_one[i],delta_two[i]);
      //  mpz_set(delta[i],tepm);
      //  gmp_printf("delta is %Zd\n", tepm);
      //  mpz_mul(tepm,W[i],alpha);
     //   gmp_printf("delta is %Zd\n", tepm);
     //   Compute_Glpha(tepm,Basic_Value.g,tepm,Basic_Value.p);
    }

//now we get galpha_1 and galpha_2 and galpha
    mpz_t galpha_one,galpha_two,galpha;
    mpz_init(galpha);
    mpz_init(galpha_one);
    mpz_init(galpha_two);
    Compute_Glpha(galpha_one,Basic_Value.g,alpha_one,Basic_Value.p);
    Compute_Glpha(galpha_two,Basic_Value.g,alpha_two,Basic_Value.p);
    Compute_G_Mul(galpha,galpha_one,galpha_two,Basic_Value.p);
	//gmp_printf("galpha is %Zd\n", galpha);

	
	

//now we get gdelta_1hr and gdelta2
    mpz_t Sever_Finall[10],gdelta2[10];
    mpz_t R[10];
    for(int i = 0;i < 10;i++)
    {
        mpz_init(R[i]);
        mpz_init(Sever_Finall[i]);
        mpz_init(gdelta2[i]);
        Get_Big_Number(R[i],len);
        Compute_Glpha(gdelta2[i],Basic_Value.g,delta_two[i],Basic_Value.p);
        Compute_Values(Sever_Finall[i],Basic_Value.g,delta_one[i],Basic_Value.h,R[i],Basic_Value.p);
    }





    mpz_t Y[10];

    for(i = 0;i<10;i++)
    {
        mpz_init(Y[i]);
        Compute_G_Mul(Y[i],Sever_Finall[i],gdelta2[i],Basic_Value.p);
        mpz_mul(Y[i],Commit[i].Commit_Value,Y[i]);
	    mpz_mod(Y[i],Y[i],Basic_Value.p);
	  //  gmp_printf("Y[%d] is %Zd\n", i,Y[i]);
     //   Compute_Glpha(tepm,Basic_Value.g,W[i],Basic_Value.p);
     //   mpz_mul(delta[i],W[i],alpha);
      //  Compute_Glpha(y,Basic_Value.g,delta[i],Basic_Value.p);
     //   Compute_G_Mul(tepm,tepm,y,Basic_Value.p);
     //   mpz_add(rrr,R[i],Commit[i].r);
     //   Compute_Glpha(y,Basic_Value.h,rrr,Basic_Value.p);
     //   Compute_G_Mul(tepm,tepm,y,Basic_Value.p);
     //   gmp_printf("Y[%d] is %Zd\n", i,tepm);
    }
 

   //用于生成V,得到V
   Check_Compute Compute[10];
    for(i = 0;i<10;i++)
    {
        Init_Check_Compute(&Compute[i]);
        mpz_set(Compute[i].W,W[i]);
	//gmp_printf("w is %Zd\n", Compute[i].W);
        mpz_set(Compute[i].R,R[i]);
	mpz_set(Compute[i].r,Commit[i].r);
        Get_Vi(&Compute[i],32);
    }
    //用于得到其它参数t，s
     Check_Value Value[10];
    for(i = 0;i<10;i++)
    {
        Init_Check_Value(&Value[i]);
        //Get_Big_Number(Value[i].C,len);
	mpz_set_ui(Value[i].C,32);
        mpz_set(Value[i].P,Basic_Value.p);
        mpz_set(Value[i].Y,Y[i]);
        //t，s在这一步生成
        Get_T(&Value[i],&Compute[i],Basic_Value.g,galpha,Basic_Value.h);
    }
    //验证阶段
    mpz_t Eta[10];
    mpz_t teta,gseta,yneta;
    mpz_init(teta);
    mpz_init(gseta);
    mpz_init(yneta);
    for(i = 0;i<10;i++)
    {
        mpz_init(Eta[i]);
        Get_Eta(Eta[i],len); 
    }
    Compute_TEta(teta,Value,Eta,10);
    Compute_GsEta(gseta,Value,Eta,Basic_Value.g,Basic_Value.h,galpha,10);
    Compute_YnEta(yneta,Value,Eta,10);
    Check_Equal(teta,gseta,yneta,Basic_Value.p);
    finish=clock();
	double time;
	time = (double)(finish - start)/ CLOCKS_PER_SEC;  
	printf( "%f seconds\n", time );  
    return 0;
}
