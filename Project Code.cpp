#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <windows.h>
#include <string>


#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>

/*
draw rectangle
https://stackoverflow.com/questions/40120433/draw-rectangle-in-opencv



*/



using namespace std;
using namespace cv;
class ColorPoint {
private:
    int red, green, blue; string ColorClass; double distance;
public:

    ColorPoint(int x = 0, int y = 0, int z = 0, string color = "n/a") {
        if (x > 255)  // check if point value inserted is greater than max range
        {
            red = 255;
        }
        else if (y > 255)
        {
            green = 255;
        }
        else if (z > 255)
        {
            blue = 255;
        }
        else if (x < 0)  // check if point value inserted is less than min range
        {
            red = 0;
        }
        else if (y < 0)
        {
            green = 0;
        }
        else if (z < 0)
        {
            blue = 0;
        }
        else
        {
            red = x;
            green = y;
            blue = z;
        }
        ColorClass = color;
    }
    void setRED(int arg)
    {
        if (arg < 0)
        {
            red = 0;
        }
        else if (arg > 255)
        {
            red = 255;
        }
        else
        {
            red = arg;
        }
    }
    void setGREEN(int arg)
    {
        if (arg < 0)
        {
            green = 0;
        }
        else if (arg > 255)
        {
            green = 255;
        }
        else
        {
            green = arg;
        }
    }
    void setBLUE(int arg)
    {
        if (arg < 0)
        {
            blue = 0;
        }
        else if (arg > 255)
        {
            blue = 255;
        }
        else
        {
            blue = arg;
        }
    }
    void setDistance(double arg)
    {
        distance = arg;
    }
    void setColorClass(string arg)
    {
        ColorClass = arg;
    }
    int getRED(void)
    {
        return red;
    }
    int getGREEN(void)
    {
        return green;
    }
    int getBLUE(void)
    {
        return blue;
    }
    double getDistance(void)
    {
        return distance;
    }
    string getColorClass(void)
    {
        return ColorClass;
    }
    void printColorCode(void)
    {
        cout << "(" << getRED() << ", " << getGREEN() << ", " << getBLUE() << ")";
    }

    void Print_Unknown_Color(void)
    {
        cout << "The unknown color is " << getColorClass() << endl;
    }
    void Print_Color()
    {
        cout << "The color is " << getColorClass() << "\n";
        cout << "The red value is " << getRED() << "\n";
        cout << "The green value is " << getGREEN() << "\n";
        cout << "The blue value is " << getBLUE() << "\n";
        cout << "The distance value is " << getDistance() << "\n\n";

    }
    void Define_Color(int Red, int Green, int Blue, string Color_Class)
    {
        setRED(Red);
        setGREEN(Green);
        setBLUE(Blue);
        setColorClass(Color_Class);

    }
    void Define_Unknown_Color(int Red, int Green, int Blue)
    {
        setRED(Red);
        setGREEN(Green);
        setBLUE(Blue);
        setColorClass("Unknown");
    }
};
class IMPKNN {
public:

