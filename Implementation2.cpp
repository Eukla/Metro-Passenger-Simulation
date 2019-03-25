#include<iostream>
#include <time.h>
#include<cstdlib>
#include "classes.h"
using namespace std;

Passenger::Passenger():avoid(0){ // Passenegers constructor

 	hasticket=rand()%2;	// If he has a ticket

	ticket=rand()%2;	// If he has a discount ticket

	deserve=rand()%2;	//If he deserves a discount ticket

}
int Passenger:: get_ticket()const{	//Accessors of Passenger
	return ticket;
}
int Passenger:: get_hasticket()const{
	return hasticket;
}
int Passenger:: get_deserve()const{
	return deserve;
}
int Passenger:: get_avoid()const{
	return avoid;
}
void Passenger::set_avoid(const int n){	//Mutator
	avoid=n;
}
void Wagon::createnode(){	//list implementatiion for the wagon list

      	  node *temp=new node;

	  Passenger *object=new Passenger;

	  temp->data=object;

	  temp->next=NULL;

	  if(head==NULL)

	  {

	    head=temp;

	    tail=temp;

	    temp=NULL;

	  }

	  else

	  {
        tail->next=temp;

	    tail=temp;
      }
}
void Wagon::delete_imp(){	//deletion algorithm for the exiting passengers
	 node *temp;

   	 temp=head;

   	head=head->next;

	if(temp->data->get_avoid()==1){	//counter for the people that avoided checking and penallisation
			escaped++;
	}

	delete temp->data;
	delete temp;

}

int Wagon::get_money()const{	// Accessors of Waggon
		return money;
}

int * Wagon::get_p()const{
	return p;
}

int * Wagon::get_kicked()const{
	return kicked;
}

int Wagon::get_escaped()const{
	return escaped;
}

Wagon ** Train:: get_array(){
	return nodes;
}
Wagon::Wagon(int n,int s):maxCapacity(n),passengers(0),kicked(0),p(0),escaped(0),money(0){	//Constructor of Waggon

	int i;

	kicked=new int[s];														//Array for the people that escaped or were caught

	p=new int[s];															//Array that determines if the Waggon is going to be checked

	cout<<"A waggon with capacity for "<<maxCapacity<<" passengers, was created"<<endl;

	list();																			//Initiallising The passenger list

	for(i=1;i<s;i++){																//Initiallising the arrays of the object

		p[i]=0;

		kicked[i]=0;

	}

}

