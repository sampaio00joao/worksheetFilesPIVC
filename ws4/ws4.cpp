#include "functions.h"

Mat dilatation(Mat& image, Mat structuringElement) {
	Mat imageT;
	dilate(image, imageT, structuringElement);
	return imageT;
}

Mat erosion(Mat& image, Mat structuringElement) {
	Mat imageT;
	erode(image, imageT, structuringElement);
	return imageT;
}

Mat closing(Mat& image, Mat structuringElement) {
	Mat imageT, imageT2;
	dilate(image, imageT, structuringElement);
	erode(imageT, imageT2, structuringElement);
	return imageT2;
}

Mat opening(Mat& image, Mat structuringElement) {
	Mat imageT, imageT2;
	erode(image, imageT, structuringElement);
	dilate(imageT, imageT2, structuringElement);
	return imageT2;
}

Mat structuringElement(int size, int type) {
	// Define the size of the structuring element
	Size ksize(size, size);
	Mat structElement;
	if (type == 0) { // Morph_rect
		structElement = getStructuringElement(MORPH_RECT, ksize);
	}
	else if (type == 1) { // Morph_ellipse
		structElement = getStructuringElement(MORPH_ELLIPSE, ksize);
	}
	else if (type == 2) { // Morph_cross
		structElement = getStructuringElement(MORPH_CROSS, ksize);
	}
	else if (type == 3) { // Morph_line
		Size ksize(1, size);
		structElement = getStructuringElement(MORPH_RECT, ksize);
	}
	return structElement;
}

void exercise1_ws4(const string& imagePath, const string& imageName) {
	
	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

   // Define the size of the structuring element
	Size ksizeRect(3, 3);
	Mat structElementRect = getStructuringElement(MORPH_RECT, ksizeRect);
	// Define the size of the structuring element
	Size ksizeLine(3, 1); // to make a line
	Mat structElementLine = getStructuringElement(MORPH_RECT, ksizeLine);

	// Fill the line in the first rectangle
	Mat outputOpeningImage = opening(image, structElementRect);
	// Fix the line between rectangles
	Mat outputClosingImage1 = closing(outputOpeningImage, structElementRect);
	// Remove points from the image
	Mat outputClosingImage2 = closing(outputClosingImage1, structElementLine);
	
	Mat outputImage1, outputImage2, outputImage3;
	hconcat(image, outputOpeningImage, outputImage1);
	hconcat(outputImage1, outputClosingImage1, outputImage2);
	hconcat(outputImage2, outputClosingImage2, outputImage3);

	imshow(imageName, outputImage3);
	waitKey(0);
}

void exercise2_ws4(const string& imagePath, const string& imageName, Mat structuringElement) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

	// Electronic smoothing
	Mat outputOpeningImage = opening(image, structuringElement);
	Mat outputClosingImage = closing(outputOpeningImage, structuringElement);

	Mat outputImage1, outputImage2, outputImage3;
	hconcat(image, outputOpeningImage, outputImage2);
	hconcat(outputImage2, outputClosingImage, outputImage3);

	//Save the image with a new name
	//imwrite("head_gaussian_smooth_9x9.png", outputClosingImage);

	imshow(imageName, outputImage3);
	waitKey(0);
}

// exercise 3 from ws4 is the same as the ws3 Sobel implementation 

void exercise4_ws4(const string& imagePath, const string& imageName, Mat structuringElement) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

	// Dilation
	Mat imageDilation = dilatation(image, structuringElement);
	// Erosion
	Mat imageErosion = erosion(image, structuringElement);

	// new empty image 
	Mat result = Mat::zeros(imageErosion.size(), imageErosion.type());
	
	for (int r = 0; r < imageErosion.rows; r++) {
		for (int c = 0; c < imageErosion.cols; c++) {
			result.at<uchar>(r, c) = static_cast<int>(imageDilation.at<uchar>(r, c)) - imageErosion.at<uchar>(r, c);
		}
	}

	Mat outputImage1, outputImage2, outputImage3, outputImage4;
	hconcat(image, result, outputImage1);
	//hconcat(outputImage1, imageDilation, outputImage2);
	//hconcat(outputImage2, imageErosion, outputImage3);
	//hconcat(outputImage3, result, outputImage4);

	imshow(imageName, outputImage1);
	waitKey(0);
}

void exercise5_ws4(const string& imagePath, const string& imageName) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

	Mat binaryImage = Mat::zeros(image.size(), image.type()); // Initialize with zeros (all black)

	for (int r = 0; r < image.rows; r++) {
		for (int c = 0; c < image.cols; c++) {
			uchar pixelValue = image.at<uchar>(r, c);
			if (pixelValue > 200) {
				binaryImage.at<uchar>(r, c) = 255; // Set to white
			}
		}
	}

	Mat strucElement1 = structuringElement(25,1);
	Mat strucElement2 = structuringElement(47,1); 
	Mat strucElement3 = structuringElement(40,1);

	Mat imageClosing = closing(binaryImage, strucElement2);
	Mat imageOpening = opening(imageClosing, strucElement1);
	//Mat imageDilation = dilatation(imageOpening, strucElement1);
	Mat imageOpening2 = opening(imageOpening, strucElement3);

	Mat resizedImage, resizedBinaryImage, resizedImageOpening, resizedImageDilation, resizedImageClosing;
	Mat resizedImageOpening2;

	// Resize images to make them smaller
	resize(image, resizedImage, Size(), 0.5, 0.5);
	resize(binaryImage, resizedBinaryImage, Size(), 0.5, 0.5);
	resize(imageClosing, resizedImageClosing, Size(), 0.5, 0.5);
	resize(imageOpening, resizedImageOpening, Size(), 0.5, 0.5);
	resize(imageOpening2, resizedImageOpening2, Size(), 0.5, 0.5);

	// Concatenate horizontally
	Mat outputImage1, outputImage2, outputImage3;
	hconcat(resizedImageClosing, resizedImageOpening, outputImage1);
	hconcat(resizedImageClosing, resizedImageOpening2, outputImage2);


	// Display the result
	imshow(imageName, resizedImageOpening2);
	waitKey(0);
}