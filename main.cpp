#include <QCoreApplication>
#include <iostream>
#include <math.h>

using namespace std;

class IIntegrator{
public:
    virtual double integrate(double a, double b, double h)=0;
};

double f(double x)
{
     return sin(3*x);
};

class Parabola: public IIntegrator{
public:
    double integrate(double a, double b, double h){
        double Integral;
        double n;
        n = (b - a) / h;
        Integral = h * (f(a) + f(b)) / 6.0;
        for(int i = 1; i <= n; i++)
            Integral = Integral + 4.0 / 6.0 * h * f(a + h * (i - 0.5));
        for(int i = 1; i <= n-1; i++)
            Integral = Integral + 2.0 / 6.0 * h * f(a + h * i);
        std::cout<< "Parabola: " << Integral << std::endl;
    };
};

class Trapezoid: public IIntegrator{
public:
    double integrate(double a, double b, double h){
        double Integral;
        double n;
        n = (b - a) / h;
        Integral = h * (f(a) + f(b)) / 2.0;
      for(int i = 1; i <= n-1; i++){
        Integral = Integral + h * f(a + h * i);
      };
      std::cout<< "Trapezoid: " << Integral << std::endl;
    };
};

class Rectangle: public IIntegrator{
public:
    double integrate(double a, double b, double h){
        double Integral;
        double n;
        n = (b - a) / h;
        Integral = 0;
        for(int i = 1; i <= n; i++){
            Integral = Integral + h * f(a + h * (i - 0.5));
        };
        std::cout<< "Rectangle: " << Integral << std::endl;
    };
};

class Client {
private:
    IIntegrator* integrator;
public:
    Client(IIntegrator* integrator) : integrator(integrator) {}

    void setStrategy(IIntegrator* integrator) {
        this->integrator = integrator;
    }

    void integrateStrategy() {
        integrator->integrate(2,4,0.1);
    }
};


int main(int argc, char *argv[])
{
    Parabola parabola;
    Trapezoid trapezoid;
    Rectangle rectangle;

    Client client(&parabola);
    client.integrateStrategy();

    client.setStrategy(&trapezoid);
    client.integrateStrategy();

    client.setStrategy(&rectangle);
    client.integrateStrategy();

    QCoreApplication a(argc, argv);
    return a.exec();
}
