### Shell 常用操作整理

基本命令
``` shell
control + a  #光标移动终端前面
control + e  #光标移动到终端后面
control + u  #清除终端的一些信息
ls -Rl       #目录文件递归展示

cp hello.c cpp #将hello.c拷贝到cpp目录下
cp -a dir dest #将当前目录下的文件夹dir 拷贝到目标路径dest下 
ln -s 文件绝对路径 软连接名字

# 在目标路径下查找，且查找的深度为1， 按照 *.jpg的格式查找
# -type 按照文件类型搜索
find 要在哪个路径下查询 -maxdepth 1 -name '*.jpg'
find ./ -size 20M -size 50M #在当前路径下查找文件大小在20M-50M之间的文件

# -exec 将find 搜索的结果集执行某一条指令
# xargs 将find搜索的结果集执行某一指定命令，当结果集数量过大时，可以分片映射
find ./ -maxdepth 1 -name '*.jpg' -exec ls -la {} \;
# 这种缺陷在处理 有的文件名有空格时会报错
find ./ -maxdepth 1 -name '*.jpg' | xargs ls -la;
find ./ -maxdepth 1 -name '*.jpg' -print0 | xargs -print0 ls -la;



# 递归从当前目录下搜索每个文件中是否包含 'copy'
# -n 可以给出行号
grep -r 'copy' ./ -n 
# 打开文件stdio.h 并定位到15行
vim stdio.h +15 

# 查询进程中运行名字包含java的进程
ps aux | grep "java"

# 压缩 gzip方式压缩
tar -czvf test.tar.gz file  #gzip方式压缩
tar -jcvf test.tar.gz file  #使用bzip2方式压缩
# -r 是递归
rar a -r 新名字 要压缩的文件
# 将dir stdio.h test.mp3 压缩进test.zip中 -r是递归压缩
zip -r test.zip dir stdio.h test.mp3

# 解压 就是将解压的内容放到指定文件中
tar -zxvf 压缩表.tar.gz -C 目标名
# 解压到当前目录
unrar x 新名字
# 这个也是解压到当前目录 注意创建新文件夹接收
unzip -r test.zip -d /home/sofency/test


# 命令起别名
alias 别名="指令"
```

vim相关操作
```shell
# 进入插入模式
i：插入光标前一个字符
I: 插入行首
a: 插入光标后一个字符
A: 插入行末
o: 向下新开一行，插入行首
O: 向上新开一行，插入行首

# 跳转到指定行
1. 88G 跳转到88行
2. :88  命令方式下:输入88

gg # 跳转整个文本开头

G #  跳转文本尾
gg=G # 代码自动格式化

ctrl + d #向下翻半屏
ctrl + u #向上翻半屏
ctrl + f #向下翻一屏
ctrl + b #向上翻一屏

%   #{ 大(小)括号对应
dw  #鼠标位于单词首部 删除整个单词
D 或者 d$   #删除光标至行尾
0   #光标移至行首  
$   #光标移至行尾
d0  #删除关标至行首


yy # 复制整行
p  #往光标后粘贴
P  #向光标前粘贴

# 查找
/name  #在文件中查找name  按n找下一个
光标置于任意一个字符上  按* 或者 # 全文查找光标后的单词

# 这样操作会替换全部行 但是每行只有一个被替换
:%s /sofency/alice 将sofency替换为alice

# 这样可以全部替换
:%s /sofency/alice/g 将sofency替换为alice

# 选中区域进行替换
:29,35s /sofency/alice/g 将29-35之间行的sofency替换为alice

u #撤销操作 

# 分屏操作
:sp  横屏分 
:vsp 竖屏分
ctrl ww #切换分屏

#强制退出所有分屏
:qall! 

# 查找函数含义
# yum install -y man-pages 没有文档 需要下载下
2+K #鼠标移动到要查找的函数上 按3K

# 在编辑文件的时候可以输入命令
# 这样有助于 在函数编写过程中需要的话 不用退出当前文件进行操作
:!ps aux | grep kernel

# 删除指定区域
V 然后操作hjkl 选中区域进行选择要删除的区域，最后按d进行删除

dd # 删除一行
29dd #删除光标下29行数据

# gcc编译
# -I 指定头文件所在的目录
# -g 编译时添加调试语句 主要支持gdb调试
# -Wall 显示所有警告信息
# -D是否启动宏定义 #ifdef HELLO #endif
gcc -I ./inc hello.c -o hello
gcc -I ./inc hello.c -o hello -D HELLO


# 静态库的制作
# 1. 首先编写相关的函数 例如network.c hello.c
# 2. 然后将它们都编译为.o文件 gcc -c network.c -o network.o

# 3. 制作静态库(最好以lib开头)  ar rcs liboperate.a network.o hello.o 
# 4. 然后 在使用的时候编译时 gcc test.c  liboperate.a -o test
# test.c中要向不警告 最好声明下你在使用外部的函数 extern int add(int a, int b);(函数位于hello.c中)
# 这样才不警告
# 或者 将对应的函数声明放到.h文件中
# 这样test.c中才能使用上面生成的动态库中的函数
# lib下存放静态库 inc存放.h文件
gcc hello.c ./lib/liboperate.a -o hello -I ./inc


# 动态库的制作
# 1. 首先编写相关的函数 例如add.c sub.c
# 2. 编译为.o文件 gcc -c add.c -o add.o -fPIC
# 3. 制作动态库 gcc -shared -o lib库名.so add.o sub.o
# 4. 编译可执行文件 gcc test.c -o test.out -l库名 -L库路径  注意库名不要和上面生成的.o名字一样 否则容易报错
# 5. 需要将生成的lib库名.so 放到 LD_LIBRARY_PATH指定的目录下 即在环境变量中声明动态库路径
# vim /etc/profile.d/cpp.sh  export LD_LIBRARY_PATH=/root/gcc/lib source /etc/profile
gcc test.c -o test.out -loperate -L./lib -I./inc

# 动态库路径问题解决
# 1. 或者拷贝自定义动态库到系统的lib库下 sudo cp liboperate.so /lib (C标准所在库)但是不建议这样做
# 2. 上述5
# 3. sudo vim /etc/ld.so.conf 将lib库路径写进该文件 /root/gcc/lib
#    sudo ldconfig -v #更新lib配置文件 这样就可以生效了


# gdb断点调试
gcc hello.c -o a.out -g #这样得到调试表
gdb a.out

list： list 1 列出源码  可以根据源码指定行好设置断点
b 12 : 在12行设置断点
run : 设置完断点后输入run 执行程序
n/next: 下一条指令 会越过函数
s/step: 下一条指令 会进入函数
p/print: p num  输出变量值
continue: 继续执行断点后的其他指令
quit: 退出gdb调试

set args 设置main函数命令行参数 
start: 进入调试界面操作后，我们可以直接输入start 默认从main函数第一行开始执行 然后再自己输入n/s进行继续调试
finish: 如果我们s进入函数里面进行测试时 可以输入finish完成当前函数执行
info b：展示所有断点信息
b 45 if i = 5 # 条件断点 如果当前i=5的话设置断点信息
delete b 45 删除45行断点num


bt 列出当前程序存活的栈针
frame 编号： 根据栈针编号切换栈

display i : 当进行n操作 进行下一步时 会显示 i当前的值 追踪i的变化
undisplay 编号：取消跟踪 这里的编号是在上述显示时 最前面的编号
```