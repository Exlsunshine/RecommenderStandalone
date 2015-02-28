#include "PreferenceArray.h"
#include <iostream>
using namespace std;
namespace RS
{
	int PreferenceArray::length() { return 0; }
	Preference PreferenceArray::get(int i) { return Preference(); }
	void PreferenceArray::set(int i, Preference pref) { }
	long PreferenceArray::getUserID(int i) { return 0; }
	void PreferenceArray::setUserID(int i, long userID) { }
	long PreferenceArray::getItemID(int i) { return 0; }
	void PreferenceArray::setItemID(int i, long itemID) { }
	std::vector<long> PreferenceArray::getIDs() { vector<long> v; return v; }
	float PreferenceArray::getValue(int i) { return 0; }
	void PreferenceArray::setValue(int i, float value) {}
	PreferenceArray& PreferenceArray::clone() { return *(new PreferenceArray()); }
	void PreferenceArray::sortByUser() {}
	void PreferenceArray::sortByItem() {}
	void PreferenceArray::sortByValue() {}
	void PreferenceArray::sortByValueReversed() {}
	bool PreferenceArray::hasPrefWithUserID(long userID) { return false; }
	bool PreferenceArray::hasPrefWithItemID(long itemID) { return false; }
}