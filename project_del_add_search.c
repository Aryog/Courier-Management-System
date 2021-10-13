#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<unistd.h>


struct log 
{

    char username[15];
    char password[16];

};



struct user
{
    int id;
    char s_name[25];
    char s_address[25];
    char s_phone[10];
    char s_email[25];
    char r_name[25];
    char r_address[25];
    char r_phone[10];
    char r_email[25];
};



void createuser()
{
    FILE *fp;
	struct user users;

	// Open for binary writing
	fp=fopen("customer_record.txt","ab+");
	if (!fp) {
		printf("Unable to open file!");
	}
    char ch;
	// Just write records that you want to implement
    do 
    {
        printf("Enter Id: ");
        scanf("%d",&users.id);
        printf("Enter Sender's Name: ");
        scanf("%s",users.s_name);
        fflush(stdin);
        printf("Enter Sender's Address: ");
        scanf("%s",users.s_address);
        fflush(stdin);
        printf("Enter Sender's Phone Number:");
        scanf("%s",users.s_phone);
        fflush(stdin);
        printf("Enter Sender's Email: ");
        scanf("%s",users.s_email);
        fflush(stdin);
        printf("Enter Reciever's Name: ");
        scanf("%s",users.r_name);
        fflush(stdin);
        printf("Enter Reciever's Address: ");
        scanf("%s",users.r_address);
        fflush(stdin);
        printf("Enter Reciever's Phone Number:");
        scanf("%s",users.r_phone);
        fflush(stdin);
        printf("Enter Reciever's Email: ");
        scanf("%s",users.r_email);
        fflush(stdin);
        fwrite(&users,sizeof(users),1,fp);
        printf("Enter Y/N to add another client!");
        fseek(stdin,0,SEEK_END);
        scanf("%c",&ch);
    }while(ch=='y' || ch=='Y');
    rewind(fp);
    fclose(fp);
    char c;
    fflush(stdin);
    printf("\nEnter b to move back: ");
    scanf("%c",&c);
    if(c=='b')
    {
        menu2();
    }
    else
    {
        createuser();
    }
}




void search()
{

    FILE *fp;
    struct user cus;
    int uid;
    int count = 0;

    fp = fopen("customer_record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error while opening the file");
    }

    fflush(stdin);

    printf("\nSearch the customer records\n");

    printf("Please enter the unique Id of customer\n");
    scanf("%d",&uid);
    while (fread(&cus, sizeof(cus), 1, fp) > 0 && count == 0)
    {
        if (cus.id==uid)
        {
            count = 1;
            printf("Record found\n");
            printf(" Sender's Name = %s \n", cus.s_name);
            printf(" Sender's Phone number = %s \n", cus.s_phone);
            printf(" Sender's Address = %s \n", cus.s_address);
            printf(" Sender's Email = %s \n\n\n", cus.s_email);

            printf(" Receiver Name = %s \n", cus.r_name);
            printf(" Receiver Phone number = %s \n", cus.r_phone);
            printf(" Receiver Address = %s \n", cus.r_address);
            printf(" Receiver Email = %s \n", cus.r_email);
        }
    }

    if (count == 0)
    {
        printf("NO Match Found");
    }
    fclose(fp);
    fflush(stdin);
    char c;
    printf("\nEnter b to move back: ");
    scanf("%c",&c);
    if(c=='b')
    {
        menu2();
    }
    else
    {
        search();
    }
}




void todelete()
{
    int uid;
    printf("Please give the Sender's Unique ID to delete the successful delivery: ");
    scanf("%d",&uid);
    fflush(stdin);
    FILE *fptr,*fptr1;
    struct user u;
    fptr=fopen("customer_record.txt","rb+");
    fptr1=fopen("temp.txt","ab+");
    int found=0;
    while (fread(&u,sizeof(u),1,fptr))
    {
        fflush(stdin);
        if (u.id==uid)
        {
            printf("Record found and deleted successfully!");
            found=1;
        }
        else{
            fwrite(&u,sizeof(u),1,fptr1);
        }
    }
    if(!found)
    printf("record was not found to delete.");
    rewind(fptr);
    fclose(fptr);
    fclose(fptr1);
    remove("customer_record.txt");
    //rename("required_file,to_be_deleted_file")
    rename("temp.txt","customer_record.txt");
    char c;
    fflush(stdin);
    printf("\nEnter b to move back: ");
    scanf("%c",&c);
    if(c=='b')
    {
        menu2();
    }
    else
    {
        todelete();
    }
}




void SignUp()
{
    FILE *fp;
    fp = fopen("operators.txt","ab+");
    struct log l;
    char uname[15];
    char pass[16];
    printf("Enter the UserName:");
    scanf("%s",uname);
    strcpy(l.username,uname);
    printf("Enter the Password:");
    scanf("%s",pass);
    strcpy(l.password,pass);
    fwrite(&l,sizeof(l),1,fp);
    rewind(fp);
    fclose(fp);
    printf("Account Created Successfully!\n");
    printf("Please Login!");
    sleep(2);
    menu1();
}


void menu2()
{
    system("cls");
    printf("WELCOME TO THE DASHBOARD!\n");
    printf("Enter a number of following selection.\n");
    int n;
    printf("1-> Create New User\n2-> Delete Existing User\n3-> Search For User\n0-> Main Panel\n");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        createuser();
        break;
    case 2:
        todelete();
        break;
    case 3:
        search();
        break;
    default:
        menu1();
        break;
    }
}

void Login()
{
    FILE *fp;
    fp = fopen("operators.txt","rb+");
    struct log l;
    char uname[15];
    char pass[16];
    printf("UserName:");
    scanf("%s",uname);
    printf("Password:");
    scanf("%s",pass);
    fflush(stdin);
    int found = 0;
    while (fread(&l,sizeof(l),1,fp)>0)
    {
        if((strcmp(l.username,uname)==0) && (strcmp(l.password,pass)==0))
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        menu2();
    }
    else
    {
        char c;
        printf("Enter b/a to move back and try again respectively:");
        fflush(stdin);
        scanf("%c",&c);
        if(c=='b')
        {
            menu1();
        }
        else
        {
            printf("Enter the verified credentials.");
            Login();
        }
    }
}

void menu1()
{
    system("cls");
    int n = 0;
    printf("Enter a number of following selection.\n");
    printf("1-> SignUp Panel\n2-> Login Panel\n0-> Exit\n");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        SignUp();
        break;
    case 2:
        Login();
        break;
    default:
        printf("Exiting.......!");
        break;
    }
}



int main()
{
    menu1();
    return 0;
}
