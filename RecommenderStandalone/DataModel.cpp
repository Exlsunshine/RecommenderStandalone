#include "DataModel.h"

namespace RS
{
	DataModel::DataModel() : maxPreference(NAN), minPreference(NAN) { }
	DataModel::~DataModel() { }
	
	std::vector<long> DataModel::getUserIDs() { std::vector<long> v; return v; }
	PreferenceArray DataModel::getPreferencesFromUser(long userID) { return PreferenceArray(); }
	std::vector<long> DataModel::getItemIDsFromUser(long userID) { std::vector<long> v; return v; }
	std::vector<long> DataModel::getItemIDs() { std::vector<long> v; return v; }
	PreferenceArray DataModel::getPreferencesForItem(long itemID) { return PreferenceArray(); }
	float DataModel::getPreferenceValue(long userID, long itemID) { return 0; }
	long DataModel::getPreferenceTime(long userID, long itemID) { return 0; }
	int DataModel::getNumItems() { return 0; }
	int DataModel::getNumUsers() { return 0; }
	int DataModel::getNumUsersWithPreferenceFor(long itemID) { return 0; }
	int DataModel::getNumUsersWithPreferenceFor(long itemID1, long itemID2) { return 0; }
	void DataModel::setPreference(long userID, long itemID, float value) { }
	void DataModel::removePreference(long userID, long itemID) { }
	bool DataModel::hasPreferenceValues() { return false; }
	float DataModel::getMaxPreference() { return 0; }
	float DataModel::getMinPreference() { return 0; }
	void DataModel::setMaxPreference(float maxPreferenceValue) { }
	void DataModel::setMinPreference(float minPreferenceValue) { }
	std::string DataModel::toString(){ return ""; }
}