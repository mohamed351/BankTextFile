#include <windows.h>
#include <string.h>
#include <stdlib.h>
#define CLIENT_FILE_NAME  "Clients.txt" 
#define CLIENT_FILE_NAME_TEMP  "ClientText.txt" 
#define MAX_LINES 1000      // Maximum number of lines the file can contain
#define MAX_LINE_LENGTH 1024 // Maximum length of each line


void PrintColoredText(int number, char* text, HANDLE* handle);
void ProcessTransaction(int choice, struct Client* client);
struct Client* SplitLine(char* line);
void Deposit(struct Client* client);
void WithDraw(struct Client* client);
void CheckYourBalance(struct Client* client);
void ExitTransaction(struct Client* client);
void Save(struct Client* client);

void PrintColoredText(int number, char* text, HANDLE* handle) {
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	printf("%d . ", number);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
	printf("%s \n", text);
}
void ProcessTransaction(int choice , struct Client * client) {
	switch (choice)
	{
	
	case 1:
		Deposit(client);
		Save(client);
		break;

	case 2:
		WithDraw(client);
		Save(client);
		break;

	case 3:
		CheckYourBalance(client);
		break;

	case 4:
		ExitTransaction(client);
		
		break;

	default:
		break;
	}


}
struct Client * ReadTextFileAndGetClient(char * clientId) {
	struct Client * currentClient = NULL;
	int index = 0;
	FILE* file = fopen(CLIENT_FILE_NAME, "r");
	char line[200];
	if (file == NULL) {
		printf("Faild to proccess Data");
	}
	while (fgets(line, sizeof(line), file))
	{
	   currentClient = SplitLine(line);
	 
	   if (strcmp(currentClient->id, clientId) ==0) {

		   fclose(file);
		   currentClient->lineNumber = index;
		   return currentClient;
	   }
	   index++;
	}
	fclose(file);
	return NULL;



}

struct Client*  SplitLine(char * line) {
	struct Client* client = malloc(sizeof(struct Client));
	int index = 0;

	char balance[9];

	char de[] = ",";

	char* head = strtok(line, ",");
	strcpy(client->id, head);

	head = strtok(NULL, ",");
	strcpy(client->name, head);

	head = strtok(NULL, ",");
	strcpy(balance, head);
	char* ptr;
	client->balance = strtod(balance, &ptr);

	return client;
}

void Deposit(struct Client* client) {

	double depositAmount = 0;
	printf("Hello  %s you want to deposit  \n", client->name);
	printf("Please enter the amount to deposit in LE : ");
	scanf("%lf", &depositAmount);
	client->balance = client->balance + depositAmount;
	printf("your balance is now : %0.2lf", client->balance);

}
void WithDraw(struct Client* client) {

	double withdrawAmount = 0;
	printf("Hello  %s you want to withdraw \n", client->name);
	printf("Please enter the amount to withdraw in LE : ");
	scanf("%lf", &withdrawAmount);

	if (withdrawAmount > client->balance) {
		printf("you can't withdraw the amount is insufficient\n");
	}
	else {
		client->balance = client->balance - withdrawAmount;
		printf("your balance is now : %0.2lf", client->balance);
	}
	

}

void CheckYourBalance(struct Client* client) {
	printf("Hello %s", client->name);
	printf("You Amount is %0.2lf", client->balance);
}

void ExitTransaction(struct Client* client) {
	printf("Thank you %s for visiting our bank ", client->name);

}

void Save(struct Client* client) {
	struct  Client* clients[100] = { NULL };
	char line[200];
	int index = 0;
	FILE* file = fopen(CLIENT_FILE_NAME, "r");
	while (fgets(line, sizeof(line), file))
	{
		clients[index] = SplitLine(line);
		if (strcmp(client->id, clients[index]->id) == 0) {

			clients[index] = client;
		}

		index++;
	}
	fclose(file);



	FILE* filewrite = fopen(CLIENT_FILE_NAME, "w");
	char* contactedString = malloc(sizeof(100));
	for (int i = 0; i < 100; i++)
	{
		
		if (clients[i] != NULL) {

		
			contactedString = strcpy(contactedString, clients[i]->id);
			contactedString = strcat(contactedString, ",");
			contactedString = strcat(contactedString, clients[i]->name);
			contactedString = strcat(contactedString, ",");
			

			char balance[20];
			snprintf(balance, sizeof(balance), "%.0lf", clients[i]->balance);
			char* line = strcat(contactedString, balance);
			char* lineAddingSpace = strcat(line, "\n");
			
			fprintf(filewrite, lineAddingSpace);
			
		}
		
	}
	//free(contactedString);
	/*free(contactedString);
	free(clients);*/
	fclose(filewrite);

	

	


 
}
