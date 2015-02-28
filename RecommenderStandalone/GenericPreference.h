#ifndef GENERIC_PREFERENCE_H
#define GENERIC_PREFERENCE_H

#include "Preference.h"
#include <iostream>

namespace RS
{
	class GenericPreference :Preference
	{
	private:
		long userID;
		long itemID;
		float value;

	public:
		GenericPreference(long userID, long itemID, float value);
		
		/**********		Override member functions from Preference		**********/
		long getUserID();
		long getItemID();
		float getValue();
		void setValue(float value);
		std::string toString();
	};
}

#endif