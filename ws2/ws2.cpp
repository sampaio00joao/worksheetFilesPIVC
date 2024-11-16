#include "functions.h"


void exercise1_ws2(int channel) {

	// channels B-G-R
	Mat image_extract = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/retina.tif");
	// greyscale reference image / CV_8UC1 -> 1 channel
	Mat grayImage(image_extract.rows, image_extract.cols, CV_8UC1, Scalar(0));
	// go through all the pixels in the image
	for (int r = 0; r < image_extract.rows; r++) {
		for (int c = 0; c < image_extract.cols; c++) {
			Vec3b pixel_value = image_extract.at<Vec3b>(r, c); // extract the values from the picture
			grayImage.at<uchar>(r, c) = pixel_value[channel]; // transfer the values to the reference image
		}
	}
	imshow("Image Greyscale", grayImage);
	waitKey(0);
	destroyAllWindows();
}

void exercise2_ws2(int channel) {

	// channels B-G-R
	Mat image_extract = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/retina.tif");
	// reference image / CV_8UC3 -> 3 channel
	Mat newImage(image_extract.rows, image_extract.cols, CV_8UC3, Scalar(0));

	for (int r = 0; r < image_extract.rows; r++) {
		for (int c = 0; c < image_extract.cols; c++) {
			Vec3b pixel_value = image_extract.at<Vec3b>(r, c); // extract the values from the picture
			pixel_value[channel] = 0; // remove the channel that the user typed // all pixels to 0 
			newImage.at<Vec3b>(r, c) = pixel_value; // save the other channels in the reference image
		}
	}
	imshow("Image 2 channels", newImage);
	waitKey(0);
	destroyAllWindows();
}

void exercise3_ws2(int userChoice) {

	// channels B-G-R
	Mat image_extract = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/retina.tif");
	// greyscale reference image / CV_8UC1 - > 1 channel
	Mat grayImage(image_extract.rows, image_extract.cols, CV_8UC1, Scalar(0));
	cv::String imageLabel;

	if (userChoice) { //weighted 
		for (int r = 0; r < image_extract.rows; r++) {
			for (int c = 0; c < image_extract.cols; c++) {
				Vec3b pixel_value = image_extract.at<Vec3b>(r, c);
				// calculate the intensity using the weighted formula
				uchar intensity = (
					(pixel_value[0] * 0.144) +
					(pixel_value[1] * 0.587) +
					(pixel_value[2] * 0.299));
				grayImage.at<uchar>(r, c) = intensity; // save in the new image
			}
		}
		imageLabel = "Weighted Formula Greyscale Image";
	}
	else { //normal
		for (int r = 0; r < image_extract.rows; r++) {
			for (int c = 0; c < image_extract.cols; c++) {
				Vec3b pixel_value = image_extract.at<Vec3b>(r, c); // extract the values from the picture
				// calculate the intesity between all channels
				uchar intensity = (pixel_value[0] + pixel_value[1] + pixel_value[2]) / 3; 
				grayImage.at<uchar>(r, c) = intensity; // save the other channels
			}
		}
		imageLabel = "Normal Formula Greyscale Image";
	}
	imshow(imageLabel, grayImage);
	waitKey(0);
	destroyAllWindows();
}

void exercise4_ws2(int userChoice) {

	if (userChoice) { // breast
		Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_image.png", IMREAD_GRAYSCALE);
		// greyscale reference image / CV_8UC1 -> Channel
		Mat newImage(image.rows, image.cols, CV_8UC1, Scalar(0));

		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
			newImage.data[i] = 255 - image.data[i];
		}
		imshow("Image Negative Greyscale", newImage);
	}
	else { // retina
		Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/retina.tif");
		// reference image / CV_8UC3 -> 3 channels
		Mat newImage(image.rows, image.cols, CV_8UC3, Scalar(0));

		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
			newImage.data[i] = 255 - image.data[i];
		}
		imshow("Image Negative RGB", newImage);
	}
	waitKey(0);
	destroyAllWindows();
}

