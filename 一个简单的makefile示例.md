
# 一个简单的makefile示例

在当前目录新建demo文件夹：

```bash
mkdir demo && cd demo
```

编写主函数：

```bash
vim main.cpp
```

写入文件内容：

```cpp
#include <iostream>
using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

新建并写入makefile的内容：

```bash
all: main.o
	g++ -std=c++11 -o all main.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
  
clean:　　　　　　　　　　  
	rm -rf all main.o
```

执行make命令：

```bash
make
```

执行新编译的可执行文件：

```bash
./a.out
```








