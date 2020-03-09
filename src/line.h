#ifndef _line_h
#define _line_h
#pragma once
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
#include<cmath>

#define MAXSLOPE 17373524.2
using namespace std;

class Line {
private:
	//Ax + By + C = 0;
	long long A, B, C;
public:
	void SetLine(long long x1, long long y1, long long x2, long long y2) {
		A = y2 - y1;
		B = x1 - x2;
		C = x2 * y1 - x1 * y2;
	}
	void SetLine1(long long a, long long b, long long c) {
		A = a;
		B = b;
		C = c;
	}
	//判断两条直线是否平行
	bool isParallel(Line line_2) {
		return A * line_2.B == B * line_2.A;
	}

	//求两条直线的交点，输入的两条直线不平行
	pair<double,double> getInterSect(Line line) {
		long long x = line.C * B - C * line.B;
		long long y = C * line.A - line.C * A;
		long long m = A * line.B - line.A * B;
		double x_real = double(x) / m;
		double y_real = double(y) / m;
		pair<double, double> intersection;
		intersection.first = x_real;
		intersection.second = y_real;
		//printf("%lf %lf\n", x_real, y_real);
		return intersection;
	}
	//获取直线的斜率
	double getSlope() {
		if (A == 0) {
			return 0;
		}
		else if (B == 0) {
			return MAXSLOPE;
		}
		else {
			return -double(A) / B;
		}
	}
	//得到直线的解析式
	string getFunc() {
		string x = "";
		x = to_string(A) + "x+" + to_string(B) + "y+" + to_string(C) + "=0";
		return x;
	}
	long long getA() {
		return A;
	}
	long long getB() {
		return B;
	}
	long long getC() {
		return C;
	}
};

extern map<pair<double, double>, int> point2count;
class Circle {
private:
	long long x0, y0, r0;
public:
	void setCircle(long long x, long long y, long long r) {
		x0 = x;
		y0 = y;
		r0 = r;
	}
	double getDistance(Line line) {
		long long A = line.getA();
		long long B = line.getB();
		long long C = line.getC();
		double dis = (double)(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
		return abs(dis);
	}
	//求圆与直线的交点
	void getIntersectWithLine(Line line) {
		long long A = line.getA();
		long long B = line.getB();
		long long C = line.getC();
		Line line_s;
		line_s.SetLine1(B, -A, A * y0 - B * x0);
		double dis = getDistance(line);
		pair<double, double> point = line_s.getInterSect(line);
		if (dis < r0) {
			double times = sqrt((double)r0 * r0 - dis * dis);
			pair<double, double> point1;
			pair<double, double> point2;
			pair<double, double> d;
			d.first = (double)(B) / sqrt(A * A + B * B);
			d.second = -(double)(A) / sqrt(A * A + B * B);
			point1.first = point.first + d.first * times;
			point1.second = point.second + d.second * times;
			point2.first = point.first - d.first * times;
			point2.second = point.second - d.second * times;
			//printf("%lf %lf %lf %lf\n", point1.first, point1.second, point2.first, point2.second);
			if (point2count.count(point1) < 1) {
				point2count.insert(pair<pair<double, double>, int>(point1, 1));
			}
			if (point2count.count(point2) < 1) {
				point2count.insert(pair<pair<double, double>, int>(point2, 1));
			}
		}
		else if (dis == r0) {
			printf("%lf %lf\n", point.first, point.second);
			if (point2count.count(point) < 1) {
				point2count.insert(pair<pair<double, double>, int>(point, 1));
			}
		}
		else {
			return;
		}
	}
	//
	void getIntersectWithCirc(Circle circ1) {
		//printf("该圆的半径：%lld\n", r0);
		long long x1 = circ1.x0;
		long long y1 = circ1.y0;
		long long r1 = circ1.r0;
		//圆心距离
		double d = sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
		if (d <= 0 || d > (double)r1 + r0 || d < abs((double)r0 - r1)) { 
			//printf("%lf\n", d);
			//printf("%lld %lld\n", r1, r0);
			//printf("1\n");
			return;
		};
		Line line1;
		line1.SetLine1(2 * x1 - 2 * x0, 2 * y1 - 2 * y0, - x1 * x1 + x0 * x0 - y1 * y1 + y0 * y0 + r1 * r1 - r0 * r0);
		getIntersectWithLine(line1);
	}
};
#endif
