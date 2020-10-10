#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Written by Mr. Koe Shwin
// Contact to koeshwin00@gmail.com if you found any error in this source code 

int option;
char back;
int flag;
char user_file[30];
int password;
long amount;
time_t t;

FILE *fptr;

struct Data
{
    char id[30];
    int password;
    char name[30];
    char fname[30];
    int age;
    char birthday[20];
    char nrc[50];
    char job[20];
    char email[20];
    char ph[10];
    char physical_address[80];
    long total_amount;


}user[12];

void functionlist(void);
void menu(void);
void add_user(void);
void cash_out(void);
void user_info(void);
void cash_in(void);
void change_password(void);
void erase_user(void);
void edit_user(void);
void recent_action(void);

int main()
{
    time(&t);
    system("color DF");
    functionlist();
    menu();
    return main();
}

void functionlist(void)
{
    printf("\n\t\t\t\tAYA ATM MACHINE");
    printf("\n\t\t\t\t===============");
    printf("\n============================================================================================================================================================");
    printf("\n[1]Withdrawl\t[2]Deposit\t[3]Add User\t[4]Edit User\t[5]Erase User\t[6]Change Password\t[7]Info Of User  [8]Recent Actions   [9]Exit Program");
    printf("\n============================================================================================================================================================");

}

void menu(void)
{
    BACK:
    printf("\nEnter command :");
    scanf("%d",&option);
    switch(option)
    {
    case 1:cash_out();break;
    case 2:cash_in();break;
    case 3:add_user();break;
    case 4:edit_user();break;
    case 5:erase_user();break;
    case 6:change_password();break;
    case 7:user_info();break;
    case 8:recent_action();break;
    case 9:exit(0);
    default :
        printf("\nWrong command !");
        goto BACK;
    }

}

void add_user(void)
{
    printf("\n\tAdding User Data");
    printf("\n\t================");

    GO:
    printf("\nEnter Account Number :");
    scanf("%s",&user[0].id);
    printf("\nEnter New Password :");
    scanf("%d",&user[1].password);
    printf("\nEnter Name :");
    fflush(stdin);
    gets(user[2].name);
    printf("\nEnter Father Name :");
    gets(user[3].fname);
    printf("\nEnter Age :");
    scanf("%d",&user[4].age);
    printf("\nEnter Birthday :");
    fflush(stdin);
    gets(user[5].birthday);
    printf("\nEnter NRC :");
    gets(user[6].nrc);
    printf("\nEnter Job:");
    gets(user[7].job);
    printf("\nEnter Email Address :");
    gets(user[8].email);
    printf("\nEnter Phone Number :");
    gets(user[9].ph);
    printf("\nEnter Physical Address :");
    gets(user[10].physical_address);
    printf("\nEnter Total Amount :");
    scanf("%ld",&user[11].total_amount);



    strcpy(user_file,user[0].id);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"w");
    if(fptr==0)
    {
        printf("\nFile Error !");
        printf("\nRecreating The File .........");
        fptr=fopen(user_file,"a");
    }
    fwrite(&user,sizeof(user),1,fptr);
    printf("\nAdded Successfully !");

    fclose(fptr);

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"\n It Added New User named %s and Account Number is %s at %s",user[2].name,user[0].id,ctime(&t));
    fclose(fptr);

    printf("\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;
}

void user_info()
{
    printf("\n\tUser Information ");
    printf("\n\t==================");
    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"r");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }

    while(fread(&user,sizeof(user),1,fptr))
    {
        printf("\nAccount Number :%s",user[0].id);
        printf("\nUser Name :%s",user[2].name);
        printf("\nFather Name :%s",user[3].fname);
        printf("\nAge :%d",user[4].age);
        printf("\nBirthday :%s",user[5].birthday);
        printf("\nNRC :%s",user[6].nrc);
        printf("\nJob :%s",user[7].job);
        printf("\nEmail :%s",user[8].email);
        printf("\nPhone Number:%s",user[9].ph);
        printf("\nPhysical Address :%s",user[10].physical_address);
        printf("\nTotal Amount :%ld Ks",user[11].total_amount);
    }
    fclose(fptr);

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"It Searched Account Number %s at %s",user[0].id,ctime(&t));
    fclose(fptr);

    printf("\nOne More Search (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;

}

