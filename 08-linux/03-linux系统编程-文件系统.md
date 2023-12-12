### 常见系统调用IO函数
#### 1. open函数
- 常见参数： O_RDONLY(只读), O_WRONLY(只写), O_RDWR(可读可写), O_APPEND(追加), O_CREAT(创建), O_EXCL(), O_TRUNC(清空), O_NONBLOCK
- 使用头文件<fcntl.h>
- 创建文件时，指定文件访问权限，权限同时受umask影响 文件权限 = mode & ~umask
- 常见错误如何查看 引入头文件errno.h 就可以直接使用errno(系统提供的变量)查看错误类型的整型值，然后再引入string.h, 使用strerror(errno) 可以返回错误类型描述符

#### 2. read 函数
- ssize_t read(int fd, void * buf, size_t count);
- 参数 fd:文件描述符，buf:存数据的缓冲区首地址，count, 缓冲区大小
- 返回值: 0 读到文件尾；成功: > 0 读到的字节数，失败: -1, 设置errno,如果errno=EAGIN或者WEWOULDBLOCK,说明不是read失败，而是read在以非阻塞方式读一个设备文件，并且文件无数据。

#### 3. 文件描述符
- 一个进程最多可以打开1024个文件，fd就是文件描述符的标号
- 0 STDIN_FILENO /  1 - STDOUT_FILENO   /  2 - STDERR_FILENO 这三个描述符有固定作用，在打开文件的时候不会使用0-2

#### 4. 阻塞非阻塞
- 产生阻塞的场景，读设备文件，或读网络设备
- /dev/tty -- 终端文件
- open("/dev/tty", O_RDWR|O_NONBLOCK) -- 设置/dev/tty非阻塞状态
#### 5. fcntl函数 获取文件状态
- int flgs = fcntl(fd, F_GETFL);
- flgs |= O_NONBLOCK;
- fcntl(fd, F_SETFL, flgs);

- 获取文件状态: F_GETFL, 设置文件状态: F_SETFL


#### 6. lseek函数
linux可以使用系统函数lseek来修改文件偏移量，每个打开的文件都记录着当前读写位置，打开文件时读写位置为0，表示文件开头，当以追加方式写入的时候，lseek就是文件末尾。文件的读写使用同一个便宜量, 如果不将偏移量初始化为0则读取不到数据
- lseek(fd_write, 0, SEEK_SET);  // 重定义文件偏移量位置 这里的0如果设置为10，这样获取到的size依旧不是，除非发生文件IO操作，文件大小才变化
- int size = lseek(fd_read, 0, SEEK_END); // 野路子获取文件大小

#### 7. access函数
- 测试指定文件是否存在某种权限
- int access(const char * pathname, int mode); //成功/具备该权限 0; 失败/不具备该权限 errno为相应值。
- 参数2 R_OK, W_OK, X_OK
- 通常使用access函数测试某个文件是否存在。F_OK

#### 8. chmod函数
- 修改文件的访问权限
- int chmod(const char *path, mode_t mode); 成功：0 失败：-1 设置errno相应值
- int fchmod(int fd, mode_t mode);

#### 9. truncate函数
- 截断文件长度为指定长度，常用来拓展文件大小，代理lseek
- int truncate(const char*path, off_t length); 成功：0； 失败：-1  设置errno相应值
- int ftruncate(int fd, off_t length);

#### 10: link/unlink函数
- linux允许多个目录项共享一个inode,即共享盘块。link函数可以为已经存在的文件创建目录项（硬连接）
- int link(const char* oldpath, const char * newpath);成功：0，失败：-1 设置errno相应值 类似 mv命令改名
- int unlink(const char* pathname); 成功:0 失败:-1  设置errno为相应值 #类似删除文件
- unlink函数的特征：清除文件时，如果文件的硬连接数到0了，没有dentry对应，但该文件仍不会马上被释放，要等到所有打开该文件的进程关闭该文件，系统才会挑时间将该文件释放掉。unlink操作只是让文件具备了被释放的条件。

#### 11. 隐式回收
当进程结束运行时，所有该进程打开的文件会被关闭，盛情的内存空间会被释放，系统的这一特性称之为隐式回收系统资源
#### 12. readlink
- 读取符号连接文件本身内容，得到连接所指向的文件名
- ssize_t readlink(const char*path, char * buf, size_t bufsiz);成功 返回时机读到的字节数，失败-1，设置errno为相应值


#### dup和dup2函数
- int dup(int oldfd); 成功：返回一个新文件描述符；失败：-1设置errno为相应值 自动分配newfd
- int dup2(int oldfd, int newfd);  本身就是使两个文件描述符都指向一个文件 可以手动指定newfd
- fcntl函数实现dup  fcntl(fd, F_DUPFD, fd_other) 如果第三个参数的fd是被占用的则，返回最小可用的描述符，如果是未被占用的，就返回该值
