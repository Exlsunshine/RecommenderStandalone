#ifndef PREFERENCE_ARRAY_H
#define PREFERENCE_ARRAY_H

#include <vector>
#include "Preference.h"

namespace RS
{
	/**
		An alternate representation of an array of Preference.
		Implementations, in theory, can produce a more memory-efficient representation.
	*/
	class PreferenceArray
	{
	public:
		virtual ~PreferenceArray() { }

		/**
			return size of length of the "array"
		*/
		virtual int length();

		/**
		* @param i
		*          index
		* @return a materialized {@link Preference} representation of the preference at i
		*/
		virtual Preference get(int i);

		/**
		* Sets preference at i from information in the given {@link Preference}
		*
		* @param i
		* @param pref
		*/
		virtual void set(int i, Preference pref);

		/**
		* @param i
		*          index
		* @return user ID from preference at i
		*/
		virtual long getUserID(int i);

		/**
		* Sets user ID for preference at i.
		*
		* @param i
		*          index
		* @param userID
		*          new user ID
		*/
		virtual void setUserID(int i, long userID);

		/**
		* @param i
		*          index
		* @return item ID from preference at i
		*/
		virtual long getItemID(int i);

		/**
		* Sets item ID for preference at i.
		*
		* @param i
		*          index
		* @param itemID
		*          new item ID
		*/
		virtual void setItemID(int i, long itemID);

		/**
		* @return all user or item IDs
		*/
		virtual std::vector<long> getIDs();

		/**
		* @param i
		*          index
		* @return preference value from preference at i
		*/
		virtual float getValue(int i);

		/**
		* Sets preference value for preference at i.
		*
		* @param i
		*          index
		* @param value
		*          new preference value
		*/
		virtual void setValue(int i, float value);

		/**
		* @return independent copy of this object
		*/
		virtual PreferenceArray& clone();

		/**
		* Sorts underlying array by user ID, ascending.
		*/
		virtual void sortByUser();

		/**
		* Sorts underlying array by item ID, ascending.
		*/
		virtual void sortByItem();

		/**
		* Sorts underlying array by preference value, ascending.
		*/
		virtual void sortByValue();

		/**
		* Sorts underlying array by preference value, descending.
		*/
		virtual void sortByValueReversed();

		/**
		* @param userID
		*          user ID
		* @return true if array contains a preference with given user ID
		*/
		virtual bool hasPrefWithUserID(long userID);
		
		/**
		* @param itemID
		*          item ID
		* @return true if array contains a preference with given item ID
		*/
		virtual bool hasPrefWithItemID(long itemID);
	};
}

#endif