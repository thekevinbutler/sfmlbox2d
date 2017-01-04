#include "Camera.h"
//CALL INIT
Camera::Camera(sf::RenderWindow& pWindow, Player& pPlayer) : target(pPlayer), LayeredView(pWindow)
{
	//setCenter(target.getPos());
	elapsedTime = 0.0;
	isGroundCam = false;
}
void Camera::init()
{
	LayeredView::init();
	//initialZoom = getWindow().getView().getSize();
	//zoomRes = initialZoom;
	//setSize(initialZoom);
	setCenter(target.getPos());
}

float Lerp(float a, float b, float time)
{
	//multiply by desired duration
	//time *= 30.0f;
	return a + ((b - a) * time);
}
void Camera::updatePos(sf::Time dt)
{
	sf::Vector2f distance;
	distance.x = target.getPos().x - getCenter().x;
	distance.y = target.getPos().y - getCenter().y;

	
	if (target.isGrounded())
	{
		if (isGroundCam == false)
		{
			elapsedTime = 0;
			isGroundCam = true;
		}
		sf::Vector2f resultPos = target.getPos();
		if (elapsedTime < 10.0)
		{
			elapsedTime += dt.asSeconds();
			/*setZoomRes( Lerp(getSize().x, getInitZoom().x * 0.75, elapsedTime / 10.0),
						Lerp(getSize().y, getInitZoom().y * 0.75, elapsedTime / 10.0));*/
			setZoomRes(Lerp(getSize().x, getInitZoom().x * 0.5, elapsedTime / 10.0),
				Lerp(getSize().y, getInitZoom().y * 0.5, elapsedTime / 10.0));

			//always follow player when zoom
		
			resultPos.x = Lerp(getCenter().x, target.getPos().x, elapsedTime/10.0);
			resultPos.y = Lerp(getCenter().y, target.getPos().y, elapsedTime/10.0);
		}
		setCenter(resultPos);
	}
	else
	{
		if (isGroundCam == true)
		{
			elapsedTime = 0;
			isGroundCam = false;
		}
		sf::Vector2f newPos = target.getPos();
		
		if (elapsedTime < 5.0)
		{
			elapsedTime += dt.asSeconds();
			
			/*setZoomRes(Lerp(getSize().x, getInitZoom().x, elapsedTime / 5.0),
						Lerp(getSize().y, getInitZoom().y, elapsedTime / 5.0));*/
			setZoomRes(Lerp(getSize().x, getInitZoom().x * 0.75, elapsedTime / 5.0),
				Lerp(getSize().y, getInitZoom().y * 0.75, elapsedTime / 5.0));
			
			newPos.x = Lerp(getCenter().x, target.getPos().x, elapsedTime/5.0);
			newPos.y = Lerp(getCenter().y, target.getPos().y, elapsedTime/5.0);
		}
		setCenter(newPos);


	}
	//setSize(zoomRes);
	
	//Figure out how to interpolate using velocity
	

}