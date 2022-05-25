# -A-SPDZ-friendly-input-consistency-inspection-scheme
本实验仅用于学术研究，不能保证其在工业上没有问题  
方案依赖于以下项目  
##HElib  
HElib is an open-source (Apache License v2.0) software library that implements homomorphic encryption (HE).  
项目地址：https://github.com/homenc/HElib  
##SPDZ  
Software to benchmark various secure multi-party computation (MPC) protocols such as SPDZ, SPDZ2k, MASCOT, Overdrive, BMR garbled circuits, Yao's garbled circuits, and computation based on three-party replicated secret sharing as well as Shamir's secret sharing (with an honest majority).  
项目地址：https://github.com/data61/MP-SPDZ  
##功能实现  
利用HElib中同态加密方案BGV实现了在利用SPDZ进行安全计算前对输入的验证（单方）。  
功能实现在test.cpp中
##环境依赖  
*Linux(Ubuntu 18.04)  
*g++ >=9  
*GMP >=6.1.0  
*HElib  
*SPDZ  
##运行方式
参考HElib中项目运行方式，将test.cpp、tool.c、tool.h放到HElib项目运行目录中