Wagon::~Wagon(){

	cout<<endl<<"A waggon was destroyed"<<endl;							//Deleting the list and arrays

	while(head!=NULL){

		delete_imp();

	}

	delete[] kicked;

	delete[] p;

}
Train::Train(int n,int w):totalWagons(w),Stations(n),money(0),counter(0){		//Train constructor

	int i;

	Wagon *node;

	cout<<endl<<"A metro train with total "<<w<<" waggons, was created"<<endl;

	nodes=new Wagon*[w];													//Creating the array of waggons

	for(i=0;i<w;i++){

		cout << endl << "Give me the waggon capacity: ";

		cin>>n;

		nodes[i]=new Wagon(n,Stations);

	}

}
Train::~Train(){											//Train destructor
	int i;
	for(i =0;i<totalWagons;i++){							//Deleting the array of Waggons
		delete nodes[i];

	}
	delete[] nodes;
	cout<<endl<<"A metro train was destroyed"<<endl;

}
int Train:: get_Stations()const {			//Acessors of Train
	return Stations;
}
int Train::get_totalWagons()const {
	return totalWagons;
}
void Wagon::inStation(int n){				//Here passengers enter or leave the stations

	int left, i ,entered,counter=0;
	node *temp;
  node *current;

	node *previous;

	current=head;
while(current!=NULL)
if(current->data->get_avoid()==2)         //Checking for perpetrators once the train reaches the station before anyone enters or leaves
  if(head==current){			//Deleting according to his position in the list

    head=head->next;

    previous=head;

    delete current->data;

    delete current;

    current=previous;

  }
  else{
    if(current==tail){tail=previous;}

    previous->next=current->next;

    delete current->data;

    delete current;

    current=previous->next;
  }
else{
  previous=current;

  current=current->next;
  }



	if(passengers!=0){					//If there are passengers, it deletes a number equal to or less than the existing passengers

		left=rand()%(passengers+1);

		passengers-=left;

		for(i=1;i<=left;i++)

			delete_imp();
		}

	entered=rand()%(maxCapacity-passengers+1);		//It inserts passengers , but ensures that the passenger count won't exceed the capacity

	passengers+=entered;

	for(i=0;i<entered;i++)
		createnode();

    p[n]=rand()%2;                              //Determining if it is checked and storing it

}
void Wagon::betweenStations(int i){					//The checking for passengers with no ticket or have a discount while they dont have the right.It take the int i so that we can store if the Waggon was checked

	int h=0,c=0,d=0;

	node *current;

	node *previous;

	current=head;

	while(current!=NULL){

			h=current->data->get_hasticket();		//Acessing the current passenger's "ticket state"

			c=current->data->get_ticket();

			d=current->data->get_deserve();

			if(h==0 || (c==0 && d==0)){				// If he doen't have a ticket or he has but it's a discount one whie he doens't deserve it

				if(p[i]){							// If the waggon is checked , force him to exit the moment before anyone leaves in the instation

					current->data->set_avoid(2);	//Marking current passenger a caught perpetrator

          current=current->next;

					if(d==1){				//If he doesn't have a ticket but deserves a discount ticket, he pays less

						money+=5;

					}

					else{				//If he doesn't have a ticket but deserves a regular ticket , he pays full price

						money+=10;

					}

					passengers--;		//Decreasing the overall passenger count of the Waggon

				}

				else{

					current->data->set_avoid(1);	//Mark the perpatrator as an escapee for now

					current=current->next;

				}

				kicked[i]++;						// Increasing the counter of total people caught or escaped in this waggon
			}
			else{									//Passenger is clean so keep searching

				previous=current;

				current=current->next;

			}
	}
}
void operate(Train *T){								//Key function that operates the train

	int i,j,s,w;

	Wagon **nodes;

	nodes=T->get_array();							//Array of Waggons

	s=T->get_Stations();							//Number of stations

	w=T->get_totalWagons();							//NUmber of Waggons

	for(i=1;i<s;i++){								//Operating the train for each station and Waggon

		for(j=0;j<w;j++){

			nodes[j]->inStation(i);

			nodes[j]->betweenStations(i);

		}

	}

	for(j=0;j<w;j++){					//	Functions that finds how many passengers escaped testing while being at fault

			nodes[j]->Traverse();

	}

}

void Wagon::Traverse(){				//Function that increases a counter each time it finds a marked person is about to exit at the final station unckecked

	node *temp=head;

	while(temp!=NULL){

		if(temp->data->get_avoid()==1){

			escaped++;

		}

	temp=temp->next;

	}

}

void PrintStatistics(Train *T){									//Function that prints Statistics

	int *possibility,*k,i,waggons,money=0,s,j,*fkicked,n;

	Wagon **nodes;

	nodes=T->get_array();										//Get the array of wagons

	waggons=T->get_totalWagons();								//Get total Waggons

	s=T->get_Stations();										//Get total Stations

	fkicked=new int[waggons];									//Array for total result

	for(i=0;i<waggons;i++){										//Initiallising list

		fkicked[i]=0;

	}

	for(j=1;j<s;j++){													//Printing Statistics of each Wagon at each Station

		cout<<endl<<"FROM STATIONS "<<j<<" TO "<<j+1<<endl;

		for(i=0;i<waggons;i++){

			possibility=nodes[i]->get_p();									//Get if it was checked

			k=nodes[i]->get_kicked();										//Get how many escaped or were kicked

			if(possibility[j]){

				cout<<endl<<"The Waggon number "<<i+1<<" was checked"<<endl<<k[j]<<" people were caught"<<endl;

				fkicked[i]+=k[j];

			}

			else{

				cout<<endl<<"The Waggon number "<<i+1<<" was not checked"<<endl<<k[j]<<" people escaped"<<endl;

			}
		}

	}

	cout<<endl<<endl<<"FINAL RESULTS :"<<endl;

	for(i=0;i<waggons;i++){

		n=nodes[i]->get_escaped();							//Get how many ultimately escaoed testing

		money+=nodes[i]->get_money();						//Collect funds

		cout<<endl<<"At Waggon number "<<i+1<<": "<<fkicked[i]<<" people in total were caught and "<<n<<" completely escaped"<<endl;

	}

	cout<<endl<<"Fines collected : "<<money<<" € "<<endl;

	delete[] fkicked;

}
