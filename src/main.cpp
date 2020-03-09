#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include "line.h"
using namespace std;
map<pair<double, double>, int> point2count;
vector<Line> lines;
vector<Circle> circles;
int main(int argc, char* argv[]) {
	ifstream in_file;
	ofstream out_file;
	int i;
	for (i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "-i") == 0) {
			in_file.open(argv[i+1]);
		}
		if (strcmp(argv[i], "-o") == 0) {
			out_file.open(argv[i+1]);
		}
	}
	int n;
	in_file >> n;
	for (i = 0; i < n; ++i) {
		char type;
		long long  x1, y1, x2, y2;
		in_file >> type;
		if (type == 'L') {
			in_file >> x1 >> y1 >> x2 >> y2;
			Line line;
			line.SetLine(x1, y1, x2, y2);
			for (auto it : lines) {
				if (line.isParallel(it)) 
					continue;
				pair<double, double> point = it.getInterSect(line);
				//printf("直线与直线交点：%lf %lf\n", point.first, point.second);
				if (point2count.count(point) < 1) {
					point2count.insert(pair<pair<double, double>, int>(point, 1));
				}
			}
			for (auto it : circles) {
				it.getIntersectWithLine(line);
			}
			lines.push_back(line);
		}
		else if (type == 'C') {
			long long x0, y0, r0;
			in_file >> x0 >> y0 >> r0;
			Circle circ;
			circ.setCircle(x0, y0, r0);
			for (auto it : lines) {
				circ.getIntersectWithLine(it);
			}
			for (auto it : circles) {
				circ.getIntersectWithCirc(it);
			}
			circles.push_back(circ);
		}
	}
	printf("%d\n", point2count.size());
	out_file << point2count.size();
}