#include "bits/stdc++.h"

using namespace std;

#define structure map<vector<int>, int>
#define FOR_MAP(ii,T) for(structure::iterator (ii)=(T).begin();(ii)!=(T).end();(ii)++)
#define FOR_next_MAP(jj,ii,T) for(structure::iterator (jj)=(ii);(jj)!=(T).end();(jj)++)
#define VI vector<int>

const int MIN_SUP = 2;

structure C;
structure L;

void C1();
void L1();
void generate_C();
void generate_L();
void output(structure );
void scan_D();
void prune();
bool check_compatibility(VI ,VI );
void set_count(VI );

int main(int argc, char const *argv[])
{
	C.clear();
	L.clear();

	bool mv=true;
	int index=2;
	while(true)
	{
		if (mv)
		{
			C1();
			cout<<"C1\n";
			output(C);

			L1();
			cout<<"L1\n";
			output(L);
			
			mv=!mv;
		}else
		{
			generate_C();
			if(C.size()==0)
				break;
			cout<<"\nC"<<index<<"\n";
			output(C);
			prune();
			if (C.size()==0)
			{
				break;
			}
			cout<<"\nC"<<index<<" after prune \n";
			output(C);
			scan_D();
			cout<<"\nC"<<index<<"after scaning dataset \n";
			output(C);
			generate_L();
			if (L.size()==0)
			{
				break;
			}
			cout<<"\nL"<<index<<"\n";
			output(L);
			index++;
		}
	}
	return 0;
}


void C1()
{
	int n;
	VI v;
	while(cin>>n)
	{
		v.clear();
		if (n==-1)
		{
			continue;
		}
		v.push_back(n);
		if(C.count(v)>0)
			C[v]++;
		else
			C[v]=1;
	}
}

void output(structure T)
{
	cout<<"\n";
	VI v;
	FOR_MAP(ii,T)
	{
		v.clear();
		v=ii->first;
		for (int i = 0; i < v.size(); ++i)
		{
			cout<<v[i]<<" ";
		}

		cout<<" ---(frequency)----->> "<<ii->second;
		cout<<"\n";

	}
}

void L1()
{

	FOR_MAP(ii,C)
	{
		if (ii->second >= MIN_SUP)
		{
			L[ii->first]=ii->second;
		}
	}

}

void generate_C()
{
	//clean(C);
	C.clear();
	FOR_MAP(ii,L)
	{

		FOR_next_MAP(jj,ii,L)
		{
			if(jj==ii)
				continue;
			VI a,b;
			a.clear();
			b.clear();
			a=ii->first;
			b=jj->first;
			if(check_compatibility(a,b))	
			{
				a.push_back(b.back());
				sort(a.begin(), a.end());
				C[a]=0;
			}
		}

	}


}

bool check_compatibility(VI a,VI b)
{
	bool compatible=true;
	for (int i = 0; i < a.size()-1; ++i)
	{
		if (a[i]!=b[i])
		{
			compatible=false;
			break;
		}
	}

	return compatible;
}

void prune()
{
	VI a,b;
	
	FOR_MAP(ii,C)
	{
		a.clear();
		b.clear();

		a=ii->first;
		for(int i = 0;i<a.size();i++)
		{
			b.clear();
			for (int j = 0; j < a.size(); ++j)
			{
				if(j==i)
					continue;
				b.push_back(a[j]);
			}
			if(L.find(b)==L.end())
				{
					ii->second=-1;
					break;
				}
			
		}

		
	}

	structure temp;
	temp.clear();
	FOR_MAP(ii,C)
	{
		if (ii->second != -1)
		{
			temp[ii->first]=ii->second;
		}
	}
	
	C.clear();
	C=temp;
	temp.clear();
}

void scan_D()
{
	ifstream fin;
	fin.open("input.txt");
	if(!fin)
		{
			cout<<"Input file opening error\n";
			exit(0);
		}

	int n;
	VI a;
	while(fin>>n)
	{
		if(n==-1 && a.size()>0)
		{
			set_count(a);
			a.clear();
		}else if(n!=-1)
		{
			a.push_back(n);
		}
		
	}
	fin.close();
}

void set_count(VI a)
{
	FOR_MAP(ii,C)
	{
		VI b;
		b.clear();
		b=ii->first;
		int true_count=0;
		if (b.size()<=a.size())
		{
			for (int i = 0; i < b.size(); ++i)
			{
				for (int j = 0; j < a.size(); ++j)
				{
					if(b[i]==a[j])
					{
						true_count++;
						break;
					}
				}
			}
		}

		if (true_count==b.size())
		{
			ii->second++;
		}
	}
}

void generate_L()
{
	L.clear();

	FOR_MAP(ii,C)
	{
		if(ii->second >= MIN_SUP)
		{
			L[ii->first]=ii->second;
		}
	}
}
