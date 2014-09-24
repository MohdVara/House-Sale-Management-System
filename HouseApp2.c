#include<stdio.h>
#include<string.h>
#include<windows.h>
/* 		Struct Declaration Area			*/
typedef struct HouseDetails
{
	char Title[30];                            //Title Given To The House
    float HousePrice;                            //Price in RM
	int HouseNumber;                           //House Number Shown
	char RoadName[30],City[30],StateName[30];int Postcode;//Address                           
	char OwnershipStatus[30];                     //Ownership Status
	int NumRooms;                                 //Number Of Rooms in House
	int NumToilets;                               //Number Of Toilets
	float Size;                                   //Size in square feet
	char TypeOfLandscape[100];                     //Type Of Landscape
	char Speciality[250];                         //Other essential info
}House;

typedef struct RealEstateStatus
{
        int NumOfHouses;                  //Total Number Of Houses In Database
        float HighestPrice;                 //Most expensize house in database
        float LowestPrice;                  //Most cheapest house in database
        float MedianPrice;                  //Average house price
}RealEstateStatus;
/*		End Struct Declaration Area		*/


/* 		Function Declaration Area		*/       			
House AddHouseNDetails(int);                 		//Add House Detail To Database                     //List Houses That Are In Database               
void ShowHouseDetails(House,int);                 	//Display House Info
void DisplayStats();                      			//Display Real Estate Status                  
int Verify();
void clear_screen();
/*		End Function Declaration Area	*/

/*RunTime Variables*/

int x,AddHouse,ShowHD,DelHD,Stop,valid,TempHigh,TempLow;
int NumOfHouses;
char Username[20];
RealEstateStatus StatsDB;


