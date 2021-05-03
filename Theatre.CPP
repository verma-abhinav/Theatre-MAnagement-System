#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

class movie
{
int movieid;
char name[100];
char date[50];
char timing[50];
int audino;

public:
int ticket;
int seats;
void input();
void disp();
int getid();
};

class book
{
int mid;
char mname[100];
char date[50];
char timing[50];
public:
void booking();
int retid()
{
return mid;
}
};


void movie::input()
{
cout<<"Enter movie ID \t\t";
cin>>movieid;
cout<<"Enter  movie Name \t";
gets(name);
cout<<"Enter date \t\t";
gets(date);
cout<<"Enter timings \t \t";
gets(timing);
cout<<"Enter Audi No. \t\t";
cin>>audino;
cout<<"Enter no of seats \t";
cin>>seats;
}

   int movie::getid()
    {
     return movieid;
    }

void movie::disp()
{
cout<<"\nMovie ID \t"<<movieid<<endl;
cout<<"Name  \t\t"<<name<<endl;
cout<<"Date \t\t"<<date<<endl;
cout<<"Timing \t\t"<<timing<<endl;
cout<<"No of seats \t"<<seats<<endl;
}

void book::booking()
{
cout<<"Enter movie ID \t\t";
cin>>mid;
cout<<"Enter  movie Name \t";
gets(mname);
cout<<"Enter date \t\t";
gets(date);
cout<<"Enter timings \t \t";
gets(timing);
}
      void main()
      {
      movie m;
      book b;
      m.ticket=0;
      int ch;
      do
      {
      clrscr();
      cout<<"\n\n------------------------------WELCOME TO STAR CINEMAS-----------------------------------------------------------------------------------------------------------\n";
      cout<<"\n\tPlease enter your choice\n\n";
      cout<<"\t1- to Add a New Movie "<<endl;
      cout<<"\t2- to Dislay all Movies"<<endl;
      cout<<"\t3- to search for a movie"<<endl;
      cout<<"\t4- to Book a Ticket for a Movie"<<endl;
      cout<<"\t5- to Cancel ticket"<<endl;
      cout<<"\t6- to Delete a movie from the list"<<endl;
      cout<<"\t7- to exit"<<endl;
      cout<<"\n \tEnter your choice-> ";
      cin>>ch;
      cout<<"\n";
      switch(ch)
      {

      case 1:
      fstream f1;
      f1.open("movie.dat",ios::app|ios::binary);
      m.input();
      f1.write((char*)&m,sizeof(m));
      f1.close();
      break;

      case 2:
      fstream f2;
      f2.open("movie.dat",ios::in|ios::binary);
      if(f2.eof())
      {
      cout<<"\n Sorry no record exists\n";
      }
      f2.read((char*)&m,sizeof(m));
      while(!f2.eof())
      {
      m.disp();
      f2.read((char*)&m,sizeof(m));
      }
      f2.close();
      break;

      case 3:
      int n;
      fstream f3;
      f3.open("movie.dat",ios::in|ios::binary);
      if(!f3)
      {
      cout<<"File does not exist\n";
      return;
      }
      cout<<"Enter Movie ID -> ";
      cin>>n;
      f3.read((char*)&m,sizeof(m));
      while(!f3.eof())
      {
      if(m.getid()==n)
      {
      m.disp();
      break;
      }
      f3.read((char*)&m,sizeof(m));
      }
      if(f3.eof())
      cout<<"\n Invalid Movie ID";
      f3.close();
      break;

      case 4:
      b.booking();
      if(m.seats>0)
      {
      if(m.getid()==b.retid())
      {
      fstream f4;
      f4.open("book.dat",ios::app|ios::binary);
      f4.write((char*)&b,sizeof(b));
      f4.close();
      cout<<"\n booking confirmed";
      m.seats--;
      m.ticket++;
      }
      else
      cout<<"\n invalid movie details";
      }
      else
      {
      cout<<"\n sorry all tickets are booked";
      }
      break;

      case 5:
      int d;
      cout<<"\n Enter movie id->";
      cin>>d;
      if(m.ticket>0)
      {
      fstream f5,f6;
      f5.open("book.dat",ios::in|ios::binary);
      f6.open("temp.dat",ios::out|ios::binary);
      f5.read((char*)&b,sizeof(b));
      while(!f5.eof())
      {
      if(b.retid()!=d)
      f6.write((char*)&b,sizeof(b));
      f5.read((char*)&b,sizeof(b));
      }
      f5.close();
      f6.close();
      remove("book.dat");
      rename("temp.dat","book.dat");
      cout<<"\n ticket cancelled";
      m.seats++;
      m.ticket=m.ticket-2;
      }
      else
      cout<<"\n Sorry no tickets are booked ";
      break;

      case 6:
      fstream f7,f8;
      f7.open("movie.dat",ios::in|ios::binary);
      f8.open("temp1.dat",ios::out|ios::binary);
      int e;
      cout<<"\n Enter movie id-> ";
      cin>>e;
      f7.read((char*)&m,sizeof(m));
      while(!f7.eof())
      {
      if(m.getid()!=e)
      f8.write((char*)&m,sizeof(m));
      f7.read((char *)&m,sizeof(m));
      }
      f7.close();
      f8.close();
      remove("movie.dat");
      rename("temp1.dat","movie.dat");
      cout<<"\n movie Deleted \n";
      break;
      }
      cout<<"\tThank You For Visiting Us";
      getch();
      }
      while(ch!=7);
      }
