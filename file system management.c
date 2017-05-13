#include<iostream>
#include<fstream>
using namespace std;
struct file							
	{
	int back;
	int forward;
	char Udata[504];
	};
struct Dir
	{
	int back;
	int forward;
	int free;
	int filler;
	char type[30];
	char Name[30][9];
	int link[30];
	int size[30];
	};
union block
	{
	struct file f;
	struct Dir d;
	}block[100];

int emptyblock[100];
char str[10][9];

int openqueue[100];
void stackqueue(int y)
{
	for(int i=98;i>=0;i--)
	{
		openqueue[i+1]=openqueue[i];
	}
	
	openqueue[0]=y;
}

void removequeue()
{
	for(int i=1;i<100;i++)
	openqueue[i]=openqueue[i+1];
}

int status[100];		//1=Input(read and seek)	0=Output(wite command only)		-1=Update(all)
int pointer[100];

int dirno;	//dir number
int w=1;
int n=1;		//no of names

void shift(int* xy)		//for shift operation of 100 int array
	{
	int ai;
	for(ai=0;ai<99;ai++)
	xy[ai]=xy[ai+1];
	xy[99]=-1;
	}
	
void addempty(int p)
	{
		int l;
		for(l=0;l<100;l++)
		{
			if(emptyblock[l]==-1)
			break;
		}
		
		emptyblock[l]=p;
	}


int find(char* m, int k=0)
{
	int f=-1;
	for(int j=0;j<30;j++)
		{
			for(int i=0;i<8;i++)
			{
				if(block[k].d.Name[j][i]!=m[i])
				break;
				
				if(i=7)
				f=j;
			}
		}
	while(f==-1 && block[k].d.forward!=-1)
	{
		int k= block[k].d.forward;
			for(int j=0;j<30;j++)
				{
					for(int i=0;i<8;i++)
						{
							if(block[k].d.Name[j][i] != m[i])
								break;
								
							if(i=7)
							f=j;
						}
				}
	};
	if(f==-1)
	{
		
		return -1;
	}

	if(w!=n)
	for(int z=1;z<=n;z++)
	{
	find(str[z],k);
	}
	w++;
	
	dirno = k;
	return f;
}



void taken(char* s)
{
	int in=0;	
	int ny=0;
	int kz=0;
	for(int i=0;i<100;i++)
	{
	if(s[i]=='\n')
	in++;
	break;
	}
	for(int j=0;j<=in;j++)
	{
	if(s[j]=='/')
	{
		str[kz][ny]='\n';
	kz++;
	ny=0;
	n++;
	continue;
	}
	str[kz][ny]=s[j];
	}
		
}	

void clearn()
{
	n=1;
	w=1;
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<9;j++)
				str[i][j]=' ';
		}
	for(int i=0;i<10;i++)
	{
		str[i][0]='\n';
	}
	dirno=0;
}



void del(char* s,int nom=0)
	{	
			int k=0;
			clearn();
			taken(s);
			int f=-1;	
			int number=8;
			
			if(n==1 && nom==0)
	{ int i=0;
	for(int j=0;j<30;j++)
		{	
			for(int i=0;i<9;i++)
			{
				if(block[k].d.Name[j][i]=='\n')
					{number=i;
					break;		
				}
	}
			for(i=0;i<number;i++)
			{
				if(block[k].d.Name[j][i]!=s[i])
				break;
			}	
				if(i=number-1)
				f=j;
			}
		
	while(f==-1 && block[k].d.forward!=-1)
	{
		int k= block[k].d.forward;
			for(int j=0;j<30;j++)
				{		for(i=0;i<9;i++)
						{
							if(block[k].d.Name[j][i]=='\n')
								{number=i;
								break;
							}
						}
					for(i=0;i<number;i++)
						{
							if(block[k].d.Name[j][i]!=s[i])
								break;
								
							if(i=number-1)
							f=j;
						}
			}
				
	};
	
	}
	if(f!=-1)
	{
		if(block[k].d.type[f]=='U')
		{
			addempty(block[k].d.link[f]);
			block[k].d.link[f]=-1;
			block[k].d.type[f]='E';
		}	
	cout<<"File is Deleted"<<endl;	
	}
	else if(nom!=0)
		{
			for(int j=0;j<30;j++)
				{	
					for(int i=0;i<9;i++)
						{
							if(block[nom].d.Name[j][i]=='\n')
								{number=i;
								break;
							}
					for(int i=0;i<number;i++)
						{
							if(block[nom].d.Name[j][i]!=s[i])
								break;
								
							if(i=number-1)
							f=j;
						}
				}
					if(f!=-1)
					{
						addempty(block[nom].d.link[f]);
						block[nom].d.type[f]='E';
						
					}	
		}
	cout<<"File is deleted"<<endl;
		}
	else
		cout<<"No Such File Exist"<<endl;
	
}
		
