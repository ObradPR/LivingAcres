//#include <SFML/Graphics.hpp>
//#include <SFML/OpenGL.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//#include <cmath>

int main()
{
	sf::Window window(sf::VideoMode({ 800, 600 }), "Farm 3D OpenGL");
	window.setVerticalSyncEnabled(true);

	// Enable depth testing for correct 3D rendering
	glEnable(GL_DEPTH_TEST);

	// Camera position
	float camX = 0.0f, camY = 0.0f, camZ = 4.0f; // start above and back a bit
	float camAngleYaw = 0.0f; // Y rotation
	// rotation (left/right), measured in radians
		// 0 radiants -> facing forward
		// Increasing -> turning right
		// Decreasing -> turning left

	float camAnglePitch = 20.0f;
	// nodding your head up / down

	bool running = true;
	while (running)
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				running = false;

			if (event->is<sf::Event::KeyPressed>())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					running = false;
				}
			}
		}

		// Keyboard camera control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			camAngleYaw -= 0.02f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			camAngleYaw += 0.02f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			camX += sin(camAngleYaw) * 0.05f;
			camY -= cos(camAngleYaw) * 0.05f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			camX -= sin(camAngleYaw) * 0.05f;
			camY += cos(camAngleYaw) * 0.05f;
		}

		// Clear screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set viewport to window size
		glViewport(0, 0, 800, 600);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5, 5, -3.5, 3.5, -100, 100); // wider view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set camera
		glRotatef(camAnglePitch, 4, 0, 0); // 20 degree tilt
		glRotatef(camAngleYaw * 57.2958f, 0, 1, 0);	// rotate around Y
		// degrees = radians * (180 / PI) ~ 57.2958
		glTranslatef(-camX, -camY, -camZ);

		// Draw a colored cube at origin
		glBegin(GL_QUADS);

		// Front face (red)
		glColor3f(1, 0, 0);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		// Back face (green)
		glColor3f(0, 1, 0);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		// Left face (blue)
		glColor3f(0, 0, 1);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		// Right face (yellow)
		glColor3f(1, 1, 0);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		// Top face (cyan)
		glColor3f(0, 1, 1);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		// Bottom face (magenta)
		glColor3f(1, 0, 1);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glEnd();

		// Display
		window.display();
	}

	return 0;
}