
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

// Definição de uma estrutura que recebe 3 valores do tipo double ( onde é quardado os valores de x, f(x) e pertinencia
struct trinca{
       long double valorx, valorfx, valorp;
};



void ordenacao(vector < trinca > &vet);
void principioextencao(vector<trinca> &vet);
void convexo(vector<trinca> &vet );
long double centroide (vector<trinca> &veto );





ofstream convex("./aposalgoritmo.gnu", ios::out);
ofstream borrao("./sclassica.gnu", ios::out);
ofstream cla("./classica.gnu", ios::out);
ofstream defuzzy("./defu.gnu", ios::out);


int main()
{

  vector < trinca > vetorPonto;	
  trinca armazena0,armazena1,armazena2;		
 
  long double  pon,c,inf, sup, z,r,t,x,x1,u1,u2,u0,al,pic;
 
  const  double d= 1;

// The parameters a1,a2 and a3 for the fuzzy number c
cout<<" Enter the lower range, the peak and the upper range of the triangular membership: "<<endl;
cin>>inf; cin>>pic; cin>>sup;
// The moment	
cout<<" Enter time: "<<endl;
cin>>t;
// pipe length
cout<<"  Enter the initial and final point of the x (pipe): "<<endl;
cin>>x; cin>>x1;

  
	   
	 while(x<=x1)   // Length of the whole, in this case (<80)
       	{         
          al=0;
          while (al<=0.99)
		    {
//[min f(s)] 
		       u1= (1/sqrt(4*d*M_PI))*exp((-0.25/d)*(x-((pic-inf)*al+inf)*t)*(x-((pic-inf)*al+inf)*t));
       	       armazena1.valorx = x;
			   armazena1.valorfx =u1;
			   armazena1.valorp = al;
			   vetorPonto.push_back(armazena1);
//[max f(s)] 										
                u2= (1/sqrt(4*d*M_PI))*exp((-0.25/d )*(x-((pic-sup)*al+sup)*t)*(x-((pic-sup)*al+sup)*t));
				armazena2.valorx = x;
				armazena2.valorfx =u2;
				armazena2.valorp = al;
				vetorPonto.push_back(armazena2);
	    		al+=0.01;
			 } 
//  u(x,t) classic, membership equal to 1

               z=(1/sqrt(d*4*M_PI))*exp((-0.25/d)*(x-pic*t)*(x-pic*t));  
                                                       
              armazena0.valorx = x;
              armazena0.valorfx = z ;
              armazena0.valorp = 1;
              vetorPonto.push_back(armazena0);

// Stores classic function data (3d)  t, x , u(x,t) 
               
			 borrao<<setiosflags(ios::fixed| ios:: showpoint)<<setprecision(15.0);
             borrao<<t<<" "<<x<<" "<<z<<endl;

// Stores classic function data (2d) x e u(x,t)              
             cla<<setiosflags(ios::fixed| ios:: showpoint)<<setprecision(15.0);
             cla<<x<<" "<<z<<endl;

// Sorts data according to u(x,t)
            ordenacao(vetorPonto);

// More relevance 

            principioextencao(vetorPonto);

//  Defuzzification
           	r=centroide(vetorPonto);

// Stores defuzzified data  
           	defuzzy<<setiosflags(ios::fixed| ios:: showpoint)<<setprecision(15.0);
         	defuzzy<<x<<" "<<r<<endl;

// Eliminates "noise"                          
			convexo(vetorPonto);  	
	   
// Storage of fuzzy u(x,t)                             
          	convex<<setiosflags(ios::fixed| ios:: showpoint)<<setprecision(15);
		
		for (int v=0;v<vetorPonto.size();v++)
 	     	{
	      	convex<<vetorPonto[v].valorx<<" "<<vetorPonto[v].valorfx<<" "<<vetorPonto[v].valorp<<endl;
	      	}
				convex<<" "<<endl;


               vetorPonto.clear();

	            x+=0.01;

               
               }
               

		
 return 0;
}





// select sort
void ordenacao(vector < trinca > &vet)
{ 

	double b,i;
           trinca orden;
       
		b=1;
         while (b<vet.size())
	    {
               orden.valorx = vet[b].valorx;
               orden.valorfx =vet[b].valorfx;
	       orden.valorp = vet[b].valorp;
	       
	       i = (b-1);
	      while((i>=0)&&(vet[i].valorfx > orden.valorfx))
		 {
		  vet[i+1] = vet[i];
		  i = (i - 1);
		}
	        vet[i+1]=orden;
		b+=1;
            }
          

}

// Sup f(u(x,t))
void principioextencao(vector<trinca> &vet)
{ 
     int i,j;
     
     j=1;
          
     while(j<vet.size())
	{	
	   i = (j-1);
     	   if((vet[j].valorfx)==(vet[i].valorfx))
	     {  
					if(vet[j].valorp>=vet[i].valorp)
					 { 
						vet.erase(vet.begin()+i);

						
					 }
					 else
			                 {
						 vet.erase(vet.begin()+j);
						 
					  }
			continue;	
		 }j+=1;
		 
	}
       
 }


//Defuzzification
long double centroide (vector<trinca> &veto)
{
     long double numerador,denominador,c;
     numerador=0.0;
     denominador=0.0;
      c=0.0;
 while(c<=(veto.size()))

    { 
         numerador+=(veto[c].valorp)*(veto[c].valorfx);
	    denominador+=veto[c].valorp;       
     c+=1.0; }
    
   
   return (numerador/denominador);

}


// "Noise
void convexo(vector<trinca> &vet)
{        double i,j,l;
	j,l=1;
         
         
         while (l<(vet.size()-1.0))
           {
	         i=j-1;	l=j+1;
	         if( (vet[i].valorp>=vet[j].valorp)&&(vet[j].valorp<=vet[l].valorp))
			{   	
                   if( vet[j].valorp!=1){
                   vet.erase(vet.begin()+j);
				                         }
			        j=1;
                    l=1;
			        
				continue;

			}
	             
                  j+=1;
	    }



}




 