//============ del function===----------------


void create(char m,char* s,int nom=0)
{	int ui=0;
	int zy=0;
	int f=-1;
	int k=0;
	int ioz;
	int yu=0;
	int kai=0;
	clearn();
	taken(s);
	int chg =0;	
	if(m=='U')
{	
	if(n==1 && nom==0)
	{
	for(int j=0;j<30;j++)
		{
			for(int i=0;i<9;i++)
			{
				if(block[k].d.Name[j][i]!=str[0][i])
				break;
				
				if(i=8)
				f=j;
			}
		}
	while(f==-1 && block[k].d.forward!=-1)
	{
		int k= block[k].d.forward;
			for(int j=0;j<30;j++)
				{
					for(int i=0;i<8;i++)
						{
							if(block[k].d.Name[j][i]!=s[i])
								break;
								
							if(i=7)
							f=j;
						}
				}
	};
	if(f!=-1)
	{
		del(s);
	}	
	int sd=0;

	int got=-1;
	for(int io=0;io<30;io++)
	{	
	if(block[kai].d.type[io]='E')
		{	got=1;
			break;
		}
	}
	while(got ==-1 && block[kai].d.forward!=-1)
{
			kai=block[kai].d.forward;
			for(int io=0;io<30;io++)
	{	
	if(block[kai].d.type[io]='E')
		{	got=1;
			break;
		}
	}
			
}
	
	if(got==-1)
		{
			int ms=emptyblock[0];
			shift(emptyblock);
			block[kai].d.forward=ms;
			
		}
	for(sd=0;sd<30;sd++)
	{
		if(block[kai].d.type[sd]=='E')
			break;
	}

	block[kai].d.type[sd]='U';
	block[kai].d.size[sd]=0;
	
	for(int zio=0;zio<9;zio++)		
	block[kai].d.Name[sd][zio]=str[0][zio];
	
	int pqr=emptyblock[0];
	shift(emptyblock);
	
	int ert;
	for(ert=0;ert<30;ert++)
	{
		if(block[kai].d.type[ert]=='E')
			break;
	}
	block[kai].d.link[ert]= pqr;
	block[pqr].f.back=-1;
	block[pqr].f.forward=-1;
	
	
}
	else if (n>1 && nom==0)
	{
		int zxi=find(s);
			if(zxi!=-1)
			{
				del(s);
			}
			
			int r=1;
			int dirloc=0;
			int posdir=0;
			while(r<n)
			{
				create('D',&str[r-1][0],posdir);
				posdir=find(&str[r-1][0]);
				dirloc=dirno;
				r++;									
			};
			create('U',&str[r-1][0],posdir);
	}
	else if(n==1 && nom!=0)
		{ 
			for(ui=0;ui<30;ui++)
			{
				if(block[nom].d.type[ui]=='E')
				{
					chg=1;
					break;
				}
			}
			
			int ms=emptyblock[0];
			shift(emptyblock);
			block[nom].d.link[ui]=ms;
			block[nom].d.size[ui]=0;
			block[nom].d.type[ui]='U';
			
			for(int aei=0;aei<9;aei++)
				{
					block[nom].d.Name[ui][aei]=s[aei];
				}
			
		}
		}
		
		else if(block[nom].d.type[ui] == 'D')		//===============================
		
{
	if(n==1 && nom==0)
	{
	for(int j=0;j<30;j++)
		{
			for(int i=0;i<9;i++)
			{
				if(block[k].d.Name[j][i]!=str[0][i])
				break;
				
				if(i=8)
				f=j;
			}
		}
	while(f==-1 && block[k].d.forward!=-1)
	{
		int k= block[k].d.forward;
			for(int j=0;j<30;j++)
				{
					for(int i=0;i<8;i++)
						{
							if(block[k].d.Name[j][i]!=s[i])
								break;
								
							if(i=7)
							f=j;
						}
				}
	};
	if(f!=-1)
	{
		del(s);
	}	
	
	int kai=0;
	int got=-1;
	for(int io=0;io<30;io++)
	{	
	if(block[kai].d.type[io]='E')
		{	got=1;
			break;
		}
	}
	while(got ==-1 && block[kai].d.forward!=-1)
{
			kai=block[kai].d.forward;
			for(ioz=0;ioz<30;ioz++)
	{	
	if(block[kai].d.type[ioz]='E')
		{	got=1;
			break;
		}
	}
			
}
	
	if(got==-1)
		{
			int ms=emptyblock[0];
			shift(emptyblock);
			block[kai].d.forward=ms;
			
		}
	
	for(yu=0;yu<30;yu++)
	{
		if(block[kai].d.type[yu]=='E')
		break;
	}
	block[kai].d.type[yu]='D';
	

	}

	for(int zio=0;zio<9;zio++)		
	block[kai].d.Name[yu][zio]= str[0][zio];
	
	int pqr=emptyblock[0];
	shift(emptyblock);
	
	block[kai].d.link[yu]= pqr;
	block[pqr].d.back=-1;
	block[pqr].d.forward=-1;
	
	
}
	else if (n>1 && nom==0)
	{
		int zxi=find(s);
			if(zxi!=-1)
			{
				del(s);
			}
			
			int r=1;
			int dirloc=0;
			int posdir=0;
			while(r<n)
			{
				create('D',&str[r-1][0],posdir);
				posdir=find(&str[r-1][0]);
				dirloc=dirno;
				r++;									
			};
			create('D',&str[r-1][0],posdir);
	}
	else if(n==1 && nom!=0)
		{ int ui;
			for(ui=0;ui<30;ui++)
			{
				if(block[nom].d.type[ui]=='E')
				{
					chg=1;
					break;
				}
			}
			
			int ms=emptyblock[0];
			shift(emptyblock);
			block[nom].d.link[ui]=ms;
			block[nom].d.size[ui]=0;
			block[nom].d.type[ui]='D';
			
			for(int aei=0;aei<9;aei++)
				{
					block[nom].d.Name[ui][aei]=s[aei];
				}
			
		}
	cout<<"File is Created"<<endl;
		}
	
	
	
	
	
	
	
	
	

	

