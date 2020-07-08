#include <iostream>

using namespace std;

class Point
{
public:
    Point() { m_x = 0; m_y = 0; };
    Point(int x, int y) : m_x(x), m_y(y) {};
    ~Point() {};

    friend ostream& operator<<(ostream& output, Point& p);
    friend istream& operator>>(istream& input, Point& p);

private:
    int m_x;
    int m_y;
};

ostream& operator<<(ostream& output, Point& p)
{
    output << "x = " << p.m_x << ", " << "y = " << p.m_y;
    return output;
}

istream& operator>>(istream& input, Point& p)
{
    input >> p.m_x >> p.m_y;
    return input;
}

int main()
{
    Point p1(1, 2);
    Point p2;

    cout << "请输入横、纵坐标，以空格间隔：";
    cin >> p2;

    cout << "point1: " << p1 << endl;
    cout << "point2: " << p2 << endl;

    return 0;
}
