#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int counter = 0;

struct flightnode;
flightnode *head = NULL;

struct person
{
  string name;
  int age;
  char gender;
  string passport;
  string phone;
  float cost;
  char stype;
};
struct flightnode
{
  int aid;			/* flight number */
  string depcity;		/* departure city */
  int dept;			/* departure time hhmm, e.g. 623 or 1258 */
  string arrcity;		/* arrival city */
  int arrt;			/* arrival time hhmm, e.g. 623 or 1258 */
  int passcount;		/* number of passengers on the flight */
  flightnode *next;
  int *eseats;
  int *fseats;
  person *eid;
  person *fid;
  float pe;
  float pf;
};

bool checkt(int s)
{
  int m=s%10;
  s/=10;
  m+=10*(s%10);
  s/=10;
  int h=(s%10);
  s/=10;
  h+=10*(s%10);
  s/=10;
  // cout<<h<<" "<<m<<endl;
  if(h>=24 || m>=60) {
    cout<<"invalid time!"<<endl;
    return false;
  }
  return true;
}

void addflight ()
{
  float e, g;
  flightnode *f = new flightnode;
  counter++;
  int p, id;
  cout << "Enter flight id:";
  cin >> id;
  f->aid = id;
  string a, d;
  cout << "Enter departure city:";
  cin >> d;
  cout << "Enter arrival city:";
  cin >> a;
  f->depcity = d;
  f->arrcity = a;
  int dt, ar;
  while(1)  {
    cout << "Enter departure time: (in format 'HourHourMinuteMinute' according to 24 hour time format)   ";
    cin >> dt;
    if(checkt(dt))  {
      f->dept=dt;
      break;
    }
  }
  while(1) {
    cout << "Enter arrival time: (in format 'HourHourMinuteMinute' according to 24 hour time format)    ";
    cin >> ar;
    if(checkt(ar))  {
      f->arrt=ar;
      break;
    }
  }
  cout << "Enter economy class ticket price:";
  cin >> e;
  cout << "Enter first class ticket price:";
  cin >> g;
  f->pe = e;
  f->pf = g;
  cout << "Enter passenger count:";
  cin >> p;
  p /= 3;
  f->eid = new person[2 * p];
  f->fid = new person[p];
  f->passcount = p * 3;
  f->eseats = new int[2 * p];
  f->fseats = new int[p];
  for (int i = 0; i < 2 * p; i++)
    f->eseats[i] = 0;
  for (int i = 0; i < p; i++)
    f->fseats[i] = 0;
  flightnode *k = head;
  if (k == NULL)
    {
      head = f;
      f->next = NULL;
      return;
    }
  while (k->next != NULL)
    k = k->next;
  if (k == head)
    {				//head=f;
      k->next = f;
      f->next = NULL;
    }
  else
    {
      k->next = f;
      f->next = NULL;
    }

}

void modify ()
{
  cout << "Enter the flight id you want to modify:";
  int id;
  cin >> id;
  int flag=0;
  flightnode *p = head;
  while (p)
    {
      if (p->aid == id)
	{
	  cout << "Do you want to change departure city?(Y/N):";
	  char c;
	  cin >> c;
	  if (c == 'Y')
	    {
	      string v;
	      cout << "Enter new departure city:";
	      cin >> v;
	      p->depcity = v;
	    }
	  cout << "Do you want to change arrival city?(Y/N):";
	  cin >> c;
	  if (c == 'Y')
	    {
	      string v;
	      cout << "Enter new arrival city:";
	      cin >> v;
	      p->arrcity = v;
	    }
	  cout << "Do you want to change departure time?(Y/N):";
	  cin >> c;
	  if (c == 'Y')
	    {
	      int t;
	      cout << "Enter new departure time:";
	      cin >> t;
	      p->dept = t;
	    }
	  cout << "Do you want to change arrival time?(Y/N):";
	  cin >> c;
	  if (c == 'Y')
	    {
	      int t;
	      cout << "Enter new arrival time:";
	      cin >> t;
	      p->arrt = t;
	    }
	  cout << "Do you want to change passenger count?(Y/N):";

	  cin >> c;
	  if (c == 'Y')
	    {
	      int t;
	      cout << "Enter new passenger count:";
	      cin >> t;
	      p->passcount = t;
	    }
      flag=1;
	  break;
	}
      p = p->next;
    }
    if(flag==0)  cout<<"NO FLIGHT FOUND!!"<<endl;
}

