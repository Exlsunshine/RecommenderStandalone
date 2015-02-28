#include"GenericPreference.h"
#include <string>
using namespace std;

namespace RS
{
	GenericPreference::GenericPreference(long userID, long itemID, float value)
	{
		this->userID = userID;
		this->itemID = itemID;
		this->value = value;
	}

	long GenericPreference::getUserID() { return userID; }

	long GenericPreference::getItemID() { return itemID; }

	float GenericPreference::getValue() { return value; }

	void GenericPreference::setValue(float value) { this->value = value; }

	string GenericPreference::toString()
	{
		string uID = to_string(userID);
		string iID = to_string(itemID);
		string v = to_string(value);
		return "GenericPreference[userID:" + uID + ", itemID : " + iID + ", value : " + v + ']';
	}
}