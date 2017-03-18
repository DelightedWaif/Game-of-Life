/*
 * Main.cpp
 *
 *  Created on: 29 Feb 2016
 *      Author: Tim
 */
//poly Game
//Monopoly Game
#include<cstdlib>
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int FirstPlayer=1;
bool Roll=false;
int pCount=0;
int pTurn=0;
int pID = 1;
int roll1;
int roll2;
bool inJail[8]{false,false,false,false,false,false,false,false};
string player[8];
int position[8] = {0,0,0,0,0,0,0,0};
double balance[8] = {1500,1500,1500,1500,1500,1500,1500,1500};
int distance = 0;
bool OwnedProperties[]={};
const int price[40]={0,60,0,60,0,200,100,0,100,120,0,140,150,140,160,200,180,0,180,200,0,220,0,220,240,200,260,260,150,280,0,300,300,0,320,200,0,350,0,400};
const string property[40]={"Go","Mediteranean Avenue","Community Chest","Baltic Avenue","Income Tax","Reading Railroad",
				 "Oriental Avenue","Chance","Vermont Avenue","Connecticut Avenue","In Jail/Just Visiting",
				 "St. Charles Place","Electric Company","States Avenue","Virginia Avenue","Pennsylvania Railroad",
				 "St. James Place","Community Chest","Tennessee Avenue","New York Avenue", "Free Parking",
				 "Kentucky Avenue","Chance","Indiana Avenue","Illinois Avenue","B.& O.Railroad",
				 "Atlantic Avenue","Ventnor Avenue","Water Works","Marvin Gardens","Go To Jail",
				 "Pacific Avenue","North Carolina Avenue","Community Chest","Pennsylvania Avenue","Short Line",
				 "Chance","Park Place","Luxury Tax","Boardwalk"};

