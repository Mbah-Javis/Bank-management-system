// MADE BY
// MBAH JAVIS (JASNIFF)
// FROM CAMEROON
// NORHT WEST REGION
// FOLLOW ME ON GIT HUB AT https://github.com/Mbah-Javis
// FACEBOOK AT Mbah Javis (Jasniff)
// MY gmail at javisthegeek@gmail.com


#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
    int accountno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account();
    void show_account() const;
    void modify();
    void dept(int);
    void draw(int);
    void report() const;
    int retaccountno() const;
    int returndeposit() const;
    char rettype() const;
};

void account::create_account()
{
    cout<<"\nEnter The account NO. :";
    cin>>accountno;
    cout<<"\n\nEnter The name of the account holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter The type of account (C/S) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter The Initial amount (>=500 for saving and >=1000 for Current ) : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Created... ";
}

void account::show_account() const
{
    cout<<"\nAccount No : "<<accountno;
    cout<<"\nAccount holder name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<deposit;

}

void account::modify()
{
    cout<<"\nAccount No : "<<accountno;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    cout<<"Modify Account Balance : ";
    cin>>deposit;
}

void account::dept(int x)
{
    deposit+=x;
}
void account::draw(int x)
{
    deposit-=x;
}

void account::report() const
{
    cout<<accountno<<setw(10)<<" "<<name<<setw(10)<<type<<setw(6)<<deposit<<endl;
}

int account::retaccountno() const
{
    return accountno;
}

int account::returndeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delet_accout(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main()
{
    char ch;
    int num;
    intro();
    do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01: NEW ACCOUNT";
        cout<<"\n\n\t02: DEPOSITE AMMOUNT";
        cout<<"\n\n\t03: WITHDRAW AMMOUNT";
        cout<<"\n\n\t04: BALANCE ENQUIRY";
        cout<<"\n\n\t05: ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06: CLOSE AN ACCOUNT";
        cout<<"\n\n\t07: MODIFY AN ACCOUNT";
        cout<<"\n\n\t08: EXIT";
        cout<<"\n\n ";
        cout<<"Use the numbers 1-8 to select";
        cin>>ch;

        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n\n\tEnter the Account No : "; cin>>num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout<<"\n\n\tEnter The Account No : ";cin>>num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout<<"\n\n\tEnter The Account No : ";cin>>num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"\n\n\tEnter The Account No : "; cin>>num;
            delet_accout(num);
            break;
        case '7':
            cout<<"\n\n\tEnter The Account No : "; cin>>num;
            modify_account(num);
            break;
        case '8':
            cout<<"\n\n\n\tThanks for Using the Bank Management system";
            break;
        default:
            cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while (ch!='8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if (!inFile)
    {
        cout<<"File could not be open !! Press any key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if (ac.retaccountno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if (flag=false)
    {
        cout<<"\n\nAccount Number does not exist";
    }
}

void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if (!File)
    {
      cout<<"File could not be open !! Press any key...";
        return;
    }
   while (!File.eof() && found==false)
   {
       File.read(reinterpret_cast<char *> (&ac), sizeof(account));
       if (ac.retaccountno()==n)
       {
           ac.show_account();
           cout<<"\n\nEnter the details of the account"<<endl;
           ac.modify();
           int pos=(-1)*static_cast<int>(sizeof(account));
           File.seekp(pos,ios::cur);
           File.write(reinterpret_cast<char *> (&ac), sizeof(account));
           cout<<"\n\n\tRecord updated";
           found==true;
       }
   }
   File.close();
   if (found=false)
   {
       cout<<"\n\nRecord not found";
   }
}

void delet_accout(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if (!inFile)
    {
       	cout<<"File could not be open !! Press any Key...";
		return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)));
    {
     if (ac.retaccountno()!=n)
     {
         outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
     }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted ";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if (!inFile)
    {
      cout<<"File could not be open !! Press any Key...";
		return;
    }
    cout<<"\n\n\n\tACCOUNT HOLDER LIST";
    cout<<"===============================================\n";
    cout<<"A/c no.      NAME         TYPE        BALANCE";
    cout<<"================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary);
    if (!File)
    {
        cout<<"File could not be open !! Press any Key...";
		return;
    }
    while (File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac),sizeof(account));
        if (ac.retaccountno()==n)
        {
            ac.show_account();
            if (option=1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter the amount to be deposited";
                cin>>amt;
                ac.dept(amt);
            }
            if (option=2)
            {
                cout<<"\n\n\tTO WITHDDRAW AMOUNT ";
                cout<<"\n\nEnter amount to be withdraw ";
                cin>>amt;
                int bal=ac.returndeposit()-amt;
                if ((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"Insufficient Balance";
                else
                    ac.draw(amt);
                int pos=(-1)*static_cast<int>(sizeof(ac));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                cout<<"\n\nRecord Updated ";
                found=true;
            }
        }
    }
    File.close();
    if (found=false)
    cout<<"\n\nRecord Not Found";
}

void intro()
{
    cout<<"\n\n\n\tBANK  MANAGEMENT";
    cout<<"\n\n\n\tSYSTEM ";
    cout<<"\n\n\n\tMADE BY : MBAH JAVIS(JASNIFF)";
    cout<<"\n\n\n\tSCHOOL : G.B.H.S BAMENDA";
    cin.get();

}






