#include "tool.h"
#define MAX_LENTH 2048

int Get_Prime_Number(mpz_t prime_number,int len)
{
	int flag = 0;

	Get_Big_Number(prime_number,len);
	flag = Is_Prime(prime_number);
	while(flag == 0)
	{
	//	gmp_printf("number is %Zd\n", prime_number); //输出大数，大数的格式化标志为%Zd
		Get_Big_Number(prime_number,len);
		flag =Is_Prime(prime_number);
	}

	//	gmp_printf("prime is %Zd\n", prime_number); //输出大数，大数的格式化标志为%Zd
	
	
	return 0;

}

int Get_Big_Number(mpz_t rand_value,int len)
{
	clock_t time = clock();
	gmp_randstate_t grt;
   	gmp_randinit_default(grt);
    gmp_randseed_ui(grt, time);
	mpz_urandomb(rand_value, grt, len);
	return 0;
}

int Get_Big_Number2(mpz_t rand_value,mpz_t big_number)
{
	clock_t time = clock();
	gmp_randstate_t grt;
   	gmp_randinit_default(grt);
    gmp_randseed_ui(grt, time);
	mpz_urandomm(rand_value, grt, big_number);
	return 0;
}

int Is_Prime(mpz_t rand_value)
{
	int flag ;
	flag = mpz_probab_prime_p (rand_value, 15); 
//	printf("%d\n",flag);
	return flag;
}

int Next_Prime(mpz_t prime_number)
{
	mpz_nextprime(prime_number,prime_number);
	return 0;
}

int Get_Group_G(mpz_t Group_g,int len,mpz_t prime_number_p,mpz_t big_number_q)
{
	int flag = 0;
	long int one = 1;
	long int two = 2;

	mpz_t h;
	mpz_init(h);

	while(flag==0)
	{
		Get_Prime_Number(prime_number_p,len);
		Next_Prime(prime_number_p);
		mpz_mul_si(big_number_q,prime_number_p,two);
		mpz_add_ui(big_number_q,big_number_q,one);
		flag =Is_Prime(big_number_q);
	}

	Get_Big_Number2(h,big_number_q);
	mpz_powm_ui(Group_g,h,two,big_number_q);


	mpz_clear(h);

	return 0;


}

int Compute_Values(mpz_t commit_values,mpz_t Group_g,mpz_t m,mpz_t commit_h,mpz_t r,mpz_t mod_p)
{
	mpz_t used;
	mpz_init(used);
	mpz_powm(used,Group_g,m,mod_p);
	mpz_powm(commit_values,commit_h,r,mod_p);
	mpz_mul(commit_values,commit_values,used) ;
	//gmp_printf("number M is %Zd\n\n",commit_values);
	mpz_mod(commit_values,commit_values,mod_p);
	mpz_clear(used);
	return 0;


}

int Int_To_String(mpz_t data ,char* string)
{
	mpz_get_str(string,10,data);
	return 0;
}

int String_To_Int(char* string,mpz_t data)
{
	mpz_set_str(data,string,10);
	return 0;
}
 
int Init_Commit(Commit* Commit)
{
	mpz_init(Commit->Commit_Value);
	mpz_init(Commit->r);
	return 0;

}

int Clear_Commit(Commit*  Commit)
{
	mpz_clear(Commit->Commit_Value);
	mpz_clear(Commit->r);

	return 0;
}

int Get_Alpha(mpz_t alpha,int len)
{
	Get_Big_Number(alpha,len);
	return 0;
}

int Compute_Glpha(mpz_t Value,mpz_t g,mpz_t alpha,const mpz_t q)
{
	mpz_powm(Value,g,alpha,q);
	return 0;
}

