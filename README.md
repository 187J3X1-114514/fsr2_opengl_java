# fsr2_opengl_java
关于FSR2+OpenGL+Java这种抽象组合的库

> [!IMPORTANT]
> 这个库是为了[SuperResolution](https://github.com/187J3X1-114514/superresolution) *(一个Minecraft模组)* 所编写的，可能有些代码不适合直接使用，建议修改后再使用

> [!IMPORTANT]
> 这个库仅只支持OpenGL

## 构建
> 构建在bin文件夹中
### Linux 
> [!CAUTION]
> 仅支持在WSL2中构建

需求：

* OpenGL开发环境
* C/C++开发环境
* Python

构建命令：
```
git clone https://github.com/187J3X1-114514/fsr2_opengl_java
cd fsr2_opengl_java
mkdir build
cd build
cmake ..
make
```
### Windows
需求：
* mingw32
* cmake

构建命令：
```
git clone https://github.com/187J3X1-114514/fsr2_opengl_java
cd fsr2_opengl_java
mkdir build
cd build
cmake .. -G"MinGW Makefiles"
mingw32-make
```

## 支持的平台

* Windows x64
* Linux x64 *(可能会有armv8架构)*

## TODO

* 将大部分C++类型转换为Java类型
* 支持Android系统

## 感谢

* [@JuanDiegoMontoya](https://github.com/JuanDiegoMontoya/FidelityFX-FSR2-OpenGL) 把FSR2移植到OpenGL
* [@TheJackiMonster](https://github.com/TheJackiMonster/FidelityFX-FSR2) 让FSR2可以在Linux上编译