void deleteflight ()
{
  flightnode *p = head, *q = head;
  cout << "Enter flight id you want to delete:";
  int id;
  int flag=0;
  cin >> id;
  while (p)    {
    if (p->aid == id)	{
	    q->next = p->next;
	    p->next = NULL;
	    if (p == head)   head = p->next;
	    delete p;
      flag=1;
	    break;
	  }
    q = p;
    p = p->next;
  }
  if(flag==0)  cout<<"NO FLIGHT FOUND!!"<<endl;
}

void flightschedule ()
{
  int f = 0;
  flightnode *p = head;
  string d, a;
  cout <<"Enter departure port and arrival port  whose schedule you want to check:";
  //int id;  cin>>id;
  cin >> d;
  cin >> a;
  while (p)    {
    if (p->depcity == d && p->arrcity == a)	{
  	  cout << "Flight id:" << p->aid << endl;
	    cout << "Departure city:" << p->depcity << endl;
  	  cout << "Arrival city:" << p->arrcity << endl;
	    cout << "Departure time:" << p->dept / 100 << ":";
	    if (p->dept % 100 > 9)    cout << p->dept % 100 << endl;
	    else  cout << "0" << p->dept % 100 << endl;
  	  cout << "Arrival time:" << p->arrt / 100 << ":";
	    if (p->arrt % 100 > 9)    cout << p->arrt % 100 << endl;
	    else   cout << "0" << p->arrt % 100 << endl;
	    cout << "Passenger count:" << p->passcount << endl;
	    f = 1;
	    cout << endl;
	    break;
  	}
    else	p = p->next;
  }
  if (f == 0)  cout << "No flight found!" << endl;
  return;
}

void details (struct flightnode *p, int no, char type)
{
  if (type == 'e')    {
      cout << "enter name" << endl;
      cin >> (p->eid[no]).name;
      cout << "enter age" << endl;
      cin >> (p->eid[no]).age;
      cout << "enter passport no" << endl;
      cin >> (p->eid[no]).passport;
      cout << "enter phone no" << endl;
      cin >> (p->eid[no]).phone;
      (p->eid[no]).cost = p->pe;
    }
  if (type == 'f')    {
      cout << "enter name" << endl;
      cin >> (p->fid[no]).name;
      cout << "enter age" << endl;
      cin >> (p->fid[no]).age;
      cout << "enter passport no" << endl;
      cin >> (p->fid[no]).passport;
      cout << "enter phone no" << endl;
      cin >> (p->fid[no]).phone;
      (p->fid[no]).cost = p->pf;
    }
}

