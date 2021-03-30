#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Used macro
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "1.bin"
// Macro related to the vehicle info
#define MAX_CHASSI_NUMBER 17
#define MAX_OWNER_NAME 50
#define MAX_OWNER_ADDRESS 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;
//Elements of structure
typedef struct// to call in program
{
    char chassino[MAX_CHASSI_NUMBER]; // declare the integer data type
    char OwnerName[MAX_OWNER_NAME];// declare the charecter data type
    char vehicleName[MAX_OWNER_NAME];// declare the character data type
    char owneraddr[MAX_OWNER_ADDRESS];// declare the character data type
    char vrname[MAX_OWNER_NAME];//vehivel registered name
    Date vehicleRegisterDate;// declare the integer data type
} v;
//Align the message
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//Head message
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Automobile Record Management System Project     ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
//Display message
void welcomeMessage()
{
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Automobile Record           =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
//Validate name
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add Vehicle in list
void AddVehicle()
{
    v vehicleinfo= {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW Vehicle");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tChassi Number  = ");
    fflush(stdin);
    fgets(vehicleinfo.chassino,MAX_CHASSI_NUMBER,stdin);
    do
    {
        printf("\n\t\t\tOwner Name  = ");
        fflush(stdin);
        fgets(vehicleinfo.OwnerName,MAX_OWNER_NAME,stdin);
        status = isNameValid(vehicleinfo.OwnerName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tVehicle registered number  = ");
        fflush(stdin);
        fgets(vehicleinfo.vrname,MAX_OWNER_NAME,stdin);
        
    }
    while(!status);
    do
    {
        printf("\n\t\t\tVehicle Name  = ");
        fflush(stdin);
        fgets(vehicleinfo.vehicleName,MAX_OWNER_NAME,stdin);
        status = isNameValid(vehicleinfo.vehicleName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tOwner Address  = ");
        fflush(stdin);
        fgets(vehicleinfo.owneraddr,MAX_OWNER_ADDRESS,stdin);
        status = isNameValid(vehicleinfo.owneraddr);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&vehicleinfo.vehicleRegisterDate.dd,& vehicleinfo.vehicleRegisterDate.mm,& vehicleinfo.vehicleRegisterDate.yyyy);
        //check date validity
        status = isValidDate(&vehicleinfo.vehicleRegisterDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    fwrite(&vehicleinfo,sizeof(vehicleinfo), 1, fp);
    fclose(fp);
}
// search vehicle
void searchVehicle()
{
    int found = 0;
     int chassi_no[MAX_CHASSI_NUMBER];
    v vehicleinfo= {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH VEHICLES");
    //put the control on student detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Chassi Number to search:");
    fflush(stdin);
    scanf("%u",&chassi_no);
    while (fread (&vehicleinfo, sizeof(vehicleinfo), 1, fp))
    {
        if(vehicleinfo.chassino ==chassi_no)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tChassi Number = %d\n",vehicleinfo.chassino);
        printf("\n\t\t\tVehicle name = %s", vehicleinfo.vehicleName);
        printf("\t\t\tOwner Name = %s", vehicleinfo.OwnerName);
        printf("\t\t\tvehicle registered number = %s", vehicleinfo.vrname);
        printf("\n\t\t\tOwner Address = %s", vehicleinfo.owneraddr);
        printf("\t\t\tVehicle registration date(day/month/year) =  (%d/%d/%d)", vehicleinfo.vehicleRegisterDate.dd,
               vehicleinfo.vehicleRegisterDate.mm, vehicleinfo.vehicleRegisterDate.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// view vehicle function
void viewVehicle()
{
    int found = 0;
    v vehicleinfo= {0};
    FILE *fp = NULL;
    unsigned int countvehicle= 1;
    headMessage("VIEW VEHICLE DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&vehicleinfo, sizeof(vehicleinfo), 1, fp))
    {
        printf("\n\t\t\tVehicle Count = %d\n\n",countvehicle);
        printf("\t\t\tChassi no = %u\n", vehicleinfo.chassino);
        printf("\t\t\tOwner Name = %s", vehicleinfo.OwnerName);
        printf("\t\t\tvehicle Name = %s", vehicleinfo.vehicleName);
        printf("\t\t\tvehicle registered number = %s", vehicleinfo.vrname);
        printf("\t\t\tOwner Address = %s", vehicleinfo.owneraddr);
        printf("\t\t\tVehicle Registration Date(day/month/year) =  (%d/%d/%d)\n\n", vehicleinfo.vehicleRegisterDate.dd,
               vehicleinfo.vehicleRegisterDate.mm, vehicleinfo.vehicleRegisterDate.yyyy);
        found = 1;
        ++countvehicle;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// Delete vehicle entry
void DeleteVehicle()
{
    int found = 0;
    int vehicleDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    v vehicleinfo= {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("Delete Vehicle Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Chassi nmber for delete:");
    scanf("%s",&vehicleDelete);
    while (fread (&vehicleinfo, sizeof(vehicleinfo), 1, fp))
    {
        if(vehicleinfo.chassino!= vehicleDelete)
        {
            fwrite(&vehicleinfo,sizeof(vehicleinfo), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
//function to update credential
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\ttLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
//Display menu
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add New Vehicle info");
        printf("\n\t\t\t2.Search Vehicle");
        printf("\n\t\t\t3.View Registered vehicles");
        printf("\n\t\t\t4.Delete Registered vehicle");
        printf("\n\t\t\t5.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            AddVehicle();
            break;
        case 2:
            searchVehicle();
            break;
        case 3:
            viewVehicle();
            break;
        case 4:
            DeleteVehicle();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
//login password
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//Check file exist or not
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="1234\n";
    const char defaultPassword[] ="1234\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}

