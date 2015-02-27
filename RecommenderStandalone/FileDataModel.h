#ifndef FILE_DATAMODEL_H
#define FILE_DATAMODEL_H

#include <iostream>
#include "DataModel.h"

namespace RS
{
	class FileDataModel : public DataModel
	{
	private:
		static const char COMMENT_CHAR;// = '#';
		static const char DELIMIETERS[];// = { ',', '\t' };

		std::FILE dataFile;
		long lastModified;
		long lastUpdateFileModified;
		char delimiter;
		bool hasPrefValues;
		DataModel delegate;
		bool transpose;
		long minReloadIntervalMS;

		std::vector<std::FILE> findUpdateFilesAfter(long minimumLastModified);
		long readLastUpdateFileModified();
		void addTimestamp();//Insufficient params 
		static void removeTimestamp();//Insufficient params 
	public:
		static const long DEFAULT_MIN_RELOAD_INTERVAL_MS;// = 60 * 1000L;

		FileDataModel(std::FILE *dataFile);
		FileDataModel(std::FILE *dataFile, std::string delimiterRegex);
		FileDataModel(std::FILE *dataFile, bool transpose, long minReloadIntervalMS);
		FileDataModel(std::FILE *dataFile, bool transpose, long minReloadIntervalMS, std::string delimiterRegex);
		std::FILE getDataFile();
		static char determineDelimiter(std::string line);

		//Below functions are overrided from DataModel
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
		void setPreference(long userID, long itemID, float value);
		void removePreference(long userID, long itemID);
		bool hasPreferenceValues();
		float getMaxPreference();
		float getMinPreference();
		void setMaxPreference(float maxPreferenceValue);
		void setMinPreference(float minPreferenceValue);
		//Above functions are overrided from DataModel

	protected:
		void reload();
		DataModel buildModel();
		void processFile();//Insufficient params 
		void processLine();//Insufficient params 
		void processFileWithoutID();//Insufficient params 
		void processLineWithoutID();//Insufficient params 
		long readUserIDFromString(std::string value);
		long readItemIDFromString(std::string value);
		long readTimestampFromString(std::string value);

	private:
		void getDateInfo(FILE *dataFile);
	};
}

#endif