int main()
{
	/*Load important information*/
	FILE *RealEstateDataFile;
    FILE *HouseRecordDatabase;
    FILE *STOREFILE;
	FILE *APPDATA;
    //Load All Important Info
    RealEstateDataFile=fopen("RealEstateDataFile.happ","r");
    if(RealEstateDataFile==NULL)
    {
    	printf("Installing important files needed\n");
    	RealEstateDataFile=fopen("RealEstateDataFile.happ","w");
    	
		StatsDB.NumOfHouses=0;
		StatsDB.HighestPrice=0;
		StatsDB.LowestPrice=0;
		StatsDB.MedianPrice=0;
    	
    	fwrite(&StatsDB,sizeof(RealEstateStatus),1,RealEstateDataFile);
    	fclose(RealEstateDataFile);
    	HouseRecordDatabase=fopen("HouseDatabase.happ","w");
    	fclose(RealEstateDataFile);
    	printf("\nThe app must shutdown to finish installation");
    	printf("\nReopen app in to use it");
    	printf("Press enter to shutdown");
    	fseek(stdin,0,SEEK_END);
		getchar();
		return 0;
	}

		fread(&StatsDB,sizeof(RealEstateStatus),1,RealEstateDataFile);
		HouseRecordDatabase=fopen("HouseDatabase.happ","r");
		if(HouseRecordDatabase==NULL)
		{
			printf("Error:Database is missing!!!\nDelete RealEstateDataFile.happ to initializa state\n");
			printf("\nReinstall app");
			fseek(stdin,0,SEEK_END);
			getchar();
			return 0;
		}
			
			NumOfHouses=StatsDB.NumOfHouses+10;
			
			House RunHouseDatabase[NumOfHouses];
		
			for (x=0;x<StatsDB.NumOfHouses;x++)
			{
				fread(&RunHouseDatabase[x],sizeof(House),1,HouseRecordDatabase);
				printf("\nHouse %d title : %s has been read\n",x+1,RunHouseDatabase[x].Title);
			}
			printf("\n\nPreferences Loaded\n");
			fclose(HouseRecordDatabase);
			printf("Press enter to continue");
			getchar();fseek(stdin,0,SEEK_SET);
			clear_screen();
	
		    
    /* End Load Information */
    
    
    /* User Menu Options*/
    int UserOption;
    int Verified;
	char Exit;
	Verified=0;
	Exit='N';
	while(!(Exit=='Y'))
	{
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\n\t\t\t House Sale Management System\n");
		printf("\n\t\t\t\t  (H.S.M.S)\n");
		printf("\n-------------------------------------------------------------------------------\n");
		if(Verified==1)
		{printf("Welcome %s\n\n",Username);}
		printf("\nWelcome To House App, Please enter the code for desired command:");
		printf("\n1.List All Houses");
    	printf("\n2.Shows House Detail");
    	printf("\n3.Display Real Estate Status");
    	if(Verified==0)
    	{
			printf("\n4.Login As Administrator");
			printf("\n5.Exit App");
		}
		else
		{
			printf("\n4.Add House");
			printf("\n5.Delete House");
			printf("\n6.Update All Data");
			printf("\n7.Exit App");
			
			printf("\n\nRemember to update all data to save database");
			printf("\nDo not force close program or all saved items will be lost");
		}
		
    	do
    	{
    		printf("\n\n\nCommand: ");scanf("%d",&UserOption);fseek(stdin,0,SEEK_SET);
    	}while((Verified==0)&&(UserOption>5));
    	
    	switch(UserOption)
    	{
    		case 1:
    			if(StatsDB.NumOfHouses==0)
				{	
				clear_screen();
				printf("\nNo data inside database");
				printf("\nPlease contact admin");
				printf("\nPress enter to exit");
				getchar();fseek(stdin,0,SEEK_SET);
				return 0;
				}
				else
				{
					clear_screen();
					printf("The List Of Houses");
					for(x=0;x<StatsDB.NumOfHouses;x++)
					{
						printf("\n\nHouse ID:%d\tHouse Title: %s",x+1,RunHouseDatabase[x].Title);
						printf("\t               City: %s",RunHouseDatabase[x].City);
					}
				printf("\n\n\n\nPress enter to exit to main menu:");
				getchar();fseek(stdin,0,SEEK_SET);
				clear_screen();
				}
			break;
		
			case 2:
			if(StatsDB.NumOfHouses==0)
			{
				clear_screen();
				printf("\nNo data inside database");
				printf("\nPlease contact admin");
				printf("\nPress enter to exit");
				getchar();fseek(stdin,0,SEEK_SET);
				return 0;
			}
			else
			 {
			 	clear_screen();
				printf("HouseID\t\tTitle");
				for(x=0;x<StatsDB.NumOfHouses;x++)
				{
					printf("\n%d.  \t\t%s",x+1,RunHouseDatabase[x].Title);
				}
				do
				{
					printf("\nEnter House ID: ");scanf("%d",&ShowHD);fseek(stdin,0,SEEK_SET);
				}while(ShowHD>NumOfHouses+1);
				ShowHouseDetails(RunHouseDatabase[ShowHD-1],ShowHD);
				printf("\n\n\n\nPress enter to exit to main menu:");
				getchar();fseek(stdin,0,SEEK_SET);
				clear_screen();
			}	
			break;
		
			case 3:
			clear_screen();
			DisplayStats();
			printf("\n\n\n\nPress enter to exit to main menu:");
			getchar();fseek(stdin,0,SEEK_SET);
			clear_screen();
			break;
		
			case 4:
			if(Verified==0)
			{
				Verified=Verify();
			}
			else
			{
				clear_screen();
				do	
				{
					printf("Add how many houses?(less than 10): ");scanf("%d",&AddHouse);fseek(stdin,0,SEEK_SET);
				}while(AddHouse>10);
	
				for(x=0;x<AddHouse;x++)
				{
					RunHouseDatabase[x+StatsDB.NumOfHouses]=AddHouseNDetails(x+StatsDB.NumOfHouses);
				}
				StatsDB.NumOfHouses=StatsDB.NumOfHouses+AddHouse;	
				printf("\n\n\n\nPress enter to exit to main menu:");
				getchar();fseek(stdin,0,SEEK_SET);
				clear_screen();
				
			}
			break;
		 
			case 5:
			if(Verified==0)
			{
				printf("Are you sure you want to close this app[case sensitive](Y/N): ");
				scanf("%c",&Exit);fseek(stdin,0,SEEK_SET);
				if(Exit=='Y')
				{
					return 0;
				}
				clear_screen();
			}
			else
			{
				clear_screen();
				printf("Enter House ID: ");scanf("%d",&DelHD);
     			strcpy(RunHouseDatabase[DelHD-1].Title,"NULL");
     			for(x=0;x<StatsDB.NumOfHouses;x++)
     			{
     	
     				if(strcmp(RunHouseDatabase[x].Title,"NULL")==0)
     				{
     					Stop=x;
     					break;
     				}
     				else
		 			{
		 				RunHouseDatabase[x]=RunHouseDatabase[x];
			 		}
     			}
     			for(x=Stop;x<StatsDB.NumOfHouses;x++)
     			{
     				RunHouseDatabase[x]=RunHouseDatabase[x-1];
     			}	
     			StatsDB.NumOfHouses=StatsDB.NumOfHouses-1;
     			printf("\n\n\n\nPress enter to exit to main menu:");
			getchar();fseek(stdin,0,SEEK_SET);
			clear_screen();
			}
			
			break;
			
			case 6:
	 		STOREFILE=fopen("HouseDatabase.happ","w");
	 		APPDATA=fopen("RealEstateDataFile.happ","w");
	 		if(STOREFILE==NULL)
	 		{
	 			printf("HouseDatabase.happ is missing, close and reopen app for setup");
	 		}
	 		else
	 		{
	 			for(x=0;x<StatsDB.NumOfHouses;x++)
	 			{
	 				TempHigh;
	 				if(TempHigh<RunHouseDatabase[x].HousePrice)
	 				{
					 	TempHigh=RunHouseDatabase[x].HousePrice;
					}
					StatsDB.HighestPrice=TempHigh;
	 				TempLow=1000000000;
	 				if(TempLow>RunHouseDatabase[x].HousePrice)
					{
						TempLow=RunHouseDatabase[x].HousePrice;
					}
					StatsDB.LowestPrice=TempLow;
					
					if(StatsDB.NumOfHouses==0)
					{
						StatsDB.HighestPrice=0;
						StatsDB.LowestPrice=0;
						StatsDB.MedianPrice=0;
					}
						 			
	 			}
	 			for(x=0;x<StatsDB.NumOfHouses;x++)
	 			{
	 				fwrite(&RunHouseDatabase[x],sizeof(House),1,STOREFILE);
	 				printf("HouseID: %d stored sucesssfully",x+1);
	 			}
	 			printf("\nAll houses saved sucessfully");
	 	
	 			fwrite(&StatsDB,sizeof(RealEstateStatus),1,APPDATA);
	 			printf("\nApp Data saved successfully");
	 		}
	 		printf("\n\n\n\nPress enter to exit to main menu:");
			getchar();fseek(stdin,0,SEEK_SET);
			clear_screen();
			break;
			case 7:
				printf("Are you sure you want to close this app[case sensitive](Y/N): ");
				scanf("%c",&Exit);
				if(Exit=='Y')
				{
					return 0;
				}
				clear_screen();
			break;
			}
    clear_screen();}	
	}	/* End User Menu Option*/  


