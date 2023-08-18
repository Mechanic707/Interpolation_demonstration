#include <opencv.hpp>
#include <iostream>
#include "mymath.h"
//#include <math.h>

using namespace cv;
using namespace std;

#define WIDTH 800.0
#define HEIGHT 1000.0


void drawPoint(Mat& src, Point2f scatter);
void drawLine(Mat& src, Point2f start, Point2f end);
void drawPos(Mat& src, Point2f point, float theta);
int quadrant_feedback(Point2f start, Point2f end);
void Linear_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y);
void Linear_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y, int quadrant);
void Linear_Interpolation(Mat& src, Point2f* continuous, float step_x, float step_y, int quadrant);
void Linear_Interpolation(Mat& src, Point2f* continuous, int num, float step_x, float step_y);

void Arc_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y, float step_angle);
void Arc_Interpolation(Mat& src, Point2f start, Point2f end, float step_angle);





int main()
{
	Point2f start = Point2f(-200, 0);
	Point2f end = Point2f(200, 0);
	int num = 4;
	Point2f* continuous = new Point2f[num];
	continuous[0] = Point2f(-250, -100);
	continuous[1] = Point2f(-25.0, 10);
	continuous[2] = Point2f(25.0, 300);
	continuous[3] = Point2f(35.0, -300);
	//cout << continuous[4].x << endl;
	//continuous[4] = Point2f(35.0, -300);
	//cout << continuous[4].x << endl;

	Mat src = cv::Mat(HEIGHT, WIDTH, CV_8UC3, Scalar::all(255));

	Point2f zero = Point2f(WIDTH/2, HEIGHT/2);	
	line(src, Point2f(0, HEIGHT / 2), Point2f(WIDTH, HEIGHT / 2), Scalar(0, 255, 255), 2, LINE_AA);
	line(src, Point2f(WIDTH / 2, 0), Point2f(WIDTH / 2, HEIGHT), Scalar(0, 255, 255), 2, LINE_AA);
	circle(src, zero, 3, Scalar(0, 0, 0), -1);
	drawLine(src, start, end);
	imshow("直线插补", src);
	
	//int quadrant = quadrant_feedback(start, end);

	float step_x = 0.01;
	float step_y = 0.01;

	//Linear_Interpolation(src, continuous, step_x, step_y, quadrant);
	//Linear_Interpolation(src, start, end, step_x, step_y, quadrant);
	//Linear_Interpolation(src, continuous, num, step_x, step_y);
	Arc_Interpolation(src, start, end, 12.0);

	//drawPos(src, Point2f(0, 0), -135);

	imshow("直线插补", src);
	waitKey(0);
	return 0;
}


void drawPoint(Mat& src, Point2f scatter)
{
	scatter.x += WIDTH / 2;
	scatter.y = HEIGHT / 2 - scatter.y;
	circle(src, scatter, 1.5, Scalar(0, 0, 255), -1);
}

void drawLine(Mat& src, Point2f start, Point2f end)
{
	start.x += WIDTH / 2;
	start.y = HEIGHT / 2 - start.y;
	end.x += WIDTH / 2;
	end.y = HEIGHT / 2 - end.y;
	line(src, start, end, Scalar(0, 0, 0), 1, LINE_AA);
}