void cash_out()
{
    printf("\n\tWithdrawl");
    printf("\n\t========");
    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"r+");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }
    printf("\nEnter The Password :");
    scanf("%d",&password);

    while(fread(&user,sizeof(user),1,fptr))
    {
        printf("\nTotal Amount :%ld Ks",user[11].total_amount);

        if(password==user[1].password)
           {
               printf("\nEnter the Amount To Withdraw :");
               scanf("%ld",&amount);
               user[11].total_amount-=amount;
               printf("\nRemaining Balance :%ld Ks",user[11].total_amount);
               fseek(fptr,0,SEEK_CUR);
               fptr=fopen(user_file,"w");
               fwrite(&user,sizeof(user),1,fptr);
               flag=0;
               if(fptr==0)
                 printf("\nFailed To Cash Out !");
               else
                 printf("\nSuccessfully Cash Out !");
               fclose(fptr);
               break;

           }

    }


    fclose(fptr);
    if(flag)
        printf("\n\aInvalid Password !");

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"It withdrawed %ld Ks from Account Number %s at %s",amount,user[0].id,ctime(&t));
    fclose(fptr);

    printf("\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;


}

void cash_in()
{
    printf("\n\tDeposit");
    printf("\n\t========");
    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"r+");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }
    printf("\nEnter The Password :");
    scanf("%d",&password);

    while(fread(&user,sizeof(user),1,fptr))
    {
        printf("\nTotal Amount :%ld Ks",user[11].total_amount);

        if(password==user[1].password)
           {
               printf("\nEnter the Amount To Deposit :");
               scanf("%ld",&amount);
               user[11].total_amount+=amount;
               printf("\nRemaining Balance :%ld Ks",user[11].total_amount);
               fseek(fptr,0,SEEK_CUR);
               fptr=fopen(user_file,"w");
               fwrite(&user,sizeof(user),1,fptr);
               flag=0;
               if(fptr==0)
                 printf("\nFailed To Cash In !");
               else
                 printf("\nSuccessfully Cash In !");
               fclose(fptr);
               break;

           }

    }


    fclose(fptr);
    if(flag)
        printf("\n\aInvalid Password !");

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"It deposited %ld Ks to Account Number %s at %s",amount,user[0].id,ctime(&t));
    fclose(fptr);

    printf("\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;


}

void change_password()
{
    printf("\n\tChanging Your Password ");
    printf("\n\t=====================");

    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"r+");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }
    printf("\nEnter The Old Password :");
    scanf("%d",&password);

    while(fread(&user,sizeof(user),1,fptr))
    {
        if(password==user[1].password)
        {
            printf("\nEnter The New Password :");
            scanf("%d",&password);
            user[1].password=password;
            fseek(fptr,1,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            flag=0;
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change  !");

            break;
        }
    }
    fclose(fptr);
    if(flag)
        printf("\n\aInvalid Password !");

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"Account Number %s changed password at %s",user[0].id,ctime(&t));
    fclose(fptr);

    printf("\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;


}


void erase_user()
{
    printf("\n\tErasing User Data ");
    printf("\n\t==================");

    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    //remove(user_file);
    fptr=fopen(user_file,"w");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }
    remove(user_file);

    printf("\nErased Successfully !");
    fclose(fptr);
    //printf("\nErased Successfully !");

    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    fprintf(fptr,"Account Number %s was erased at %s",user_file,ctime(&t));
    fclose(fptr);

    printf("\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;


}

