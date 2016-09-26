#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int width = 700;
const int height = 560;
double xpos, ypos;

float* pixels = new float[width*height * 3];
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}
void drawline(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
	}
}
void drawline2(const int& i0, const int& j0, const int& i1, const int&j1, const float& red, const float& green, const float& blue)
{
	for (int j = j0; j <= j1; j++)
	{
		const int i = (i1 - i0)*(j - j0) / (j1 - j0) + i0;
		drawPixel(i, j, red, green, blue);
	}
}
void draw_full_circle(int x, int y, int R, float red, float green, float blue)
{
	int z, k;
	int ix;
	for (z = y - 100; z < y + 100; z++)
	{
		for (k = x - 100; k < x + 100; k++)
		{

			ix = k + z*width;

			if ((k - x)*(k - x) + (z - y)*(z - y) < R * R)
			{
				pixels[ix * 3 + 0] = red;
				pixels[ix * 3 + 1] = green;
				pixels[ix * 3 + 2] = blue;
			}
		}
	}
}
void draw_empty_circle(int x, int y, int R, float red, float green, float blue)
{
	int z, k;
	int ix;
	for (z = y - 100; z < y + 100; z++)
	{
		for (k = x - 100; k < x + 100; k++)
		{

			ix = k + z*width;

			if ((k - x)*(k - x) + (z - y)*(z - y) > R *(R - 1) && (k - x)*(k - x) + (z - y)*(z - y) < R * (R + 1))
			{
				pixels[ix * 3 + 0] = red;
				pixels[ix * 3 + 1] = green;
				pixels[ix * 3 + 2] = blue;
			}
		}
	}
}

int main(void)
{
	GLFWwindow* window;
	int k, z;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//바탕화면 흰색으로 채우기
		std::fill_n(pixels, width*height * 3, 1.0f);
		
		//커서가 가까이 가면 원의 색깔 변경
		glfwGetCursorPos(window, &xpos, &ypos);

		//아래쪽에 빨간색 원 5개 만들기
		k = 150;
		for (z = 80; z < 600; z = z + 120)
		{
			if ((xpos - z)*(xpos - z) + (ypos - 300 - k)*(ypos - 300 - k) < 50 * 50)
				draw_empty_circle(z, k, 50, 0, 0, 255);
			else
				draw_empty_circle(z, k, 50, 255, 0, 0);
		}
		//위쪽에 빨간색 원 5개 만들기
		k = 400;
		for (z = 80; z < 600; z = z + 120)
		{
			if ((xpos - z)*(xpos - z) + (ypos - 300 - k)*(ypos - 300 - k) < 50 * 50)
				draw_empty_circle(z, k, 50, 0, 0, 255);
			else
				draw_empty_circle(z, k, 50, 255, 0, 0);
		}
		//아랫줄 첫번째 원 안에 -> 그리기
		drawline(50, 150, 120, 150, 255, 0, 0);
		drawline2(120, 150, 95, 180, 255, 0, 0);
		drawline(95, 120, 120, 150, 255, 0, 0);
		//아랫줄 두번째 원 안에 A 그리기
		drawline(170, 120, 200, 180, 255, 0, 0);
		drawline(200, 180, 230, 120, 255, 0, 0);
		drawline(185, 150, 215, 150, 255, 0, 0);
		//아랫줄 세번째 원 안에 | 그리기
		drawline2(320, 120, 320, 180, 255, 0, 0);
		//아랫줄 네번째 원 안에 <- 그리기
		drawline(400, 150, 480, 150, 255, 0, 0);
		drawline(400, 150, 425, 180, 255, 0, 0);
		drawline(400, 150, 425, 120, 255, 0, 0);
		//아랫줄 다섯번째 원 안에 화살표 그리기
		drawline2(560, 120, 560, 180, 255, 0, 0);
		drawline(535, 150, 560, 180, 255, 0, 0);
		drawline(560, 180, 585, 150, 255, 0, 0);
		//위쪽 첫번째 원 안에 / 그리기
		drawline(60, 370, 90, 430, 255, 0, 0);
		//위쪽 두번째 원 안에 굵은 원 그리기
		draw_empty_circle(200, 400, 20, 255, 0, 0);
		draw_empty_circle(200, 400, 21, 255, 0, 0);
		draw_empty_circle(200, 400, 19, 255, 0, 0);
		//위쪽 세번째 원 안에 사각형 그리기
		drawline(290, 380, 350, 380, 255, 0, 0);
		drawline(290, 420, 350, 420, 255, 0, 0);
		drawline2(290, 380, 290, 420, 255, 0, 0);
		drawline2(350, 380, 350, 420, 255, 0, 0);
		//위쪽 네번째 원 안에 X 그리기
		drawline(410, 380, 470, 420, 255, 0, 0);
		drawline(410, 420, 470, 380, 255, 0, 0);
		//위쪽 다섯번째 원 안에 화살표 그리기
		drawline2(560, 370, 560, 430, 255, 0, 0);
		drawline(530, 400, 560, 370, 255, 0, 0);
		drawline(560, 370, 590, 400, 255, 0, 0);

		

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();

	delete[] pixels;

	return 0;
}