House AddHouseNDetails(int a)
{
		House Home;
      	printf("\n\n         HouseID : %d Details\n",a+1);
      	printf("     House Title : ");fgets(Home.Title,30,stdin);fseek(stdin,0,SEEK_SET);
      	printf("     House Price : ");scanf("%f",&Home.HousePrice);fseek(stdin,0,SEEK_SET);
      	printf("     House Number: ");scanf("%d",&Home.HouseNumber);fseek(stdin,0,SEEK_SET);
      	printf("     Street Name : ");fgets(Home.RoadName,30,stdin);fseek(stdin,0,SEEK_SET);
      	printf("        Area Name: ");fgets(Home.City,30,stdin);fseek(stdin,0,SEEK_SET);
      	printf("         Postcode: ");scanf("%d",&Home.Postcode);fseek(stdin,0,SEEK_SET);
      	printf("       State Name: ");fgets(Home.StateName,30,stdin);fseek(stdin,0,SEEK_SET);
      	printf(" Ownership Status: ");fgets(Home.OwnershipStatus,30,stdin);fseek(stdin,0,SEEK_SET);
      	printf("  Number Of Rooms: ");scanf("%d",&Home.NumRooms);fseek(stdin,0,SEEK_SET);
      	printf("Number Of Toilets: ");scanf("%d",&Home.NumToilets);fseek(stdin,0,SEEK_SET);
      	printf("        Size(f^2): ");scanf("%f",&Home.Size);fseek(stdin,0,SEEK_SET);
      	printf("Type Of Landscape: ");fgets(Home.TypeOfLandscape,100,stdin);fseek(stdin,0,SEEK_SET);
      	printf("Speciality(under 40 words):\n");fgets(Home.Speciality,250,stdin);fseek(stdin,0,SEEK_SET);
      	printf("\nHouseID: %d added to the database\n\n",a+1);
      	
      	return Home;
}

