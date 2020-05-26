//Aryaman Singh
//Banking Project

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

void main();

int GlobalCounter; /* 	Assigning Roll No. Values.
			The value is assigned by opening the last object in .dat
			Initialisation done in main()
		   */

class Account  //Main Class holding information for each Student
{
	int AccNo;
	char name[100];
	char Gender;
	double Amount;
	int Points;  	//Reward Points
	int pin;

	public:
		void getdata()  //Input Function
		{																																												do {
			cout << "Enter Name: ";
			gets(name);
			} while (strlen(name) < 2);

			do {
			cout << "Enter Gender(M/F): ";
			cin >> Gender;
			} while (Gender != 'M' && Gender != 'F');

			do {
			cout << "Enter Initial Amount: ";
			cin >> Amount;
			} while (Amount < 0);

			randomize();
			pin = 1000 + random(9000);

			cout << "\nPin is: " << pin;

			Points = 0;
			AccNo = GlobalCounter;
			GlobalCounter++;
		}

		void showdata() //Output Function
		{
			cout << "\nName: " << name;
			cout << "\nAccount No. " << AccNo;
			cout << "\nGender: " << Gender;
			cout << "\nAmount: " << Amount;
			cout << "\nReward Points: " << Points;
			cout << "\nPin: " << pin;

		}

		int ret_AccNo()
		{
			return AccNo;
		}

		int ret_Points()
		{
			return Points;
		}

		int ret_pin()
		{
			return pin;
		};

		char* ret_name()
		{
			return name;
		}

		void deposit()
		{
			fstream f1;
			f1.open("Trans.txt", ios::out | ios::app);

			if (!f1)
			{
				cout << "Error! File not found,";
				getch();
				exit(1);
			}

			double temp;
			cout << "Enter Amount to be deposited: ";
			cin >> temp;
			Amount += temp;

			Points += temp/100;

			//TIME
			time_t tt;
			struct tm * ti;
			time (&tt);
			ti = localtime(&tt);

			f1 << "\n-------------------------";
			f1 << endl << asctime(ti);
			f1 << "\nDEPOSIT";
			f1 << "\nName: " << name;
			f1 << "\nAccount No: " << AccNo;
			f1 << "\nAmount: " << temp;

			cout << "\nNew Amount: " << Amount;
			cout << "\n\nPoints Earned: " << temp/100;
			cout << "\nCurrent Points: " << Points;

			f1.close();
		}

		void withdraw()
		{
			fstream f1;
			f1.open("Trans.txt", ios::out | ios::app);

			double temp;
			cout << "Enter Amount to Withdraw: ";
			cin >> temp;
			Amount -= temp;


			//TIME
			time_t tt;
			struct tm * ti;
			time (&tt);
			ti = localtime(&tt);

			f1 << "\n-------------------------";
			f1 << endl << asctime(ti);
			f1 << "\nWITHDRAWAL";
			f1 << "\nName: " << name;
			f1 << "\nAccount No: " << AccNo;
			f1 << "\nAmount: " << temp;


			cout << "\nNew Amount: " << Amount;
			Points++;
			cout << "\nCurrent Points: " << Points;
		}

		void redPoints(int a)
		{
			Points -= a;
			cout << "\nNew Points:" << Points;
		}


};

void addtofile()
{
	clrscr();

	Account i1;
	fstream f1;
	f1.open("BankAcc.dat", ios::binary | ios::app);

	if (!f1)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Input
	char choice = 'Y';
	do {
		i1.getdata();
		f1.write((char *)&i1, sizeof(i1)); //Writing to file

		cout << "\nContinue? (Y/N): ";
		cin >> choice;
	} while(choice == 'Y');

	f1.close();
}

void displayfile()
{
	clrscr();

	Account i2;
	fstream f2;
	f2.open("BankAcc.dat", ios::binary | ios::in);

	if (!f2)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Output
	int counter = 0;
	while(f2.read((char *)&i2, sizeof(i2)))
	{
		//Reading file
		i2.showdata();
		cout << endl;
		counter++;
		if (counter == 3)
		{
			cout << "\nPress Any Key for Next Page...";
			getch();
			counter = 0;
			clrscr();
		}
	}

	f2.close();
}

void displayfileAccNo()
{
	clrscr();

	//Input of what Account No. to Display
	int test;
	cout << "\nEnter Account No.: ";
	cin >> test;

	Account i2;
	fstream f2;
	f2.open("BankAcc.dat", ios::binary | ios::in);

	if (!f2)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Output
	while(f2.read((char *)&i2, sizeof(i2)))
	{
		//Reading file
		if (i2.ret_AccNo() == test)
		{
			i2.showdata();
			cout << endl;
		}
	}

	f2.close();
}

