#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

struct Point
{
    int x;
    int y;
    Point() :x(0), y(0) {}
    Point(int x,int y) :x(x), y(y) {}
};

class Shape
{
protected:
    string name;
    string type;
public:
    Shape() :name("no name"), type("none") {}
    Shape(string n, string t) :name(n), type(t) {}
    
    virtual void Print()const = 0;

    virtual ~Shape() = 0 {}
};

class Line : Shape
{
    Point point1;
    Point point2;
public:
    Line() :point1(), point2(), Shape() {}
    Line(string n, string t, Point p1, Point p2) :
        point1(p1), point2(p2), Shape(n, t) {}

    void Print()const
    {
        gotoxy(point1.x, point1.y);
        cout << "*";
        gotoxy(point2.x, point2.y);
        cout << "*" << endl;

        cout << "Shape's name : " << name << endl;
        cout << "Shape's type : " << type << endl;
        Sleep(1500);
        system("cls");
    }
};

class Rectangled : public Shape
{
    Point start;
    int width;
    int height;
public:
    Rectangled() :start(), width(0), height(0), Shape() {}
    Rectangled(string n, string t, Point p, int w, int h) :
        start(p), width(w), height(h), Shape(n, t) {}

    void Print()const
    {
        gotoxy(start.x, start.y);
        for (int i = 0; i < height; i++)
        {
            gotoxy(start.x, start.y+i);
            for (int i = 0; i < width; i++)
            {
                cout << "#";
            }
            cout << endl;
        }
        cout << "Shape's name : " << name << endl;
        cout << "Shape's type : " << type << endl;
        Sleep(1500);
        system("cls");
    }
};

class Polylined : Shape
{
    Point* points;
    int countPoints;
public:
    Polylined() :points(nullptr), countPoints(0), Shape() {}
    Polylined(string n, string t) : Shape(n, t) {};

    void AddPoint(Point point)
    {
        Point* temp = new Point[countPoints+1];
        for (int i = 0; i < countPoints; i++)
        {
            temp[i] = points[i];
        }
        temp[countPoints] = point;
        delete[]points;
        points = temp;
        countPoints++;
    }

    void Print()const
    {
        for (int i = 0; i < countPoints; i++)
        {
            gotoxy(points[i].x, points[i].y);
            cout << "*";
        }
        cout << endl;
        cout << "Shape's name : " << name << endl;
        cout << "Shape's type : " << type << endl;
        Sleep(3000);
        system("cls");
    }

    ~Polylined()
    {
        if (points != nullptr)
            delete[]points;
    }
};

int main()
{
    /*Line line("Shape 1", "Line", { 2,2 }, { 4,4 });
    line.Print();

    Rectangled rect("Shape 2", "Rectangle", { 6,5 }, 7, 5);
    rect.Print();*/

    Polylined poly("Shape 3", "Polyline");
    for (int i = 0; i <= 5; i++)
    {
        poly.AddPoint({ i,i });
    }
    poly.Print();
}