void open(char mod, char*m)
{
	clearn();
	taken(m);
	
	
	int r=find(m);
	
	int loc=block[dirno].d.link[r];
	int tloc=loc;
	int ptr;
	stackqueue(loc);
	
	if(mod=='I')
		{
			status[loc]=1;
			pointer[loc]=0;
		}
	else if(mod=='U')
	{
		status[loc]=-1;
		pointer[loc]=0;
	}
		else if(mod=='O')
		{
			status[loc]=1;
			
			for(ptr=0;ptr<=504;ptr++)
				{
					if(block[dirno].f.Udata[ptr]=='\n')
					break;
				}
		if(block[tloc].f.forward!=-1)
		{
			while(block[tloc].f.forward!=-1)
				{
					tloc=block[loc].f.forward;
					
				}
			for(ptr=0;ptr<=504;ptr++)
				{
					if(block[tloc].f.Udata[ptr]=='\n')
					break;
				}	
		}		
			block[dirno].d.size[loc]=ptr-1;
					
				
				
		}
		
		
		
	cout<<"File has been Sucessfully opened"<<endl;	
	}
	
	
	
	
//===================open d end------------------	

void close()
{
	for(int i=1;i<100;i++)
	{
		openqueue[i-1]=openqueue[i];
	}
	cout<<"Last file is Closed"<<endl;
	
}
//======================close end===================------------