void displayfileAccNo(Account i1) //Parameterised, for Customer Mode
{
	clrscr();

	Account i2;
	fstream f2;
	f2.open("BankAcc.dat", ios::binary | ios::in);

	if (!f2)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Output
	while(f2.read((char *)&i2, sizeof(i2)))
	{
		//Reading file
		if (i2.ret_AccNo() == i1.ret_AccNo())
		{
			i2.showdata();
			cout << endl;
		}
	}

	f2.close();
}

void displayfilename()
{
	clrscr();

	//Input
	char test[100];
	cout << "\nEnter Name: ";
	gets(test);

	Account i2;
	fstream f2;
	f2.open("BankAcc.dat", ios::binary | ios::in);

	if (!f2)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Output
	while(f2.read((char *)&i2, sizeof(i2)))
	{
		//Reading file
		if (strcmp(i2.ret_name(), test) == 0)
		{
			i2.showdata();
			cout << endl;
		}
	}

	f2.close();
}

void transaction(Account i1)
{

	int flag = 0;
	Account i2;
	fstream f1;
	fstream f2;

	f1.open("BankAcc.dat", ios::binary | ios::in);
	f2.open("Temp.dat", ios::binary | ios::out);


	if(!f1 || !f2)
	{
		cout << "Error!";
		exit(1);
	}

	char choice;
	cout << "\nEnter W for Withdrawal, and D for Deposit: ";
	cin >> choice;
	while(f1.read((char *)&i2, sizeof(i2)))
	{
		if(i1.ret_AccNo() == i2.ret_AccNo())
		{
			if (choice == 'W')
				i2.withdraw();
			else if (choice == 'D')
				i2.deposit();
			else
				cout << "Invalid Choice!";

			f2.write((char *)&i2, sizeof(i2));
			flag++;
		}
		else
			f2.write((char *)&i2, sizeof(i2));

	}

	f1.close();
	f2.close();

	if (flag == 0)
		cout << "\nRecord Not Found.";


	remove("BankAcc.dat");
	rename("Temp.dat", "BankAcc.dat");

}

void del_record()
{
	clrscr();
	int check;
	int flag = 0;
	cout << "\nEnter Record to delete: ";
	cin >> check;
	Account i2;
	fstream f1;
	fstream f2;
	f1.open("BankAcc.dat", ios::binary | ios::in);
	f2.open("Temp.dat", ios::binary | ios::out);

	if(!f1 || !f2)
	{
		cout << "Error!";
		exit(1);
	}

	while(f1.read((char *)&i2, sizeof(i2)))
	{
		if(i2.ret_AccNo() != check)
		{
			f2.write((char *)&i2, sizeof(i2));
		}
		else
			flag++;
	}

	f1.close();
	f2.close();

	if (flag == 0)
		cout << "\nRecord Not Found.";
	else
		cout << flag << " record(s) deleted.";

	remove("BankAcc.dat");
	rename("Temp.dat", "BankAcc.dat");

}

void update_record()
{

	int check;
	int flag = 0;
	cout << "\nEnter Record to update: ";
	cin >> check;
	Account i2;
	fstream f1;
	fstream f2;
	f1.open("BankAcc.dat", ios::binary | ios::in);
	f2.open("Temp.dat", ios::binary | ios::out);

	if(!f1 || !f2)
	{
		cout << "Error!";
		exit(1);
	}

	while(f1.read((char *)&i2, sizeof(i2)))
	{
		if(i2.ret_AccNo() == check)
		{
			i2.getdata();
			f2.write((char *)&i2, sizeof(i2));
			flag++;
		}
		else
			f2.write((char *)&i2, sizeof(i2));

	}

	f1.close();
	f2.close();

	if (flag == 0)
		cout << "\nRecord Not Found.";
	else
		cout << flag << " record(s) updated.";

	remove("BankAcc.dat");
	rename("Temp.dat", "BankAcc.dat");

}