int Compute_G_Mul(mpz_t Value,mpz_t glpha1,mpz_t glpha2,mpz_t p)
{
	mpz_mul(Value,glpha1,glpha2);
	mpz_mod(Value,Value,p);
	return 0;
}
/*
int Pedersen(int len,mpz_t  m,commit* Pedersen,mpz_t r)
{

	mpz_t big_number;
	mpz_init(r);

	mpz_init(big_number);

	get_Group_G(Pedersen->Group_g,len,Pedersen->mod_p, big_number);
	get_big_number2(Pedersen->commt_h,Pedersen->Group_g);	
	get_big_number2(r,Pedersen->Group_g);
	//get_big_number2(m,Pedersen->Group_g);
	
	Compute_Values(Pedersen->commit_values,Pedersen->Group_g,m,Pedersen->commt_h,r,Pedersen->mod_p);


	//gmp_printf("commit is %Zd\n", Pedersen.commit_values);


	//Clear_Commit(&Pedersen);
	mpz_clear(big_number);

	return 0;
} 

int Get_Key(Key* PK,Key* SK,int len)
{
	
	mpz_t n2;
	mpz_t mul;
	mpz_t prime_number_p;
	mpz_t prime_number_q;

//	int len = 32;
	int flag = 1;
	
	
	mpz_init(n2);
	mpz_init(mul);
	mpz_init(prime_number_p);
	mpz_init(prime_number_q);

	while(flag!=0)
	{
		Get_Prime_Number(prime_number_p,len);
		Get_Prime_Number(prime_number_q,len);
	
		mpz_mul(PK->one,prime_number_p,prime_number_q);
		mpz_sub_ui(prime_number_p,prime_number_p,1);
		mpz_sub_ui(prime_number_q,prime_number_q,1);
		mpz_mul(mul,prime_number_p,prime_number_q);
		mpz_gcd(SK->one,mul,PK->one);
		flag = mpz_cmp_ui(SK->one,1);
//		gmp_printf("number is %Zd\n", PK->one);
//		gmp_printf("number is %Zd\n", PK->two);
//		gmp_printf("number is %Zd\n", SK->one);
//		gmp_printf("number is %Zd\n", SK->two);
//		printf("flag = %d\n",flag);
	}
	
	flag = 0;
	mpz_lcm(SK->one,prime_number_p,prime_number_q);
	mpz_mul(n2,PK->one,PK->one);

	while(flag!=1)
	{
		Get_Big_Number2(PK->two,n2);
		mpz_powm(SK->two,PK->two,SK->one,n2);
		Lx(SK->two,PK->one);
		mpz_invert(SK->two,SK->two,PK->one);
        flag = mpz_cmp_ui(SK->two,0);
//		gmp_printf("number is %Zd\n", PK->one);
//		gmp_printf("number is %Zd\n", PK->two);
//		gmp_printf("number is %Zd\n", SK->one);
//		gmp_printf("number is %Zd\n", SK->two);
//		printf("flag2 = %d\n",flag);
	}

	mpz_clear(n2);
	mpz_clear(mul);
	mpz_clear(prime_number_p);
	mpz_clear(prime_number_q);

	return 0;
}

int Init_Key(Key* Key_Key)
{
	mpz_init(Key_Key->one);
	mpz_init(Key_Key->two);
	return 0;
}

int Get_Fxi(mpz_t F1,mpz_t F2,mpz_t N,mpz_t m,mpz_t beitam)
{
        mpz_t a1;
        mpz_t Nm;
        mpz_t Nm_1;

        mpz_init(a1);
        mpz_init(Nm);
        mpz_init(Nm_1);

        //Nm = N * m
        mpz_mul(Nm,N,m);
        mpz_sub_ui(Nm_1,Nm,1);
     	 Get_Big_Number2(a1,Nm_1); 
       
        mpz_add(F1,beitam,a1);
        mpz_mod(F1,F1,Nm);

        mpz_mul_ui(a1,a1,2);
        mpz_add(F2,beitam,a1);
        mpz_mod(F2,F2,Nm);
        mpz_clear( a1);
        mpz_clear( Nm);
        mpz_clear( Nm_1);
        return 0;
}

int Init_New_Key(New_Paillier_Key* Key_Key)
{
	mpz_init(Key_Key->N);
	mpz_init(Key_Key->G);
	mpz_init(Key_Key->theta);
	mpz_init(Key_Key->SK);
	return 0;
}

int Clear_Key(Key*  Key_Key)
{
	mpz_clear(Key_Key->one);
	mpz_clear(Key_Key->two);
	return 0;
}

int Clear_New_Key(New_Paillier_Key*  Key_Key)
{
	mpz_clear(Key_Key->N);
	mpz_clear(Key_Key->G);
	mpz_clear(Key_Key->theta);
	mpz_clear(Key_Key->SK);
	return 0;
}

int Lx(mpz_t x,mpz_t n)
{
	mpz_sub_ui(x,x,1);
	mpz_cdiv_q(x,x,n);
	return 0;
}

int Encrypt(Key* PK,mpz_t m)
{
	int flag = 1;

	mpz_t r;
	mpz_t n2;
	mpz_t flag2;

	mpz_init(r);
	mpz_init(n2);
	mpz_init(flag2);

	mpz_mul(n2,PK->one,PK->one);

	while(flag!=0)
	{
		Get_Big_Number2(r,n2);
		mpz_gcd(flag2,r,n2);
		flag = mpz_cmp_ui(flag2,1);
	}
	Compute_Values(m,PK->two,m,r,PK->one,n2);

	mpz_clear(r);
	mpz_clear(n2);
	mpz_clear(flag2);

	return 0;
}

int Encypt_New( New_Paillier_Key *Key,mpz_t c,mpz_t m)
{
        int flag = 1;

	
	mpz_t x;
	mpz_t n2;

	mpz_init(x);
	
	mpz_init(n2);



	mpz_mul(n2,Key->N,Key->N);
        Get_Big_Number2(x,Key->N); 
	Compute_Values(c,Key->G,m,x,Key->N,n2);
	

	
	mpz_mod(c,c,n2);
	
	mpz_clear(x);
	mpz_clear(n2);



	return 0;
}

int Decrypt(Key* PK,Key *SK,mpz_t c)
{
	mpz_t n2;

	mpz_init(n2);

	mpz_mul(n2,PK->one,PK->one);
	mpz_powm(c,c,SK->one,n2);
	Lx(c,PK->one);
	mpz_mul(c,c,SK->two);
	mpz_mod(c,c,PK->one);

	mpz_clear(n2);

	return 0;
}

int Decypt_New( New_Paillier_Key *Key,mpz_t c,mpz_t Ci)
{
        int delta = 2;
        mpz_t n2,tep;
        mpz_init(n2);
        mpz_init(tep);
        //n2 = N*N
        mpz_mul(n2,Key->N,Key->N);
        //tep = 2 * delta * f(i)
        mpz_mul_ui(tep,Key->SK,4);
        //ci = c^(2*delta*f(i)) mod n2
        Compute_Glpha(Ci,c,tep,n2);
        mpz_clear(n2);
        mpz_clear(tep);
        return 0;
}

int Paillier_ADD(mpz_t Value,mpz_t m0,mpz_t m1,mpz_t N)
{
	mpz_t n2;

	mpz_init(n2);

	mpz_mul(n2,N,N);
	mpz_mul(Value,m0,m1);
	mpz_mod(Value,Value,n2);
	mpz_clear(n2);

	return 0;
}

int Paillier_MUL(Key* PK,mpz_t Value,mpz_t m0,mpz_t m1)
{
	mpz_t n2;

	mpz_init(n2);

	mpz_mul(n2,PK->one,PK->one);
	mpz_powm(Value,m0,m1,n2);
	mpz_clear(n2);

	return 0;
}

int Share_Key(Key*  SK,Key*  SKU)
{
	Get_Big_Number2(SKU->one,SK->one);
	Get_Big_Number2(SKU->two,SK->two);
	mpz_sub(SK->one,SK->one,SKU->one);
	mpz_sub(SK->two,SK->two,SKU->two);
	return 0;
}

int Construct_Ci(mpz_t M,mpz_t C1,mpz_t C2, mpz_t N,mpz_t theta)
{
        //0-2/1-2  0-1/2-1
        int lamda1 =2;
        int lamda2 = -1;
        //dlieta  = 2
        int mu1 = 4;
        int mu2 = -2;
        //int mu12 = 8;
        //int mu22 = -4;
        //4dleta^2 = 4*2^2 = 16
        int delta24 = 16;
	//gmp_printf("number C1 is %Zd\n\n\n",C1);
	//gmp_printf("number C2 is %Zd\n\n\n",C2);
        mpz_t n2,tep,mu12,mu22;
        mpz_t divnum;

        mpz_init(n2);
        mpz_init(tep);
        mpz_init(mu12);
        mpz_init(mu22);
        mpz_mul(n2,N,N);
        
        mpz_init(divnum);
        //divnum = theta * delta24
        mpz_mul_ui(divnum,theta,delta24);
     //  gmp_printf("number divnum is %Zd\n",divnum);
        //2MU1,2MU2
        mpz_set_ui(mu12,8);
        mpz_set_ui(mu22,4);


	
        mpz_neg(mu22,mu22);
        mpz_powm(C1,C1,mu12,n2);
	mpz_powm(C2,C2,mu22,n2);
	mpz_mul(tep,C1,C2);
	mpz_mod(tep,tep,n2);
	
        Lx(tep,N);
	mpz_mod(tep,tep,N);
	//gmp_printf("number tep is %Zd\n",tep);
	//
	mpz_invert(divnum,divnum,N);
	mpz_mod(divnum,divnum,N);
    //    mpz_cdiv_q(tep,tep,divnum);
	mpz_mul(tep,tep,divnum);
	//gmp_printf("number divnum is %Zd\n",divnum);
	
        mpz_mod(M,tep,N);

        mpz_clear(n2);
        mpz_clear(tep);
        mpz_clear(divnum);
        return 0;
}

int Contruct_Key(Key* key,char* sendbuff)
{ 
	char one[2048],two[2048];
	Int_To_String(key->one,one);
	//printf("%s\n\n",one);
	//gmp_printf("%Zd\n", key->one);
	strcpy(sendbuff,one);
	
	//printf("%s\n\n",sendbuff);
	strcat(sendbuff,"|");
	Int_To_String(key->two,two);
	//printf("%s\n\n",two);
	strcat(sendbuff,two);
	//printf("%s\n\n",sendbuff);
	return 0;
}

int Slipt_Key(Key*  key,char *recievebuff)
{
	char  one[MAX_LENTH+1];
	char *token;
	char *s = strdup(recievebuff);
	token=strsep(&s,"|");
	strcpy(one,token);
	String_To_Int(one,key->one);
	token=strsep(&s,"|");
	strcpy(one,token);
	String_To_Int(one,key->two);
	return 0;
}

int New_Reshare(mpz_t C_Alpha_One,mpz_t C_Alpha_Two,mpz_t C_Omiga_One,mpz_t C_Omiga_Two,mpz_t N,mpz_t theta)
{
	mpz_t  Alpha,Omiga;
	mpz_init(Alpha);
	mpz_init(Omiga);
	Construct_Ci(Alpha,C_Alpha_One,C_Alpha_Two,N,theta);
	Construct_Ci(Omiga,C_Omiga_One,C_Omiga_Two,N,theta);
	mpz_mul(C_Alpha_One,Omiga,Alpha);
	Get_Big_Number2(C_Alpha_Two,C_Alpha_One);
	mpz_sub(C_Alpha_One,C_Alpha_One,C_Alpha_Two);
	mpz_clear(Alpha);
	mpz_clear(Omiga);
	return 0;

}


/*int Reshare(Key* PK,Key * SK,Key * SKU,mpz_t C_Alpha_ONE,mpz_t C_Alpha_TWO,mpz_t C_Omega)
{
	mpz_t C_Alpha;
	mpz_init(C_Alpha);
	Paillier_ADD(PK,C_Alpha,C_Alpha_ONE,C_Alpha_TWO);
	mpz_add(SK->one,SK->one,SKU->one);
	mpz_add(SK->two,SK->two,SKU->two);
	Decrypt(&PK,&SK,C_Alpha_ONE);
	Decrypt(&PK,&SK,C_Omega);
	mpz_mul(C_Alpha_ONE,C_Alpha_ONE,C_Omega);
	Get_Big_Number2(C_Alpha_TWO,C_Alpha_ONE);
	mpz_sub(C_Alpha_ONE,C_Alpha_ONE,C_Alpha_TWO);
	Clear_Key(&SK);
	Clear_Key(&SKU);
	Clear_Key(&PK);
	mpz_clear(C_Omega);
	mpz_clear(C_Alpha);
	return 0;
}

int Get_Hash(mpz_t C,mpz_t CommitValue,char *buff)
{
	
}*/
/*****************************check******************************/