void read(int n,char* s)
{	int rtk;
	if(status[openqueue[0]]==1 || status[openqueue[0]]==-1)
		{
		int	rtk= openqueue[0];		//take from open
		int pgn=n/504;
		int offinlstpg=n%504;		
				if(n>504)
				{
					for(int o=0;o<n;o++)
						{
							for(int yu=0;yu<504;yu++)
								cout<<block[rtk].f.Udata[yu];
							rtk=block[rtk].f.forward;
						}
					for(int yu=0;yu<offinlstpg;yu++)
						cout<<block[rtk].f.Udata[yu];
						
				}
			
			else 
				for(int h=0;h<n;h++)
				{
					cout<<block[rtk].f.Udata[h];
					
				}

		cout<<"Data is read completely"<<endl;						
		}
		
	else
		{
			cout<<"open the file in either Input Mode or Update mode"<<endl;
			
		}
}
	
//====read end--------------================================

void write(int n,char* s)
	{	int rtk;
		if(status[openqueue[0]]==-1 || status[openqueue[0]]==0)
		
		{
		int g=1;	
		int rtk=openqueue[0];	
		while(g!=-1)
			{
			cout<<"no of characters in string (must be less than or equal to 504"<<endl;	
			cin>>n;
			cout<<"please give the string upto 504 characters"<<endl;
			
			cin>>&block[rtk].f.Udata[pointer[rtk]];			//loop may require=========================
			pointer[rtk]=pointer[rtk]+n;

			cout<<"do u have more data? press 1 for yes otherwise press -1"<<endl;
			cin>>g;
				if(g!=-1 && pointer[rtk]==504)
					{int	z= emptyblock[0];
					shift(emptyblock);
					block[rtk].f.forward=z;
					block[z].f.back=rtk;
					rtk=z;
				}
				
			};
			pointer[openqueue[0]]=n;
			cout<<"Data Has been succesfully written"<<endl;
		}	
		else
			cout<<"Open the file in proper mode"<<endl;
		
	}
//======================write data the end-------------------------------

void seek(int base, int offset)
	{
		int rtk=openqueue[0];
		if(base==0)
		{
			int tm=pointer[rtk];
			tm=tm+offset;
			pointer[rtk]=tm;
			
		}
		else if(base==+1)
		{
			pointer[rtk]=offset-1;
			
		}
		else if(base==-1)
		{
			int tm=pointer[rtk];
			tm=tm-offset;
			pointer[rtk]=tm;
		}
		cout<<"Seek Operation is sucessfully completed"<<endl;
	}


//=========================seek completed------------------------

void restoresave()
{
	fstream f,i,j,k,l;
	f.open("restore.txt",ios::out|ios::binary);
	f.write((char*)&block[0],102400);
	f.close();
	i.open("C:\Users\Aditya\Desktop\emptyblock.txt",ios::out|ios::binary);
	i.write((char*)&emptyblock[0],sizeof(int)*100);
	i.close();
	j.open("C:\Users\Aditya\Desktop\openqueue.txt",ios::out|ios::binary);
	j.write((char*)&openqueue[0],sizeof(int)*100);
	j.close();
	k.open("C:\Users\Aditya\Desktop\status.txt",ios::out|ios::binary);
	k.write((char*)&status[0],sizeof(int)*100);
	k.close();
	l.open("C:\Users\Aditya\Desktop\pointer.txt",ios::out|ios::binary);
	l.write((char*)&pointer[0],sizeof(int)*100);
	l.close();
}

