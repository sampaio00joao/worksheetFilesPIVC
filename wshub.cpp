#include "functions.h"

void wsHub() {
	int userInputValue = 0;
	while (1) {
		cout << "Choose a worksheet number:" << endl;
		cout << "(available: WS1 -> 1 / WS2 -> 2 / WS -> 3 / WS -> 4)" << endl;
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
		case 3: //ws2
			cout << "WS3!" << endl;
			ws3hub();
			system("cls");
			break;
		case 4:
			cout << "WS4!" << endl;
			ws4hub();
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
	String imageName, maskName;
	float contrast_choice = 0;
	while (1) {
		switch (userInputValue) {
		case 10:
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
			imageName = "Retina.tif";
			exercise1_ws2(imageName, userChoice);
			userInputValue = 10;
			system("cls");
			break;
		case 2:
			cout << "Choose a channel: (0 => B / 1 => G / 2 => R)" << endl;
			cin >> userChoice;
			imageName = "Retina.tif";
			exercise2_ws2(imageName, userChoice);
			userInputValue = 10;
			system("cls");
			break;
		case 3:
			cout << "Choose an option: (Normal => 0 / Weighted => 1)" << endl;
			cin >> userChoice;
			imageName = "Retina.tif";
			exercise3_ws2(imageName, userChoice);
			userInputValue = 10;	
			system("cls");
			break;
		case 4:
			cout << "Choose image: (Retina => 0 / Breast => 1)" << endl;
			cin >> userChoice;
			if (userChoice != 0) imageName = "breast_image.png";
			else imageName = "Retina.tif";
			exercise4_ws2(imageName);
			userInputValue = 10;
			system("cls");
			break;
		case 5:
			cout << "Choose image: (Retina => 0 / Breast => 1)" << endl;
			cin >> userChoice;
			if (userChoice != 0)
			{
				imageName = "breast_image.png";
				maskName = "breast_mask.png";
			}
			else imageName = "Retina.tif";
			exercise5_ws2(imageName, maskName);
			userInputValue = 10;
			system("cls");
			break;
		case 6:
			cout << "Choose an option for brightness: (Decrease => 0 / Increase => 1)" << endl;
			cin >> userChoice;
			cout << "Choose the value of b: " << endl;
			cin >> bright_choice;
			imageName = "breast_image.png";
			exercise6_ws2(imageName, userChoice, bright_choice);
			userInputValue = 10;
			system("cls");
			break;
		case 7:
			cout << "Choose the value of alpha: (contrast)" << endl;
			cin >> contrast_choice;
			imageName = "breast_image.png";
			if(contrast_choice != 0 && contrast_choice != 1) exercise7_ws2(imageName, contrast_choice);
			else cout << "Value cant be 0 or 1." << endl;
			userInputValue = 10;
			system("cls");
			break;
		case 8:
			cout << "Choose an option: (Normal => 0 / Brigthness example => 1 / Contrast Example => 2)" << endl;
			cin >> userChoice;
			userInputValue = 10;
			system("cls");
			break;

		default:
			userInputValue = 10; //go back to main submenu
			system("cls");
			break;
		}
	}
}

void ws3hub() {
	int userInputValue = 0, imageChoice = 0, userChoice = 0, userChoice2 = 0, bright_choice = 0;
	float contrast_choice = 0;
	String imagePath, imageName;
	Mat Gauss;
	while (1) {
		switch (userInputValue) {
		case 10:
			cout << "1. Average filter to remove noise." << endl;
			cout << "2. Median filter to remove noise." << endl;
			cout << "3. Create a gaussian kernel." << endl;
			cout << "4. Convolution with gaussian kernel." << endl;
			cout << "5. Convolution with Sobel kernel." << endl;
			cout << "6. Convolution with Laplace kernel." << endl;
			cout << "Press 0 to go back!" << endl;
			cin >> userInputValue;
			if (userInputValue != 0) break;
			else wsHub();
		case 1:
			cout << "Choose image: (head_gaussian_noise => 0 / head_saltpepper_noise => 1)" << endl;
			cin >> imageChoice;
			if (imageChoice != 0){
				imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_saltpepper_noise.png";
				imageName = "Salt and Pepper Noise Filtering";
			}
			else{
				imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_gaussian_noise.png";
				imageName = "Gaussian Noise Filtering";
			}
				cout << "Choose kernel size: " << endl;
			cin >> userChoice;
			exercise1_ws3(imagePath,imageName,userChoice);
			userInputValue = 10;
			system("cls");
			break;
		case 2:
			cout << "Choose image: (head_gaussian_noise => 0 / head_saltpepper_noise => 1)" << endl;
			cin >> imageChoice;
			if (imageChoice != 0) {
				imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_saltpepper_noise.png";
				imageName = "Salt and Pepper Noise Filtering";
			}
			else {
				imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_gaussian_noise.png";
				imageName = "Gaussian Noise Filtering";
			}
				cout << "Choose kernel size: " << endl;
			cin >> userChoice;
			exercise2_ws3(imagePath, imageName, userChoice);
			userInputValue = 10;
			system("cls");
			break;
		case 3:
			cout << "Choose kernel size:" << endl;
			cin >> userChoice;
			// must be odd
			if (userChoice % 2 && userChoice >= 1) {
				cout << "Choose sigma value:" << endl;
				cin >> userChoice2;
				Gauss = exercise3_ws3(userChoice, userChoice2);
				cout << "Gaussian Kernel:" << Gauss << endl;
				cout << "Press any number to go back." << endl;
				cin >> userChoice; // program gets stuck to allow the kernel print
			}
			else {
				cout << "Must be an odd number and higher than 1." << endl;
				cout << "Press any number to go back." << Gauss << endl;
				cin >> userChoice; // program gets stuck to warn the user
			}
			
			userInputValue = 10;
			system("cls");
			break;
		case 4:
			cout << "Choose kernel size:" << endl;
			cin >> userChoice;
			// must be odd
			if (userChoice % 2 && userChoice >= 1) {
				cout << "Choose sigma value:" << endl;
				cin >> userChoice2;
				imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_gaussian_noise.png";
				imageName = "Gaussian Noise Filtering";
				Gauss = exercise3_ws3(userChoice, userChoice2);
				cout << "Gaussian Kernel:\n" << Gauss << "\n";
				exercise4_ws3(imagePath, imageName, Gauss, userChoice);
			}
			else {
				cout << "Must be an odd number and higher than 1." << endl;
				cout << "Press any number to go back." << Gauss << endl;
				cin >> userChoice; // program gets stuck to warn the user
			}
			userInputValue = 10;
			system("cls");
			break;
		case 5:
			imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_clean.png";
			imageName = "Sobel Filtering";
			exercise5_ws3(imagePath, imageName);
			userInputValue = 10;
			system("cls");
			break;
		case 6:
			imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/head_clean.png";
			imageName = "Laplace Filtering";
			exercise6_ws3(imagePath, imageName);
			userInputValue = 10;
			system("cls");
			break;
		default:
			userInputValue = 10; //go back to main submenu
			system("cls");
			break;
		}
	}
}

void ws4hub() {
	int userInputValue = 0, imageChoice = 0, userChoice = 0, 
		userChoice2 = 0, structElementSize = 0, structElementType = 0;
	String imagePath, imageName;
	Mat Gauss, structElement, structElement2;
	while (1) {
		switch (userInputValue) {
		case 10:
			cout << "1. From BinaryImg.png to BinaryImg_processed.png." << endl;
			cout << "2. Smooth the image head_gaussian_noise.png." << endl;
			cout << "3. Sobel filter to detect the outlines." << endl;
			cout << "4. Mathematical morphology to detect outlines." << endl;
			cout << "5. Segmentation of kidney.png." << endl;
			cout << "Press 0 to go back!" << endl;
			cin >> userInputValue;
			if (userInputValue != 0) break;
			else wsHub();
		case 1:
			imagePath = "J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/BinaryImg.png";
			imageName = "Binary Image";
			exercise1_ws4(imagePath, imageName);
			userInputValue = 10;
			system("cls");
			break;
		case 2:
			imagePath = "head_gaussian_noise.png";
			imageName = "Smoothed Image";
			cout << "Structuring element size: " << endl;
			cin >> structElementSize;
			cout << "Structuring element type: " << endl;
			cout << "(0 -> Rectangle / 1 -> Ellipse)" << endl;
			cin >> structElementType;
			structElement = structuringElement(structElementSize, structElementType);
			exercise2_ws4(imagePath, imageName, structElement);
			userInputValue = 10;
			system("cls");
			break;
		case 3:
			cout << "Choose an image:" << endl;
			cout << "(0 -> 3x3 / 1 -> 5x5 / 2-> 9x9)" << endl;
			cin >> imageChoice;
			if (imageChoice == 0) {
				imagePath = "head_gaussian_smooth_3x3.png";
			}
			else if (imageChoice == 1) {
				imagePath = "head_gaussian_smooth_5x5.png";
			}
			else if (imageChoice == 2) {
				imagePath = "head_gaussian_smooth_9x9.png";
			}
			imageName = "Gaussian Noise Filtering";
			exercise5_ws3(imagePath, imageName);
			userInputValue = 10;
			system("cls");
			break;
		case 4:
			cout << "Choose an image:" << endl;
			cout << "(0 -> 3x3 / 1 -> 5x5 / 2-> 9x9)" << endl;
			cin >> imageChoice;
			if (imageChoice == 0) {
				imagePath = "head_gaussian_smooth_3x3.png";
			}
			else if (imageChoice == 1) {
				imagePath = "head_gaussian_smooth_5x5.png";
			}
			else if (imageChoice == 2) {
				imagePath = "head_gaussian_smooth_9x9.png";
			}
			imageName = "Morphology Outlines Image";
			cout << "Structuring element size: (outline) " << endl;
			cin >> structElementSize;
			cout << "Structuring element type: (outline)" << endl;
			cout << "(0 -> Rectangle / 1 -> Ellipse / 2 -> Cross)" << endl;
			cin >> structElementType;
			structElement = structuringElement(structElementSize, structElementType);
			exercise4_ws4(imagePath, imageName, structElement);
			userInputValue = 10;
			system("cls");
			break;
		case 5:
			imagePath = "kidney.png";
			imageName = "Pipeline Kidney Image";
			exercise5_ws4(imagePath, imageName);
			userInputValue = 10;
			system("cls");
			break;
		default:
			userInputValue = 10; //go back to main submenu
			system("cls");
			break;
		}
	}
}

