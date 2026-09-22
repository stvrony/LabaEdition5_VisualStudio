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
		double mianownik = ((m_re * other.m_re) + (m_im + other.m_im));		// *
		double newRe = ((m_re * other.m_re) + (m_im * other.m_im)) / mianownik;
		double newIm = ((m_im * other.m_re) - (m_re * other.m_im)) / mianownik;
		return ComplexNumber(newRe, newIm);
	}

protected:
	double m_re = 0;
	double m_im = 0;
};


int main()
{






	return 0;
}