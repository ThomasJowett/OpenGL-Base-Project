#include "Teapot.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include "../gl/glut.h"
#include <time.h>

Teapot::Teapot() {
	// use random numbers to initialise the position, scale and velocity

	position.x = 1000 * (float)rand() / (RAND_MAX)-5;
	position.y = 1000 * (float)rand() / (RAND_MAX)-5;
	position.z = 0;

	//scale = (float)rand() / ((RAND_MAX * 20));
	scale = 50;

	velocity.x = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.y = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.z = 0;

	boundingSphere = new Sphere(position, scale*1.4);
}

void Teapot::Render() {
	if (boundingSphere->GetCollided()) {
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glColor3f(0.0, 1.0, 0.0);
	}

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutWireTeapot(scale);
	glColor3f(0.0, 0.0, 0.0);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

}

void Teapot::Update() {
	boundingSphere->SetCollided(false);
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	if (position.x > 500 || position.x < -500)
		velocity.x *= -1;

	if (position.y > 500 || position.y < -500)
		velocity.y *= -1;

	if (position.z > 500 || position.z < -500)
		velocity.z *= -1;

	boundingSphere->Update(position);
}

Sphere * Teapot::GetBoundingSphere() {
	return boundingSphere;
}