#include "functions.h"

void wsHub() {
	int userInputValue = 0;
	while (1) {
		cout << "Choose a worksheet number: " << endl;
		cin >> userInputValue;
		system("cls");

		switch(userInputValue) {
		case 1: //ws1
			cout << "WS1!" << endl;
			ws1hub();
			system("cls");
			break;
		case 2: //ws2
			cout << "WS2!" << endl;
			ws2hub();
			system("cls");
			break;
		default:
			cout << "Not a valid choice!" << endl;
			system("cls");
			break;
		}
	}

}

void ws1hub() {
	int userInputValue = 0, imageChoice = 0;
	while (1) {
		switch(userInputValue){
		case 0:
			cout << "1. 8bpp image / 704x576 / 2D array conversion / px=127 middle and px=0 on borders." << endl;
			cout << "2. Read image, number of channels, colums and rows." << endl;
			cout << "3. Put px=127 on the borders of the image." << endl;
			cout << "4. Set the borders to Red on Retina.tif." << endl;
			cout << "5. Generate a 320x320 image and save it." << endl;
			cout << "Press 0 to go back!" << endl;
			cin >> userInputValue;
			if (userInputValue != 0) break;
			else wsHub();
		case 1:
			exercise_makeImage_ws1();
			userInputValue = 0;
			system("cls");
			break;
		case 2:
			cout << "Choose a number: (Retina => 0 / Kidney => 1)" << endl;
			cin >> imageChoice;
			exercise8_ws1(imageChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 3:
			cout << "Choose a number: (Retina => 0 / Kidney => 1)" << endl;
			cin >> imageChoice;
			exercise9_ws1(imageChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 4:
			exercise10_ws1();
			userInputValue = 0;
			system("cls");
			break;
		case 5:
			exercise11_ws1();
			userInputValue = 0;
			system("cls");
			break;
		default:
			userInputValue = 0; //go back to main submenu
			system("cls");
			break;
		}
	}
}

void ws2hub() {
	int userInputValue = 0, imageTypeChoice = 0, userChoice = 0, bright_choice = 0;
	float contrast_choice = 0;
	while (1) {
		switch (userInputValue) {
		case 0:
			cout << "1. Greyscale image of a channel. (Retina.tif)" << endl;
			cout << "2. Remove a channel from an image.(Retina.tif)" << endl;
			cout << "3. Convert an image from RGB to Greyscale.(Retina.tif)" << endl;
			cout << "4. Conversion to negative using a RGB or Greyscale image." << endl;
			cout << "5. Remove background and convert to negative." << endl;
			cout << "6. Increase or decrease the brightness of an image." << endl;
			cout << "7. Increase or decrease the contrast of an image." << endl;
			cout << "8. Make an histogram of an image." << endl;
			cout << "Press 0 to go back!" << endl;
			cin >> userInputValue;
			if (userInputValue != 0) break;
			else wsHub();
		case 1:
			cout << "Choose channel: (0 => B / 1 => G / 2 => R)" << endl;
			cin >> userChoice;
			exercise1_ws2(userChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 2:
			cout << "Choose a channel: (0 => B / 1 => G / 2 => R)" << endl;
			cin >> userChoice;
			exercise2_ws2(userChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 3:
			cout << "Choose an option: (Normal => 0 / Weighted => 1)" << endl;
			cin >> userChoice;
			exercise3_ws2(userChoice);
			userInputValue = 0;	
			system("cls");
			break;
		case 4:
			cout << "Choose image: (Retina => 0 / Breast => 1)" << endl;
			cin >> userChoice;
			exercise4_ws2(userChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 5:
			cout << "Choose image: (Retina => 0 / Breast => 1)" << endl;
			cin >> userChoice;
			exercise5_ws2(userChoice);
			userInputValue = 0;
			system("cls");
			break;
		case 6:
			cout << "Choose an option for brightness: (Decrease => 0 / Increase => 1)" << endl;
			cin >> userChoice;
			cout << "Choose the value of b: " << endl;
			cin >> bright_choice;
			exercise6_ws2(userChoice, bright_choice);
			userInputValue = 0;
			system("cls");
			break;
		case 7:
			cout << "Choose the value of alpha: (contrast)" << endl;
			cin >> contrast_choice;
			if(contrast_choice != 0 && contrast_choice != 1) exercise7_ws2(contrast_choice);
			else cout << "Value cant be 0 or 1." << endl;
			userInputValue = 0;
			system("cls");
			break;
		case 8:
			cout << "Choose an option: (Normal => 0 / Brigthness example => 1 / Contrast Example => 2)" << endl;
			cin >> userChoice;
			exercise8_ws2(userChoice);
			userInputValue = 0;
			system("cls");
			break;

		default:
			userInputValue = 0; //go back to main submenu
			system("cls");
			break;
		}
	}
}