int Get_Vi(Check_Compute * Check,int len)
{
   Get_Big_Number(Check->V[0],len);
    mpz_set(Check->V[1], Check->V[0]);
   Get_Big_Number(Check->V[2],len);
    return 0;
}

int Get_T(Check_Value * Value,Check_Compute*  Check, mpz_t g,mpz_t glpha, mpz_t h)
{
   
   
  //  gmp_printf("three in %Zd\n\n",three);
  
    //计算si
mpz_t add;
mpz_init(add);
	mpz_set(Value->S[0],Check->V[0]);
	mpz_set(Value->S[1],Check->V[1]);
	mpz_set(Value->S[2],Check->V[2]);
    mpz_submul(Value->S[0],Value->C,Check->W);
    mpz_submul(Value->S[1],Value->C,Check->W);
	mpz_add(add,Check->r,Check->R);
	mpz_mul(add,add,Value->C);
    mpz_sub(Value->S[2],Value->S[2],add);
  //  mpz_mod(Value->S[0],Value->S[0],Value->P);
   // gmp_printf("s0 in %Zd\n\n",Value->S[0]);
  //  mpz_mod(Value->S[1],Value->S[1],Value->P);
//	gmp_printf("s1 in %Zd\n\n",Value->S[1]);
   // mpz_mod(Value->S[2],Value->S[2],Value->P);
//	gmp_printf("s2 in %Zd\n\n",Value->S[2]);
    mpz_t one,two,three;

    mpz_init(one);
    mpz_init(two);
    mpz_init(three);
    //计算t
    Compute_Glpha(one,g,Check->V[0],Value->P);
	//gmp_printf("one in %Zd\n\n",one);
    Compute_Glpha(two,glpha,Check->V[1],Value->P);
//	gmp_printf("two in %Zd\n\n",two);
//	gmp_printf("three in %Zd\n\n",three);
    Compute_Glpha(three,h,Check->V[2],Value->P);

    Compute_G_Mul(one,one,two,Value->P);
    Compute_G_Mul(three,three,one,Value->P);

    mpz_set(Value->T, three);

    mpz_clear(one);
    mpz_clear(two);
    mpz_clear(three);
	mpz_clear(add);

    return 0;
}