int pOwned[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void start(int& pCount, string player[]);
void FirstRoll(bool& rollAgain, int& First);
void roll(int& roll1, int& roll2);
void turn(int& pID, string player[], int FirstP);
void move(int pID, int position[]);
//double deposit(double amount);
double withdraw(double& balance, int Position, char x);
void account();
void buy(int pID, int position[]);
//void sell(string pID);
void tax(int money);

int main(){
	start(pCount, player);
	if(1 < pCount && pCount <= 8){
		do{
			FirstRoll(Roll, FirstPlayer);
		}while (Roll);
		turn(pID, player, FirstPlayer);
	}
	else if (pCount<1){
		cout <<"Find at least one more person to play with.\n"
				"Goodbye!";
	}
	else if(pCount>8){
		cout<<"Woah! You're so popular go do something else with all your friends.\n Goodbye!";
	}
	return 0;
}
void start(int& pCount, string player[]){
	cout<< "Welcome to Molopoly!"<<endl;
	cout<< "This game is designed for 8 or less people."<< endl;
	cout << "How many players are there?\n";
	cin >> pCount;
	for (pID=1; pID <= pCount; pID++){
		cout << "Enter player " << pID <<"’s name.";
		cin >> player[pID-1]; cout << endl;
	}
	if(pCount<=1){
		cout <<"Welcome " << player[0] <<"!\nSorry!\nYou have no friends!\n";
	}
	else if(pCount>=9){
		cout <<"Welcome everyone! \nYou have too many people. Go away.";
	}
	else{
		cout << "Welcome, ";
		for(int pID=1; pID<pCount; pID++){
			cout << player[pID-1] <<", ";
		}
		cout <<"and " << player[pCount-1] <<"!\n";
	}
}
void move(int pID, int position[]){
	position[pID-1]+= roll1 + roll2;
	if(inJail[pID]){
		position[pID]=9;
		cout<<"You are in jail, pay $50 or wait until you roll doubles to leave."<<endl;
	}
	else if(40 < position[pID-1]){
		position[pID-1] = position[pID-1]-40;
		balance[pID-1] += 200;
	}
	cout <<"You are on: " << property[position[pID-1]] <<endl;
}

void roll(int& roll1, int& roll2){
	int rCount=1;
	if (inJail[pID-1]){
		roll1 = rand()%7;
		roll2 = rand()%7;
		if(roll1==0)roll1++;
		if(roll2==0)roll2++;
		cout << "Rolled: " << roll1 << " & "<< roll2 << "." <<endl;
		if(roll1==roll2){
			inJail[pID-1]=false;
		}
	}
	else {
		roll1 = rand()%7;
		roll2 = rand()%7;
		if(roll1==0)roll1++;
		if(roll2==0)roll2++;
		cout << "Rolled: " << roll1 << " & "<< roll2 << "." <<endl;

		while(roll1==roll2){
			if(rCount<3){
				cout<<"Roll Again!\n";
				roll1 = rand()%7;
				roll2 = rand()%7;
				if(roll1==0)roll1++;
				if(roll2==0)roll2++;
				cout << "Rolled: " << roll1 << " & "<< roll2 << "." <<endl;
				rCount++;
			}
			else{
				inJail[pID-1]=true;
				break;
			}
		}
	}
}

void turn(int& pID, string player[], int FirstP){
	bool endTurn = false;
	char turn;

	char action;
	for(pID=FirstP; pID <= pCount; pID++){
		cout << "It is " << player[pID-1] <<"'s turn.\n\n";
		roll(roll1, roll2);
		move(pID, position);
		if(pOwned[position[pID-1]]!=0){
			tax(balance[pID-1]);
		}
		while(endTurn == false){

			cout <<"What would you like to do?\n Type 'd' for deposit\n 'w' to withdraw money\n 'b' to buy a property\n 's' to sell a property\n 'a' to view your balance\n 'n' to end your turn.\n ";
			cin >> action;
			while (action!='n'){
				if (action=='b'){
					buy(pID, position);
					}
				else if (action=='w'){
					char x='n';
					withdraw(balance[pID-1], position[pID-1], x);
					}
				else if (action=='a'){
					account();
					}
				cout <<"What would you like to do?\n Type 'd' for deposit\n 'w' to withdraw money\n 'b' to buy a property\n 's' to sell a property\n 'a' to view your balance\n 'n' to end your turn.\n ";
				cin>>action;

				/*else if (action=='d'){
					deposit();
				}

				else if (action=='s'){
					sell();
		 	 	}

		 	 	else {
		 	 	 	 cout<< "please enter a valid option"<<endl;
		 	 	}
			 */
				//turn stuff in here
			}
			cout << "Would you like to end your turn? (y/n)\n";
			cin >> turn;
			if (turn == 'y'){
					cout <<"Turned Ended.\n";
					endTurn = true;
				}
				else if (turn == 'n'){
					endTurn = false;
					cout <<"Turn not ended.\n";
				}
				else{
					bool incorrect = true;
					while(incorrect == true){
						cout <<"Please enter a valid option.\n";
						cin >> turn;
						if (turn == 'y'){
							endTurn = true;
							incorrect = false;
							cout <<"Turned Ended.\n";
						}
						else if (turn == 'n'){
							endTurn = false;
							incorrect = false;
							cout <<"Turn not ended.\n";
						}
						else incorrect = true;
					}
				}
		}
		if(pID == pCount) pID = 0;
		endTurn = false;
	}
}

double deposit(int amount){

	return 0;
}
double withdraw(double& balance, int Position, char x){
		int amount;
		char w;
		if (inJail[pID-1]){
			cout<<"Are you trying to get out of jail?"<<endl;
			cout<<"It costs $50 to get out of jail. \nWould you like to pay?";
			cin>>w;
			if (w=='y'){
				inJail[pID-1]=false;
			}

		}
		if (x=='y'){
			amount=price[position[pID-1]];
			if (amount>balance){
				cout<<"You do not have enough money to buy this property. Get a job.\n";
			}
			else{
				balance-=amount;
				//property=ownedbypID
				cout<<"You have $"<<balance<<" remaining"<<endl;
			}
		}
		else if(x=='n'){
			cout<<"How much do you owe?\n";
			cin>>amount;
				if (amount>balance){
					cout<<"You do not have enough money. Get a loan.\n";
				}
			else{
				balance-=amount;
				cout<<"You have $"<<balance<<" remaining."<<endl;
			}
		}
		else if (x!='n'&& x!='y') {
			cout<<"Please enter a valid option."<<endl;
		}

	return 0;
}
void account(){
		cout << player[pID-1] << "'s Account Information\n";
		cout <<"The account balance is: $" << balance[pID-1]<<endl;
		//cout <<"Owned properties: \n\t";

}

void FirstRoll(bool& rollAgain, int& First){

	int i;
	int x;
	int highest=0;
	int temp;
	rollAgain=false;
	for (i=1;i<=pCount;i++){
		temp=rand()%7;
		if (temp==0){
			temp++;
		}
		cout<<"Player "<<i<<"'s roll is "<<temp<<endl;
		if (temp==highest){
				rollAgain=true;
		}
		else if (temp>highest){
			highest=temp;
			x=i;
			rollAgain=false;
			First=x;
		}
	}
	if (!rollAgain){
		cout<<"Player "<<x<<" has the highest roll. Player "<<x<<" goes first"<<endl;
	}


}

void buy(int pID, int position[]){
	cout<<property[position[pID-1]]<<" costs $"<<price[position[pID-1]]<<endl;
	cout<< "Would you like to buy "<< property[position[pID-1]]<<"? (y/n)"<<endl;
	char x;
	cin>>x;

		if (x=='y'){
			if (position[pID-1]==2||position[pID-1]==7||position[pID-1]==4||position[pID-1]==10||position[pID-1]==17||position[pID-1]==20||position[pID-1]==22||position[pID-1]==30||position[pID-1]==33||position[pID-1]==36||position[pID-1]==38){
				cout<<"You cannot purchase this property"<<endl;
			}
			else {

				if(pOwned[position[pID-1]]==0){
					withdraw(balance[pID-1], price[position[pID-1]], x);
					pOwned[position[pID-1]]=pID-1;
				}
				else{
				cout<<"This property is already owned."<<endl;
				}
			}
		}
	if (x!='y'&&x!='n') {
		while(x!='y'||x!='n') {
				cout<<"Please enter a valid option"<<endl;
				cin>>x;
			}
	}

}
void sell(int pID){


}

void tax(int money){
	for (int i=0;i<pCount;i++){
		int tax=price[position[pID-1]]/10;
		if(pOwned[position[pID-1]]==pID-1){
			cout<< "This is your property, you don't owe anything you lucky bastard.";
		}
		else if (pOwned[position[pID-1]]==i){
			money-=tax;
			balance[i]+=tax;

		}
	}
}
