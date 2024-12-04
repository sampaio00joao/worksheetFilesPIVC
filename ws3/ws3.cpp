#include "functions.h"

void exercise1_ws3(const string& imagePath, const string& imageName, int kernel) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = kernel/2; // pad is equal to the kernel/2 
	//creates a padded image
	// 4x pad because its top, bottom, left and right
	// border_constant => puts all 0 (default).
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1 channel image to serve as final reference
	Mat filterImage(image.rows, image.cols, CV_8UC1, Scalar(0));

    // loops through each pixel of the padded image, excluding the padding borders.
	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			int sum = 0;
			// loops through the kernel region centered at (r, c).
			// accumulates the sum of all pixel intensities in the kernel.
			for (int kx = -pad; kx <= pad; kx++) { // go through x 
				for (int ky = -pad; ky <= pad; ky++) { // go through y
					sum += paddedImage.at<uchar>(r + kx, c + ky);
				}
			}
			// avg calculation of pixels for the output image
			filterImage.at<uchar>(r - pad, c - pad) = static_cast<int>(round(float(sum))) / (kernel * kernel);
		}
	}

	Mat combinedImage;
	hconcat(image, filterImage, combinedImage); // image side by side

	imshow(imageName, combinedImage);
	waitKey(0);
}

void exercise2_ws3(const string& imagePath, const string& imageName, int kernel) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = kernel / 2; // pad is equal to the kernel/2 
	//creates a padded image
	// 4x pad because its top, bottom, left and right
	// border_constant => puts all 0 (default).
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1 channel image to serve as final reference
	Mat filterImage(image.rows, image.cols, CV_8UC1, Scalar(0));

	// loops through each pixel of the padded image, excluding the padding borders.
	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			vector<int> kernelValues; // To store the kernel values
			// loops through the kernel region centered at (r, c).
			// accumulates the sum of all pixel intensities in the kernel.
			for (int kx = -pad; kx <= pad; kx++) { // go through x 
				for (int ky = -pad; ky <= pad; ky++) { // go through y
					kernelValues.push_back(paddedImage.at<uchar>(r + kx, c + ky));
				}
			}
			// Sort the kernel values to find the median
			sort(kernelValues.begin(), kernelValues.end());

			// Calculate the median
			int median = 0;
			int kernelSizeSquared = kernel * kernel;
			if (kernelSizeSquared % 2 == 0) { // check if it's an even number
				// takes in consideration the two values in the middle / because its not odd
				median = (kernelValues[kernelSizeSquared / 2 - 1] + kernelValues[kernelSizeSquared / 2]) / 2;
			}
			else { // check if it's an odd number
				median = kernelValues[kernelSizeSquared / 2]; // its the middle element
			}

			// Assign the median value to the output image pixels / without padding (r - pad, c - pad)
			filterImage.at<uchar>(r - pad, c - pad) = static_cast<uchar>(median);
		}
	}	
	Mat combinedImage;
	hconcat(image, filterImage, combinedImage); // image side by side

	imshow(imageName, combinedImage);
	waitKey(0);
}

Mat exercise3_ws3(int kernelSize, int sigma){

	int waitUser = 0;
	int w = kernelSize / 2;

	// CV_64F = double in cpp
	Mat Gauss(kernelSize, kernelSize, CV_32F, Scalar(0));

	// Fill the kernel using the Gaussian formula
	for (int i = -w; i <= w; i++) {
		for (int j = -w; j <= w; j++) {
			double value = (1 / (2 * 3.14 * sigma * sigma)) *
				exp(-((i * i + j * j) / (2 * sigma * sigma))); // gaussian formula
			// the value is applied to the matrix created
			Gauss.at<float>(i + w, j + w) = value; 
		}
	}
	// Normalize the kernel
	//Gauss /= sum(Gauss)[0]; // Normalize so the sum of all elements equals 1
	
	return Gauss;
}

void exercise4_ws3(const string& imagePath, const string& imageName, Mat kernel, int kernelSize) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

	Mat paddedImage;
	int pad = kernelSize / 2;
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT, Scalar(0));

	Mat filterImage(image.rows, image.cols, CV_32F, Scalar(0)); // Ensure float type

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			float sum = 0.0;

			for (int kx = -pad; kx <= pad; kx++) {
				for (int ky = -pad; ky <= pad; ky++) {
					float kernelValue = kernel.at<float>(kx + pad, ky + pad);
					float pixelValue = (float)paddedImage.at<uchar>(r + kx, c + ky);
					sum += static_cast<float>(pixelValue) * kernelValue;
				}
			}
			filterImage.at<float>(r - pad, c - pad) = sum;
		}
	}

	Mat displayImage;
	filterImage.convertTo(displayImage, CV_8U); // Convert for display

	Mat combinedImage;
	hconcat(image, displayImage, combinedImage);

	imshow(imageName, combinedImage);
	waitKey(0);
}