void redeem(Account i1)
{
	randomize();

	Account i2;
	int flag = 0;
	fstream f1;
	fstream f2;
	f1.open("BankAcc.dat", ios::binary | ios::in);
	f2.open("Temp.dat", ios::binary | ios::out);

	if(!f1 || !f2)
	{
		cout << "Error!";
		exit(1);
	}

	int choice;
	cout << "\nOPTIONS:";
	cout << "\n 1. Flipkart Voucher (Rs. 500): 100 Points";
	cout << "\n 2. Amazon Voucher (Rs. 499): 99 Points";
	cout << "\n 3. BookMyShow Free Ticket: 50 Points";

	cout << "\nEnter Choice: ";
	cin >> choice;

	while(f1.read((char *)&i2, sizeof(i2)))
	{
		if(i2.ret_AccNo() == i1.ret_AccNo())
		{
			cout << "\n\nCurrent Points: " << i2.ret_Points();

			switch (choice)
			{
				case 1:
					if (i2.ret_Points() >= 100)
					{
						i2.redPoints(100);

						cout << "\n\nCongratulations! \nYour Voucher Code is: " << (char)(65 + random(26)) << random(10000);
					}
					else
						cout << "\nNot Enough Points!";
					break;
				case 2:
					if (i2.ret_Points() >= 99)
					{
						i2.redPoints(99);
						cout << "\n\nCongratulations! \nYour Voucher Code is: " << random(10000);
					}
					else
						cout << "\nNot Enough Points!";
					break;
				case 3:
					if (i2.ret_Points() >= 50)
					{
						i2.redPoints(50);
						cout << "\n\nCongratulations! \nYour Voucher Code is: " << random(10000);
					}
					else
						cout << "\nNot Enough Points!";
					break;

				default: cout << "Invalid Choice!";

			}
			f2.write((char *)&i2, sizeof(i2));
			flag++;
		}
		else
			f2.write((char *)&i2, sizeof(i2));

	}

	f1.close();
	f2.close();

	if (flag == 0)
		cout << "\nRecord Not Found.";

	remove("BankAcc.dat");
	rename("Temp.dat", "BankAcc.dat");

}

void readTrans()
{
	clrscr();

	fstream f1;

	f1.open("Trans.txt", ios::in);

	if (!f1)
	{
		cout << "Error! File not found.";
		getch();
		exit(1);
	};

	char ch[25];
	while(f1)
	{
		f1.getline(ch, 25);

		cout << endl << ch;
	};
	f1.close();
};

void server()
{

	clrscr();
	int choice;

	//Time
	time_t tt;
	struct tm * ti;
	time (&tt);
	ti = localtime(&tt);
	cout << asctime(ti);

	cout << "Current Acc No. Position: " << GlobalCounter;
	cout << "\n1. Create a Record \n2. Display All Records";
	cout << "\n3. Display Record (Account No.) \n4. Display Record (Name)";
	cout << "\n5. Delete Record \n6. Update Record \n7. Read Transaction File";
	cout << "\n8. Main Menu \n9. Exit";

	cout << "\n\nEnter: ";
	cin >> choice;

	switch (choice)
	{
		case 1: addtofile();
			break;
		case 2: displayfile();
			break;
		case 3: displayfileAccNo();
			break;
		case 4: displayfilename();
			break;
		case 5: del_record();
			break;
		case 6: update_record();
			break;
		case 7: readTrans();
			break;
		case 8: cout << "Exiting Server Mode...";
			getch();
			main();
			break;
		case 9: cout << "Thank you for using this program!";
			getch();
			exit(0);
		default: cout << "Oops! Try Again.";
			 getch();
			 server();
	}

	getch();
	server();
}

void customer(int test, int inpin)
{
	clrscr();

	cout << "\n\t\t\t      PEARSON BANKING DATABASE   ";
	cout << "\n\t\t\t ---------------------------------- \n";

	int flag = 0;

	Account i2;
	fstream f2;
	f2.open("BankAcc.dat", ios::binary | ios::in);

	if (!f2)
	{
		cout << "File can not be opened!";
		exit(1);
	}

	//Output
	while(f2.read((char *)&i2, sizeof(i2)))
	{
		//Reading file
		if ((i2.ret_AccNo() == test) && (i2.ret_pin() == inpin))
		{
			flag = 1;
			break;
		}
		else if ((i2.ret_AccNo() == test) && (i2.ret_pin() != inpin))
		{
			cout << "Incorrect Pin! Try Again.";
			getch();
			main();
		}
	}

	if (flag == 0)
	{
		clrscr();

		cout << "\n\n\t\t\t\tAccount Not Found!";
		getch();
		main();
	}

	int choice;

	cout << "\n\t\t\t     Welcome, " << i2.ret_name() << "!\n";

	cout << "\n\t\t\t   |  Enter 1 for Transactions  | " << endl;
	cout << "\n\t\t\t   |  Enter 2 to Redeem Points  | " << endl;
	cout << "\n\t\t\t   |  Enter 3 to Display Info   | " << endl;
	cout << "\n\t\t\t   |   Enter 4 for Main Menu    | " << endl;
	cout << "\n\t\t\t   |      Enter 5 to Exit       | " << endl;
	cout << "\n\t\t\t             Enter: ";
	cin >> choice;

	clrscr();

	switch (choice)
	{
		case 1: transaction(i2);
			break;
		case 2: redeem(i2);
			break;
		case 3: displayfileAccNo(i2);
			break;
		case 4: cout << "Exiting Customer Mode...";
			getch();
			f2.close();
			main();
			break;
		case 5: cout << "\n\n\t\tThank you for using this program!";
			getch();
			f2.close();
			exit(0);
		default: cout << "\n\n\t\t\tOops! Try Again.";
			 getch();
			 customer(test, inpin);
	}
	getch();
	customer(test, inpin);

}