    ColorPoint red = ColorPoint(255, 0, 0, "red");
    ColorPoint green = ColorPoint(0, 255, 0, "green");
    ColorPoint blue = ColorPoint(0, 0, 255, "blue");
    ColorPoint purple = ColorPoint(127, 0, 255, "purple");
    ColorPoint yellow = ColorPoint(255, 255, 0, "yellow");
    ColorPoint orange = ColorPoint(255, 128, 0, "orange");
    ColorPoint black = ColorPoint(0, 0, 0, "black");
    ColorPoint white = ColorPoint(255, 255, 255, "white");
    vector<ColorPoint> pointsVECT{ red, green, blue, yellow, black, white,orange,purple }; // stores points
    // add purple and orange
    ColorPoint Findmin() {
        ColorPoint min = pointsVECT[0]; // set first element to compare to the rest
        for (int i = 1; i < pointsVECT.size(); i++) { // find distance for all colors
            if (min.getDistance() > pointsVECT[i].getDistance()) // compare smallest distance with next distance in list
            {
                min = pointsVECT[i];
            }
        }
        return min;
    }
    string classify(ColorPoint arg) {

        for (int i = 0; i < pointsVECT.size(); i++) { // find distance for all colors sqrt(  (x1-x2)^2  +  (y1-y2)^2  +  (z1-z2)^2)
            pointsVECT[i].setDistance(sqrt((pointsVECT[i].getRED() - arg.getRED()) * (pointsVECT[i].getRED() - arg.getRED()) + (pointsVECT[i].getGREEN() - arg.getGREEN()) * (pointsVECT[i].getGREEN() - arg.getGREEN()) + (pointsVECT[i].getBLUE() - arg.getBLUE()) * (pointsVECT[i].getBLUE() - arg.getBLUE())));
        }
        ColorPoint closest = Findmin(); // sorting alg which finds the nearest point
        return closest.getColorClass(); // returns nearest point
    }
    void IMPKNNprompt(void)
    {
        cout << "\nIMPKNNprompt" << endl;
        ColorPoint unknown = ColorPoint(0, 0, 0, "unknown"); // temp color point used for classifing

        int inputloop = 0, input;
        while (inputloop == 0) { // input loop for unknown

            cout << "Enter a red value: ";
            cin >> input;
            unknown.setRED(input);

            cout << "Enter a green value: ";
            cin >> input;
            unknown.setGREEN(input);

            cout << "Enter a blue value: ";
            cin >> input;
            unknown.setBLUE(input);

            cout << "Entered color code"; unknown.printColorCode(); cout << endl;

            cout << "Point is closest to: " << classify(unknown) << endl;
            char userResponse;
            cout << "\nWould you like to classify another point? (y or n): "; cin >> userResponse;
            cin.ignore(); // to clean up the input stream
            if (userResponse == 'n' || userResponse == 'N') { inputloop++; }
        }
    }
};
class Freq {
public:
    string name;
    int count;

    Freq() {
        count = 0;
        name = "Not yet assigned";
    }
    Freq(string Name)
    {
        name = Name;
        count = 0;
    }
    void Increase_Count(Freq F)
    {
        count = count + 1;
    }
};
class NaiveKNN
{
public:
    vector<ColorPoint> All_Color_Groups; // creating a vector that will have all the colors