void reserveflight ()
{
  int i,j,n;
  flightnode *p = head;
  string d, a;
  if (head == NULL)
    {
      cout << "no flight available currently" << endl;
      return;
    }
  cout << "Enter Departure port:";
  cin >> d;
  cout << "Enter arrival port:";
  cin >> a;
  while (p)    {
      if (d.compare (p->depcity) == 0 && a.compare (p->arrcity) == 0)	break;
      p = p->next;
  }
  if (!p)  {
      cout << "NO FLIGHT AVAILABLE!!";
      return;
  }
  cout << "Enter the class in which you want to travel:(1 for FIRST and 2 for ECONOMY):";
  int c;
  cin >> c;
  if (c == 1) {
    cout << "Enter no. of tickets:";
    cin >> n;
    int v = 0;
    for (int i = 0; i < (p->passcount / 3); i++)
	  if (p->fseats[i] == 0)   v++;
    if (v < n)  {
      cout << "NOT ENOUGH SEATS AVAILABLE!!!";
	    return;
	  }
    else  {
  	  cout<<"Enter your choice for window or aisle seat.Press 1 for window and 2 for aisle"<<endl;
      {
      int a,seat;
	  	cin>>a;
		  int i,j;
		  if(a==1)   {
		     for( i=0;i<p->passcount/3;i++)   {
	         if(i%4==0||i%4==3)   {
		         if(p->fseats[i]==0)   {
		           p->fseats[i]=1;
		           details(p,i,'f');
		           cout << "seat number " << i + 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
               n--;
               break;
		        }
		       }
		     }
		  if(n>0)   {
		    if(i%4==0)    {
		       for( j=i+1;(j>i?j<p->passcount/3:j<i);j=(j+1)%(p->passcount/3))   {
             if(n==0)   break;
		         if(n>0)  {
		           if(p->fseats[j]==0)   {
		               p->fseats[j]=1;
		               details(p,j,'f');
		               cout << "seat number " << j+ 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                   n--;
		           }
		         }
		       }
		     }
		     if(i%4==3)   {
		       for(int j=i-1;(j<i?j>=0:j>i);j=(j-1)%(p->passcount/3))  {
             if(n==0)     break;
		         if(n>0)   {
		           if(p->fseats[j]==0)   {
		               p->fseats[j]=1;
		               details(p,j,'f');
		               cout << "seat number " << j+ 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                   n--;
		           }
	           }
           }
		     }
		   }
		 }
		 if(a==2)		 {
		     for( i=0;i<p->passcount/3;i++)	  {
		         if(i%4==1||i%4==2)	  {
		           if(p->fseats[i]==0)    {
		             p->fseats[i]=1;
		             details(p,i,'f');
		             cout << "seat number " << i + 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                 n--;
                 break;
		           }
		         }
		     }
		     if(n>0)    {
		       if(i%4==1)  {
		         for( j=i+1;(j>i?j<p->passcount/3:j<i);j=(j+1)%(p->passcount/3))   {
               if(n==0)   break;
		           if(n>0)   {
		             if(p->fseats[j]==0)   {
		               p->fseats[j]=1;
		               details(p,j,'f');
		               cout << "seat number " << j+ 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                   n--;
		             }
		           }
		         }
		       }
		       if(i%4==2)   {
		         for( j=i-1;(j<i?j>=0:j>i);j=(j-1)%(p->passcount/3))   {
               if(n==0)  break;
		           if(n>0)  {
		             if(p->fseats[j]==0)    {
		               p->fseats[j]=1;
		               details(p,j,'f');
		               cout << "seat number " << j+ 1 << " of first class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                   n--;
	               }
	             }
	           }
		       }
		     }
		   }
  	 }
	  }
  }
  else
    {
      cout << "Enter no. of tickets:";
      cin >> n;
      int v = 0;
      for (int i = 1; i <= 2 * (p->passcount / 3); i++)    if (p->eseats[i] == 0)	  v++;
      if (v < n)	{
	      cout << "NOT ENOUGH SEATS AVAILABLE!!!";
	      return;
     	}
      else  {
	      cout<<"Enter your choice for window or aisle seat.Press 1 for window and 2 for aisle"<<endl;
        {
        int a,seat;
		cin>>a;
		int i,j;
		 if(a==1)
		 {
		     for( i=0;i<p->passcount/3*2;i++)
		     {
		         if(i%4==0||i%4==3)
		         {
		             if(p->eseats[i]==0)
		             {
		                 p->eseats[i]=1;
		                 details(p,i,'e');
		                 cout << "seat number " << i + 1 << " of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
                         break;

		             }
		         }
		     }
		     if(n>0)
		     {
		         if(i%4==0)
		         {
		             for( j=i+1;(j>i?j<p->passcount/3*2:j<i);j=(j+1)%(p->passcount/3*2))
		             {if(n==0)
		             break;
		                 if(n>0)
		                 {
		                     if(p->eseats[j]==0)
		                     {
		               p->eseats[j]=1;
		               details(p,j,'e');
		              cout << "seat number " << j+ 1 << "of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
		                     }
		                 }
		             }
		         }

		         if(i%4==3)
		         {
		             for( j=i-1;(j<i?j>=0:j>i);j=(j-1)%(p->passcount/3*2))
		             {if(n==0)
		             break;
		                 if(n>0)
		                 {
		                     if(p->eseats[j]==0)
		                     {
		               p->eseats[j]=1;
		               details(p,j,'e');
		              cout << "seat number " << j+ 1 << "of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
		                     }
		                 }
		             }
		         }

		     }

		 }
		 if(a==2)
		 {

		     for( i=0;i<p->passcount/3*2;i++)
		     {
		         if(i%4==1||i%4==2)
		         {
		             if(p->eseats[i]==0)
		             {
		                 p->eseats[i]=1;
		                 details(p,i,'e');
		                 cout << "seat number " << i + 1 << " of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
                         break;

		             }
		         }
		     }
		     if(n>0)
		     {
		         if(i%4==1)
		         {
		             for( j=i+1;(j>i?j<p->passcount/3*2:j<i);j=(j+1)%(p->passcount/3*2))
		             {if(n==0)
		             break;
		                 if(n>0)
		                 {
		                     if(p->eseats[j]==0)
		                     {
		               p->eseats[j]=1;
		               details(p,j,'e');
		              cout << "seat number " << j+ 1 << "of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
		                     }
		                 }
		             }
		         }

		         if(i%4==2)
		         {
		             for(int j=i-1;(j<i?j>=0:j>i);j=(j-1)%(p->passcount/3*2))
		             {if(n==0)
		             break;
		                 if(n>0)
		                 {
		                     if(p->eseats[j]==0)
		                     {
		               p->eseats[j]=1;
		               details(p,j,'e');
		              cout << "seat number " << j+ 1 << "of economy class reserved.Get your ticket by going to get info on passenger mode!" << endl;
                         n--;
		                     }
		                 }
		             }
		         }

		     }
       }

		 }
	  }
    }
}

