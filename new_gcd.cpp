
#include<iostream>
#include<math.h>

using namespace std;


int gcd(int m,int n);
bool check(int m,int n);
int numberofFactor(int number,int factor);



struct node
{
	int factor;
	int frequency;
	node * next;
};

void display(node * head);
node * primeFactors(int number);
node * addFactor(node * head,int factor,int frequency);
node * commonFactors(node * head_factorm,node * head_factorn);
int multiply(node * head);

int smaller(int frequency1,int frequency2)
{
if(frequency1==frequency2)
	return frequency1;
else if(frequency1>frequency2)
	return frequency2;
else
	return frequency1;
}



int main(int argc,char ** argv)
{

int m,n;

if(argc<=2)
{
cout<<"\n\nEnter m and n respectively\n";
cin>>m>>n;
}
else
{
	m=stoi(argv[1]);
	n=stoi(argv[2]);
}

if(check(m,n))
{
cout<<"\nGCD is "<<gcd(m,n)<<endl;
}



//display(primeFactors(m));
//display(primeFactors(n));
//display(commonFactors(primeFactors(m),primeFactors(n)));




return 0;
}




bool check(int m,int n)
{
if(m==0&&n==0)
	{
		cout<<"\n\n Both M and N cannot be 0";
return false;
	}
else if(m<0||n<0)
{
	cout<<"\n\n Both M and N must be natural numbers";
return false;
}
else if(round(m)!=m||round(n)!=n)
{

	cout<<"\n\n Both M and N must be Whole Numbers without a decimal";
return false;
}
else
{
	return true;
}
}

int gcd(int m,int n)
{

node * head_factorm=primeFactors(m);
node * head_factorn=primeFactors(n);

node * head_commonFactor=commonFactors(head_factorm,head_factorn);

//display(head_commonFactor);
return multiply(head_commonFactor);

}




bool isPrime(int number)
{
	bool prime=true;
	if(number==1)
		prime=false;

	else if(number==2)
		prime=true;
	else
	{
	for(uint counter=2;counter<=number/2 && prime==true;counter++)
	{
	if(number%counter==0)
		prime=false;
	}
}
return prime;
}




int numberofFactor(int number,int factor)
{
	if(number%factor>0)
		return 0;
	else
		return 1+numberofFactor(number/factor,factor);
}




void display(node * head)
{
	bool comma=false;
cout<<endl;
node * me=head;
while(me!=NULL)
{
for(uint counter=1;counter<=me->frequency;counter++)
{
	if(comma)
		cout<<" , ";
cout<<me->factor;
comma=true;
}

me=me->next;

}
}


node * addFactor(node * head,int factor,int frequency)
{
	node * nhead;
	node * new_factor=new node();
	new_factor->factor=factor;
	new_factor->frequency=frequency;
	new_factor->next=NULL;

	if(head==NULL)
		nhead=new_factor;
	else
	{
		nhead=head;
	bool found=false;
	node * me=head;
	while(me!=NULL&&!found)
	{
		if(me->next==NULL)
		{
			me->next=new_factor;
			found=true;
		}
		else
		me=me->next;
	}
	}
	//cout<<"\n";display(head);cout<<"\n";
return nhead;
}


node * primeFactors(int number)
{
node * head=NULL;
for(int counter=1;counter<=number;counter++)
	if(number%counter==0)
		if(isPrime(counter))
			head=addFactor(head,counter,numberofFactor(number,counter));

return head;
}

node * commonFactors(node * head_factorm,node * head_factorn)
{
	node * head=NULL;
	node * home_m=head_factorm;
	node * home_n=head_factorn;

	while(home_m!=NULL&&home_n!=NULL)
	{
		if(home_m->factor==home_n->factor)
		{
			head=addFactor(head,home_m->factor,smaller(home_m->frequency,home_n->frequency));
			home_n=home_n->next;
			home_m=home_m->next;
		}
		else if(home_m->factor>home_n->factor)
			home_n=home_n->next;
		else
			home_m=home_m->next;

	}
return head;
}



int multiply(node * head)
{
	if(head==NULL)
		return 1;
	else
		return pow(head->factor,head->frequency)*multiply(head->next);
}