#ifndef GENERIC_DATAMODEL_H
#define GENERIC_DATAMODEL_H

#include "DataModel.h"
#include "PreferenceArray.h"
#include <iostream>

namespace RS
{
	/**
	* A simple {@link DataModel} which uses a given {@link List} of users as its data source. This implementation
	* is mostly useful for small experiments and is not recommended for contexts where performance is important.
	*/
	class GenericDataModel :public DataModel
	{
	private:
		const std::vector<long> userIDs;
		const std::vector<PreferenceArray> preferenceFromUsers;
		const std::vector<long> itemIDs;
		const std::vector<PreferenceArray> preferenceForItems;
		const std::vector<std::vector<long>> timestamps;

	public:
		/**
		* Creates a new {@link GenericDataModel} from the given users (and their preferences). This
		* {@link DataModel} retains all this information in memory and is effectively immutable.
		* @param userData users to include; (see also {@link #toDataMap(FastByIDMap, boolean)})
		*/
		GenericDataModel(std::vector<PreferenceArray> userData);

		/**
		* Creates a new {@link GenericDataModel} from the given users (and their preferences). This
		* {@link DataModel} retains all this information in memory and is effectively immutable.
		*
		* @param userData users to include; (see also {@link #toDataMap(FastByIDMap, boolean)})
		* @param timestamps optionally, provided timestamps of preferences as milliseconds since the epoch.
		*  User IDs are mapped to maps of item IDs to Long timestamps.
		*/
		GenericDataModel(std::vector<PreferenceArray> userData, std::vector<std::vector<long>> timestamps);
	
		/**
		* Swaps, in-place, {@link List}s for arrays in {@link Map} values .
		* @return input value
		*/
		static std::vector<PreferenceArray> toDataMap(std::vector<std::vector<Preference>> data, bool byUser);

		/**
		* Exports the simple user IDs and preferences in the data model.
		* @return a {@link FastByIDMap} mapping user IDs to {@link PreferenceArray}s representing  that user's preferences
		*/
		static std::vector<PreferenceArray> toDataMap(DataModel dataModel);

		/*  This is used mostly internally to the framework, and shouldn't be relied upon otherwise. */
		std::vector<PreferenceArray> getRawItemData();
	
		/**********			Override member functions from DataModel			**********/
		std::vector<long> getUserIDs();
		PreferenceArray getPreferencesFromUser(long userID);
		std::vector<long> getItemIDsFromUser(long userID);
		std::vector<long> getItemIDs();
		PreferenceArray getPreferencesForItem(long itemID);
		float getPreferenceValue(long userID, long itemID);
		long getPreferenceTime(long userID, long itemID);
		int getNumItems();
		int getNumUsers();
		int getNumUsersWithPreferenceFor(long itemID);
		int getNumUsersWithPreferenceFor(long itemID1, long itemID2);
		void removePreference(long userID, long itemID);
		void setPreference(long userID, long itemID, float value);
		bool hasPreferenceValues();
		std::string toString();
	};
}

#endif