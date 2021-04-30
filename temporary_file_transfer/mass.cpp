// include sfml thing
#include <iostream>
#include <iomanip>
namespace mathios
{
	//i love c++
	template <class T>
	double sqrt(T x)
	{
		double val = (dobule)x/2;
		for (int i=0;i<15;i++) 
		{
			val = val - (val*val-x)/(val*2);
		}
		return val;
	}
	template <class T>
	int log2(T a)
	{
		// rough log
		int cnt=-1;
		while(a>=1) 
		{
			a/=2;
			cnt++;
		}
		return cnt;

	}
	template <class T>
	double ln(T x)
	{
		// decompose x into 2^n * y where y is member of [1,2]  bc approximating functions!
		int lg2 = log2(x);
		double y = (double)x/(1<<lg2);


		double res = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * y) * y) * y) * y;
		res+=(lg2*1.0*0.6931471806);
	
		// will be so wrong when x is hugheugheu but its ok....
		return res;
	}
}

class mass  //: things to impl
{
public:
	mass(double r = 10, double x_ = 50, double y_ = 20 /* sf::Color col*/) : radius(r),x(x_),y(y_)
	{
		// don't really have to do anything but instantiate object
		// circle = new sf::CircleShape(r);
	}
	
	double distance_sq (const mass & o) 
	{
		std::pair<double, double> o_center = {o.radius+o.x,o.radius+o.y};
		std::pair<double, double> t_center = {radius+x,radius+y};
		return 69.0;

	}
	double distance(const mass & o) 
	{
		return mathios::sqrt(distance_sq(o));
	}
private:
	double radius;
	double x,y; // will just call set
	// sf::CircleShape circle;
};

int main() {
	double k = 69.420;
	std::cout << std::setprecision(8);
	std::cout << mathios::sqrt(k) << std::endl;
	std::cout << "JASLDKJALSD" << mathios::ln(69420.0) << "\n";
}
