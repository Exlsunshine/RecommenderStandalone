#ifndef PREFERENCE_H
#define PREFERENCE_H

namespace RS
{
	/**
		A Preference encapsulates an item and a preference value, which indicates the strength of the
		preference for it.
		Preferences are associated to users.
	*/
	class Preference
	{
	public:
		virtual ~Preference() { }

		/** @return ID of user who prefers the item */
		virtual long getUserID();

		/** @return item ID that is preferred */
		virtual long getItemID();
		
		/**
		* @return strength of the preference for that item. Zero should indicate "no preference either way";
		*         positive values indicate preference and negative values indicate dislike
		*/
		virtual float getValue();
		
		/**
		* Sets the strength of the preference for this item
		*
		* @param value
		*          new preference
		*/
		virtual void setValue(float value);
	};
}

#endif