    void Swap_Position_Color(ColorPoint& x, ColorPoint& y)
    {
        ColorPoint temp;

        temp = x;
        x = y;
        y = temp;
    }
    void Find_Distance(ColorPoint Unknown_Color)
    {
        for (int i = 0; i < All_Color_Groups.size(); i++)
        {
            All_Color_Groups[i].setDistance(sqrt((All_Color_Groups[i].getRED() - Unknown_Color.getRED()) * (All_Color_Groups[i].getRED() - Unknown_Color.getRED()) + (All_Color_Groups[i].getGREEN() - Unknown_Color.getGREEN()) * (All_Color_Groups[i].getGREEN() - Unknown_Color.getGREEN()) + (All_Color_Groups[i].getBLUE() - Unknown_Color.getBLUE()) * (All_Color_Groups[i].getBLUE() - Unknown_Color.getBLUE())));
        }

    }
    void Sort_Distances(vector<ColorPoint>& Vec)
    {
        // using bubble sort O(n^2)
        for (int i = 0; i < Vec.size(); i++) {

            for (int j = 0; j < Vec.size() - 1; j++) {

                if (Vec[j].getDistance() > Vec[j + 1].getDistance()) {
                    Swap_Position_Color(Vec[j], Vec[j + 1]);
                }
            }
        }
    }
    void Sort_Distances1(vector<ColorPoint>& Vec)
    {
        //O(nlgn)
        sort(Vec.begin(), Vec.end(), [](ColorPoint& lhs, ColorPoint& rhs) {return lhs.getDistance() < rhs.getDistance(); });
    }
    void Classify_Unknown_Color_KNN(ColorPoint& Unknown_Color, int sortType)
    {
        Find_Distance(Unknown_Color);

        if (sortType == 1)
        {
            Sort_Distances(All_Color_Groups);
        }
        else
        {
            Sort_Distances1(All_Color_Groups);
        }

        int K = sqrt(All_Color_Groups.size());

        if ((K % 2) == 0) // if K is even, add one to make it Odd
        {
            K = K + 1;
        }

        Freq R("Red"), B("Blue"), G("Green");
        Freq Y("Yellow"), P("Purple"), O("Orange");
        Freq Bl("Black"), W("White");

        for (int i = 0; i < K; i++)
        {
            if (All_Color_Groups[i].getColorClass() == "Red")
            {
                R.Increase_Count(R);
            }
            else if (All_Color_Groups[i].getColorClass() == "Blue")
            {
                B.Increase_Count(B);
            }
            else if (All_Color_Groups[i].getColorClass() == "Orange")
            {
                O.Increase_Count(O);
            }
            else if (All_Color_Groups[i].getColorClass() == "Yellow")
            {
                Y.Increase_Count(Y);
            }
            else if (All_Color_Groups[i].getColorClass() == "Purple")
            {
                P.Increase_Count(P);
            }
            else if (All_Color_Groups[i].getColorClass() == "Green")
            {
                G.Increase_Count(G);
            }
            else if (All_Color_Groups[i].getColorClass() == "Black")
            {
                Bl.Increase_Count(Bl);
            }
            else if (All_Color_Groups[i].getColorClass() == "White")
            {
                W.Increase_Count(W);
            }
        }
        vector<Freq> Freq_Colors;
        Freq_Colors.push_back(R), Freq_Colors.push_back(B);
        Freq_Colors.push_back(G), Freq_Colors.push_back(Y);
        Freq_Colors.push_back(P), Freq_Colors.push_back(O);
        Freq_Colors.push_back(Bl), Freq_Colors.push_back(W);

        /*
         for (int i = 0; i < Freq_Colors.size(); i++)
         {
         cout << "The color is " << Freq_Colors[i].name << ".\n";
         cout << "The count is " << Freq_Colors[i].count << ".\n\n";
         }
         */
        Freq max = Freq_Colors[0];
        for (int i = 1; i < Freq_Colors.size(); i++)
        {
            if (Freq_Colors[i].count > max.count)
            {
                max = Freq_Colors[i];
            }
        }
        Unknown_Color.setColorClass(max.name);
    }
    void Print_Distances(void)
    {
        for (int i = 0; i < All_Color_Groups.size(); i++)
        {
            cout << "At index " << i << " the distance from the unknown color is " << All_Color_Groups[i].getDistance() << "\n";
        }
    }
    void Create_Color_Group_Data_Points(vector<ColorPoint>& Color_Group, int Red_Max, int Red_Min, int Green_Max, int Green_Min, int Blue_Max, int Blue_Min, string Color_Class)
    {
        // need to find a way to automate this for all color groups to generate the data points

        random_device rd;

        uniform_real_distribution<double> dist_Red(Red_Min, Red_Max);
        uniform_real_distribution<double> dist_Blue(Blue_Min, Blue_Max);
        uniform_real_distribution<double> dist_Green(Green_Min, Green_Max);


        for (int i = 0; i < Color_Group.size(); i++)
        {
            Color_Group[i].Define_Color(dist_Red(rd), dist_Green(rd), dist_Blue(rd), Color_Class);

        }
    }
    void Print_Color_Group(vector<ColorPoint>& Color_Group)
    {
        for (int i = 0; i < Color_Group.size(); i++)
        {
            cout << "For index " << i << '\n';
            Color_Group[i].Print_Color();
        }
    }
    void initialize(int sizeOFeachClassification)
    {
        // The color values below can be changed if needed
        // Red : R - 255~204, G - 80~0, B 80~0
        // Blue : R - 30~0, G - 30~0, B - 255~204
        // Yellow : R- 255~224, G - 255~224, B - 120~0
        // Green : R - 80 ~ 0, G - 255~224, B 80 ~ 0
        // Orange : R - 255~224 , G - 150 ~ 100, B - 80 ~ 0
        // Purple : R - 170 ~ 76 , G - 50~0, B - 255~204


        vector<ColorPoint> Red_Group(sizeOFeachClassification);
        vector<ColorPoint> Blue_Group(sizeOFeachClassification);
        vector<ColorPoint> Yellow_Group(sizeOFeachClassification);
        vector<ColorPoint> Green_Group(sizeOFeachClassification);
        vector<ColorPoint> Orange_Group(sizeOFeachClassification);
        vector<ColorPoint> Purple_Group(sizeOFeachClassification);
        vector<ColorPoint> Black_Group(sizeOFeachClassification);
        vector<ColorPoint> White_Group(sizeOFeachClassification);

        Create_Color_Group_Data_Points(Red_Group, 255, 225, 30, 0, 30, 0, "Red"); // Color is good
        Create_Color_Group_Data_Points(Blue_Group, 30, 0, 30, 0, 255, 225, "Blue"); // Color is good
        Create_Color_Group_Data_Points(Yellow_Group, 255, 225, 255, 225, 30, 0, "Yellow"); // Color is good
        Create_Color_Group_Data_Points(Green_Group, 30, 0, 255, 225, 30, 0, "Green"); // Color is good
        Create_Color_Group_Data_Points(Orange_Group, 255, 225, 143, 113, 30, 0, "Orange"); // color is good
        Create_Color_Group_Data_Points(Purple_Group, 142, 112, 30, 0, 255, 225, "Purple"); // color is good
        Create_Color_Group_Data_Points(Black_Group, 30, 0, 30, 0, 30, 0, "Black");
        Create_Color_Group_Data_Points(White_Group, 255, 225, 255, 225, 255, 225, "White");

        All_Color_Groups.reserve(Red_Group.size() + Blue_Group.size() + Yellow_Group.size() + Green_Group.size() + Orange_Group.size() + Purple_Group.size() + Black_Group.size() + White_Group.size());
        All_Color_Groups.insert(All_Color_Groups.end(), Red_Group.begin(), Red_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Blue_Group.begin(), Blue_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Yellow_Group.begin(), Yellow_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Green_Group.begin(), Green_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Orange_Group.begin(), Orange_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Purple_Group.begin(), Purple_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), Black_Group.begin(), Black_Group.end());
        All_Color_Groups.insert(All_Color_Groups.end(), White_Group.begin(), White_Group.end());
    }
    void clearAllColorGroups(void)
    {
        All_Color_Groups.clear();
    }
    void NaiveKNNprompt(void)
    {
        cout << "\nNaiveKNNprompt" << endl;
        ColorPoint unknown = ColorPoint(0, 0, 0, "unknown"); // temp color point used for classifing

        int inputloop = 0, input;
        while (inputloop == 0) { // input loop for unknown

            cout << "Enter a red value: ";
            cin >> input;
            unknown.setRED(input);

            cout << "Enter a green value: ";
            cin >> input;
            unknown.setGREEN(input);

            cout << "Enter a blue value: ";
            cin >> input;
            unknown.setBLUE(input);

            cout << "Enter a size for each classification: ";
            cin >> input;
            initialize(input);

            cout << "Entered color code"; unknown.printColorCode(); cout << endl;

            Classify_Unknown_Color_KNN(unknown, 2);
            unknown.Print_Unknown_Color();
            clearAllColorGroups();

            char userResponse;
            cout << "\nWould you like to classify another point? (y or n): "; cin >> userResponse;
            cin.ignore(); // to clean up the input stream
            if (userResponse == 'n' || userResponse == 'N') { inputloop++; }
        }
    }
};
int main()
{
   // ColorPoint Unknown_Color;

    //Unknown_Color.Define_Color(5, 5, 5, "Unknown");
   // NaiveKNN N;
   // IMPKNN I;

   // N.NaiveKNNprompt(); prompt for naive KNN
    //I.IMPKNNprompt();

    
    
                 /* **************OPENCV Portion****************/

    VideoCapture capture(0); // passing 0 will open the default camera

    if (!capture.isOpened()) { // function that will check to see if the camera opened up properly
        cout << "Error opening VideoCapture." << endl;
        return -1;
    }


    Mat frame, image; // creating a variable named frame of Data Type matrix

    while (1)
    {	// this function will display the camera with the
        //cout << "The size of the frame is (" << frame.rows << " , " << frame.cols << ")" << endl;

       


        
        capture.read(frame);
        Rect r = Rect(260, 200, 120, 120);
        Rect r2 = Rect(270, 210, 100, 100);
        //create a Rect with top-left vertex at (260,200), of width 40 and height 60 pixels.
        rectangle(frame, r, Scalar(255, 255, 255), 1, 8, 0);
       //' rectangle(frame, r2, Scalar(0, 0, 0), 1, 8, 0);
        // the function above, the first argument is the under lying picture, the second argument is image going over the first immage
        // the three values in the () is the color of the box
        imshow("Livestream", frame);
        waitKey(1);// waits a input number of milliseconds or untill a key is pressed for the screen to stop showing
        int sum_Red = 0;
        int sum_Blue = 0;
        int sum_Green = 0;
        int counter = 0;
        
        for (int i = 210; i <= 310; i++) // y point
        {
            for (int j = 270; j <= 370; j++) // x point
            {
                sum_Blue = sum_Blue + frame.at<Vec3b>(j, i)[0];
                sum_Green = sum_Green + frame.at<Vec3b>(j, i)[1];
                sum_Red = sum_Red + frame.at<Vec3b>(j, i)[2];
                counter++;

            }
        }

        int Final_R = sum_Red / counter;
        int Final_G = sum_Green / counter;
        int Final_B = sum_Blue / counter;

        cout << "The RBG color is (" << Final_R << " , " << Final_G << " , " << Final_B << " )." << endl;
        IMPKNN impknn;
        ColorPoint unknown(Final_R, Final_G, Final_B,"unknown");
        cout << "The color is : " << impknn.classify(unknown) << endl;

        Sleep(1000); // pauses the program for 0.5 seconds
    }
    
    
    /*
    while (1)
    {
    for (int i = 0; i < frame.rows; i = 1+i)
        {
            for (int j = 0; j < frame.cols; j = 1 + j) {
                capture.read(frame);
                imshow("Livestream", frame);
                waitKey(50);

                cout << "The size of the frame is " << frame.rows << " by " << frame.cols << endl;
                int B = frame.at<Vec3b>(240, 320)[0];//getting the pixel values// // X is blue
                int G = frame.at<Vec3b>(240, 320)[1];//getting the pixel values// // Y is green
                int R = frame.at<Vec3b>(240, 320)[2];//getting the pixel values// Z is red
                cout << "At index (" << 240 << ",  " << 320 << ")" << endl;
                cout << "Value of red channel:" << R << endl;//showing the pixel values//
                cout << "Value of green channel:" << G << endl;//showing the pixel values//
                cout << "Value of blue channel:" << R << endl;//showing the pixel values//
                cout << endl;
                Sleep(1000);
                }
            }

        }
        */

    return 0;
}

