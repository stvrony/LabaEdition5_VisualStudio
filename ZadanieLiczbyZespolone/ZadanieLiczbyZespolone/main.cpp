#include <iostream>
#include <cmath>

using namespace std;

class ComplexNumber
{
public: 
	ComplexNumber(double re = 0, double im = 0)		// Parameterized Constructor
	{
		m_re = re;
		m_im = im;
	}
	ComplexNumber(const ComplexNumber& other)		// Copy Constructor
	{
		m_re = other.m_re;
		m_im = other.m_im;
	}

	ComplexNumber ComplexAdd(const ComplexNumber& other)	
	{
		double newRe = m_re + other.m_re;
		double newIm = m_im + other.m_im;
		return ComplexNumber(newRe, newIm);
	}

	ComplexNumber ComplexSubstract(const ComplexNumber& other)
	{
		double newRe = m_re - other.m_re;
		double newIm = m_im - other.m_im;
		return ComplexNumber(newRe, newIm);
	}
	
	ComplexNumber ComplexMultiply(const ComplexNumber& other)
	{
		double newRe = (m_re * other.m_re) - (m_im * other.m_im);
		double newIm = (m_re * other.m_im) + (m_im * other.m_re);
		return ComplexNumber(newRe, newIm);
	}
	
	ComplexNumber ComplexDivide(const ComplexNumber& other)
	{
		double mianownik = ((other.m_re * other.m_re) + (other.m_im * other.m_im));		// Multiplication by the conjugate to eliminate the imaginary part
		double newRe = ((m_re * other.m_re) + (m_im * other.m_im)) / mianownik;
		double newIm = ((m_im * other.m_re) - (m_re * other.m_im)) / mianownik;
		return ComplexNumber(newRe, newIm);
	}


	ComplexNumber operator+ (const ComplexNumber& other)	// Overloaded + operator
	{
		return ComplexAdd(other);
	}

	ComplexNumber operator- (const ComplexNumber& other)	// Overloaded - operator
	{
		return ComplexSubstract(other);
	}

	ComplexNumber operator* (const ComplexNumber& other)		// Overloaded * operator
	{
		return ComplexMultiply(other);
	}

	ComplexNumber operator/ (const ComplexNumber& other)		// Overloaded / operator
	{
		return ComplexDivide(other);
	}


	friend ostream& operator<< (ostream& out, const ComplexNumber& x)
	{
		out << x.m_re;
		if (x.m_im >= 0)
		{
			out << " + " << x.m_im << "i";
		}
		else
		{
			out << " - " << (-x.m_im) << "i";
		}

		return out;
	}



protected:
	double m_re = 0;
	double m_im = 0;
};


int main()
{

	ComplexNumber a(8, -8);
	ComplexNumber b(1, 9);

	ComplexNumber c = a + b;
	ComplexNumber d = a - b;
	ComplexNumber e = a * b;
	ComplexNumber f = a / b;

	cout << "Complex Number A: " << a << endl;
	cout << "Complex Number B: " << b << endl << endl;
	cout << "A + B =   " << c << endl;
	cout << "A - B =   " << d << endl;
	cout << "A * B =   " << e << endl;
	cout << "A / B =   " << f << endl;

	return 0;
}