void about()
{
	clrscr();

	char head[] = "\n\t\t\t\t\t ABOUT \n\t\t\t\t\t======= ";

	int i = 0;
	while ( head[i] != '\0')
	{
		cout << head[i];
		delay(50);
		i++;
	};

	delay (1500);
	cout << "\nThis program was developed by Aryaman Singh (12 E). \n\nIt's purpose is to simulate how a Bank Program would work.";
	delay(500);
	cout << "\nIt involves two parts - (1) The Server Side, and (2) The Customer Side.";
	delay(500);
	cout << "\n\nWhen you login to the Server, you can add, view, edit and delete new accounts.\n This is done through a .dat file that stores the required infromation.";
	delay(500);
	cout << "\n The password is \"pass\". ";
	delay(500);
	cout << "\n\nWhen you login as a Customer, you will need to enter your Account Number. After that, you can withdraw/deposit money, redeem points for vouchers, and view your data.";
	delay(500);
	cout << "\n\nIn addition to this, the program also stores a transaction ledger as .txt file \nin the BIN folder.";
	delay(1000);
	cout << "\n\n\t\t  | Press Any Key to return to the Main Menu |";
	getch();
}


void main()
{
	clrscr();
	//Initializing Global Counter
	fstream f1;
	Account i1;
	f1.open("BankAcc.dat", ios::binary | ios::in);
	if (!f1)
		GlobalCounter = 1000; //If Database is opened for the first time, Roll No. start from 1000
	else
	{
		while (f1.read((char *)&i1, sizeof(i1))); //Else, Roll No is taken from last object in .dat
		GlobalCounter = i1.ret_AccNo() + 1;
	}
	f1.close();

	//Figure

	int   driver = DETECT,mode;
	int   x[10],y[10];
	int   x_center = 330, y_center = 180, rad = 100;
	int   i,j;

	/*

	initgraph(&driver,&mode,"c:\\tc\\bgi");

	for ( i = 0; i < 10; i++ )
	{
		x[i] =  x_center + rad *  cos(36*i*3.14159/180);
		y[i] =  y_center + rad *  sin(36*i*3.14159/180);
	}

	for (i = 0; i < 10; i++ )

		for ( j = 0; j < 10; j++ )
		{
			delay(10);
			line(x[i],y[i],x[j],y[j]);
		}
	*/
	cout << "\n\t\t\t WELCOME TO PEARSON BANKING DATABASE   ";

	cout << "\n\t\t\t ----------------------------------- \n";


	char CS;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	cout << "\n\t\t\t     |   Enter A for About    | " << endl;
	cout << "\n\t\t\t     |  Enter C for Customer  | " << endl;
	cout << "\n\t\t\t     |   Enter S for Server   | " << endl;
	cout << "\n\t\t\t     |    Enter E to Exit     | " << endl;
	CS = getch();



	if (CS == 'S' || CS == 's')
	{
		closegraph();
		clrscr();
		char inpass[5];
		cout << "\n\n\n\t\t\tEnter Password: ";
		for (int k = 0; k < 4; k++)
		{
			inpass[k] = getch();
			cout << "*";
		}

		inpass[4] = '\0';

		if (strcmp(inpass, "pass") == 0)
		{
			server();
		}
		else
		{
			cout << "\nIncorrect Password!";
			getch();
			main();
		}
	}
	else if (CS == 'C' || CS == 'c')
	{
		closegraph();
		clrscr();
		int ac;
		int test;

		char inpin[4];
		int pin;
		cout << "\n\t\t\tEnter Account No: ";
		cin >> ac;

		char c;
		cout << "\n\t\t\tEnter Pin: ";
		for (int k = 0; k < 4; k++)
		{
			inpin[k] = getch();
			cout << "*";

		}
		pin = atoi(inpin);

		getch();

		customer(ac, pin);
	}

	else if (CS == 'A' || CS == 'a')
	{
		closegraph();
		delay(1000);
		about();
		main();
	}
	else if (CS == 'E' || CS == 'e')
		exit(0);
	else
	{

		cout << "Oops! Try Again.";
		getch();
		closegraph();
		main();
	}

	closegraph();

}