/*
function will be used for displaying the camera

VideoCapture capture(0); // passing 0 will open the default camera

if (!capture.isOpened()) { // function that will check to see if the camera opened up properly
    std::cout << "Error opening VideoCapture." << std::endl;
    return -1;
}


Mat frame, image; // creating a variable named frame of Data Type matrix

while (1)
{	// this function will display the camera with the
    capture.read(frame);
    imshow("Livestream", frame);
    waitKey(50);
}
*/

/*
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <windows.h>
#include <string>


draw rectangle
https://stackoverflow.com/questions/40120433/draw-rectangle-in-opencv







using namespace std;
using namespace cv;

int main()
{
	


		VideoCapture capture(0); // passing 0 will open the default camera

		if (!capture.isOpened()) { // function that will check to see if the camera opened up properly
			cout << "Error opening VideoCapture." << endl;
			return -1;
		}


		Mat frame,image; // creating a variable named frame of Data Type matrix

		while (1)
		{	// this function will display the camera with the
			//cout << "The size of the frame is (" << frame.rows << " , " << frame.cols << ")" << endl;
			capture.read(frame);
			Rect r = Rect(260, 200, 120, 120);
			Rect r2 = Rect(270, 210, 100, 100);
			//create a Rect with top-left vertex at (260,200), of width 40 and height 60 pixels.
			rectangle(frame, r, Scalar(255, 255, 255), 1, 8, 0);
			rectangle(frame, r2, Scalar(0, 0, 0), 1, 8, 0);
			// the function above, the first argument is the under lying picture, the second argument is image going over the first immage
			// the three values in the () is the color of the box
			imshow("Livestream", frame);
			waitKey(1);// waits a input number of milliseconds or untill a key is pressed for the screen to stop showing
			int sum_Red = 0;
			int sum_Blue = 0;
			int sum_Green = 0;
			int counter = 0;

			for (int i = 210; i <= 310; i++) // y point
			{
				for (int j = 270; j <= 370; j++) // x point
				{
					sum_Blue = sum_Blue + frame.at<Vec3b>(j, i)[0];
					sum_Green = sum_Green + frame.at<Vec3b>(j, i)[1];
					sum_Red = sum_Red + frame.at<Vec3b>(j, i)[2];
					counter++;

				}
			}

			int Final_R = sum_Red / counter;
			int Final_G = sum_Green / counter;
			int Final_B = sum_Blue / counter;

			cout << "The RBG color is (" << Final_R << " , " << Final_G << " , " << Final_B << " )." << endl;
			Sleep(1000); // pauses the program for 0.5 seconds
		}
		
	
	while (1)
	{
	for (int i = 0; i < frame.rows; i = 1+i)
		{
			for (int j = 0; j < frame.cols; j = 1 + j) {
				capture.read(frame);
				imshow("Livestream", frame);
				waitKey(50);

				cout << "The size of the frame is " << frame.rows << " by " << frame.cols << endl;
				int B = frame.at<Vec3b>(240, 320)[0];//getting the pixel values// // X is blue
			    int G = frame.at<Vec3b>(240, 320)[1];//getting the pixel values// // Y is green
				int R = frame.at<Vec3b>(240, 320)[2];//getting the pixel values// Z is red
				cout << "At index (" << 240 << ",  " << 320 << ")" << endl;
				cout << "Value of red channel:" << R << endl;//showing the pixel values//
				cout << "Value of green channel:" << G << endl;//showing the pixel values//
				cout << "Value of blue channel:" << R << endl;//showing the pixel values//
				cout << endl;
				Sleep(1000);
				}
			}

		}
		
		
	return 0;
}


function will be used for displaying the camera

VideoCapture capture(0); // passing 0 will open the default camera

if (!capture.isOpened()) { // function that will check to see if the camera opened up properly
	std::cout << "Error opening VideoCapture." << std::endl;
	return -1;
}


Mat frame, image; // creating a variable named frame of Data Type matrix

while (1)
{	// this function will display the camera with the 
	capture.read(frame);
	imshow("Livestream", frame);
	waitKey(50);
}

*/