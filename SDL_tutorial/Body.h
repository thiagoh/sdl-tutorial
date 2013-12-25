#pragma once

class Body {

private:
	int width;
	int height;

public:
	
	Body() : width(0), height(0) {

	}

	Body(int width, int height) : width(width), height(height) {

	}

	int getWidth() {

		return width;
	}

	int getHeight() {

		return height;
	}

	void setWidth(int width) {

		this->width = width;
	}

	void setHeight(int height) {

		this->height = height;
	}
};