void exercise5_ws2(int userChoice) {

	if (userChoice) { // breast
		Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_image.png", IMREAD_GRAYSCALE);
		Mat mask = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_mask.png", IMREAD_GRAYSCALE);
		
		Mat invertedImage(image.rows, image.cols, CV_8UC1, Scalar(0));
		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
			if (mask.data[i] != 0) { // apply the negative only on the foreground 
				invertedImage.data[i] = 255 - image.data[i];
			}
		}
		imshow("Image Negative Breast Mask", invertedImage);
	}	
	else { // retina
		Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/retina.tif");
		// rgb reference image / CV_8UC3 -> Channel
		Mat inverted_img(image.rows, image.cols, CV_8UC3, Scalar(0));

		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				Vec3b vec_value = image.at<Vec3b>(i, j);
				// inversion of all channels in a threshould
				if ((vec_value[0] > 15) || (vec_value[1] > 15) || (vec_value[2] > 15)) {
					vec_value[0] = 255 - vec_value[0];
					vec_value[1] = 255 - vec_value[1];
					vec_value[2] = 255 - vec_value[2];
					inverted_img.at<Vec3b>(i, j) = vec_value; // save on the reference image
				}
			}
		}
		imshow("Image Negative Retina", inverted_img);
	}
	waitKey(0);
	destroyAllWindows();
}

void exercise6_ws2(int userChoice, int bvalue) {

	Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_image.png");
	//reference image / CV_8UC3 -> 3 channels
	Mat outputImage(image.rows, image.cols, CV_8UC3, Scalar(0));
	cv::String imageLabel;

	if (userChoice) { // brigther
		
		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
			outputImage.data[i] = image.data[i] + bvalue; // addition of a constant to increase the brightness
		}
		imageLabel = "Increased Brightness";
	}
	else {

		//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
		for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
			outputImage.data[i] = image.data[i] - bvalue; // addition of a constant to decrease the brightness
		}
		imageLabel = "Decreased Brightness";
	}
	imshow(imageLabel, outputImage);
	waitKey(0);
	destroyAllWindows();
}

void exercise7_ws2(float alphavalue) {

	Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_image.png");
	// reference image / CV_8UC3 -> 3 channels
	Mat outputImage(image.rows, image.cols, CV_8UC3, Scalar(0));
	cv::String imageLabel;

	//since all pixels and channels are modified using the same expression, we can avoid the use of 2 loops and if condition for gray and rgb
	for (int i = 0; i < image.rows * image.cols * image.channels(); i++) {
		outputImage.data[i] = image.data[i] * alphavalue; // addition of a constant increase the contrast
	}
	if (alphavalue > 1) { // more contrast
		imageLabel = "Increased Contrast";
	}
	else{ //less contrast
		imageLabel = "Decreased Contrast";
	}
	imshow(imageLabel, outputImage);
	waitKey(0);
	destroyAllWindows();
}

void exercise8_ws2(int userChoice){
	Mat image = imread("J:/MEEC/PIVC/Projects/Project_PIVC_Worksheets/breast_image.png", IMREAD_GRAYSCALE);
	int intensity = 0;
	// Initialize histogram bins for intensity values 0-255
	vector<int> histogram(256, 0);

	for (int r = 0; r < image.rows; r++) {
		for (int c = 0; c < image.cols; c++) {
			intensity = image.at<uchar>(r, c);
			histogram[intensity]++;
		}
	}

	// Set up parameters for the histogram figure
	int hist_w = 512;  // Width of the histogram image
	int hist_h = 400;  // Height of the histogram image
	int bin_w = cvRound((double)hist_w / histogram.size());  // Width of each bar/bin

	// Create a white image to draw the histogram on
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));

	// Normalize histogram values to fit within the histogram image height
	int max_value = *max_element(histogram.begin(), histogram.end());
	for (int i = 0; i < histogram.size(); i++) {
		histogram[i] = (histogram[i] * hist_h) / max_value;  // Scale histogram to fit the height
	}

	// Draw the histogram bars
	for (int i = 0; i < histogram.size(); i++) {
		line(histImage, Point(bin_w * i, hist_h), Point(bin_w * i, hist_h - histogram[i]), Scalar(0), 2, 8, 0);
	}

	// Display the histogram
	imshow("Grayscale Image", image);
	imshow("Histogram", histImage);
	waitKey(0);
}