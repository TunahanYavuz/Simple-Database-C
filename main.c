#include <stdio.h>
#include <string.h>
typedef struct {
    char Name[40];
    char SurName[40];
    int MonthlyIncome;
    int MonthlyExpenses;
    int NetIncome;
}Client;
void Write();
void Search();
Client client;
int main() {

    int choice;
    while(1){
        printf("\nWelcome to the Client Database\n"
               "__________________________________________________________\n"
               "Please choose:\n"
               "(1) New Client\n"
               "(2) Display Income, Expenses and Net Income of a Client\n"
               "(3) for Exit The Menu\n"
               "__________________________________________________________\n"
               "Please select option 1, option 2 or option 3\n");

        scanf("%d",&choice);
        switch (choice) {
            case 1:
                Write();
                break;
            case 2:
                Search();
                break;
            case 3:
                printf("\nGoodbye");
                return 0;
            default:
                printf("\nInvalid Option\n");
        }
    }
}

void Write(){
    printf("You have selected option 1\n"
           "Welcome to new client registration menu\n"
           "Please enter the name of the client\n");
    scanf(" %[^\n]%*c", client.Name);
    printf("Please enter the surname of the client\n");
    scanf(" %[^\n]%*c", client.SurName);
    printf("Please enter the monthly income of client\n");
    scanf("%d",&client.MonthlyIncome);
    printf("Please enter the monthly expenses of client\n");
    scanf("%d",&client.MonthlyExpenses);
    client.NetIncome = client.MonthlyIncome - client.MonthlyExpenses;
    FILE *F = fopen("database.txt","a");
    if(F!=NULL){
        fprintf(F, "%s %s %d %d %d\n", client.Name, client.SurName, client.MonthlyIncome,
                client.MonthlyExpenses, client.NetIncome);
        printf("Registered Client : %s %s\n"
               "Monthly Income = %d TL, Monthly Expenses = %d TL, Net Income = %d TL",client.Name, client.SurName,
               client.MonthlyIncome, client.MonthlyExpenses, client.NetIncome);
    }
    else{
        printf("File can not open");
    }
    fclose(F);
}

void Search(){
    printf("You have selected option 2\n"
           "Please enter the surname of the client\n");
    char searchSurName[40];
    int isAvailable=0;
    scanf(" %[^\n]%*c",searchSurName);
    FILE *F = fopen("database.txt","r");
    char line[266];
    if(F!=NULL){
        while(fgets(line,sizeof(line),F)!=NULL){
            if(sscanf(line, "%s %s %d %d %d", client.Name, client.SurName, &client.MonthlyIncome,
                      &client.MonthlyExpenses, &client.NetIncome) == 5) {
                if (!strcmp(searchSurName, client.SurName)) {
                    printf("\nRegistered Client: %s %s\n"
                           "Monthly Income = %d TL, Monthly Expenses = %d TL, Net Income = %d TL\n", client.Name, client.SurName,
                           client.MonthlyIncome, client.MonthlyExpenses, client.NetIncome);
                    isAvailable = 1;
                    break;
                }
            }
        }
    }
    if(!isAvailable){
        printf("This Client is not found");
    }
}
