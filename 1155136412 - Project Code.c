#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**
* ENGG1110 Problem Solving by Programming
*
* Course Project
*
* I declare that the project here submitted is original
* except for source material explicitly acknowledged,
* and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.
*
* University Guideline on Academic Honesty:
* https://www.cuhk.edu.hk/policy/academichonesty/
*
* Student Name : Pau Chun Wai
* Student ID : 1155136412
* Class/Section : BL01
* Date : 5/11/2019
*/
//Declaration
int money = 0;
int money_stored = 0;
char Item_Get = '=';
const int Passcode = 1110;

typedef struct {
	char name[20];
	int price;
	char available;
	int left;
}Product_type;
Product_type product[]= {{"Juice",10,' ',5},{"Cola",6,' ',1},{"Tea",5,' ',2},{"Water",8,' ',1},{"Coffee",7,' ',9}};;
//Function Prototype

void VM_Display();
void Customers_Menu();
void Product_Information();
void Insert_coin();
void Choose_Product();
void Money_Return();
void Service_Menu();
void Service_Pass();
void Machine_Status();
void Withdraw_Coins();
void Refill_Products();
void Change_Products();
//Main Program
int main() {
	VM_Display();
	Customers_Menu();
	return 0;
}
//Function Definition
void Customers_Menu() {
	int choice = -1;
	while (choice != 0) {
		printf("What would you like to do?\n");
		printf("1. Read product information\n");
		printf("2. Insert coin\n");
		printf("3. Press product button\n");
		printf("4. Press return button\n");
		printf("9. Open service menu (code required)\n");
		printf("0. Quit\n");
		printf("Your choice:");
		scanf("%d", &choice);
		switch (choice) {
		case 1: printf("\n"); Product_Information();	break;
		case 2: printf("\n"); Insert_coin(); break;
		case 3: printf("\n"); Choose_Product(); break;
		case 4: printf("\n"); Money_Return(); break;
		case 9: printf("\n"); Service_Menu(); break;
		case 0: break;
		default: printf("Invalid choice!\n\n");
		}
	}
}
void VM_Display() {
	for (int i = 0; i < 5; i++) {
		if (product[i].left == 0) {
			product[i].available = 'X';
		}
		else if (money >= product[i].price) {
			product[i].available = 'O';
		}
		else if (money < product[i].price)
			product[i].available = ' ';
	}
	printf("*---------------------------*\n");
	printf("|      Vending Machine      |\n");
	printf("*---------------------------*\n");
	printf("|   A    B    C    D    E   |\n");
	printf("|  $%2d  $%2d  $%2d  $%2d  $%2d  |\n", product[0].price, product[1].price, product[2].price, product[3].price, product[4].price);
	printf("|  [%c]  [%c]  [%c]  [%c]  [%c]  |\n", product[0].available, product[1].available, product[2].available, product[3].available, product[4].available);
	printf("*---------------------------*\n");
	printf("|                    [$%2d]  |\n", money);
	printf("|                           |\n");
	printf("|           [=%c=]           |\n",Item_Get);
	printf("*---------------------------*\n");
	printf("\n");
	Item_Get = '=';
}
void Product_Information() {
	printf("(1) The displayed products are:\n");
	for (int i = 0; i < 5; i++) {
		printf("%c. %s ($%d)\n", 65+i,product[i].name, product[i].price);
	}
	printf("\n");
}
void Insert_coin() {
	int choice=-1;
	while (choice != 0) {
		printf("(2) Which coin would you like to insert?\n");
		printf("1. $1\n");
		printf("2. $2\n");
		printf("3. $5\n");
		printf("4. $10\n");
		printf("0. Go back\n");
		printf("Your choice:");
		scanf("%d", &choice);
		if (money == 99) printf("\n");
		else if (choice == 1) {
			money++; printf("You have inserted $1.\n\n"); VM_Display();
		}
		else if (choice == 2) {
			money += 2; printf("You have inserted $2.\n\n"); VM_Display();
		}
		else if (choice == 3) {
			money += 5; printf("You have inserted $5.\n\n"); VM_Display();
		}
		else if (choice == 4) {
			money += 10; printf("You have inserted $10.\n\n"); VM_Display();
		}
		else if (choice == 0) {
			printf("Going back!\n\n"); VM_Display();
		}
		else printf("Invalid choice!\n\n");
		if (money > 99)money = 99;
	}
}
void Choose_Product() {
	int choice = -1;
	while (choice != 0) {
		printf("(3) Which product button would you like to press?\n");
		printf("1. A\n");
		printf("2. B\n");
		printf("3. C\n");
		printf("4. D\n");
		printf("5. E\n");
		printf("0. Go back\n");
		printf("Your choice:");
		scanf("%d", &choice);
		if (choice == 0) {
			printf("Going back!\n\n");
			VM_Display(); 
		}
		else if (choice >= 1 && choice <= 5) {
			printf("You have pressed button %c.\n\n",choice+64); 
			if (money > product[choice - 1].price&& product[choice-1].available!='X') {
				money -= product[choice - 1].price;
				money_stored += product[choice - 1].price;
				product[choice-1].left--;
				Item_Get = choice + 64;
			}
			VM_Display();
			break;
		}else printf("Invalid choice!\n\n");
		
	}
	
}
void Money_Return() {
	printf("(4) Return button is pressed.\n");
	printf("$%d has been returned.\n", money);
	printf("\n");
	money = 0;
	VM_Display();
}
void Service_Menu() {
	int user_input;
	printf("(9) Opening service menu. Access code is required.\n");
	printf("Enter access code:");
	scanf("%d", &user_input);
	if (user_input==Passcode){
		printf("Correct code!\n\n");
		Service_Pass();
	}
	else {
		printf("Incorrect code!\n\n\n");
		VM_Display();
	}

}
void Service_Pass() {
	int choice = -1;
	
	while (choice != 0) {
		printf("(9) What would you like to do?\n");
		printf("1. Inspect machine status\n");
		printf("2. Withdraw all money\n");
		printf("3. Refill product\n");
		printf("4. Change Product\n");
		printf("0. Go back\n");
		printf("Your choice:");
		scanf("%d", &choice);
		switch (choice) {
		case 1: printf("\n"); Machine_Status(); break;
		case 2: printf("\n"); Withdraw_Coins(); break;
		case 3: printf("\n"); Refill_Products(); break;
		case 4: printf("\n"); Change_Products(); break;
		case 0: printf("Going back!\n\n"); VM_Display();break;
		default: printf("Invalid choice!\n\n");
		}
	}
}
void Machine_Status() {
	printf("(9-1) Machine status\n");
	printf("Amount of revenue: $%d\n", money_stored);
	printf("Amount of inserted coins: $%d\n", money);
	printf("Product information:\n");
	for (int i = 0; i < 5; i++) {
		printf("%c. %s ($%d) ",65+i, product[i].name, product[i].price);
		if (product[i].left == 0)printf("(sold out)\n");
		else printf("(%d left)\n", product[i].left);
	}
	printf("\n");
}
void Withdraw_Coins() {
	printf("(9-2) Inserted coins are being withdrawn.\n");
	printf("$%d is withdrawn.\n",money_stored+money);
	money = 0;
	money_stored = 0;
	printf("\n");
}
void Refill_Products() {
	int choice;
	printf("(9-3) Which product would you like to refill?\n");
	printf("1. A\n");
	printf("2. B\n");
	printf("3. C\n");
	printf("4. D\n");
	printf("5. E\n");
	printf("0. Go back\n");
	printf("Your choice:");
	scanf("%d", &choice);
	if (choice>=1&&choice<=5){
		printf("You have refilled product %c to full.\n\n", choice + 64);
		product[choice-1].left = 10;
	}
	else if (choice == 0) {
		printf("Going back!\n\n");
	}
	else {
		printf("Invalid choice!\n\n");
		Refill_Products();
	}

}
void Change_Products() {
	int choice;
	printf("(9-4) Which product would you like to change?\n");
	printf("1. A\n");
	printf("2. B\n");
	printf("3. C\n");
	printf("4. D\n");
	printf("5. E\n");
	printf("0. Go back\n");
	printf("Your choice:");
	scanf("%d", &choice);
	if (choice >= 1 && choice <= 5) {
		printf("You are changing product %c.\n", 64 + choice);
		printf("\n");
		printf("Enter new product name:");
		scanf("%s", product[choice-1].name);
		printf("Enter new product price:");
		scanf("%d", &product[choice-1].price);
		printf("The new product %c has been filled to full.\n", choice + 64);
		product[choice-1].left = 10;
		printf("\n");
	}
	else if (choice == 0) {
		printf("Going back!\n\n");
	}
	else {
		printf("Invalid choice!\n\n");
		Change_Products();
	}
}