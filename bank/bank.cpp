#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;


const string ClientsFileName = "clients_data.txt";

//show,update,delete,find

int option(){
    int num;
    cout<<"enter your option :";
    cin>>num;
    return num;

}


void ShowClients(){
    

}
void DeleteClient(){



}
void updateClient(){


}
void FindClient(){

}
void exit_program(){
    cout<<"=========================="<<endl;
    cout<<"program ends"<<endl;
    cout<<"=========================="<<endl;}
void Main_Work(int option){

    switch (option)
    {
    
        case 1:
        /* code */
        break;
        case 2:
        /* code */
        break;
        case 3:
        /* code */
        break;
        case 4:
        /* code */
        break;
        case 5:
        /* code */
        break;
        case 6:
        exit_program();
        break;
    }

}
void ShowMenu(){

    cout<<"============================="<<endl;
    cout<<"[1] Show all clients"<<endl;
    cout<<"[2] Delete client"<<endl;
    cout<<"[3] Update client"<<endl;
    cout<<"[4] Find client"<<endl;
    cout<<"[6] Exit program"<<endl;
    cout<<"============================="<<endl;
    
    Main_Work(option());

}







int main()
{
    ShowMenu();

    return 0;
}
