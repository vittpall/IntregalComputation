#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define Pi 3.14159265358979323846264338327950


using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	float f(float ); //funzione
	float f1(float ); //derivata prima
	float Cerca_Minimo(int ); //soluzioni derivata prima
	float area_nondet(float, float, int, float); //integrale definito (metodo non deterministico)
	float area_det(float, float, int );
	


int main(int argc, char** argv) {
	
	srand(time(NULL));
	float a,b,n;
	float A1,A2,Aor;
	float Xmin;
	cout<<"Inserire numero di punti:";
	cin>>n;
	a=5.0; //estremi dell'intervallo di integrazione
	b=6.0;

	
	Xmin=Cerca_Minimo(n);
	Aor=Pi/2;
	A2=area_det(a,b,n);
	A1=area_nondet(a, b, n, Xmin);
	cout<<"RISULTATI\n";
	cout<<"Metodo Torricelli-Barrow\n";
	cout<<"Integrale definito di f(x) tra:"<<a<<" e "<<b<<" ="<<Aor;
	cout<<"\n-----------";
	cout<<"\nMetodo Monte Carlo\n";
	cout<<"Integrale definito di f(x) tra:"<<a<<" e "<<b<<" ="<<A1;
	float err=Pi/2-A1;
	cout<<"\nErrore="<<err;
//	cout<<"\nerrore="<<1.57-A1;
	cout<<"\n-----------";
	cout<<"\nMetodo Cavalieri-Simpson\n";
	cout<<"Integrale definito di f(x) tra:"<<a<<" e "<<b<<" ="<<A2;
	err=Pi/2-A2;
	cout<<"\nErrore="<<err;
	
	return 0;
}


	float f(float X)
	{
		return -2/(1+pow((X-6),2));
	}
	
	float f1(float X)
	{
		return 4*(X-6)/(pow(1+pow((X-6),2),2));
	}
	
	float Cerca_Minimo(int N)
	{
		//applicazione del metodo dicotomico per la ricerca degli zeri di una funzione
		int c,d, Xm, i;
		c=5;
		d=10;
		if(f1(c)*f1(d)<=0) //condizione per l'esistenza di uno zero
		{
			do
			{
				Xm=(c+d)/2;
				if((f1(Xm)*f1(c))<0) //sceglie l'intervallo sinistro o destro
					d=Xm;
				else
					c=Xm;	
				i++;		
			}while(i<N);
		}
		return Xm;	
	}
	
	float area_nondet(float A, float B, int N, float Xmin)
	{
		//METODO SIMIL-MONTECARLO, NON DETERMINISTICO
		float x, y, Nint, Ret;
		cout.precision(10);
		for(int i=0; i<N; i++)
		{
			x=(float)rand()/RAND_MAX*(B-A)+A;
			
			y=(float)rand()/RAND_MAX*(f(Xmin)); //f(Xmin)= ordinata del punto di minimo	
			
			if(y>f(x)) //condizione per la posizione del punto
				Nint++;	
		}
		Ret=((B-A)*f(Xmin));
		return -Ret*(Nint/N);	
	}
	
	float area_det(float A, float B, int N)
	{
		//METODO CAVALIERI-SIMPSON, DETERMINISTICO
		float x, s, A_tot;
		float h=(B-A)/N; //intervallo di integrazione della singola parabola;
		s=h/2;
		x=A+h;
		
		//Area singola parabola == (s/3)(f(a)+4*f((a+b)/2)+f(b))
		A_tot=f(A)+f(B)+4*(A+s);

		for(int i=0; i<N; i++)
		{
			A_tot=A_tot+2*f(x)+4*f(x+s);
			x=x+h;
		}
		
		A_tot=A_tot*(s/3.0);
		
			
		return -A_tot;
		
	}
	
	
	
	
	
	
	
	
	
	
	
