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
	Mat Gauss(kernelSize, kernelSize, CV_64F, Scalar(0));

	// Fill the kernel using the Gaussian formula
	for (int i = -w; i <= w; i++) {
		for (int j = -w; j <= w; j++) {
			double value = (1 / (2 * 3.14 * sigma * sigma)) *
				exp(-((i * i + j * j) / (2 * sigma * sigma))); // gaussian formula
			// the value is applied to the matrix created
			Gauss.at<double>(i + w, j + w) = value; 
		}
	}
	// Normalize the kernel
	Gauss /= sum(Gauss)[0]; // Normalize so the sum of all elements equals 1
	
	return Gauss;
}

void exercise4_ws3(const string& imagePath, const string& imageName, Mat kernel, int kernelSize) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = kernelSize / 2; // pad is equal to the kernel/2 
	// Create a padded image
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1 channel image to serve as final reference
	Mat filterImage(image.rows, image.cols, CV_8UC1, Scalar(0));

	// Loop through each pixel of the padded image, excluding the padding borders.
	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			double sum = 0; // Change to double to match kernel type
			// Loop through the kernel region centered at (r, c)
			// Accumulate the sum of all pixel intensities in the kernel.
			for (int kx = -pad; kx <= pad; kx++) { // Go through x 
				for (int ky = -pad; ky <= pad; ky++) { // Go through y
					// Correct data type: access kernel as double
					double kernelValue = kernel.at<double>(kx + pad, ky + pad); // Use CV_64F type
					uchar pixelValue = paddedImage.at<uchar>(r + kx, c + ky);

					// Multiply and accumulate the result / Convolve
					sum += static_cast<double>(pixelValue) * kernelValue;
				}
			}
			// Assign the result to the output image pixels (without padding)
			filterImage.at<uchar>(r - pad, c - pad) = static_cast<uchar>(round(sum));
		}
	}

	// join the images in an imshow
	Mat combinedImage;
	hconcat(image, filterImage, combinedImage); // Combine original and filtered images side by side

	imshow(imageName, combinedImage);
	waitKey(0);
}

void exercise5_ws3(const string& imagePath, const string& imageName) {
	
	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = 3 / 2; // pad is equal to the kernel/2 
	// Create a padded image
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1 channel image to serve as final reference
	Mat filterImageHorizontal(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat filterImageVertical(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat filterImageMagnitude(image.rows, image.cols, CV_8UC1, Scalar(0));

	float kernelx[3][3] = { {1, 0, -1},
							{2, 0, -2},
							{1, 0, -1} };

	float kernely[3][3] = { {1, 2, 1},
							{0, 0, 0},
							{-1, -2, -1} };

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {

			int sum_x = 0, sum_y = 0; // sumn for both axis

			for (int kx = -pad; kx <= pad; kx++) { // go through x 
				for (int ky = -pad; ky <= pad; ky++) { // go through y
					int pixel_value = paddedImage.at<uchar>(r + kx, c + ky);
					sum_x += pixel_value * kernelx[kx + pad][ky + pad];  // Convolution with Sobel X
					sum_y += pixel_value * kernely[kx + pad][ky + pad];  // Convolution with Sobel Y
				}
			}

			// Sobel x results / horizontal
			filterImageHorizontal.at<uchar>(r - pad, c - pad) = static_cast<int>(round(float(sum_x)));
			// Sobel x results / horizontal
			filterImageVertical.at<uchar>(r - pad, c - pad) = static_cast<int>(round(float(sum_y)));

			// Combine Sobel X and Y results
			int magnitude = sqrt(sum_x * sum_x + sum_y * sum_y);
			filterImageMagnitude.at<uchar>(r - pad, c - pad) = static_cast<int>(round(magnitude));
		}
	}
	
	// low pass filter
	Mat lowPassSobelHorizontal = lowpassFilter(image, filterImageHorizontal, pad);
	Mat lowPassSobelVertical = lowpassFilter(image, filterImageVertical, pad);
	Mat lowPassSobelMagnitude = lowpassFilter(image, filterImageMagnitude, pad);

	// Combine images for visualization
	Mat combinedImage;
	Mat combinedImage2;
	Mat combinedImage3;

	hconcat(image, lowPassSobelHorizontal, combinedImage);
	hconcat(combinedImage, lowPassSobelVertical, combinedImage2);
	hconcat(combinedImage2, lowPassSobelMagnitude, combinedImage3);


	// Display the final combined image
	imshow(imageName, combinedImage3);
	waitKey(0);

}

void exercise6_ws3(const string& imagePath, const string& imageName) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);
	Mat paddedImage;
	int pad = 3 / 2; // pad is equal to the kernel/2 
	// Create a padded image
	copyMakeBorder(image, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT);

	// 1 channel image to serve as final reference
	Mat filterLaplace(image.rows, image.cols, CV_8UC1, Scalar(0));

	float kernel[3][3] = {	{0, 1, -1},
							{1, -4, 1},
							{0, 1, 0}};

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {

			int sum = 0;

			for (int kx = -pad; kx <= pad; kx++) { // go through x 
				for (int ky = -pad; ky <= pad; ky++) { // go through y
					int pixel_value = paddedImage.at<uchar>(r + kx, c + ky);
					sum += pixel_value * kernel[kx + pad][ky + pad];  // Convolution with Laplace
				}
			}

			// Laplace result
			filterLaplace.at<uchar>(r - pad, c - pad) = static_cast<int>(round(float(sum)));
		}
	}

	// low pass filter
	Mat lowPassLaplace = lowpassFilter(image, filterLaplace, pad);

	// Combine images for visualization
	Mat combinedImage;
	Mat combinedImage2;
	hconcat(image, filterLaplace, combinedImage);
	hconcat(combinedImage, lowPassLaplace, combinedImage2);

	// Display the final combined image
	imshow(imageName, combinedImage2);
	waitKey(0);
}

Mat lowpassFilter(Mat& orignalImage, Mat& filteredImage, int pad) {

	// Apply a low-pass filter to the horizontal Sobel output
	Mat paddedImage;
	Mat lowPass(orignalImage.rows, orignalImage.cols, CV_8UC1, Scalar(0));
	copyMakeBorder(filteredImage, paddedImage, pad, pad, pad, pad, BORDER_CONSTANT, Scalar(0));

	for (int r = pad; r < paddedImage.rows - pad; r++) {
		for (int c = pad; c < paddedImage.cols - pad; c++) {
			int sum = 0;

			for (int kx = -pad; kx <= pad; kx++) {
				for (int ky = -pad; ky <= pad; ky++) {
					sum += paddedImage.at<uchar>(r + kx, c + ky);
				}
			}

			// Average the kernel values
			lowPass.at<uchar>(r - pad, c - pad) = saturate_cast<uchar>(sum / (3 * 3));
		}
	}
	return lowPass;
}