int Get_Eta(mpz_t Eta,int len)
{
    Get_Big_Number(Eta,len);
    return 0;
}

int Compute_TEta(mpz_t tEta,Check_Value Check[],mpz_t Eta[],int number)
{
    int i = 0;
    mpz_t Tem;
    mpz_init(Tem);
    mpz_set_ui(tEta,1);
    for(i = 0;i < number;i++)
    {
        printf("etaeta	%d\n",i);
        Compute_Glpha(Tem,Check[i].T,Eta[i],Check[i].P);
        mpz_mul(tEta,tEta,Tem);
        mpz_mod(tEta,tEta,Check[i].P);
	//gmp_printf("number Eta[i] is %Zd\n",Eta[i]);
    }
	mpz_clear(Tem);
    return 0;
}

int Compute_GsEta(mpz_t gsEta,Check_Value Check[],mpz_t Eta[],mpz_t g,mpz_t h,mpz_t glpha,int number)
{
    int i,j;
   // gmp_printf("getgseta h in %Zd\n\n",h);
    mpz_t one,two,three;
    mpz_init(one);
    mpz_init(two);
    mpz_init(three);
    ///////////////////////////////////////////////////////////////////
    i = 0;
mpz_set_ui(gsEta,0);
    for(j = 0; j < number;j++)
    {
        mpz_mul( one,Check[j].S[i],Eta[j]);
        mpz_add(gsEta,gsEta,one);
    } 
    mpz_powm(one,g,gsEta,Check[0].P);
    mpz_set_ui(gsEta,0);

     i = 1;
    for(j = 0; j < number;j++)
    {
        mpz_mul( two,Check[j].S[i],Eta[j]);
        mpz_add(gsEta,gsEta,two);
    } 
    mpz_powm(two,glpha,gsEta,Check[0].P);
    mpz_set_ui(gsEta,0);

     i = 2;
    for(j = 0; j < number;j++)
    {
        mpz_mul(three,Check[j].S[i],Eta[j]);
        mpz_add(gsEta,gsEta,three);
    } 
    mpz_powm(three,h,gsEta,Check[0].P);
    mpz_set_ui(gsEta,1);
///////////////////////////////////////////////////////////////////////////
    mpz_mul(gsEta,gsEta,one);
    mpz_mod(gsEta,gsEta,Check[0].P);

    mpz_mul(gsEta,gsEta,two);
    mpz_mod(gsEta,gsEta,Check[0].P);

    mpz_mul(gsEta,gsEta,three);
    mpz_mod(gsEta,gsEta,Check[0].P);
    mpz_clear(one);
    mpz_clear(two);
    mpz_clear(three);
    return 0;
}

