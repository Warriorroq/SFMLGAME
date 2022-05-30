#include "Food.h"

Message<CustomMessages> Food::SendDataToCreateObject() 
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::UpdateObject;
	Vector2f position = transform.GetPosition();
	msg << mass << position.x << position.y << p_id << ObjectToCreate::food;
	return msg;
}