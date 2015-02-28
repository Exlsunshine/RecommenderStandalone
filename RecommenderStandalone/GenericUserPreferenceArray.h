#ifndef GENERIC_USER_PREFERENCE_H
#define GENERIC_USER_PREFERENCE_H

#include <iostream>
#include <vector>

#include "Preference.h"
#include "PreferenceArray.h"


namespace RS
{
	/**
	* Like {@link GenericItemPreferenceArray} but stores preferences for one user (all user IDs the same) rather
	* than one item.
	*
	* This implementation maintains two parallel arrays, of item IDs and values. The idea is to save allocating
	* {@link Preference} objects themselves. This saves the overhead of {@link Preference} objects but also
	* duplicating the user ID value.
	*
	* @see BooleanUserPreferenceArray
	* @see GenericItemPreferenceArray
	* @see GenericPreference
	*/
	class GenericUserPreferenceArray :public PreferenceArray
	{
	private:
		static const int ITEM = 1;
		static const int VALUE = 2;
		static const int VALUE_REVERSED = 3;
		const std::vector<long> ids;
		long id;
		std::vector<long> values;

	public:
		GenericUserPreferenceArray(int size);//Dont forget to initialize inner
		GenericUserPreferenceArray(std::vector<Preference> prefs);//Dont forget to initialize inner

		/*************		Override member functions from PreferenceArray		**********/
		int length();
		Preference get(int i);
		void set(int i, Preference pref);
		long getUserID(int i);
		/**
		* Note that this method will actually set the user ID for <em>all</em> preferences.
		*/
		void setUserID(int i, long userID);
		long getItemID(int i);
		void setItemID(int i, long itemID);
		std::vector<long> getIDs();
		float getValue(int i);
		void setValue(int i, float value);
		void sortByUser();
		void sortByItem();
		void sortByValue();
		void sortByValueReversed();
		bool hasPrefWithUserID(long userID);
		bool hasPrefWithItemID(long itemID);
		void lateralSort(int type);
		bool isLess(int i, int j, int type);
		void swap(int i, int j);
		GenericUserPreferenceArray& clone();

	private:
		/* This is a private copy constructor for clone(). */
		GenericUserPreferenceArray(std::vector<long> ids, long id, std::vector<float> values);

		/**********			Implementation of Preference		**********/
		class PrefrenceView;
		friend class PrefrenceView;
		class PrefrenceView :public Preference
		{
		private:
			GenericUserPreferenceArray &outter;
			const int i;
		public:
			PrefrenceView(int _i, GenericUserPreferenceArray &o) :i(_i),outter(o) { }
			long getUserID() { return outter.getUserID(i); }
			long getItemID() { return outter.getItemID(i); }
			float getValue() { return outter.values[i]; }
			void setValue(float value) { outter.values[i] = value; }
		}; 
		PrefrenceView &inner;
	};
}

#endif