void drawPos(Mat& src, Point2f point, float theta)
{
	point.x += WIDTH / 2;
	point.y = HEIGHT / 2 - point.y;

	float length = 50.0;
	arrowedLine(src, point, Point(point.x + length * cos_deg(theta), point.y - length * sin_deg(theta)), Scalar(0, 255, 0), 1, 8, 0, 0.05);//
	putText(src, "x", Point(point.x + length * cos_deg(theta), point.y - length * sin_deg(theta)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0), 1, 8);
	arrowedLine(src, point, Point(point.x + length * cos_deg(theta + 90), point.y - length * sin_deg(theta + 90)), Scalar(0, 255, 0), 1, 8, 0, 0.05);//
	putText(src, "y", Point(point.x + length * cos_deg(theta + 90), point.y - length * sin_deg(theta + 90)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1, 8);
}

int quadrant_feedback(Point2f start, Point2f end)
{
	float delta_x = end.x - start.x;
	float delta_y = end.y - start.y;

	if (delta_x >= 0)
	{
		if (delta_y >= 0)
			return 1;
		else
			return 4;
	}
	else
	{
		if (delta_y >= 0)
			return 2;
		else
			return 3;
	}
}

void Linear_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y)
{
	float a = (end.y - start.y) / (end.x - start.x);
	float b = start.y - a * start.x;
	cout << "a = " << a << " " << "b = " << b << endl;

	float cal_y;
	float cal_x;

	Point2f scatter = start;
	scatter.x += step_x;
	drawPoint(src, scatter);

	while ((scatter.x <= end.x) && (scatter.y <= end.y))
	{
		cal_y = a * scatter.x + b;
		cal_x = (scatter.y - b) / a;
		if (cal_y >= scatter.y)
		{
			scatter.y += step_y;
		}
		else// (cal_x <= scatter.x)
		{
			scatter.x += step_x;
		}
		drawPoint(src, scatter);

		imshow("直线插补", src);
		waitKey(1);
	}
}

void Linear_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y, int quadrant)
{
	float a = (end.y - start.y) / (end.x - start.x);
	float b = start.y - a * start.x;
	cout << "a = " << a << " " << "b = " << b << endl;

	float cal_y;
	float cal_x;
	Point2f scatter = start;


	if (quadrant == 1)
	{
		scatter.x += step_x;
		drawPoint(src, scatter);

		while ((scatter.x <= end.x) && (scatter.y <= end.y))
		{
			cal_y = a * scatter.x + b;
			cal_x = (scatter.y - b) / a;
			if (cal_y >= scatter.y)
			{
				scatter.y += step_y;
			}
			else// (cal_x <= scatter.x)
			{
				scatter.x += step_x;
			}
			drawPoint(src, scatter);

			imshow("直线插补", src);
			waitKey(1);
		}
	}

	if (quadrant == 2)
	{
		scatter.x -= step_x;
		drawPoint(src, scatter);

		while ((scatter.x >= end.x) && (scatter.y <= end.y))
		{
			cal_y = a * scatter.x + b;
			cal_x = (scatter.y - b) / a;
			if (cal_y >= scatter.y)
			{
				scatter.y += step_y;
			}
			else// (cal_x <= scatter.x)
			{
				scatter.x -= step_x;
			}
			drawPoint(src, scatter);

			imshow("直线插补", src);
			waitKey(1);
		}
	}
	
	if (quadrant == 3)
	{
		scatter.x -= step_x;
		drawPoint(src, scatter);

		while ((scatter.x >= end.x) && (scatter.y >= end.y))
		{
			cal_y = a * scatter.x + b;
			cal_x = (scatter.y - b) / a;
			if (cal_y <= scatter.y)
			{
				scatter.y -= step_y;
			}
			else// (cal_x <= scatter.x)
			{
				scatter.x -= step_x;
			}
			drawPoint(src, scatter);

			imshow("直线插补", src);
			waitKey(1);
		}
	}

	if (quadrant == 4)
	{
		scatter.x += step_x;
		drawPoint(src, scatter);

		while ((scatter.x <= end.x) && (scatter.y >= end.y))
		{
			cal_y = a * scatter.x + b;
			cal_x = (scatter.y - b) / a;
			if (cal_y <= scatter.y)
			{
				scatter.y -= step_y;
			}
			else// (cal_x <= scatter.x)
			{
				scatter.x += step_x;
			}
			drawPoint(src, scatter);

			imshow("直线插补", src);
			waitKey(1);
		}
	}
}


void Linear_Interpolation(Mat& src, Point2f* continuous, float step_x, float step_y, int quadrant)
{
	//cout << sizeof(continuous) << endl;
	cout << continuous[5].x << endl;
	//continuous[3] = Point2f(-25.0, 1.0);
	//cout << sizeof(continuous) << endl;
}

void Linear_Interpolation(Mat& src, Point2f* continuous, int num, float step_x, float step_y)
{
	Point2f start;
	Point2f end;
	int start_num, end_num;
	for(int i =0;i<num - 1;i++)
	{
		start_num = i;
		end_num = start_num + 1;
		start = continuous[start_num];
		end = continuous[end_num];
		int quadrant = quadrant_feedback(start, end);
		Linear_Interpolation(src, start, end, step_x, step_y, quadrant);
	}
	//int quadrant = quadrant_feedback(start, end);
}