void showdetails ()
{
  struct flightnode *p;
  p = head;
  int a, b;
  string dc,ac;
  char c;
  cout << "enter departure and arrival  city" << endl;
  cin >> dc;
  cin>>ac;
  while (p)
   {
     if( p->arrcity == ac && p->depcity==dc)     break;
     else    p=p->next;
   }
  if (p == NULL)  {
      cout << "no flight found" << endl;
      return;
   }
  else  {
      cout <<	"enter type of seat.Enter f for first class and e for economy class" << endl;
      cin >> c;
      if (c == 'e')  {
     	  cout << "enter your seat no." << endl;
	      cin >> b;
    	  cout << "The details are" << endl;
	      cout << (p->eid[b - 1]).name << endl;
    	  cout << "age = " << (p->eid[b - 1]).age << endl;
    	  cout << "passport no. = " << (p->eid[b - 1]).passport << endl;
    	  cout << "phone no.= " << (p->eid[b - 1]).phone << endl;
    	  cout << "cost is Rs" << (p->eid[b - 1]).cost << endl;
    	}
      if (c == 'f')	{
	      cout << "enter your seat no." << endl;
    	  cin >> b;
    	  cout << "The details are" << endl;
    	  cout << (p->fid[b - 1]).name << endl;
    	  cout << "age = " << (p->fid[b - 1]).age << endl;
    	  cout << "passport no. = " << (p->fid[b - 1]).passport << endl;
	      cout << "phone no.= " << (p->fid[b - 1]).phone << endl;
	      cout << "cost is Rs" << (p->fid[b - 1]).cost << endl;
	    }
   }
}

// ************************************ ADMIN/PASSENGER DOMAIN FUNCTIONS ****************************************

void admin ()
{
  string pass;
  cout << "enter the password" << endl;
  cin >> pass;
  if (pass != "abc")
    {
      cout << "invalid password" << endl;
      return;
    }
  else
    {
      int choice;
      cout << "enter your choice" << endl;
      cout << "1.Add flight" << endl;
      cout << "2.Modify flight" << endl;
      cout << "3.Delete flight" << endl;
      cin >> choice;
      switch (choice) 	{
         case 1: addflight ();
	               break;
	       case 2: modify ();
	               break;
	       case 3: deleteflight ();
	               break;
	       default: cout << "invalid choice" << endl;
     	}
    }
}

void passenger ()
{
  int choice;
  cout << "enter the choice" << endl;
  cout << "1.Reserve a seat" << endl;
  cout << "2. See flight schedule" << endl;
  cout << "3.See your info" << endl;
  cin >> choice;
  switch (choice)
    {
        case 1: reserveflight ();
                break;
        case 2: flightschedule ();
                break;
        case 3: showdetails ();
                break;
        default:  cout << "invalid choice" << endl;
    }
}

// ************************************ LANDING/INDEX PAGE ****************************************

int main (void)
{
  int c = 4;
  cout << "\t\t *************************************"<<endl;
  cout << "\t\t WELCOME TO ONLINE AIRLINE RESERVATION" << endl;
  cout << "\t\t *************************************"<<endl;
  cout<<endl;
  while (1)
    {
      cout<<endl;
      cout << "1. Admin Mode"<<endl;
      cout << "2. Passenger Mode"<<endl;
      cout << "3. EXIT"<<endl;
      cout << "Enter choice:";
      cin >> c;
      cout<<endl;
      if (c == 1)  	admin ();
      else if (c == 2)  passenger ();
      else 	break;
    }
  cout << "THANKS FOR VISITING!";
  return 0;
}
