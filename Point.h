#pragma once
class Point {
public:
	Point();
	Point(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int newX);
	void setY(int newY);
private:
	int x;
	int y;

};