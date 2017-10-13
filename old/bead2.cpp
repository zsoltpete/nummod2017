
#include "matrix.hpp"

double d;

class Modell
{
public:
	std::vector<double> t,f;
	Matrix A;
protected:
	double szum(std::vector<double>& v)
	{
		double tmp=0;
		for (int i = 0; i < v.size(); ++i)
		{
			tmp+=v[i];
		}
		return tmp;
	}
	double szum2(std::vector<double>& v)
	{
		double tmp=0;
		for (int i = 0; i < v.size(); ++i)
		{
			tmp+=v[i]*v[i];
		}
		return tmp;
	}
	double szumXszum(std::vector<double>& v1,std::vector<double>& v2)
	{
		double tmp=0;
		for (int i = 0; i < v1.size(); ++i)
		{
			tmp+=v1[i]*v2[i];
		}
		return tmp;
	}
};

class Modell1 : public Modell
{
public:
	int n;
	Modell1()
	{
		std::cin >> n;
		int size;
		std::cin >> size;
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			t.push_back(d);
		}
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			f.push_back(d);
		}

		//----------- legeneráljuk ----------
		for (int i = 0; i < size; ++i)
		{
			A << Vektor{};
			for (int j = 0; j < n; ++j)
			{
				A[i] << (std::pow(t[i],j));
			}
		}
		//------------ szorozgatunk -------
		Vektor ATf=A.transposed()*Vektor{f};
		Szim_Matrix ATA=A.ATA_Clone();
		if(ATA.Cholesky(ATf))
		std::cout << ATf << std::endl;
		else
			std::cout << "szingularis" << std::endl;
	}
};

class Modell2 : public Modell
{
public:
	Modell2()
	{
		int size;
		std::cin >> size;
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			t.push_back(d);
		}
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			f.push_back(d);
		}
		//----------------------------
		for (int i = 0; i < size; ++i)
		{
			A << Vektor{};
			A[i] << 1 << 1/t[i];
		}
		//----------------------------
		//std::cout << A << std::endl;
		Vektor ATf=A.transposed()*Vektor{f};
		Szim_Matrix ATA=A.ATA_Clone();
		if(ATA.Cholesky(ATf))
		std::cout << ATf << std::endl;
		else
			std::cout << "szingularis" << std::endl;
	}
};

class Modell3 : public Modell
{
public:
	Modell3()
	{
		int size;
		std::cin >> size;
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			t.push_back(d);
		}
		for (int i = 0; i < size; ++i)
		{
			std::cin >> d;
			f.push_back(d);
		}
		//----------------------------
		for (int i = 0; i < size; ++i)
		{
			A << Vektor{};
			A[i] << 1 << cos(M_PI*t[i]) << sin(M_PI*t[i]);
		}
		//----------------------------
		Vektor ATf=A.transposed()*Vektor{f};
		Szim_Matrix ATA=A.ATA_Clone();
		if(ATA.Cholesky(ATf))
		std::cout << ATf << std::endl;
		else
			std::cout << "szingularis" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os,const std::vector<double>& v)
{
	for (std::size_t i = 0; i < v.size(); ++i)
	{
		os << v[i] << " ";
	}
	os << std::endl;
	return os;
}

int main()
{
	std::cout.precision(8);
	int N,modell,seged;
	std::cin >> N;

	std::vector<double> proba1;
	for(int i=0;i<N;i++)
	  {
			std::cin >> modell;
			
			if(modell==1)
			{
				Modell1 m1;
			}
			else if(modell==2)
			{
				Modell2 m2;
			}
			else //modell==3
			{
				Modell3 m3;
			}
	  }
	return 0;
}