void restorein()
{
	fstream f,i,j,k,l;
	f.open("C:\Users\Aditya\Desktop\restore.txt",ios::in|ios::binary);
	f.read((char*) &block[0],102400);
	f.close();
	i.open("C:\Users\Aditya\Desktop\emptyblock.txt",ios::in|ios::binary);
	i.read((char*)&emptyblock[0],sizeof(int)*100);
	i.close();
	j.open("C:\Users\Aditya\Desktop\openqueue.txt",ios::in|ios::binary);
	j.read((char*)&openqueue[0],sizeof(int)*100);
	j.close();
	k.open("C:\Users\Aditya\Desktop\status.txt",ios::in|ios::binary);
	k.read((char*)&status[0],sizeof(int)*100);
	k.close();
	l.open("C:\Users\Aditya\Desktop\pointer.txt",ios::in|ios::binary);
	l.read((char*)&pointer[0],sizeof(int)*100);
	l.close();
}
	
	
	
int main()
{
		for(int i=0;i<100;i++)		// code for initiation list of empty blocks
		{
		emptyblock[i]=i+1;
		}
		emptyblock[99]=-1;		// code is upto this

		for(int i=0;i<100;i++)
		{
			for(int j=0;j<30;j++)
			block[i].d.type[j]= 'E';
		}
		
		block[0].d.type[0]='D';

		for(int i=0;i<100;i++)		//initia;lization of all forward and Back
			{
				block[i].d.forward=-1;
				block[i].f.forward=-1;
				block[i].d.back=-1;
				block[i].f.back=-1;				
			}
		
		for(int i=0;i<100;i++)
		{
			status[i]=2;
			pointer[i]=0;
			openqueue[i]=2;
		}
		clearn();
			
//==============================------------------------==================now main programming stuff========================<<

	int w=123;

	while(w!=10)
	{
		cout<<"1.Create"<<endl;
		cout<<"2.Delete"<<endl;
		cout<<"3.Close"<<endl;
		cout<<"4.Read"<<endl;
		cout<<"5.Write"<<endl;
		cout<<"6.Seek"<<endl;
		cout<<"7.Open"<<endl;
		cout<<"8.restore save"<<endl;
		cout<<"9.restore in"<<endl;
		cout<<"10.Exit"<<endl;

		cin>>w;

		if(w==1)
		{
			cout<<"give type of the object u want to create give U-for user file or D-for Directory file"<<endl;
			char iop;
			cin>>iop;

			cout<<"give the name";
			char tyu[50];
			cin>>tyu;

			create(iop,tyu);
		}
		else if(w==2)
		{
			cout<<"give name of the File"<<endl;
			char ghy[50];
			cin>>ghy;
			del(ghy);

		}

		else if(w==3)
		{
			close();
		
		}

		else if(w==4)
		{
			cout<<"give the name of the file"<<endl;
			char jkyu[50];
			cin>>jkyu;

			cout<<"give number of character need to read"<<endl;
			int ghol;
			cin>>ghol;
			read(ghol,jkyu);
		}

		else if(w==5)
		{	cout<<"Give the name of file"<<endl;
			char dfer[50];
			cin>>dfer;
			write(0,dfer);
		}

		else if(w==6)
		{
			cout<<"give the base i.e. -1 for end of file or 0 for current position or +1 for begining of file"<<endl;
			int hdf;
			cin>>hdf;

			cout<<"give offset"<<endl;
			int ret;
			cin>>ret;
			
			seek(hdf,ret);

		}
		else if(w==7)
		{
			cout<<"Enter Mode I for Input mode or O for Output mode or U for Update"<<endl;
			char mo;
			cin>>mo;
			cout<<"Enter name of file"<<endl;
			char nm[50];
			cin>>nm;
			open(mo,nm);
		}

		else if(w==8)
		{
			restoresave();

		}

		else if(w==9)
		{
			restorein();

		}

		else if(w==10);
		else cout<<"press proper number";

		};

	}
	