void exercise5_ws3(const string& imagePath, const string& imageName) {
	
	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = 3 / 2; // Kernel size / 2
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// Intermediate matrices for Sobel filter results
	Mat filterImageHorizontal(image.rows, image.cols, CV_32F, Scalar(0));
	Mat filterImageVertical(image.rows, image.cols, CV_32F, Scalar(0));
	Mat filterImageMagnitude(image.rows, image.cols, CV_32F, Scalar(0));

	// Sobel kernels
	float kernelx[3][3] = { {1, 0, -1},
							{2, 0, -2},
							{1, 0, -1} };

	float kernely[3][3] = { {1, 2, 1},
							{0, 0, 0},
							{-1, -2, -1} };

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			float sum_x = 0, sum_y = 0; // Sums for both axes

			for (int kx = -pad; kx <= pad; kx++) { // Kernel x
				for (int ky = -pad; ky <= pad; ky++) { // Kernel y
					float pixel_value = static_cast<float>(paddedImage.at<uchar>(r + kx, c + ky));
					sum_x += pixel_value * kernelx[kx + pad][ky + pad];  // Convolution with Sobel X
					sum_y += pixel_value * kernely[kx + pad][ky + pad];  // Convolution with Sobel Y
				}
			}

			// Sobel results
			filterImageHorizontal.at<float>(r - pad, c - pad) = sum_x;
			filterImageVertical.at<float>(r - pad, c - pad) = sum_y;

			// Magnitude (combined Sobel X and Y results)
			float magnitude = sqrt(sum_x * sum_x + sum_y * sum_y);
			filterImageMagnitude.at<float>(r - pad, c - pad) = magnitude;
		}
	}

	// Low-pass filter results
	Mat lowPassSobelHorizontal = lowpassFilter(image, filterImageHorizontal, pad);
	Mat lowPassSobelVertical = lowpassFilter(image, filterImageVertical, pad);
	Mat lowPassSobelMagnitude = lowpassFilter(image, filterImageMagnitude, pad);

	// Normalize low-pass results for visualization
	Mat lowPassHorizontalDisplay, lowPassVerticalDisplay, lowPassMagnitudeDisplay;
	normalize(lowPassSobelHorizontal, lowPassHorizontalDisplay, 0, 255, NORM_MINMAX, CV_8UC1);
	normalize(lowPassSobelVertical, lowPassVerticalDisplay, 0, 255, NORM_MINMAX, CV_8UC1);
	normalize(lowPassSobelMagnitude, lowPassMagnitudeDisplay, 0, 255, NORM_MINMAX, CV_8UC1);

	// Combine images for visualization
	Mat combinedImage, combinedImage2, combinedImage3;
	hconcat(image, lowPassHorizontalDisplay, combinedImage);
	hconcat(combinedImage, lowPassVerticalDisplay, combinedImage2);
	hconcat(combinedImage2, lowPassMagnitudeDisplay, combinedImage3);
	
	// Add labels to indentify each section
	putText(combinedImage3, "Original", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	putText(combinedImage3, "Horizontal", Point(450, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	putText(combinedImage3, "Vertical", Point(800, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	putText(combinedImage3, "Magnitude", Point(1100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

	// Display the final combined image
	imshow(imageName, combinedImage3);
	waitKey(0);
}

void exercise6_ws3(const string& imagePath, const string& imageName) {
	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		cerr << "Error: Image not found!" << endl;
		return;
	}

	Mat paddedImage;
	int pad = 3 / 2; // pad is equal to kernel/2
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1-channel image to serve as final reference
	Mat filterLaplace(image.rows, image.cols, CV_32F, Scalar(0));

	// Laplacian kernel
	float kernel[3][3] = {
		{0, 1, 0},
		{1, -4, 1},
		{0, 1, 0}
	};

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			float sum = 0.0f;

			for (int kx = -pad; kx <= pad; kx++) { // go through x
				for (int ky = -pad; ky <= pad; ky++) { // go through y
					float pixel_value = static_cast<float>(paddedImage.at<uchar>(r + kx, c + ky));
					sum += pixel_value * kernel[kx + pad][ky + pad]; // Convolution with Laplace
				}
			}

			filterLaplace.at<float>(r - pad, c - pad) = sum;
		}
	}

	// Low-pass filter
	Mat lowPassLaplace = lowpassFilter(image, filterLaplace, pad);

	// Normalize for display
	Mat filterLaplaceDisplay, lowPassLaplaceDisplay;
	normalize(filterLaplace, filterLaplaceDisplay, 0, 255, NORM_MINMAX, CV_8UC1);
	normalize(lowPassLaplace, lowPassLaplaceDisplay, 0, 255, NORM_MINMAX, CV_8UC1);

	// Combine images for visualization
	Mat combinedImage, combinedImage2;
	hconcat(image, filterLaplaceDisplay, combinedImage);
	hconcat(combinedImage, lowPassLaplaceDisplay, combinedImage2);

	// Add labels to indentify each section
	putText(combinedImage2, "Original", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	putText(combinedImage2, "Laplace", Point(450, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	putText(combinedImage2, "Low pass", Point(800, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);

	// Display the final combined image
	imshow(imageName, combinedImage2);
	waitKey(0);
}

Mat lowpassFilter(Mat& originalImage, Mat& filteredImage, int pad) {
	Mat paddedImage;
	Mat lowPass(originalImage.rows, originalImage.cols, CV_32F, Scalar(0));
	copyMakeBorder(filteredImage, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT, Scalar(0));

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			float sum = 0.0f;

			for (int kx = -pad; kx <= pad; kx++) {
				for (int ky = -pad; ky <= pad; ky++) {
					sum += paddedImage.at<float>(r + kx, c + ky);
				}
			}

			// Average the kernel values
			lowPass.at<float>(r - pad, c - pad) = sum / (3 * 3);
		}
	}

	return lowPass;
}