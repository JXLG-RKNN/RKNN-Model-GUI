# Deploy NN model in RK3588  
## 目录  
- [整体流程一览](#整理流程一览)
- [前置——开发环境准备](#前置开发环境准备)
- - [RKNN-Tooolkit2安装](#rknn-toolkit2安装)  
- - - [ubantu虚拟机安装](#ubantu虚拟机安装)  
- - - [conda环境准备](#conda环境准备)  
- - [设备端NPU环境准备](#设备端npu环境准备)  
- - - [npu驱动版本确认](#npu驱动版本确认)
- - - [npu连板环境确认](#npu连板环境确认)  

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
3. 激活`miniconda`  
```bash
source ~/miniconda3/bin/activate
```  
4. 创建python3.8虚拟环境  
```bash
conda create -n rknn python=3.8 -y
```  
5. 激活环境  
```bash
conda activate rknn
```
6. 若官方源下载较慢，可以切换成国内镜像源（如清华源）  
```bash
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge
conda config --set show_channel_urls yes
```  
7. 安装RKNN-Toolkit2  
```bash
pip install rknn-toolkit2 -i https://pypi.org/simple
# 如果已安装 RKNN-Toolkit2， 可通过以下命令升级 RKNN-Toolkit2
pip install rknn-toolkit2 -i https://pypi.org/simple --upgrade
```  
8. 若执行以下命令没有报错，则安装成功  
```bash
$ python3
>>> from rknn.api import RKNN 
```  


#### 设备端NPU环境准备  
##### NPU驱动版本确认  
查询命令：  
```bash
dmesg | grep -i rknpu
或 cat
/sys/kernel/debug/rknpu/version
或 cat
/sys/kernel/debug/rknpu/driver_version
或 cat
/proc/debug/rknpu/driver_version
```  
查询结果：  
```bash
RKNPU driver: vX.X.X
```
X.X.X表示版本号，例如0.9.2。
Rockchip的固件均自带RKNPU驱动。若以上命令均查询不到NPU驱动版本，则可能为第三方固件未安装
RKNPU驱动，需要打开`kernel config`文件的“CONFIG_ROCKCHIP_RKNPU=y”选项，重新编译内核驱动并
烧录。建议RKNPU驱动版本>=0.9.2  

##### NPU连板环境确认
RKNN-Toolkit2的连板调试功能依赖板端的`RKNN Server`程序，该程序是一个运行在开发板上的后台代理
服务，用于接收PC通过USB传输过来的命令和数据，然后调用相应的运行时接口，并返回相应结果给 PC。所以在做连板调试前需要确认开发板是否已启动`RKNN Server`程序。

**检查方法**：通过ADB工具进入开发板终端，查询是否有RKNN Server进程  
```bash
adb shell
ps | grep rknn_server
```
> ***注意**：ADB工具需要使用数据线连接板端和PC，此处不明白可上网查询*  

查询结果：  
```bash
702 root 1192 S grep rknn_server
```