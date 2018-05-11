#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
float x=50;
float y=60;
float n=10;
float m=20;
float temp=0,temp2=0;
float temp1=0,temp21=0;

/*class transaccion{
private:
	float x=0;
	float y=0;
public:
	transaccion();
	int read_item(float a){
		return a;
	}	
	void write_item(float a,float b){
		a=b;
	}


}*/


float read_item(float a){
	return a;
}

void write_item(float &a,float b){
		a=b;
}
int fun1(float a,float n){
	return a-n;
}
int fun2(float a,float m){
	return a+n;
}

bool transaccion(){
	int a=0;
	float orden[9];
	cout<<"transaccion 1:"<<endl;
	cout<<"1: read_item(x)"<<endl;
	cout<<"2: x=x-n"<<endl;
	cout<<"3: write_item(x)"<<endl;
	cout<<"4: read_item(y)"<<endl;
	cout<<"5: y=y+n"<<endl;
	cout<<"6: write_item(y)"<<endl;
	cout<<endl;
	cout<<"transaccion 2:"<<endl;
	cout<<"7: read_item(x)"<<endl;
	cout<<"8: x=x+m"<<endl;
	cout<<"9: write_item(x)"<<endl;
	cout<<endl;
	cout<<"inserte el orden de ejecucion:"<<endl;
	for(int i=0;i<9;i++){
		cin>>a;
		orden[i]=a;
		cout<<endl;
	}

	cout<<"ejecucion"<<endl;
	for(int i=0;i<9;i++){
		if(orden[i]==1){
			temp=read_item(x);
			cout<<"x:"<<temp<<endl;
		}
		else if(orden[i]==2){
			temp=fun1(temp,n);
			cout<<"temp: "<<temp<<endl;
		}
		else if(orden[i]==3){
			write_item(x,temp);
			cout<<"x: "<<x<<endl;
		}
		else if(orden[i]==4){
			temp2=read_item(y);
			cout<<"temp2: "<<temp2<<endl;
		}
		else if(orden[i]==5){
			temp2=fun2(temp2,n);
			cout<<"temp2: "<<temp2<<endl;
		}
		else if(orden[i]==6){
			write_item(y,temp2);
			cout<<"y: "<<y<<endl;
		}
		else if(orden[i]==7){
			temp1=read_item(x);
			cout<<"temp1: "<<temp1<<endl;
		}
		else if(orden[i]==8){
			temp1=fun2(temp1,m);
			cout<<"temp1: "<<temp1<<endl;
		}
		else if(orden[i]==9){
			write_item(x,temp1);
			cout<<"x: "<<x<<endl;
		}
		
	}




}

int main(){
	transaccion();
	cout<<"x+y: "<<x+y<<endl;
}
