#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <vector>
#include "PreferenceArray.h"

namespace RS
{
	/**
		Implementations represent a repository of information about users and their associated {@link Preference}s
		for items.
	*/
	class DataModel
	{
	private:
		float maxPreference;
		float minPreference;

	public:
		DataModel();
		
		virtual ~DataModel();

		/**
		* @return all user IDs in the model, in order
		*/
		virtual std::vector<long> getUserIDs();

		/**
			@param  
				ID of user to get prefs for
			@return user's preferences, ordered by item ID
		*/
		virtual PreferenceArray getPreferencesFromUser(long userID);
		
		/**
		* @param userID
		*          ID of user to get prefs for
		* @return IDs of items user expresses a preference for
		*/
		virtual std::vector<long> getItemIDsFromUser(long userID);

		/**
		* @return a {@link LongPrimitiveIterator} of all item IDs in the model, in order
		*/
		virtual std::vector<long> getItemIDs();

		/**
		* @param itemID
		*          item ID
		* @return all existing {@link Preference}s expressed for that item, ordered by user ID, as an array
		*/
		virtual PreferenceArray getPreferencesForItem(long itemID);

		/**
		* Retrieves the preference value for a single user and item.
		*
		* @param userID
		*          user ID to get pref value from
		* @param itemID
		*          item ID to get pref value for
		* @return preference value from the given user for the given item or null if none exists
		*/
		virtual float getPreferenceValue(long userID, long itemID);

		/**
		* Retrieves the time at which a preference value from a user and item was set, if known.
		* Time is expressed in the usual way, as a number of milliseconds since the epoch.
		*
		* @param userID user ID for preference in question
		* @param itemID item ID for preference in question
		* @return time at which preference was set or null if no preference exists or its time is not known
		*/
		virtual long getPreferenceTime(long userID, long itemID);

		/**
		* @return total number of items known to the model. This is generally the union of all items preferred by
		*         at least one user but could include more.
		*/
		virtual int getNumItems();

		/**
		* @return total number of users known to the model.
		*/
		virtual int getNumUsers();

		/**
		* @param itemID item ID to check for
		* @return the number of users who have expressed a preference for the item
		*/
		virtual int getNumUsersWithPreferenceFor(long itemID);

		/**
		* @param itemID1 first item ID to check for
		* @param itemID2 second item ID to check for
		* @return the number of users who have expressed a preference for the items
		*/
		virtual int getNumUsersWithPreferenceFor(long itemID1, long itemID2);

		/**
		* <p>
		* Sets a particular preference (item plus rating) for a user.
		* </p>
		*
		* @param userID
		*          user to set preference for
		* @param itemID
		*          item to set preference for
		* @param value
		*          preference value
		*/
		virtual void setPreference(long userID, long itemID, float value);

		/**
		* <p>
		* Removes a particular preference for a user.
		* </p>
		*
		* @param userID
		*          user from which to remove preference
		* @param itemID
		*          item to remove preference for
		*/
		virtual void removePreference(long userID, long itemID);

		/**
		* @return true if this implementation actually stores and returns distinct preference values;
		*  that is, if it is not a 'boolean' DataModel
		*/
		virtual bool hasPreferenceValues();

		/**
		* @return the maximum preference value that is possible in the current problem domain being evaluated. For
		* example, if the domain is movie ratings on a scale of 1 to 5, this should be 5. While a
		* {@link org.apache.mahout.cf.taste.recommender.Recommender} may estimate a preference value above 5.0, it
		* isn't "fair" to consider that the system is actually suggesting an impossible rating of, say, 5.4 stars.
		* In practice the application would cap this estimate to 5.0. Since evaluators evaluate
		* the difference between estimated and actual value, this at least prevents this effect from unfairly
		* penalizing a {@link org.apache.mahout.cf.taste.recommender.Recommender}
		*/
		virtual float getMaxPreference();

		/**
		* @see #getMaxPreference()
		*/
		virtual float getMinPreference();

		virtual void setMaxPreference(float maxPreferenceValue);

		virtual void setMinPreference(float minPreferenceValue);
	};
}

#endif