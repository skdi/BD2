
//fuente github.com/skdi/OAD/hash.cpp Codigo propio
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct transaccion{
	char state;//G Granted /W Waiting
	string nombre;
	char type;//E Exclusive,S Shared
};

const int TABLE_SIZE=128;
class has{
private:
    int key;
    int value;
    char state='N';//N non a,S shared,X Exclusive
    has *next;
    queue<transaccion*> Tr;
public:
    has(int key,int value);
    int getkey(){return key;}
    int get_value(){return value;}
    void set_value(int value){this->value=value;}
    has *getnext(){return next;}
    void set_next(has* next){this->next=next;}
    void insertar_T(transaccion *T);
    void liberar();
};

class hasmap{
private:
    has **table;
public:
    hasmap(){
        table=new has*[TABLE_SIZE];
        for(int i=0;i<TABLE_SIZE;i++)
            table[i]=NULL;
    }
    int get(int key){
        int hash1=(key%TABLE_SIZE);
        if(table[hash1]==NULL){
            return -1;
        }
        else{
            has *entry=table[hash1];
            while(entry!=NULL && entry->getkey()!=key)
                entry=entry->getnext();
            if(entry==NULL)
                return -1;
            else return entry->get_value();
        }
    }
    void put(int key,int value);
    void remove(int key);
    ~hasmap(){
        for(int i=0;i<TABLE_SIZE;i++)
            if(table[i]!=NULL){
                has *prev=NULL;
                has *entry=table[i];
                while(entry!=NULL){
                    prev=entry;
                    entry=entry->getnext();
                    delete prev;
                }
            }
        delete[] table;
    }

};


has::has(int key, int value){
    this->key=key;
    this->value=value;
    this->next=NULL;
    //this->Tr=NULL;

}
void has::insertar_T(transaccion *T){
	if(this->state=='N'){		
		this->state=T->type;
		T->state='G';

	}else if(this->state=='S' && T->type=='S'){
		T->state='G';

	}else if(this->state='X'){
		T->state='W';
	}
	this->Tr.push(T);
}
void has::liberar(){
	this->Tr.pop();
	this->state='N';
	transaccion *temp;
	temp=Tr.front();
	temp->state='G';
	delete temp;

}

void hasmap::put(int key, int value){
    int hash1=key%TABLE_SIZE;
    if(table[hash1]==NULL){
        table[hash1]=new has(key,value);
        return;
    }else
        table[hash1]->set_next(new has(key,value));

}


void hasmap::remove(int key){
    int hash1=key%TABLE_SIZE;
    has *mihash=table[hash1];
    if(mihash==NULL){
        cout<<"vacio"<<endl;
        return;
    }else{
        while(mihash->getnext()!=NULL){
            if(mihash->getkey()==key){
                has *temp=mihash;//guardo la posicion anterior
                mihash=mihash->getnext();//poisicion actual
                has *temp2=mihash->getnext();//posicion sig
                temp->set_next(temp2);
                delete mihash;
            }
            mihash=mihash->getnext();
        }
    }


}


int main()
{
    hasmap* mimap=new hasmap();

    return 0;
}







