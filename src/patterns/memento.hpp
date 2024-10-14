#pragma once

#include "iostream"
#include "string"
#include <vector>
#include <memory>
 
using namespace std;
 
class Memento
{
public:
	Memento(string state):state_(state){};
	string GetState(){return state_;}
 
private:
	string state_;
};
 
class Originator
{
public:
	
	void SetState(string state)
	{
	state_=state;
	}
 
	string GetState()
	{
	return state_;
	}
 
	//创建备忘录
	std::shared_ptr<Memento>CreateMemento()
	{
		return make_shared<Memento>(state_); 
	}
 
	//恢复备忘录
	void RestoreState(std::shared_ptr<Memento> memento)
	{
		state_=memento->GetState();
	}
 
 
private:
	string state_;
};
 
class Careker
{
public:
	void AddMemento(std::shared_ptr<Memento> memento)
	{
		mementos_.push_back(memento);
	}
 
	std::shared_ptr<Memento> GetMemento(int index)
	{
		return mementos_[index];
	}
 
private: 
	vector<std::shared_ptr<Memento>>mementos_;
 
};
 
void memento_tb()
{
	Originator originator;
	Careker careker;
 
	originator.SetState("State 1");
	careker.AddMemento(originator.CreateMemento());
 
	originator.SetState("State 2");
	careker.AddMemento(originator.CreateMemento());
 
	originator.SetState("State 3");
	careker.AddMemento(originator.CreateMemento());
 
	originator.RestoreState(careker.GetMemento(0));
	cout<<originator.GetState()<<endl;
}