void edit_user()
{
    printf("\n\tEditing User Data ");
    printf("\n\t==================");

    char name[30];
    int age;
    char birthday[20];
    char nrc[50];
    char job[20];
    char email[20];
    char ph[10];
    char physical_address[80];

    GO:
    printf("\nEnter The Account Number :");
    fflush(stdin);
    gets(user_file);
    strcat(user_file,".txt");
    fptr=fopen(user_file,"r+");
    if(fptr==0)
    {
        printf("\nFile Error !");
    }

    printf("\n\nWhich Data would you like to edit ?");
    printf("\n(1)Name\t(2)Father Name\t(3)Age\t(4)Birthday\t(5)NRC\t(6)JOB\t(7)Email Address\t(8)Phone Number\t(9)Physical Address");
    printf("\n===========================================================================================================================");

    printf("\nEnter Your Command :");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Name :%s",user[2].name);
            printf("\nEnter New Name :");
            fflush(stdin);
            gets(name);
            strcpy(user[2].name,name);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");


        }
        fclose(fptr);
        break;
    case 2:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Father Name :%s",user[3].fname);
            printf("\nEnter New Father Name :");
            fflush(stdin);
            gets(name);
            strcpy(user[3].fname,name);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");

        }
        fclose(fptr);
        break;
    case 3:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Age :%d",user[4].age);
            printf("\nEnter New Age :");
            scanf("%d",&age);
            user[4].age=age;
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");


        }
        fclose(fptr);
        break;
    case 4:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Birthday :%s",user[5].birthday);
            printf("\nEnter New Birthday :");
            fflush(stdin);
            gets(birthday);
            strcpy(user[5].birthday,birthday);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;
    case 5:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld NRC :%s",user[6].nrc);
            printf("\nEnter New NRC :");
            fflush(stdin);
            gets(nrc);
            strcpy(user[6].nrc,nrc);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
           if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;
    case 6:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld job :%s",user[7].job);
            printf("\nEnter New JOB :");
            fflush(stdin);
            gets(job);
            strcpy(user[7].job,job);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;
    case 7:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Email Address :%s",user[8].email);
            printf("\nEnter New Email Address :");
            fflush(stdin);
            gets(email);
            strcpy(user[8].email,email);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;
    case 8:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Phone Number :%s",user[9].ph);
            printf("\nEnter New Phone Number :");
            fflush(stdin);
            gets(ph);
            strcpy(user[9].ph,ph);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;
    case 9:
        while(fread(&user,sizeof(user),1,fptr))
        {
            printf("\nOld Physical Address :%s",user[10].physical_address);
            printf("\nEnter New Physical Address :");
            fflush(stdin);
            gets(physical_address);
            strcpy(user[10].physical_address,physical_address);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(user_file,"w");
            fwrite(&user,sizeof(user),1,fptr);
            if(fptr==0)
                printf("\nFailed To Change !");
            else
                printf("\nSuccessfully Change !");
        }
        fclose(fptr);
        break;

    }





    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");

    switch(option)
    {
    case 1:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[2].name,ctime(&t));
        fclose(fptr);
        break;
    case 2:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[3].fname,ctime(&t));
        fclose(fptr);
        break;
    case 3:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %d ' at %s",user_file,user[4].age,ctime(&t));
        fclose(fptr);
        break;
    case 4:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[5].birthday,ctime(&t));
        fclose(fptr);
        break;
    case 5:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[6].nrc,ctime(&t));
        fclose(fptr);
        break;
    case 6:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[7].job,ctime(&t));
        fclose(fptr);
        break;
    case 7:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[8].email,ctime(&t));
        fclose(fptr);
        break;
    case 8:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[9].ph,ctime(&t));
        fclose(fptr);
        break;
    case 9:
        fptr=fopen("Recent_Action.txt","a+");
        if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
        fprintf(fptr,"Account Number %s was edited ' %s ' at %s",user_file,user[10].physical_address,ctime(&t));
        fclose(fptr);
        break;

    }

    fclose(fptr);




    printf("\n\nOne More (Y/N):");
    back=getch();
    if(toupper(back)=='Y')
        goto GO;
}


void recent_action()
{
    char read[100];
    fptr=fopen("Recent_Action.txt","a+");
    if(fptr==0)
        fptr=fopen("Recent_Action.txt","a+");
    printf("\n\tRecent Actions ");
    printf("\n\t===============");
    while(!feof(fptr))
    {
        fgets(read,100,fptr);
        printf("\n%s",read);
    }
    fclose(fptr);
}

























