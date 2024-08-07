#ifndef SPRITE_H
#define SPRITE_H


class Sprite 
{
public:
	Sprite();
	Sprite(float x, float y, float angle, float height, float width, float speed);

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	float getSpeed();
	void setSpeed(float speed);
	
	typedef struct
	{
		int m_x0;
		int m_y0;
		int m_x1;
		int m_y1;
	} box;

	box boundBox;

	float m_width;
	float m_height;
	float m_x;
	float m_y;
	float m_oldX;
	float m_oldY;
	float m_direction;
	float m_speed;
	bool showSprite;
	int s_frame;
	
private:
	
	

protected:

};

#endif