int Compute_YnEta(mpz_t ynEta,Check_Value Check[],mpz_t Eta[],int number)
{
    int i ;
	mpz_t Tem;
	mpz_init(Tem);
    mpz_set_ui(ynEta,1);
    for(i = 0; i < number; i++)
    {
        mpz_mul(Tem,Eta[i],Check[i].C);
        Compute_Glpha(Tem,Check[i].Y,Tem,Check[i].P);
        mpz_mul(ynEta,ynEta,Tem);
        mpz_mod(ynEta,ynEta,Check[i].P);
    }
    return 0;
}

int Check_Equal(mpz_t tEta,mpz_t gsEta,mpz_t ynEta,mpz_t p)
{
    int flag;
    mpz_mul(gsEta,gsEta,ynEta);
    mpz_mod(gsEta,gsEta,p);
    flag = mpz_cmp(tEta,gsEta);
    if(flag == 0)
    {
        printf("equal! Check successed!\n");
        return 0;
    }
    else
    {
        printf("Check failed!\n");
        return 1;
    }
    
}

int Init_Check_Compute(Check_Compute*  Check)
{
    mpz_init(Check->R);
    mpz_init(Check->r);
    mpz_init(Check->V[0]);
    mpz_init(Check->V[1]);
    mpz_init(Check->V[2]);
    mpz_init(Check->W);
    return 0;
}

