#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

const double quart_pi = 0.785;
typedef enum point_type
{
    line,radx,rady
    
} point_type;

typedef enum shape_type
{
    l,e
    
} shape_type;

struct Point
{
    double x;
    double y;
};

struct Vector
{
    double dx;
    double dy;
};

double get_point(double t, double coord, double vec); // x = x0 + vt, y = y0 + vt


class Shape
{
    protected:
    Point o;
    Vector v1;
    shape_type st;
    
    public:
    virtual ~Shape(){cout<<"Shape Destructor"<<endl;}
    Shape(Point cntr, Vector vec):o(cntr),v1(vec){}
    virtual Point GetCoord(double t, point_type pt) const = 0;
    virtual Vector GetVector(point_type pt) const = 0;
    virtual void PrintCoordQuartPi() = 0;
    shape_type GetType() const
    {
        return st;
    }
   
};

class Line : public Shape
{
    public:
    Line(Point cntr, Vector vec):Shape(cntr,vec){st = l;}
   
    Point GetCoord(double t, point_type const pt = line) const
    {
        Point p;
        
        p.x =  get_point(t, o.x, v1.dx );
        p.y =  get_point(t, o.y, v1.dy );
          
        return p;
    }
    Vector GetVector(point_type const pt = line) const
    {
        return v1;
    }
    void PrintCoordQuartPi()
    {
        Point p;
        p = GetCoord(quart_pi);
        
             cout<<"Line:";
             cout<<"Point at Pi/4:";
             cout <<"x = "<<p.x<<" "
                  <<"y = "<<p.y<<"; ";
             cout<<"Vector("<<v1.dx<<", "<<v1.dy<<")"<<endl;
    }
    
};

class Ellipse : public Shape
{
    private:
    Vector v2;
    public:
    Ellipse(Point cntr, Vector vx, Vector vy):Shape(cntr,vx)
    {
        st = e;
        v2 = vy;
    }
    Point GetCoord(double t, point_type pt) const
    {
        Point p;
        
        switch (pt)
        {
            case radx:
                p.x =  get_point(t, o.x, v1.dx );
                p.y =  get_point(t, o.y, v1.dy );
                break;
            case rady:
                p.x =  get_point(t, o.x, v2.dx );
                p.y =  get_point(t, o.y, v2.dy );
                break;
                
            default:
                
                break;
       }
       
        return p;
    }
    Vector GetVector(point_type pt) const
    {
        Vector v;
        switch (pt)
        {
            case radx:
                v.dx = v1.dx;
                v.dy = v1.dy;
                break;
            case rady:
                v.dx = v2.dx;
                v.dy = v2.dy;
                break;
                
            default:
                
                break;
       }
       
        return v;
        
    }
    void PrintCoordQuartPi()
    {
        Point p;
        p = GetCoord(quart_pi,radx);
        
        cout<<"Ellipse:";
        
        cout<<"Point at Pi/4 radii x:";
        cout <<"x = "<<p.x<<" "
             <<"y = "<<p.y<<"; ";
        cout<<"Vector("<<v1.dx<<", "<<v1.dy<<")"<<endl;
        
        p = GetCoord(quart_pi,rady);

        cout<<"        Point at Pi/4 radii y:";
        cout <<"x = "<<p.x<<" "
             <<"y = "<<p.y<<"; ";
        cout<<"Vector("<<v2.dx<<", "<<v2.dy<<")"<<endl;
        
    }
};

double get_point(double t, double coord, double vec )
{
    return coord + (t*vec);
}

// Testing the Interface
int main()
{
   
    Point mp;
     
    vector <Shape*> container = {
                                 new Line({13,6},{0,3}),
                                 new Line({13,6},{5,0}),
                                 new Ellipse({13,6},{5,0},{0,3}),
                                 new Line ({2,2},{11,1}),
                                 new Line ({3,10},{5,-5})
                                };
  
    cout<< "Print point coordinates at t = PI/4 for each figure in the container:"<<endl;
    for(int i = 0; i < 5; i++)
    {
        container[i]->PrintCoordQuartPi();
    }
    
    double t;
    srand(time(NULL));
    
    cout<< "Print point coordinates at random t for each figure in the container:"<<endl;
    for(int i = 0; i < 5; i++)
    {
        
        if(container[i]->GetType() == l)
        {
            mp = container[i]->GetCoord(t = (rand()%100)/(100*1.0), line);
            cout<<"Line:"<<endl;
            cout<<"Coord:x = "<<mp.x<<" y = "<<mp.y<<" at t = "<<t<<endl;
        }
        else if (container[i]->GetType() == e)
        {
            cout<<"Ellipse:"<<endl;
            mp = container[i]->GetCoord(t = (rand()%100)/(100*1.0),radx);
            cout<<"Ellipse radii x:"<<endl;
            cout<<"Coord:x = "<<mp.x<<" y = "<<mp.y<<" at t = "<<t<<endl;
            mp = container[i]->GetCoord(t = (rand()%100)/(100*1.0),rady);
            cout<<"Ellipse radii y:"<<endl;
            cout<<"Coord:x = "<<mp.x<<"  y = "<<mp.y<<" at t = "<<t<<endl;
        }

    }
    for(int i = 0; i < 5; i++)
    delete container[i];
 
    return 0;
}

