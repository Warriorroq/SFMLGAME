#include "Food.h"

using namespace olc;
using namespace net;
using namespace sf;

Message<CustomMessages> Food::SendDataToCreateObject() 
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::UpdateObject;
	msg << mass << position.x << position.y << p_id << ObjectToCreate::food;
	return msg;
}