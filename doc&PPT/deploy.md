# Deploy NN model in RK3588  
## 目录  
- [整体流程一览](#整理流程一览-)
- [前置——开发环境准备](#前置开发环境准备-)
- - [RKNN-Tooolkit2安装](#rknn-toolkit2安装-)  
- - [ubantu虚拟机安装](#ubantu虚拟机安装)  
- - [conda环境准备](#conda环境准备-)
### 整理流程一览  
- [x] 1.配置RKNN-TOOLKIT及相关库的环境    
- [x] 2.通过rknn的API进行量化并转换成rknn格式  
- [x] 3.模型连板运行（需要ubantu、PC、板端三端通信）  
- [x] 4.板端部署运行（交叉编译，推送可执行文件到板端）  
- [x] 5.模型评估（精度、内存、耗时等）  

### 前置——开发环境准备  
[参考教程，02_Rockchip_RKNPU_User_Guide_RKNN_SDK_V2.3.2_CN.pdf](http://www.openedv.com/docs/boards/arm-linux/RK3588Linux.html "02_Rockchip_RKNPU_User_Guide_RKNN_SDK_V2.3.2_CN.pdf")
#### RKNN-Toolkit2安装  
此处可使用Docker安装或pip方式安装，作者习惯使用pip，以下介绍pip方式，如需docker，可参考上面参考教程  
##### ubantu虚拟机安装  
虚拟机安装网上教程很多，此处不做赘述，可参考以下链接：  
[虚拟机安装教程](https://blog.csdn.net/qq_62888264/article/details/145102532)  

<u>**说明：请留给虚拟机足够大的磁盘空间和内存，磁盘空间理论上不小于50G，运行内存16G**</u>  

##### Conda环境准备  
1. 下载`miniconda`  
```bash
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
```  
2. 安装`miniconda`  
```bash
bash Miniconda3-latest-Linux-x86_64.sh
```


