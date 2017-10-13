#include <iostream>
#include <vector>
#include <cmath>

int db,modell,n,meresszam;
std::vector<double> t,f;
double szam;

void kiir(std::vector<double>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

void kiir(std::vector<double>&& v)
{
	kiir(v);
}

void kiir(std::vector<std::vector<double> >& A)
{
	for (int i = 0; i < A.size(); ++i)
	{
		kiir(A[i]);
	}
}

void kiir(std::vector<std::vector<double> >&& A)
{kiir(A);}

void beolvas()
{
	t.clear();
	f.clear();
	std::cin>>modell;
	if(modell==1)
		std::cin>>n;
	std::cin>>meresszam;
	for (int i = 0; i < meresszam; ++i)
	{
		std::cin>>szam;
		t.push_back(szam);
	}
	for (int i = 0; i < meresszam; ++i)
	{
		std::cin>>szam;
		f.push_back(szam);
	}
}

std::vector<std::vector<double> > Transzszor(std::vector<std::vector<double> >& A)
{
	std::vector<std::vector<double> > visszateres;
	visszateres.resize(A[0].size());
	for (int i = 0; i < A[0].size(); ++i)		//helyet foglalunk h tudjunk indexelni és kinullázzuk
		{
			visszateres[i].resize(A[0].size()); 
			for (int j = 0; j < A[0].size(); ++j)
				visszateres[i][j]=0;
		}
	for (int i = 0; i < A[0].size(); ++i)
	{
		for (int j = 0; j < A[0].size(); ++j)
		{
			for (int k = 0; k < A.size(); ++k)
			{
				visszateres[i][j]+=A[k][i]*A[k][j];
			}
		}
	}
	return visszateres;	
}

std::vector<double> Transzf(std::vector<std::vector<double> >& A)
{
	std::vector<double> visszaadando;
	visszaadando.resize(A[0].size());
	for (int i = 0; i < A[0].size(); ++i)
	{
		for (int j = 0; j < A.size(); ++j)
		{
			visszaadando[i]+=A[j][i]*f[j];
		}
	}
	return visszaadando;
}

std::vector<double> Transzf(std::vector<std::vector<double> >&& A)
{
	return Transzf(A);
}

void modell1()
{
	std::vector<std::vector<double> > A;
	std::vector<double> seged;
	seged.resize(n);
	for (int i = 0; i < meresszam; ++i)
	{
		for (int j = 0; j < n; ++j)
			seged[j]=std::pow(t[i],j);
		A.push_back(seged);
	}
	std::vector<double> ATf=Transzf(A);
	std::vector<std::vector<double> > ATA=Transzszor(A);
}

void modell2()
{
	std::vector<std::vector<double> > A;
	std::vector<double> seged;
	seged.resize(2);
	for (int i = 0; i < meresszam; ++i)
	{
		seged[0]=1;
		seged[1]=1/t[i];
		A.push_back(seged);
	}
	std::vector<double> ATf=Transzf(A);
	std::vector<std::vector<double> > ATA=Transzszor(A);
}
void modell3()
{
	std::vector<std::vector<double> > A;
	std::vector<double> seged;
	seged.resize(n);
	for (int i = 0; i < meresszam; ++i)
	{
			seged[0]=1;
			seged[1]=cos(M_PI*t[i]);
			seged[2]=sin(M_PI*t[i]);
		A.push_back(seged);
	}
	std::vector<double> ATf=Transzf(A);
	std::vector<std::vector<double> > ATA=Transzszor(A);
}

int main()
{
	std::cout.precision(8);
	std::cin >> db;
	for (int i = 0; i < db; ++i)
	{
		beolvas();
		switch(modell)
		{
			case 1: modell1();
			break;
			case 2:	modell2();
			break;
			case 3:	modell3();
			break;
			default:
			break;
		}
	}
	return 0;
}

