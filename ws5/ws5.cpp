#include "functions.h"

Mat thresholdMethods(const string& imagePath, string method, string mode) {

	Mat image = imread(imagePath, IMREAD_GRAYSCALE);

	Mat binaryImage = Mat::zeros(image.size(), image.type()); // Initialize with zeros (all black)
	
	if (method == "manual" && mode == "normal") { // manual
		threshold(image, binaryImage, 200, 255, THRESH_BINARY);
	}
    else if (method == "manual" && mode == "inverted") {
        threshold(image, binaryImage, 200, 255, THRESH_BINARY_INV);
    }
	else if (method == "mean" && mode == "normal") { // mean
		Scalar mean_value = cv::mean(image);
		double mean = mean_value[0];  // Grayscale image has only one channel
		// Apply thresholding using the mean value
		threshold(image, binaryImage, mean, 255, THRESH_BINARY);
	}
    else if (method == "mean" && mode == "inverted") {
        Scalar mean_value = cv::mean(image);
        double mean = mean_value[0];  // Grayscale image has only one channel
        // Apply thresholding using the mean value
        threshold(image, binaryImage, mean, 255, THRESH_BINARY_INV);
    }
	else if (method == "otsu" && mode == "normal") { // otsu
		threshold(image, binaryImage, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
	}
    else if (method == "otsu" && mode == "inverted") {
        threshold(image, binaryImage, 0, 255, THRESH_BINARY + THRESH_OTSU);
    }
    // adaptative (blocksize is the kernel. AN ODD NUMBERS ONLY!!)
	else if (method == "adaptative" && mode == "normal") { 
		adaptiveThreshold(image, binaryImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 201, 10);
	}
    else if (method == "adaptative" && mode == "inverted") {
        (image, binaryImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 201, 10);
    }
	return binaryImage;
}

void exercise1_ws5(const string& imagePath, const string& imageName, string method){

    Mat image;
    if (method != "otsu") {
         image = thresholdMethods(imagePath, method, "inverted");
    }else image = thresholdMethods(imagePath, method, "normal");

    imshow("Thresholding", image);
    waitKey(0);
}

Mat imageLabelling(Mat& image, int areaValue, string ws4Flag) {

    Mat labels, stats, centroids;

    string side;

    // for exercise 4 pixel spacing
    double pixelSpacing = 0.8;
    int colsSizePixels = image.cols * pixelSpacing;
    int rowsSizePixels = image.rows * pixelSpacing;
    int midColSizePixels = colsSizePixels / 2;

    // Find connected components
    int numLabels = connectedComponentsWithStats(image, labels, stats, centroids);
    int objectNumber = 0;

    // Create a copy of the image for output after blob removal
    Mat resultImage = image.clone();

    // Iterate through the components and remove small areas
    for (int i = 1; i < numLabels; i++) {
        int area = stats.at<int>(i, CC_STAT_AREA);
        // Remove small objects (less than 10000 area)
        if (area < areaValue) {
            for (int y = 0; y < labels.rows; y++) {
                for (int x = 0; x < labels.cols; x++) {
                    if (labels.at<int>(y, x) == i) {
                        resultImage.at<uchar>(y, x) = 0;  // Set to background (0)
                    }
                }
            }
        }
        else {
            objectNumber++;
 
            // Width and Height
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            // Centroid x and y
            Point2d centroid(centroids.at<double>(i, 0), centroids.at<double>(i, 1));
            if (ws4Flag == "activate") {
                if ((centroid.x * pixelSpacing) < midColSizePixels)
                    side = "left";
                
                else
                    side = "right";
            }
            
            // Extract blob mask for this label
            Mat blobMask = (labels == i);

            // Perimeter
            vector<vector<Point>> contours;
            findContours(blobMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            double perimeter = 0.0;
            if (!contours.empty()) {
                perimeter = arcLength(contours[0], true);
            }

            // Orientation and Eccentricity using Moments
            Moments moments = cv::moments(blobMask, true);
            double mu20 = moments.mu20 / moments.m00;
            double mu02 = moments.mu02 / moments.m00;
            double mu11 = moments.mu11 / moments.m00;

            double theta = 0.5 * atan2(2 * mu11, mu20 - mu02); // Orientation in radians
            double orientation = theta * (180.0 / CV_PI);     // Convert to degrees

            // Eccentricity
            double numerator = (mu20 - mu02) * (mu20 - mu02) + 4 * mu11 * mu11;
            double denominator = (mu20 + mu02) * (mu20 + mu02);
            double eccentricity = sqrt(1 - (numerator / denominator));

            // Display properties
            cout << "Blob " << objectNumber << ":" << endl;
            cout << "Area: " << area << endl;
            cout << "Width: " << width << endl;
            cout << "Height: " << height << endl;
            cout << "Centroid: (" << centroid.x << ", " << centroid.y << ")" << endl;
            cout << "Orientation: " << orientation << " degrees" << endl;
            cout << "Eccentricity: " << eccentricity << endl;
            cout << "Perimeter: " << perimeter << endl;
            if (side == "left") cout << "Left Side" << endl;
            else if (side == "right") cout << "Right Side" << endl;
            cout << "--------------------------" << endl;

        }
    }
    return resultImage;
}

void exercise2_ws5() {
    // Load and process the image
    Mat image = thresholdMethods("beans.png", "otsu", "normal");
    Mat structElement = structuringElement(9, 1);
  
    Mat closingImage = closing(image, structElement);

    // (image, area, actiavate ws4)
    Mat imageLabbeled = imageLabelling(closingImage, 8000, "");

    // Resize
    Mat resizedImage, resizedImageOutput, outputImage;
    resize(image, resizedImage, Size(), 0.5, 0.5);
    resize(imageLabbeled, resizedImageOutput, Size(), 0.5, 0.5);

    hconcat(resizedImage, resizedImageOutput, outputImage);

    // Show the result
    imshow("Labelling", outputImage);
    waitKey(0);
}

void exercise3_ws5() {
    Mat image = thresholdMethods("kidney.png", "manual", "normal");
    Mat goal = imread("kidney_segmented.png", IMREAD_GRAYSCALE);

    // Morphology
    Mat strucElement1 = structuringElement(9, 1);
    Mat strucElement2 = structuringElement(9, 4);
    Mat imageClosing = closing(image, strucElement1);
    Mat imageErosion = erosion(imageClosing, strucElement2);

    // Labelling call (image, area, actiavate ws4)
    Mat imageLabbeled = imageLabelling(imageErosion, 8000, "activate");

    // Fill the labeled regions (after labelling)
    Mat filledImage = imageLabbeled.clone();  // Create a copy of the labeled image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // Find contours of the labeled regions
    findContours(filledImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Fill each contour
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(filledImage, contours, (int)i, Scalar(255), FILLED);  // Fill the regions with white color
    }

    Mat strucElement3 = structuringElement(9, 1);
    Mat imageDilation = dilation(filledImage, strucElement3);
    Mat imageClosing2 = closing(imageDilation, strucElement3);

    // Resize
    Mat resizedImage, resizedGoalImage, resizedImageOutput, firstConcat, secondConcat;
    resize(image, resizedImage, Size(), 0.5, 0.5);
    resize(goal, resizedGoalImage, Size(), 0.5, 0.5);
    resize(imageClosing2, resizedImageOutput, Size(), 0.5, 0.5);

    hconcat(resizedImage, resizedGoalImage, firstConcat);
    hconcat(firstConcat, resizedImageOutput, secondConcat);

    // Show the result
    imshow("Pipeline Kidney WS5", secondConcat);
    waitKey(0);

    // saving the image
    //Mat normalizedLabelImage;
    //normalize(imageClosing2, normalizedLabelImage, 0, 255, NORM_MINMAX, CV_8U);
    //imwrite("kidney_bad_example.png", normalizedLabelImage);
}

// ws4 inside ws3 on the labelling i use "activate".

void exercise5_ws5(const string& imageName, Mat& imageOutput, Mat& imageReference) {
    int TP = 0, FP = 0, FN = 0, TN = 0;

    // Loop through each pixel of the output and reference images
    for (int r = 0; r < imageOutput.rows; r++) {
        for (int c = 0; c < imageOutput.cols; c++) {
            int ref = imageReference.at<uchar>(r, c) > 0 ? 1 : 0;  // Binary value for reference
            int pred = imageOutput.at<uchar>(r, c) > 0 ? 1 : 0; // Binary value for prediction

            if (ref == 1 && pred == 1) ++TP; // True positive
            else if (ref == 0 && pred == 1) ++FP; // False positive
            else if (ref == 1 && pred == 0) ++FN; // False negative
            else if (ref == 0 && pred == 0) ++TN; // True negative
        }
    }

    // Calculate the metrics

    // Accuracy
    double accuracy = static_cast<double>(TP + TN) / (TP + FP + FN + TN);

    // Precision
    double precision = (TP + FP > 0) ? static_cast<double>(TP) / (TP + FP) : 0.0;

    // Recall
    double recall = (TP + FN > 0) ? static_cast<double>(TP) / (TP + FN) : 0.0;

    // Dice Coefficient
    double dice = (TP + TP > 0) ? (2.0 * TP) / (2.0 * TP + FP + FN) : 0.0;

    // Intersection over Union (IoU)
    double jaccard = (TP + FP + FN > 0) ? static_cast<double>(TP) / (TP + FP + FN) : 0.0;

    // Output the confusion matrix and metrics
    cout << std::fixed << std::setprecision(2);
    cout << "Confusion Matrix:\n";
    cout << "TP: " << TP << ", FP: " << FP << ", FN: " << FN << ", TN: " << TN << "\n";
    cout << "Metrics:\n";
    cout << "Accuracy: " << accuracy * 100 << "%\n";
    cout << "Precision: " << precision * 100 << "%\n";
    cout << "Recall: " << recall * 100 << "%\n";
    cout << "Dice Coefficient: " << dice * 100 << "%\n";
    cout << "Intersection over Union (IoU): " << jaccard * 100 << "%\n";

    // Resize images for displaying side by side
    Mat resizedImage, resizedGoalImage, concatOutput;
    resize(imageOutput, resizedImage, Size(), 0.5, 0.5);
    resize(imageReference, resizedGoalImage, Size(), 0.5, 0.5);

    // Concatenate the images horizontally
    hconcat(resizedImage, resizedGoalImage, concatOutput);

    // Show the result
    imshow(imageName, concatOutput);
    waitKey(0);
}