int Clear_Check_Compute(Check_Compute*  Check)
{
    mpz_clears(Check->W,Check->V,Check->r,Check->R);
    return 0;
}

int Init_Check_Value(Check_Value*  Check)
{
    mpz_init(Check->Y);
    mpz_init(Check->T);
    mpz_init(Check->P);
    mpz_init(Check->C);
    mpz_init(Check->S[0]);
    mpz_init(Check->S[1]);
    mpz_init(Check->S[2]);
    return 0;
}

int Clear_Check_Value(Check_Value*  Check)
{
    mpz_clears(Check->Y,Check->T,Check->P,Check->C,Check->S[0],Check->S[1],Check->S[2]);
    return 0;
}

int Init_Basic(Basic * Basic_Value)
{
	mpz_init(Basic_Value->g);
//	mpz_init(Basic_Value->glpha);
	mpz_init(Basic_Value->h);
	mpz_init(Basic_Value->p);
	return 0;
}

int Clear_Basic(Basic * Basic_Value)
{
	mpz_clear(Basic_Value->g);
//	mpz_clear(Basic_Value->glpha);
	mpz_clear(Basic_Value->h);
	mpz_clear(Basic_Value->p);
	return 0;
}

int Get_Bisic_Value(Basic * Basic_Value,int len)
{
        mpz_t q;
        mpz_init(q);
        Get_Group_G(Basic_Value->g,len,Basic_Value->p,q);
        Get_Big_Number2(Basic_Value->h,Basic_Value->g);
        mpz_clear(q);
        return 0;
}

int Pedersen(Basic *  Basic_Value,Commit * Commit_Value,mpz_t m)
{
        Get_Big_Number2(Commit_Value->r,Basic_Value->g);
        Compute_Values(Commit_Value->Commit_Value,Basic_Value->g,m,Basic_Value->h,Commit_Value->r,Basic_Value->p);
        return 0;
}

int Compute_Y(Check_Value* Value,Commit* Commit,Basic* Basic_Value,mpz_t Gdelta2)
{
        Compute_G_Mul(Value->Y,Commit->Commit_Value,Gdelta2,Basic_Value->p);

}

int Get_Glpha(mpz_t glpha,mpz_t Glpha1,mpz_t Glpha2,Basic * Basic_Value)
{
        Compute_G_Mul(glpha,Glpha1,Glpha2,Basic_Value->p);
        return 0;
}

int Compute_Gwlpha(Commit* Commit,Basic* Basic_Value,mpz_t Delta1)
{
        Pedersen(Basic_Value,Commit,Delta1);
        return 0;
}

int Compute_Gdelta(mpz_t Gdelta,Basic * Basic_Value,mpz_t Delta2)
{
        Compute_Glpha(Gdelta,Basic_Value->g,Delta2,Basic_Value->p);
        return 0;
}

int Client_Check(Check_Value Value[],mpz_t Eta[],mpz_t glpha,Basic Basic_Value,int len)
{
        mpz_t Teta,Yneta,Gseta;
        mpz_init(Teta);
        mpz_init(Yneta);
        mpz_init(Gseta);
        Compute_TEta(Teta,Value,Eta,len);
        Compute_YnEta(Yneta,Value,Eta,len);
        Compute_GsEta(Gseta,Value,Eta,Basic_Value.g,Basic_Value.h,glpha,len);
        Check_Equal(Teta,Gseta,Yneta,Basic_Value.p);
        mpz_clear(Teta);
        mpz_clear(Yneta);
        mpz_clear(Gseta);
        return 0;
}
