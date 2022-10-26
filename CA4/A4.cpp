#include<iostream>
#include<vector>
#include <string>
#include<cstdlib>
#include <bits/stdc++.h>
using namespace std;
class Worker;
class CarWash;
enum Command
{
	add_car,
	add_stage,
	advance_time,
	finish,
	show_stage_info,
	show_carwash_info,
};
class Car{
public:
	Car(int ID,int Ceo);
	int Left_Time_Units;
	int curr_workerID;
	void show_car_info();
	int get_CarCoe(){return CarCoe;}
	int get_CarID(){return CarID;}
private: 
	int CarID;
	int CarCoe;
};
Car::Car(int ID,int Coe)
{
    CarID=ID;
    CarCoe=Coe;
    Left_Time_Units=-1;
}
class Stage{
public:
	Stage(int Num,vector<Worker*> workers);
	vector<Car*> Cars_In_Progress;
	vector<Car*> Waiting_Queue;
	bool Stage_In;
	bool Stage_Out;
	void show_stage_info();
	Car* find_car(int ID);
	int choose_worker();
	bool There_Is_Free_Worker_InStage();
	bool Search_Waiting_Queue(Car car);
    bool Search_Cars_In_progress(Car car);
    Worker* find_worker_with_ID(int ID);
    bool car_can_exit_stage(int workerID);
	vector<Worker*> get_Stge_workers(){return Stage_workers;}
	int get_Stage_number(){return Stage_number;}
private:
	int Stage_number;
	vector<Worker*> Stage_workers;
};
Stage :: Stage(int Num,vector<Worker*> workers)
{
	Stage_number=Num;
	Stage_workers=workers;
	Stage_In=true;
	Stage_Out=true;
}
class Worker{
public:
	Worker( int ID,int Ceo);
	bool Worker_Status;
	int curr_carID;
	int get_WorkerCoe(){return WorkerCoe;}
	int get_WorkerID(){return WorkerID;}
private:
	int WorkerID;
	int WorkerCoe;
};
Worker :: Worker(int ID,int Ceo)
{
	WorkerID=ID;
	WorkerCoe=Ceo;
	curr_carID=-1;
	Worker_Status=true;
}
class CarWash{
public:
	vector<Car*> Cars_Waiting;
	vector<Car> Cars_finished;
	int time_of_simulation=0;
	void add_stage(int Stage_level,vector<int> Ceos);
	void add_car(int CarID,int CarCeo);
	void show_stage_info(int stageID){Stages[stageID].show_stage_info();}
	void show_carwash_info();
    void finish();
	Car* find_car_with_ID(int ID);
	void advance_time_One_Unit();
	void advance_time(int time);
	void push_Car_forword(Car *car);
	int Car_Current_Stage(Car car);
	void push_Car_in_waiting_cars_forword(Car *car);
	void push_Car_in_waiting_queue_forword(Car *car,int stage_num);
	void car_leaves_carwash(Car *car,int stage_num);
	void car_enters_stage(Car *car,int stage_num);
	void car_exits_stage(Car *car,int stage_num);
	void advance_car_in_progress(Car *car,int Curr_Stage_num);
	vector<Stage> get_Stages(){return Stages;}
	vector<Car*> get_Cars(){return Cars;}
private:
	vector<Stage> Stages;
	vector<Car*> Cars;
};
void Car::show_car_info()
{
	cout<<"Car ID: "<<CarID<<endl;
	cout<<"Luxury coefficient: "<<CarCoe<<endl;
}
bool Stage::Search_Waiting_Queue(Car car)
{
	for(int i=0;i<Waiting_Queue.size();i++)
	{
		if(Waiting_Queue[i]->get_CarID()==car.get_CarID())
			return true;
	}
	return false;
}
bool Stage::Search_Cars_In_progress(Car car)
{
	for(int i=0;i<Cars_In_Progress.size();i++)
	{
		if(Cars_In_Progress[i]->get_CarID()==car.get_CarID())
			return true;
	}
	return false;
}
bool Stage::There_Is_Free_Worker_InStage()
{
	for(int i=0;i<Stage_workers.size();i++)
	{
		if(Stage_workers[i]->Worker_Status)
			return true;
	}
	return false;
}
Car* Stage::find_car(int ID)
{
	for(int i=0;i<Cars_In_Progress.size();i++)
	{
		if(Cars_In_Progress[i]->get_CarID()==ID)
			return Cars_In_Progress[i];
	}
}
void Stage::show_stage_info()
{
	cout<<"Stage ID: "<<Stage_number<<endl;
	for(int i=0;i<Stage_workers.size();i++)
	{
		cout<<"Worker ID: "<<Stage_workers[i]->get_WorkerID()<<endl;
		if(Stage_workers[i]->Worker_Status)
			cout<<"Free"<<endl;
		else
		{
			Car* current_car=find_car(Stage_workers[i]->curr_carID);
			current_car->show_car_info();
			cout<<"Time left: "<<current_car->Left_Time_Units<<endl;
		}
	}
	cout<<"Cars in waiting queue: "<<endl;
	for(int i=0;i<Waiting_Queue.size();i++)
		Waiting_Queue[i]->show_car_info();
}
Worker* Stage::find_worker_with_ID(int ID)
{
	for(int i=0;i<Stage_workers.size();i++)
	{
		if(Stage_workers[i]->get_WorkerID()==ID)
		{
			return Stage_workers[i];
		}
	}
}
int Stage::choose_worker()
{
	for(int i=0;i<Stage_workers.size();i++)
	{
		if(Stage_workers[i]->Worker_Status)
			return Stage_workers[i]->get_WorkerID();
	}
}
bool Stage::car_can_exit_stage(int workerID)
{
	if(!Stage_Out)
		return false;
	else
	{
	  for(int i=0;i<Cars_In_Progress.size();i++)
	  {
		 if(Cars_In_Progress[i]->Left_Time_Units==0)
		 {
			 if(Cars_In_Progress[i]->curr_workerID<workerID)
				return false;
		 }
	  }
    }
	return true;
}
bool comparetwocar(Car *car1,Car *car2){return(car1->Left_Time_Units<=car2->Left_Time_Units);}
vector<int> Sort_carIDs_in_order(vector<Stage> Stages,vector<Car*> Cars_Waiting)
{
	vector<int> carIDs_in_order;
	for(int i=Stages.size()-1;i>-1;i--)
	{
		vector<Car*> stagecars;
		for(int j=0;j<Stages[i].Cars_In_Progress.size();j++)
		{
			stagecars.push_back(Stages[i].Cars_In_Progress[j]);
		}
		if(stagecars.size()>1)
		    sort(stagecars.begin(),stagecars.end(),comparetwocar);
		for (int i = 0; i < stagecars.size(); i++)
		{
			carIDs_in_order.push_back(stagecars[i]->get_CarID());
		}
		for (int j = 0; j < Stages[i].Waiting_Queue.size(); j++)
		{
			carIDs_in_order.push_back(Stages[i].Waiting_Queue[j]->get_CarID());
		}
	}
	for(int i=0;i<Cars_Waiting.size();i++)
	{
		carIDs_in_order.push_back(Cars_Waiting[i]->get_CarID());
	}
	return carIDs_in_order;
}
void CarWash::add_car(int CarID,int CarCoe)
{
	Car *newcar=new Car(CarID,CarCoe);
	Cars.push_back(newcar);
	Cars_Waiting.push_back(newcar);
}
void CarWash::add_stage(int Stage_level,vector<int> Ceos)
{
	vector<Worker*> stageworkers;
	int num=0;
	for(int i=0;i<Stages.size();i++)
	{
		num+=Stages[i].get_Stge_workers().size();
	}
	for(int i=0;i<Ceos.size();i++)
	{
		Worker *w=new Worker(num+i,Ceos[i]);
		stageworkers.push_back(w);
	}
	Stages.push_back(Stage(Stage_level,stageworkers));	
}
void CarWash::finish()
{
	while(Cars.size()>0)
	{
		time_of_simulation++;
		advance_time_One_Unit();
	}
}
void CarWash::show_carwash_info()
{
	cout<<"Passed time: "<<time_of_simulation<<endl;
	cout<<"Cars waiting: "<<endl;
	for(int i=0;i<Cars_Waiting.size();i++)
		Cars_Waiting[i]->show_car_info();
	cout<<"Stages info: "<<endl;
	for(int i=0;i<Stages.size();i++)
		show_stage_info(i);
	cout<<"Cars finished: "<<endl;
	for(int i=0;i<Cars_finished.size();i++)
		Cars_finished[i].show_car_info();
}
Car* CarWash::find_car_with_ID(int ID)
{
	for(int i=0;i<Cars.size();i++)
	{
		if(Cars[i]->get_CarID()==ID)
			return Cars[i];
	}
}
void CarWash::advance_time_One_Unit()
{
	vector<int> carIDs_in_order=Sort_carIDs_in_order(Stages,Cars_Waiting);
	for(int i=0;i<carIDs_in_order.size();i++)
	{
	    Car *car=find_car_with_ID(carIDs_in_order[i]);
	    push_Car_forword(car);
	}
	for(int i=0;i<Stages.size();i++)
	{
		Stages[i].Stage_Out=true;
		Stages[i].Stage_In=true;
	}
}
void CarWash::advance_time(int time)
{
	for(int i=0;i<time;i++)
		advance_time_One_Unit();
	time_of_simulation+=time;
}
void CarWash::car_enters_stage(Car *car,int stage_num)
{
	int workerID=Stages[stage_num].choose_worker();
    Worker* worker=Stages[stage_num].find_worker_with_ID(workerID);
    worker->Worker_Status=false;
	worker->curr_carID=car->get_CarID();
	car->Left_Time_Units=car->get_CarCoe()*worker->get_WorkerCoe();
	Stages[stage_num].Cars_In_Progress.push_back(car);
	car->curr_workerID=worker->get_WorkerID();
}
void CarWash::push_Car_in_waiting_cars_forword(Car *car)
{
	if(Stages[0].Stage_In==false)
		return;
    else
    {
      Cars_Waiting.erase(remove(Cars_Waiting.begin(),Cars_Waiting.end(),Cars_Waiting[0]),Cars_Waiting.end());
      Stages[0].Stage_In=false;
	  if(Stages[0].Waiting_Queue.size()==0)
	  {
		if(Stages[0].There_Is_Free_Worker_InStage())
		{
			car_enters_stage(car,0);
		    return ;	
		}
	  }
	  Stages[0].Waiting_Queue.push_back(car); 
	  return;
    }
}
void CarWash::push_Car_in_waiting_queue_forword(Car *car,int stage_num)
{
	if(Stages[stage_num].Waiting_Queue[0]->get_CarID()==car->get_CarID())
	{
		if(Stages[stage_num].There_Is_Free_Worker_InStage())
		{
			car_enters_stage(car,stage_num);
			Stages[stage_num].Waiting_Queue.erase(remove(Stages[stage_num].Waiting_Queue.begin(),Stages[stage_num].Waiting_Queue.end(),Stages[stage_num].Waiting_Queue[0]),Stages[stage_num].Waiting_Queue.end());
			Stages[stage_num].Stage_In=false;	
		}
	}
	return;
}
void CarWash::car_exits_stage(Car *car,int stage_num)
{
	Stages[stage_num].Stage_Out=false;
	int carindex;
	for(int i=0;i<Stages[stage_num].Cars_In_Progress.size();i++)
	{
		if(Stages[stage_num].Cars_In_Progress[i]->get_CarID()==car->get_CarID())
	    {
			carindex=i;
			break ;
		}
	}
	Stages[stage_num].Cars_In_Progress.erase(remove(Stages[stage_num].Cars_In_Progress.begin(),Stages[stage_num].Cars_In_Progress.end(),Stages[stage_num].Cars_In_Progress[carindex]),Stages[stage_num].Cars_In_Progress.end());
	Worker* worker=Stages[stage_num].find_worker_with_ID(car->curr_workerID);
	worker->Worker_Status=true;
}
void CarWash::car_leaves_carwash(Car *car,int stage_num)
{
	Cars.erase(remove(Cars.begin(),Cars.end(),Cars[car->get_CarID()]),Cars.end());
	Cars_finished.push_back(*car);
}
void CarWash::advance_car_in_progress(Car *car,int Curr_Stage_num)
{
	if(car->Left_Time_Units>0)
	{
		car->Left_Time_Units--;
		return;
	}
	if(Stages[Curr_Stage_num].car_can_exit_stage(car->curr_workerID))
	{
		car_exits_stage(car,Curr_Stage_num);
		if(Curr_Stage_num+1==Stages.size())
		{
			car_leaves_carwash(car,Curr_Stage_num);
			return;
		}
	    if(Stages[Curr_Stage_num+1].Waiting_Queue.size()==0 && Stages[Curr_Stage_num+1].There_Is_Free_Worker_InStage()&& Stages[Curr_Stage_num+1].Stage_In)
		{
			car_enters_stage(car,Curr_Stage_num+1);
			Stages[Curr_Stage_num+1].Stage_In=false;
			return;
		}
		Stages[Curr_Stage_num+1].Waiting_Queue.push_back(car);
		return;
	}
}
void CarWash::push_Car_forword(Car *car)
{
	int Curr_Stage_num=Car_Current_Stage(*car);
	if(Curr_Stage_num==-1)
		push_Car_in_waiting_cars_forword(car);
	else if(Stages[Curr_Stage_num].Search_Waiting_Queue(*car))
		push_Car_in_waiting_queue_forword(car,Curr_Stage_num);
	else if(Stages[Curr_Stage_num].Search_Cars_In_progress(*car))
		advance_car_in_progress(car,Curr_Stage_num);
}
int CarWash::Car_Current_Stage(Car car)
{
	for(int i=0;i<Stages.size();i++)
	{
		if((Stages[i].Search_Waiting_Queue(car)) || (Stages[i].Search_Cars_In_progress(car)))
		    return i;
	}
	return -1;
}
vector<string> split(string line)
{
	vector<string> words;
	stringstream linestream(line);
	string word;
	while(linestream>>word)
		words.push_back(word);
	return words;
}
Command get_command(string line)
{
	string word = split(line)[0];
	if(word=="add_stage")
		return add_stage;
	else if(word=="add_car")
		return add_car;
	else if(word=="advance_time")
		return advance_time;
	else if(word=="finish")
		return finish;
	else if (word=="show_stage_info")
		return show_stage_info;
	else
		return show_carwash_info;
}
vector<int> get_coes(string line)
{
	int numofworkers=stoi(split(line)[1]);
	vector<int> Coes;
	for(int i=0;i<numofworkers;i++)
	{
	    Coes.push_back(stoi(split(line)[2+i]));
	}
	return Coes;
}
void ReadAndRunCommands()
{
	string line;
	CarWash CarWash;
	int stagelevel=0;
	int numofcars=0;
	while(getline(cin,line))
	{
		Command command=get_command(line);
		switch (command)
		{
		case add_stage:
	         CarWash.add_stage(stagelevel,get_coes(line));
		     cout<<"OK"<<endl;
	         stagelevel++;
	         break;
	    case add_car:
	    	CarWash.add_car(numofcars,stoi(split(line)[1]));
	    	cout<<"OK"<<endl;
	    	numofcars++;
	        break;
	    case advance_time:	
	    	CarWash.advance_time(stoi(split(line)[1]));
	    	cout<<"OK"<<endl;
	        break;
	    case show_stage_info:
	    	CarWash.show_stage_info(stoi(split(line)[1]));;
	    	break;
	    case show_carwash_info:
	    	CarWash.show_carwash_info();
	        break;
	    case finish:
	    	CarWash.finish();
	    	cout<<"OK"<<endl;
	    	break;
       }
	}  
}
int main()
{
	ReadAndRunCommands();
}