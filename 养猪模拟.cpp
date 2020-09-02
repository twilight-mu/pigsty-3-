using namespace std;
#include<bits/stdc++.h>
#define random(a,b) (rand()%(b-a+1))+a
struct pig
{
	int species; //����Ϊ1 С����Ϊ2 ��׻���Ϊ3 
	int id; 	//��� 
	int gday; 	//�ɳ�����(һ���°�30���) 
	//int isInfected; //����ȾΪ1 û����ȾΪ2 
	double weight; //���� 
	pig *next;
};
class pigsty
{
	private:
		pig *head;
		int isblack;
		int sum;
	public:
		pigsty();				//��ʼ�� 
		int getspecies(int i);	//��ȡ������Ϣ 
		int getgday(int i);		//��ȡ�ɳ�������Ϣ 
		double getweight(int i);//��ȡ���� 
		double getprice();		//��ȡ��Ǯ
		//void print();			//��ӡ��Ȧ��Ϣ 
		//void clear();			//�����Ȧ 
		void addpig(pig*p);		//������Ҫ���ڳ�ʼ��
		void insert(int i);      //������Ҫ���ڹ������ 
		void setisblack(int i);	//���ú���Ȧ,1Ϊ����Ȧ��0Ϊ�Ǻ���Ȧ 
		int getsumspecies(int i);	//��ȡĳ��������� 
		int getsum()
		{
			return sum;
		}
		int getisblack()
		{
			return isblack;
		}                
		pig* gethead()
		{
			return head;
		}
};
pigsty::pigsty()
{
	int sum=0;
	int isblack=0;
	head=NULL;
}
int pigsty::getspecies(int i) 
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->species;
}
int pigsty::getgday(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->gday;
}
double pigsty::getweight(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->weight;
}
double pigsty::getprice()
{
	double price=0;
	if(head==0)
		return 0;
	int day,flag=0;
	pig*p=head,*p1=p;
	while(p)
	{
		day=p->gday;	
	if(day>=360||p->weight>75)
	{
		if(sum==1)
		{
			setisblack(0);
			head=NULL;
			delete p;
			sum--;
			break;
		}
		if(p->species==1)
		{
			price+=30*p->weight;
		}
		if(p->species==2)
		{
			price+=14*p->weight;
		}
		if(p->species==3)
		{
			price+=12*p->weight;
		}
		p1->next=p->next;
		delete p;
		p=p1->next;
		sum--;
		continue;
	}
	else if(flag==0)
	{
		flag=1;
		head=p;
	}
	p1=p;
	p=p1->next;
	}
	return price;
}
void pigsty::addpig(pig *p)
{
	sum++;
	p->next=NULL;
	if(head==NULL)
	{
		head=p;
	}
	else 
	{
		pig*p1=head;
		while(p1->next)
		{
			p1=p1->next;
		}
	p1->next=p;
	}
}
void pigsty::setisblack(int i)
{
	isblack=i;	
}
int pigsty::getsumspecies(int i)
{
	int count;
	pig *p=head;
	for(int k=0;k<sum&&p!=NULL;k++)
	{
		if(p->species==i)
		count++;
		p=p->next;
	}
	return count;
}
int getallpig(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsum();
	}
	return count;
}
void start(pigsty ps[])//����ʼ����Ȧ��ʼ�� 
{
	int count=300;	//��ʼ�ȷ�300ֻ�� 
	pig *p;
	while(count--)
	{
		p=new pig;
		p->species=random(1,3);
		p->weight=random(20,50);
		p->gday=0;
		for(int i=0;i<100;i++)
		{
			if(p->species==1&&(ps[i].getisblack()==1||ps[i].gethead()==NULL)&&ps[i].getsum()<10)
			{
				p->id=ps[i].getsum();
				ps[i].addpig(p);
				ps[i].setisblack(1);
				break;
			}
			if(p->species!=1&&ps[i].getisblack()==0&&ps[i].getsum()<5)
			{
				p->id=ps[i].getsum();
				ps[i].addpig(p);
				break;
			}
		}
	}
}
void pigsty::insert(int i) 
{
	pig*p=new pig;
	p->species=i;		
	p->weight=random(20,30);	
	p->gday=0;
	if(head==NULL)
	{
		p->id=0;
		p->next=NULL;
		head=p;
		sum++;
		return;
	}
	if(head->id!=0)
	{
		p->id=0;
		p->next=head;
		head=p;
		sum++;
		return;
	}
	else 
	{
	pig*p1=head,*p2=p1;
	int k=0;
	while(p1->id==k&&p1->next)
	{
		k++;
		p2=p1;
		p1=p1->next;
	}
	if(p1->next==NULL)
	{
		p->id=sum;
		p->next=NULL;
		p1->next=p;
	}
	else
	{
		p->id=k;
		p2->next=p;
		p->next=p1;
	}
	sum++;
	} 
}
void oneday(pigsty ps[])
{
	for(int i=0;i<100;i++)
	{
		pig *p;
		p=ps[i].gethead();
		while(p)
		{
			int w1=random(0,12);
			double w2=double(w1)/10.0;
			p->weight+=w2;
			p->gday++;
			p=p->next;
		}	
	} 
}
int main()
{
	pigsty ps[100];
	start(ps);
	int day=0;
	while(true)
	{
		int n;
		cin>>n;
		if(n==0)
		break;
		char s;//d��ʾ��һ�죬m��ʾ��һ���� 
		cin>>s;
		if(s=='d')
		{
			oneday(ps);
			day+=1;
		}
		if(s=='m')
		{
			for(int i=0;i<30;i++)
			oneday(ps);
			day+=30;
		}
		if(day>=90)
		{
			day-=90;
			cout<<"���������½��Զ�����һ����"<<endl;
			cout<<"��Ȧ�ɹ������Ƴ���"<<"ֻ��,"<<"�õ�"<<"Ԫ��"<<endl; 
			cout<<"���������½��Զ����һ����"<<endl;
			cout<<"��Ȧ�ɹ���"<<endl; 
		}
	}
	return 0;
}
