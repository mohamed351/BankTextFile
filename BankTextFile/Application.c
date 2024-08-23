
#include <windows.h>
void PrintColoredText(int number, char* text, HANDLE* handle) {
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	printf("%d . ", number);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
	printf("%s \n", text);
}
void ProcessTransaction(int choice) {
	switch (choice)
	{
	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	default:
		break;
	}


}
void ReadTextFile() {
	FILE* file = fopen("Clients.txt", "r");
	char line[200];
	if (file == NULL) {
		printf("Faild to proccess Data");
	}
	while (fgets(line, sizeof(line), file))
	{
		printf("%s", line);
	}
	fclose(file);

}
