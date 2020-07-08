我们希望在一个容器中存储类型不同但相互关联的对象，比如说派生自同一个基类的对象。但是通常容器只能包含一种数据类型，所以很难在容器中存储对象本身。存储指向对象的指针，虽然允许通过继承来处理类型不同的问题，但是也增加了内存分配的额外负担。

比如说我们有一个Animal虚基类：

```c++
class Animal
{
public:
    virtual string GetName() = 0;
    virtual Animal* copy() const = 0;
    virtual ~Animal() {}
};
```

另外有三个子类：Cat类、Dog和Bird类，派生自Animal虚基类。

Cat类：

```c++
class Cat : public Animal
{
public:
    virtual string GetName() { return "Cat"; }
    virtual Animal* copy() const { return new Cat(*this); }
};
```

Dog类：

```C++
class Dog : public Animal
{
public:
    virtual string GetName() { return "Dog"; }
    virtual Animal* copy() const { return new Dog(*this); }
};
```

Bird类：

```C++
class Bird : public Animal
{
public:
    virtual string GetName() { return "Bird"; }
    virtual Animal* copy() const { return new Bird(*this); }
};
```

现在我们想定义一个动物园容器(zoo)，用来同时存储以上三个子类。可不可以定义这样一个数组来存储呢？

```c++
Animal zoo[1000];
```

这样是不行的，原因在于Animal是一个虚基类，只有从类Animal派生出来的类才能实例化，虚基类Animal是不会有对象的（虚基类好惨）。

可以通过代理类来实现不同类型在同一容器内的存储：构造一个代理类，代理类中包含虚基类的指针，该指针可以指向不同类型但又互相关联的子类对象，进而可以通过指针调用子类的方法，同时实现内存管理。

同时需要一个无参构造函数，一个含参构造函数，一个复制构造函数，一个析构函数，重载操作符=，和实现虚基类的接口。

```C++
// 代理类
class AnimalSurrogate
{
public:
    // 构造函数
    AnimalSurrogate() :m_pAnimal(nullptr) {}
    AnimalSurrogate(const Animal& animal) :m_pAnimal(animal.copy()) {}

    // 复制构造
    AnimalSurrogate(const AnimalSurrogate& surrogate) :m_pAnimal(surrogate.m_pAnimal != nullptr ? surrogate.m_pAnimal->copy() : nullptr) {}

    ~AnimalSurrogate()
    {
        if (m_pAnimal != nullptr)
        {
            delete m_pAnimal;
            m_pAnimal = nullptr;
        }
    }

    // 重载 = 操作符
    AnimalSurrogate& operator=(const AnimalSurrogate& surrogate)
    {
        if (this != &surrogate)
        {
            delete m_pAnimal;
            m_pAnimal = surrogate.m_pAnimal != nullptr ? surrogate.m_pAnimal->copy() : nullptr;
        }
        return *this;
    }

    // 通过代理类直接访问子类的方法
    string GetName()
    {
        if (m_pAnimal == nullptr)
        {
            throw "m_pAnimal is nullptr";
        }
        return m_pAnimal->GetName();
    }

private:
    Animal* m_pAnimal;
};
```



完整代码：

```C++
#include <iostream>
#include <string>
using namespace std;

// 虚基类
class Animal
{
public:
    virtual string GetName() = 0;
    virtual Animal* copy() const = 0;
    virtual ~Animal() {}
};

// 子类Cat
class Cat : public Animal
{
public:
    virtual string GetName() { return "Cat"; }
    virtual Animal* copy() const { return new Cat(*this); }
};

// 子类Dog
class Dog : public Animal
{
public:
    virtual string GetName() { return "Dog"; }
    virtual Animal* copy() const { return new Dog(*this); }
};

// 子类Bird
class Bird : public Animal
{
public:
    virtual string GetName() { return "Bird"; }
    virtual Animal* copy() const { return new Bird(*this); }
};

// 代理类
class AnimalSurrogate
{
public:
    // 构造函数
    AnimalSurrogate() :m_pAnimal(nullptr) {}
    AnimalSurrogate(const Animal& animal) :m_pAnimal(animal.copy()) {}

    // 拷贝构造
    AnimalSurrogate(const AnimalSurrogate& surrogate) :m_pAnimal(surrogate.m_pAnimal != nullptr ? surrogate.m_pAnimal->copy() : nullptr) {}

    ~AnimalSurrogate()
    {
        if (m_pAnimal != nullptr)
        {
            delete m_pAnimal;
            m_pAnimal = nullptr;
        }
    }

    // 重载 = 操作符
    AnimalSurrogate& operator=(const AnimalSurrogate& surrogate)
    {
        if (this != &surrogate)
        {
            delete m_pAnimal;
            m_pAnimal = surrogate.m_pAnimal != nullptr ? surrogate.m_pAnimal->copy() : nullptr;
        }
        return *this;
    }

    // 通过代理类直接访问子类的方法
    string GetName()
    {
        if (m_pAnimal == nullptr)
        {
            throw "m_pAnimal is nullptr";
        }
        return m_pAnimal->GetName();
    }

private:
    Animal* m_pAnimal;
};


int main()
{
    Cat cat;
    Dog dog;
    Bird bird;

    AnimalSurrogate zoo[3];
    zoo[0] = AnimalSurrogate(cat);
    zoo[1] = AnimalSurrogate(dog);
    zoo[2] = AnimalSurrogate(bird);

    cout << zoo[0].GetName() << endl; //输出 Cat
    cout << zoo[1].GetName() << endl; //输出 Dog
    cout << zoo[2].GetName() << endl; //输出 Dird
    getchar();
    return 0;
}
```

代理类的的每个对象都代表另一个对象，该对象可以使位于一个完成继承层次中的任何类的对象。通过在容器中用代理对象而不是对象本身的方式，实现容器中存放不同类型的对象。

使用代理类的优缺点如下:

优点：使用代理类比直接在容器中存放不同对象的指针更安全，便于实现内存管理。
缺点：内存开销太大，放入容器的每个对象都需要拷贝一次，不够灵活。

参考

> 《C++沉思录》
>
> https://www.cnblogs.com/lzm-cn/articles/9094617.html
>
> https://www.cnblogs.com/marchtea/archive/2011/12/04/2275194.html











