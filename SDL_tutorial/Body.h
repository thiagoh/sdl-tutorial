#pragma once

class Body {

private:
	int width;
	int height;

public:

	Body(int width, int height) : width(width), height(height) {

	}

	int getWidth() {

		return width;
	}

	int getHeight() {

		return height;
	}
};
