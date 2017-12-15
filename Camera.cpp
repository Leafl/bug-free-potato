#include "Camera.h"

Camera::Camera()
{
    assert( false && "Do not use the default Camera constructor.");
}

Camera::Camera(vec3 pos, float width, float height)
{
    cameraPosition=pos;
    ScreenWidth=width;
    ScreenHeight=height;
    
    verticalheight = cameraPosition.y;
    
    setDefaults();
    updateCameraVectors();
}

void Camera::setDefaults()
{
    FOV=45.0f;
    AspectRatio=(float) ScreenWidth/(float) ScreenHeight;
    nearPlane=0.1f;
    farPlane=500.0f;
	worldup = vec3(0.0f, 1.0f, 0.0f);
    //Yaw: 3.119474
    //Pitch: -0.433827
	yaw = -90.0f;//3.119474;//PI;
    pitch=0.0; // Look directly down the z-axis to start
    MouseSpeed=0.1f;
    Speed=10.f;
    MovementSpeed = 10.0f;
    RotationSpeed=0.01f;
    
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 newfrontvector;
	newfrontvector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newfrontvector.y = sin(glm::radians(pitch));
	newfrontvector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front_vector = glm::normalize(newfrontvector);
	// Also re-calculate the Right and Up vector
	right_vector = glm::normalize(glm::cross(front_vector, worldup));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up_vector = glm::normalize(glm::cross(right_vector, front_vector));
}



// This function returns the View matrix, based on the position, up vector,
//   and look-at position.
// Pre:
// Post:
mat4 Camera::getViewMatrix()
{
//    glm::vec3 look=position+getViewVector();
//    glm::vec3 up=calculateUpVector();
	return lookAt(cameraPosition, cameraPosition + front_vector, up_vector);
	
	//return glm::lookAt(position, look_, up_);
}

void Camera::printOutYawandPitch()
{
    printf("Yaw: %f\n",yaw);
    printf("pitch: %f\n",pitch);
}

void Camera::printAllInfo()
{
    printf("****** Camera info: ******\n"
	    "position:\n"
	   "\tX:%13f\n"
	    "\tY:%13f\n"
	   "\tZ:%13f\n"
	   "\n",cameraPosition.x, cameraPosition.y, cameraPosition.z);
	    printOutYawandPitch();
    printf("****************************\n\n");
}


// This function returns the projection matrix, based on the camera's position,
//   and the field of view and aspect ratios, along with distances between
//   near and far planes
// Pre: 
// Post:

mat4 Camera::getPerspectiveMatrix()
{
    return glm::perspective(FOV, AspectRatio, nearPlane, farPlane);
}


// This function returns the Projection Matrix of an orthographic projection
// Pre:
// Post:

mat4 Camera::getOrthographicMatrix()
{
    return mat4(1.0f);
}

// This function sets the persepctive parameters for the persepctive camera
// Pre:
// Post:

void Camera::setPerspective(float _fov, float ar, float np, float fp)
{
    FOV=_fov;
    AspectRatio=ar;
    nearPlane=np;
    farPlane=fp;
    
    updateCameraVectors();
}
// This function sets the position to the argument _pos
// Pre:
// Post:

void Camera::setPosition(vec3 _pos)
{
    cameraPosition=_pos;
}

// This function sets the position to the argument _pos
// Pre:
// Post:

void Camera::setPosition(float x, float y, float z)
{
    cameraPosition=vec3(x, y, z);
}

// Return the current position of the camera
// Pre:
// Post:

vec3 Camera::getPosition()
{
    return cameraPosition;
}

vec3 Camera::getFront()
{
	return front_vector;
}

// Return the current mouse speed
// Pre:
// Post:

float Camera::getMouseSpeed()
{
    return MouseSpeed;
}

// This function updates the local deltaTime variable
// Pre:
// Post:

void Camera::setDeltaTime(double dt)
{
    deltaTime = dt;
}

/************************
 ** MOVEMENT FUNCTIONS **
 ***********************/



void Camera::processMovement(Camera_Movement direction, GLboolean constrainVeriticalHeight)
{
    	vec3 temppos = cameraPosition;

	vec3 moveby = vec3(0,0,0);

	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		moveby += front_vector * velocity;
	if (direction == BACKWARD)
		moveby -= front_vector * velocity;
	if (direction == LEFT)
		moveby -= right_vector * velocity;
	if (direction == RIGHT)
		moveby += right_vector * velocity;
	temppos += moveby;
	
	if (constrainVeriticalHeight)
	{
	    cameraPosition = vec3(temppos.x, verticalheight, temppos.z);
	}
	else
	    cameraPosition = vec3(temppos.x, temppos.y, temppos.z);
	
}

void Camera::processHeadMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	updateCameraVectors();
}


// This function moves the camera based on the current mouse position, based on
//   dX and dY which are movements in the mouse position
// Pre:
// Post:
void Camera::setViewByMouse(float dX, float dY)
{
    yaw += MouseSpeed * deltaTime * dX;
    pitch += MouseSpeed * deltaTime * dY;
    updateCameraVectors();
}

// This function adjusts the camera position by dX and dY
// Pre:
// Post:

void Camera::moveCamera(float dX, float dY)
{
    cameraPosition+=glm::vec3(dX*deltaTime * Speed, dY*deltaTime * Speed, 0);

	updateCameraVectors();
}

void Camera::zoomCamera(float delta)
{
    cameraPosition+=vec3(0, 0, delta*deltaTime*RotationSpeed);

	updateCameraVectors();
}


// This function calculates and returns the view direction
// Pre:
// Post:

glm::vec3 Camera::getViewVector()
{
    glm::vec3 direction(
			cos(pitch)*sin(yaw),
			sin(pitch),
			cos(pitch)*cos(yaw)
			);

    direction=glm::normalize(direction);
    return direction;
}

// This function returns the vector looking directly to the right of the camera
//   Since we're not changing the vertical component when moving
//   (we're not ever rotating the 'roll' component), Y is 0
// Pre:
// Post:

glm::vec3 Camera::getRightVector()
{
    glm::vec3 _right=glm::vec3(
			      sin(yaw-PI/2.0f),
			      0,
			      cos(yaw-PI/2.0f)
			      );
    _right=glm::normalize(_right);
    return _right;
}


// This function calculates the current 'up' vector based on the front and
//   right vectors
// Pre: front and right are correct
// Post:

glm::vec3 Camera::calculateUpVector()
{
    return glm::normalize(glm::cross(getRightVector(), getViewVector()));
}