//平向
void Arc_Interpolation(Mat& src, Point2f start, Point2f end, float step_x, float step_y, float step_angle)
{
	int quadrant = quadrant_feedback(start, end);
	cout << "quadrant = " << quadrant << endl;
	Point2f mid;
	mid.x = (start.x + end.x) / 2.0;
	mid.y = (start.y + end.y) / 2.0;
	float r = sqrt(pow((end.x - mid.x), 2) + pow((end.y - mid.y), 2));

	int Point_num = (int)(180.0 / step_angle);
	cout << "Point_num = " << Point_num << endl;

	Point2f* continuous = new Point2f[Point_num];


	float alpha = atan_deg((end.y - start.y) / (end.x - start.x));
	cout << "alpha = " << alpha << endl;

	float theta = 0.0;

	if (quadrant == 1)
	{
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x - r * cos_deg(theta - alpha);
			continuous[i].y = mid.y + r * sin_deg(theta - alpha);

			theta += step_angle;
			//cout << " ( " << continuous[i].x << ", " << continuous[i].y << ")" << endl;
			//drawPoint(src, continuous[i]);
		}
	}

	if (quadrant == 2)
	{
		alpha += 180.0;
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x - r * cos_deg(theta + alpha);
			continuous[i].y = mid.y - r * sin_deg(theta + alpha);

			theta += step_angle;
		}
	}

	if (quadrant == 3)
	{
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x + r * cos_deg(theta + alpha);
			continuous[i].y = mid.y + r * sin_deg(theta + alpha);

			theta += step_angle;
		}
	}
	
	if (quadrant == 4)
	{
		alpha += 180.0;
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x + r * cos_deg(theta - alpha);
			continuous[i].y = mid.y - r * sin_deg(theta - alpha);

			theta += step_angle;
		}
	}

	Linear_Interpolation(src, continuous, Point_num, step_x, step_y);
}

void Arc_Interpolation(Mat& src, Point2f start, Point2f end, float step_angle)
{
	int quadrant = quadrant_feedback(start, end);
	cout << "quadrant = " << quadrant << endl;
	Point2f mid;
	mid.x = (start.x + end.x) / 2.0;
	mid.y = (start.y + end.y) / 2.0;
	float r = sqrt(pow((end.x - mid.x), 2) + pow((end.y - mid.y), 2));

	int Point_num = (int)(180.0 / step_angle);
	cout << "Point_num = " << Point_num << endl;

	Point2f* continuous = new Point2f[Point_num];


	float alpha = atan_deg((end.y - start.y) / (end.x - start.x));
	cout << "alpha = " << alpha << endl;

	float theta = 0.0;

	if (quadrant == 1)
	{
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x - r * cos_deg(theta - alpha);
			continuous[i].y = mid.y + r * sin_deg(theta - alpha);

			drawPoint(src, continuous[i]);
			drawPos(src, continuous[i], 90 - theta + alpha);
			theta += step_angle;
			//cout << " ( " << continuous[i].x << ", " << continuous[i].y << ")" << endl;
			
		}
	}

	if (quadrant == 2)
	{
		alpha += 180.0;
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x - r * cos_deg(theta + alpha);
			continuous[i].y = mid.y - r * sin_deg(theta + alpha);

			drawPoint(src, continuous[i]);
			theta += step_angle;
			
		}
	}

	if (quadrant == 3)
	{
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x + r * cos_deg(theta + alpha);
			continuous[i].y = mid.y + r * sin_deg(theta + alpha);

			drawPoint(src, continuous[i]);
			theta += step_angle;
			
		}
	}

	if (quadrant == 4)
	{
		alpha += 180.0;
		for (int i = 0; i <= Point_num; i++)
		{
			continuous[i].x = mid.x + r * cos_deg(theta - alpha);
			continuous[i].y = mid.y - r * sin_deg(theta - alpha);

			drawPoint(src, continuous[i]);
			drawPos(src, continuous[i], 270 - theta + alpha);
			theta += step_angle;
			
		}
	}
}