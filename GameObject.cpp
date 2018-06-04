#include "GameObject.h"



void GameObject::update(float dt, glm::mat4 PV)
{
	addForces();


	eulerIntegration(dt);

	translation = glm::translate(glm::vec3(position));

	calcTransform();
	MVP = PV * transformation;

	totalForce = acceleration = glm::vec3();


}

void GameObject::addForces()
{
	totalForce += GRAVITY * mass;

	acceleration = totalForce / mass;
}

//Calculates Transformation matrix -> T * R * S
void GameObject::calcTransform()
{
	transformation = translation * rotation * scale;
	
}

void GameObject::eulerIntegration(float dt)
{
	//Kinematic equation x= v*dt+ 0.5(a *dt^2)
	position += velocity * dt + 0.5f*(acceleration * dt*dt);

	//Updating velocity
	velocity += acceleration * dt;

}


//Sets up the vertices in the vertex buffer
void GameObject::setupCircle( float r , float n)
{

	float radius = r;


	VertexFormat center(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	std::vector<VertexFormat> vertices;

	float theta = 360.0f / n;

	//Circle vertex generation
	//In this example we are not implementing the proper the code for indices. We are just going to produce redundant information in the buffer.
	//since we are only having a small number of objects on the screen currently, this redundancy should not matter.
	for (int i = 0; i < n; i++)
	{
		//In every iteration, the center, the point at angle theta and at angle (theta+delta) are fed into the buffer.
		vertices.push_back(center);
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(glm::radians(i*theta)), radius * sin(glm::radians(i*theta)), 0.0f), glm::vec4(0.7f, 0.20f, 0.0f, 1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(glm::radians((i + 1)*theta)), radius * sin(glm::radians((i + 1)*theta)), 0.0f), glm::vec4(0.7f, 0.20f, 0.0f, 1.0f)));
	}

	base.initBuffer(n * 3, &vertices[0]);
}


//Initalizing values
GameObject::GameObject(glm::mat4 mvp)
{
	velocity = totalForce = acceleration = position = glm::vec3();

	translation=rotation=scale=transformation= glm::mat4();

	mass = 1.0f;

	MVP = mvp;
}


GameObject::~GameObject()
{
}
