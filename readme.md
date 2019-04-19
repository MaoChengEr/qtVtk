* content
{:toc}
### 1.QT,VTK,MinGW,CMake简介

qt：<https://qt-project.org/>，Qt是1991年奇趣科技开发的一个跨平台的C++图形用户界面应用程序框架。它提供给应用程序开发者建立艺术级的图形用户界面所需的所有功能。Qt很容易扩展，并且允许真正地组件编程。基本上，Qt 同X Window上的Motif，Openwin，GTK 等图形界面库和Windows 平台上的MFC，OWL，VCL，ATL是同类型的东西。

vtk:[https://www.mingw.org](<http://www.mingw.org/>)，视觉化工具函式库（VTK，Visualization Toolkit）是一个开放源码，跨平台、支援平行处理的图形应用函式库。

MinGW:[http://www.mingw.org](http://www.mingw.org/)，MinGW，是Minimalist GNU on Windows的缩写。它是一个可自由使用和自由发布的Windows特定头文件和使用GNU工具集导入库的集合，允许你在GNU/Linux和Windows平台生成本地的Windows程序而不需要第三方C运行时库。

cmake：<https://cmake.org/>，cmake是一种跨平台编译工具，比make更为高级，使用起来要方便的多，cmake主要是编写cmakelists.txt文件，然后用cmake命令将cmakelists.txt转化为make所需要的makefile文件，最后使用make命令编译源码生成棵执行程序或共享库。

### 2.准备环境：（版本兼容是个大问题）

本机环境（win10 专业版）

软件：qt：5.5.1<http://download.qt.io/archive/qt/>

​          MinGW，<https://mirrors.tuna.tsinghua.edu.cn/osdn/mingw/68260/mingw-get-setup.exe>

​          cmake: 3.13.4，<https://github.com/Kitware/CMake/releases/download/v3.13.4/cmake-3.13.4.zip>

​          vtk:7.7.1，<https://www.vtk.org/files/release/8.2/VTK-8.2.0.zip>

​	  vs:2013(社区版)，<https://msdn.itellyou.cn/>

### 3.操作步骤

#### 3.1.创建目录

>在d盘目录下创建vtkDir目录，在vtkDir中创建两个目录，一个为vtkDir(**存放VTK7.7.1文件**)，一个为vtkbin(**存放cmake编译后的文件**)。

#### 3.2打开cmake编译VTK文件

1.首先用cmake选择好文件路径，如下图所示：

![1553656369611](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553656369611.png)

2.选择好Visual Studio 12 2013 Win64，点击Finish，会自动Generrate。

![1553656712690](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553656712690.png)



3.生成之后BUILD_SHARED_LIBS一定要打勾，为了生成Lib库文件供Qt和Vs调用，点击Configure。	

![1553657315802](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553657315802.png)

4.在Search中先输入Qt找到VTK_Group_Qt，勾选，继续Configure。

![1553657699025](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553657699025.png)

5.将VTK_QT_VERSION改成5，因为qt版本比较高，继续Configure。

![1553657864487](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553657864487.png)

6.出现以下情况是因为cmake没有正确识别Qt5_DIR的路径导致，这里需要手动设置一下。

![1553657971784](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553657971784.png)

6.找到Qt5.5.1的安装路径，我的是D:\Qt\Qt5.5.1\5.5\msvc2013_64\lib\cmake\Qt5，选择路径后，继续Configure。

![1553658139776](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658139776.png)



7.以下情况同6，需要手动设置路径，设置完毕后继续Configure。

![1553658206780](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658206780.png)

8.直到没有红色警告，点击Add Entry。Name:CMAKE_INSTALL_PREFIX,Type:PATH,Value:选择D:/Qt/Qt5.5.1/5.5/msvc2013_64（这个因人而异），点击OK。

![1553658459968](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658459968.png)



9.继续Configure，直到没有警告。

![1553658681944](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658681944.png)



10.点击Generrate，如下图。

![1553658725912](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658725912.png)



11.以**管理员**身份打开vs2013，打开项目VTK.sln。vtkbin部分文件如下。

![1553658856697](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553658856697.png)

12.选择Release x64,(Debug 会报错！)选择右击ALL_BUILD选择Build生成文件，大概需要会费15到20分钟去编译。

![1553659070913](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553659070913.png)

13.生成成功后，右击INSTALL->Project Only->Build Only INSTALL。

![1553662129125](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553662129125.png)

14.打开C:\Program Files\VTK，出现如下VTK库文件，说明生成成功。

![1553662294417](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553662294417.png)

### 4.如何在Qt设计界面中添加已经生成的Vtk图形界面

1.首先在Qt中新建一个Project，我命名为qtVtk。

![1553737411421](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553737411421.png)



![1553737475862](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553737475862.png)



2.此时打开UI界面是没有VTK组件的

![1553737590454](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553737590454.png)



3.将C:\Program Files\VTK\plugins\designer中QVTKWidgetPlugin.dll文件拷贝到QT_creator，目录为：D:\Qt\Qt5.5.1\5.5\msvc2013_64\plugins\designer（这个目录一般就是qt5.5.1安装的目录）

![1553737791447](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/553737791447.png)



4.此时重启Qt，右击qtVtk.ui->用...打开->Qt Designer。

![1553738014655](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553738014655.png)

5.此时发现在Qt Designer中已经存在QVTKWidget组件，（**NOTICE**）**但是此时的QVTLKWIdget组件看不见摸不着**。

![1553738550526](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553738550526.png)



6.为了解决5的问题，首先设置环境变量，一般为PATH=C:\Program Files\VTK\bin，这里面包含了cmake生成的vtk大量的动态库，如下图所示：

![1553738475811](https://raw.githubusercontent.com/MaoChengEr/maochenger.github.io/master/imgs/1553738475811.png)

7.