void ShowHouseDetails(House Home,int a)
{
      
      printf("\n   House ID : %d ",a);
      printf("\nHouse Title : %s ",Home.Title);
      printf("\nHouse Price : RM%.2f\n",Home.HousePrice);
      printf("\nAddress: %d,%s,%s,%d,%s",Home.HouseNumber,Home.RoadName,Home.City,Home.Postcode,Home.StateName);
      printf("\n Ownership Status: %s",Home.OwnershipStatus);
      printf("\n  Number Of Rooms: %d",Home.NumRooms);
      printf("\nNumber Of Toilets: %d",Home.NumToilets);
      printf("\n        Size(f^2): %.3f\n",Home.Size);
      printf("\nType Of Landscape(under 20 words):\n %s",Home.TypeOfLandscape);
      printf("\nSpeciality(under 50 words):\n %s",Home.Speciality);
}

void DisplayStats()  
{
     printf("\n\nReal Estate Status Of Database");
     printf("\nNumber Of Houses Listed: %d",StatsDB.NumOfHouses);
     printf("\n   Highest Price Listed: %.2f",StatsDB.HighestPrice);
     printf("\n    Lowest Price Listed: %.2f",StatsDB.LowestPrice);
}


int Verify()
{
	int Verified;
	FILE *AccountLog;
	char UsernameFile[20];
	char Password[20];char PasswordFile[20];
	AccountLog=fopen("AccLog.happ","r");
	if(AccountLog==NULL)
	{
		printf("\nPlease create a AccLog.happ and insert your username and password seperated by ONE space in the same line");
		printf("\nPress enter to go back to the main menu");
		getchar();fseek(stdin,0,SEEK_SET);
	}
	else
	{
		fscanf(AccountLog,"%s",UsernameFile);
		fscanf(AccountLog,"%s",PasswordFile);
		while(valid!=1)
		{
			printf("\n\nEnter your username: ");scanf("%s",Username);fseek(stdin,0,SEEK_SET);
			printf("Enter your password: ");scanf("%s",Password);fseek(stdin,0,SEEK_SET);
	
			if((strcmp(Username,UsernameFile)==0)&&(strcmp(Password,PasswordFile)==0))
			{
				clear_screen();
				valid=1;
				Verified=1;
			}
			else
			{
				printf("\n\nPlease input the correct username or password");
			}	
		}
	}
	return Verified;
}

void clear_screen()
{
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}

