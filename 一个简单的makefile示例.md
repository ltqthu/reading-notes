
# һ���򵥵�makefileʾ��

�ڵ�ǰĿ¼�½�demo�ļ��У�

```bash
mkdir demo && cd demo
```

��д��������

```bash
vim main.cpp
```

д���ļ����ݣ�

```cpp
#include <iostream>
using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

�½���д��makefile�����ݣ�

```bash
all: main.o
	g++ -std=c++11 -o all main.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
  
clean:��������������������  
	rm -rf all main.o
```

ִ��make���

```bash
make
```

ִ���±���Ŀ�ִ���ļ���

```bash
./a.out
```








