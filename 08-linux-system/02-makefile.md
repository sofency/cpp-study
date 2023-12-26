### MakeFile项目管理
1. 命名只能是makefile 或者 Makefile
2. 一个规则，语法如下
```txt
目标:依赖条件
(tab缩进)命令
1. 目标时间必须晚于依赖条件的时间，否则执行指令更新目标
2. 依赖条件不存在，找寻新的规则去产生依赖
3. ALl:(结果) 指定makefile生成的最终目标
```
3. 两个函数
- src = $(wildcard ./*.c): 匹配目标工作目录下的所有.c文件，将文件名组成列表，赋值给变量src
- obj=`$`(patsubst %.c, %.o, $(src)) 将参数3 包含参数1的部分替换为参数2（通过gcc编译后）

- clean
```shell
# 调用make clean 清除之前存在的二进制文件hello.out 当然也可以删除其他文件
clean:
  -rm -rf hello.out 
```
4. 三个自动变量
- $@ 在规则的命令中，表示规则中的目标
- $^ 在规则的命令中，表示所有依赖条件
- $< 在规则的命令中，表示第一个依赖条件

5. 当项目文件中存在clean文件时 make clean 会报错
```shell
ALL:hello.out

clean:
  -rm -rf ALL

.PHONY: clean ALL

```
完整的makefile案例
```shell
src=$(wildcard ./src/*.c)
# 将.c文件 gcc 编译为.o文件
obj=$(patsubst %.c, %.o, $(src))

ALL:hello.out 
hello.out:$(obj)
  gcc $(obj) -o $@
  mv $(obj) ./obj/ 
 ./src/hello.o:./src/hello.c
  gcc -c $< -o $@ -I ./inc
 #模式匹配
 #%.o从 obj中依次取出,且从src中取出对应的%.c
 #如果上面自己定义了处理方式 下面会过滤掉对于hello.c的处理
./src/%.o:./src/%.c
  gcc -c $< -o $@ 

# make clean清除之前的操作
clean:
  -rm -rf hello.out
 
.PHONY: clean ALL
```