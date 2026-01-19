#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	sf::Window window(sf::VideoMode({ 800, 600 }), "Farm 3D OpenGL");
	window.setVerticalSyncEnabled(true);

	// Enable depth testing for correct 3D rendering
	glEnable(GL_DEPTH_TEST);

	// Camera position
	float camX = 0.0f;
	float camY = 3.0f;
	float camZ = 5.0f;

	// Camer rotation
	float camYaw = 0.0f;			// left / right
	const float camPitch = 45.0f;	// lookign down (fixed)

	// yaw - rotation (left/right), measured in radians
		// 0 radiants -> facing forward
		// Increasing -> turning right
		// Decreasing -> turning left
	// pitch - nodding your head up / down

	// Camera speed
	const float camSpeed = 0.05f;

	// Camera zoom
	const float minZoom = 1.0f;
	const float maxZoom = 20.0f;

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

			if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (wheel->wheel == sf::Mouse::Wheel::Vertical)
				{
					float delta = wheel->delta;
					// delta > 0 -> scroll up (zoom in)
					// delta < 0 -> scroll down (zoom out)

					camY -= delta * camSpeed;	// move camera closer/farther vertically
					camZ -= delta * camSpeed;	// move camera closer/farther in depth

					// Clamp zoom
					camY = std::clamp(camY, minZoom, maxZoom);
					camZ = std::clamp(camZ, minZoom, maxZoom);
				}
			}
		}

		// Keyboard camera control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))	// Forward
		{
			camZ -= camSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))	// Backward
		{
			camZ += camSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))	// Left
		{
			camX -= camSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	// Right
		{
			camX += camSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))	// Rotate left
		{
			camYaw += 0.02f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))	// Rotate Right
		{
			camYaw -= 0.02f;
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
		glRotatef(camPitch, 1, 0, 0);			// tilt camera DOWN
		glRotatef(camYaw * 57.2958f, 0, 1, 0);	// rotate around Y
		// degrees = radians * (180 / PI) ~ 57.2958
		glTranslatef(-camX, -camY, -camZ);

		// Draw a floor
		glBegin(GL_QUADS);

		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(-10.f, 0.f, -10.f);
		glVertex3f(10.f, 0.f, -10.f);
		glVertex3f(10.f, 0.f, 10.f);
		glVertex3f(-10.f, 0.f, 10.f);

		glEnd();

		// Draw a colored cube at origin
		glBegin(GL_QUADS);

		// Front face (red)
		glColor3f(1, 0, 0);
		glVertex3f(-0.5f, 0.f, 0.5f);		// left bottom
		glVertex3f(-0.5f, 1.f, 0.5f);		// left top
		glVertex3f(0.5f, 1.f, 0.5f);		// right top
		glVertex3f(0.5f, 0.f, 0.5f);		// right bottom

		// Back face (green)
		glColor3f(0, 1, 0);
		glVertex3f(-0.5f, 0.f, -0.5f);		// left bottom
		glVertex3f(-0.5f, 1.f, -0.5f);		// left top
		glVertex3f(0.5f, 1.f, -0.5f);		// right top
		glVertex3f(0.5f, 0.f, -0.5f);		// right bottom

		// Left face (blue)
		glColor3f(0, 0, 1);
		glVertex3f(-0.5f, 0.f, -0.5f);		// bottom far
		glVertex3f(-0.5f, 0.f, 0.5f);		// bottom near
		glVertex3f(-0.5f, 1.f, 0.5f);		// top near
		glVertex3f(-0.5f, 1.f, -0.5f);		// top far

		// Right face (yellow)
		glColor3f(1, 1, 0);
		glVertex3f(0.5f, 0.f, -0.5f);		// bottom far
		glVertex3f(0.5f, 1.f, -0.5f);		// top far
		glVertex3f(0.5f, 1.f, 0.5f);		// top near
		glVertex3f(0.5f, 0.f, 0.5f);		// bottom near

		// Top face (cyan)
		glColor3f(0, 1, 1);
		glVertex3f(-0.5f, 1.f, -0.5f);		// left far
		glVertex3f(-0.5f, 1.f, 0.5f);		// left near
		glVertex3f(0.5f, 1.f, 0.5f);		// right near
		glVertex3f(0.5f, 1.f, -0.5f);		// right far

		glEnd();

		// Display
		window.display();
	}

	return 0;
}