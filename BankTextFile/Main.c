#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "Client.c";
#include "Application.h"



int main() {

	// for chaning color 
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char* clientId = "";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	printf("=============================== Simple Bank System =========================\n");
	printf("please enter client id :");
	scanf("%s", &clientId);
	struct Client * client =	 ReadTextFileAndGetClient(&clientId);
	if (client == NULL) {
		printf("wrong id please try again");
		return 0;
	}
	int choose = -1;

	do {


		PrintColoredText(1, "Deposit",hStdOut);
		PrintColoredText(2, "Withdraw", hStdOut);
		PrintColoredText(3, "Cheak Balance", hStdOut);
		PrintColoredText(4, "Exit", hStdOut);
		printf("please enter your choice : ");
		scanf("%d", &choose);
		ProcessTransaction(choose, client);
		printf("\n--------------------------------------\n");

	} while (choose != 4);
	

	return 0;
}
