class Passenger{

	int hasticket; //1 has it 0 he doesnt

	int ticket; // 1 has normal 0 has reduced

	int deserve; // 1 reduced 0 has normal

	int avoid;

	public:
		int get_ticket()const;

		int get_hasticket()const;

		int get_deserve()const;

		int get_avoid()const;

		void set_avoid(int n);

		Passenger();


};
class Wagon{

	private:

		int *kicked;

		int escaped;

		int passengers;

		int maxCapacity;

		int *p;

		int money;

		struct node
  		{
  	  		Passenger *data;

  	  		node *next;
  		};

		node *head ,*tail;

	public:

		int get_money()const;

		void createnode();

		void delete_imp();

		void list(){

      			head=NULL;

      			tail=NULL;

    		}

		int * get_kicked()const;

		int * get_p()const;

		int get_escaped()const;

		void inStation(int i);

		void betweenStations(int i);

		void Traverse();

		Wagon(int maxCapacity,int stations);

		~Wagon();
};
class Train{

	private:

		int Stations;

		int money;

		int totalWagons;

		int counter;

		Wagon **nodes;

	public:
		int get_Stations()const;

		int get_totalWagons()const;

		Wagon **get_array();

		Train(int n,int w);

		~Train();

};
void operate(Train *T);
void PrintStatistics(Train *T);
