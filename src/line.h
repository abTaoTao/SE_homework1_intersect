#ifndef _line_h
#define _line_h
#pragma once
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<cmath>
#include<unordered_set>
#define eps 1e-12
#define MAXSLOPE 17373524.2
using namespace std;
struct equals {
	bool operator()(const pair<double, double>& a, const pair<double, double>& b) const
	{
		return fabs(a.first - b.first) < eps && fabs(a.second - b.second) < eps;
	}
};
class Hash_pair {
public:
	size_t operator()(const pair<double, double>& pr)const
	{
		return hash<double>()(pr.first * 2 + pr.second);
	}
	
};
class Line {
private:
	//Ax + By + C = 0;
	double A, B, C;
public:
	void SetLine(double x1, double y1, double x2, double y2) {
		A = y2 - y1;
		B = x1 - x2;
		C = x2 * y1 - x1 * y2;
	}
	void SetLine1(double a, double b, double c) {
		A = a;
		B = b;
		C = c;
	}
	//�ж�����ֱ���Ƿ�ƽ��
	bool isParallel(Line line_2) {
		return A * line_2.B == B * line_2.A;
	}

	//������ֱ�ߵĽ��㣬���������ֱ�߲�ƽ��
	pair<double,double> getInterSect(Line line) {
		double x = line.C * B - C * line.B;
		double y = C * line.A - line.C * A;
		double m = A * line.B - line.A * B;
		double x_real = double(x) / m;
		double y_real = double(y) / m;
		pair<double, double> intersection;
		intersection.first = x_real;
		intersection.second = y_real;
		//printf("%lf %lf\n", x_real, y_real);
		return intersection;
	}
	//��ȡֱ�ߵ�б��
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
	//�õ�ֱ�ߵĽ���ʽ
	string getFunc() {
		string x = "";
		x = to_string(A) + "x+" + to_string(B) + "y+" + to_string(C) + "=0";
		return x;
	}
	double getA() {
		return A;
	}
	double getB() {
		return B;
	}
	double getC() {
		return C;
	}
};
extern set<pair<double, double>> pointss;
extern unordered_set<pair<double, double>,Hash_pair,equals> pointu_set;
class Circle {
private:
	double x0, y0, r0;
public:
	void setCircle(double x, double y, double r) {
		x0 = x;
		y0 = y;
		r0 = r;
	}
	double getDistance(Line line) {
		double A = line.getA();
		double B = line.getB();
		double C = line.getC();
		double dis = (double)(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
		return abs(dis);
	}
	//��Բ��ֱ�ߵĽ���
	void getIntersectWithLine(Line line) {
		double A = line.getA();
		double B = line.getB();
		double C = line.getC();
		Line line_s;
		vector<pair<double, double>> points;
		//��Բ����ֱ�ߵĴ��ߣ�������㡣
		line_s.SetLine1(B, -A, A * y0 - B * x0);
		double dis = getDistance(line);
		pair<double, double> point = line_s.getInterSect(line);
		//�󽻵�
		if (dis < r0) {
			//printf("%d\n", pointu_set.size());
			double times = sqrt((double)r0 * r0 - dis * dis);
			pair<double, double> point1;
			pair<double, double> point2;
			pair<double, double> d;
			//��ֱ�ߵĵ�λ����
			d.first = (double)(B)   / sqrt((double)A * A + B * B);
			d.second = -(double)(A)  / sqrt((double)A * A + B * B);
			//�����������ϣ���λ������Ӧ�����봹�㵽����ľ��롣�õ���������
			point1.first = point.first - d.first * times;
			point1.second = point.second - d.second * times;
			point2.first = point.first + d.first * times;
			point2.second = point.second + d.second * times;
			//printf("%.22lf %.22lf %.22lf %.22lf\n", point1.first, point1.second, point2.first, point2.second);
			//pointss.insert(point1);
			//printf("%d %d\n", pointu_set.count(point1), pointu_set.count(point2));
			pointu_set.insert(point1);
			pointu_set.insert(point2);
			//printf("%d %d\n", pointu_set.count(point1), pointu_set.count(point2));
		}
		else if (dis == r0) {
			pointu_set.insert(point);
		}
		else {
			return;
		}
	}
	//
	void getIntersectWithCirc(Circle circ1) {
		//printf("��Բ�İ뾶��%lld\n", r0);
		double x1 = circ1.x0;
		double y1 = circ1.y0;
		double r1 = circ1.r0;
		//Բ�ľ���
		double d = sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
		if (d <= 0 || d > (double)r1 + r0 || d < abs((double)r0 - r1)) { 
			return;
		};
		Line line1;
		line1.SetLine1(2 * x1 - 2 * x0, 2 * y1 - 2 * y0, - x1 * x1 + x0 * x0 - y1 * y1 + y0 * y0 + r1 * r1 - r0 * r0);
		getIntersectWithLine(line1);
	}
};
#endif
