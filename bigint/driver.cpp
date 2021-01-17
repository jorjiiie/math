#include "int_2240.cpp"

int main() {
	std::cout << "HI\n";
	int_2240::badNumber c = std::string("123456722896942049");
	int_2240::badNumber d = std::string("12345678942049");
	d.printraw();
	c.printraw();
	int_2240::badNumber a = c*d;
	a.print();
	int_2240::badNumber b = c-d;
	b.print();
}