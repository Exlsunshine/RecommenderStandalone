#include "FileDataModel.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <windef.h>
#include <fileapi.h>
#include <Windows.h>

using namespace std;

namespace RS
{
	const long FileDataModel::DEFAULT_MIN_RELOAD_INTERVAL_MS = 60 * 1000L;
	const char FileDataModel::COMMENT_CHAR = '#';
	const char FileDataModel::DELIMIETERS[] = { ',', '\t' };


	//#######################			private member functions			#######################
	std::vector<std::FILE> FileDataModel::findUpdateFilesAfter(long minimumLastModified){ vector<FILE> v; return v; }
	long FileDataModel::readLastUpdateFileModified() { return 0; }
	void FileDataModel::addTimestamp() { }//Insufficient params 
	void FileDataModel::removeTimestamp() { }//Insufficient params 


	//#######################			override member functions			#######################
	std::vector<long> FileDataModel::getUserIDs() { vector<long> v; return v; }
	PreferenceArray FileDataModel::getPreferencesFromUser(long userID) { return PreferenceArray(); }
	std::vector<long> FileDataModel::getItemIDsFromUser(long userID) { vector<long> v; return v; }
	std::vector<long> FileDataModel::getItemIDs() { vector<long> v; return v; }
	PreferenceArray FileDataModel::getPreferencesForItem(long itemID) { return PreferenceArray(); }
	float FileDataModel::getPreferenceValue(long userID, long itemID) { return 0; }
	long FileDataModel::getPreferenceTime(long userID, long itemID) { return 0; }
	int FileDataModel::getNumItems() { return 0; }
	int FileDataModel::getNumUsers() { return 0; }
	int FileDataModel::getNumUsersWithPreferenceFor(long itemID) { return 0; }
	int FileDataModel::getNumUsersWithPreferenceFor(long itemID1, long itemID2) { return 0; }
	void FileDataModel::setPreference(long userID, long itemID, float value) { }
	void FileDataModel::removePreference(long userID, long itemID) { }
	bool FileDataModel::hasPreferenceValues() { return false; }
	float FileDataModel::getMaxPreference() { return 0; }
	float FileDataModel::getMinPreference() { return 0; }
	void FileDataModel::setMaxPreference(float maxPreferenceValue) { }
	void FileDataModel::setMinPreference(float minPreferenceValue) { }

	//#######################			public member functions			#######################
	FileDataModel::FileDataModel(std::FILE *_dataFile)
	{
		FileDataModel(_dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS);
	}

	FileDataModel::FileDataModel(std::FILE *dataFile, std::string delimiterRegex)
	{
		FileDataModel(dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, delimiterRegex);
	}

	FileDataModel::FileDataModel(std::FILE *dataFile, bool transpose, long minReloadIntervalMS)
	{
		FileDataModel(dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, NULL);
	}
	
	FileDataModel::FileDataModel(std::FILE *dataFile, bool transpose, long minReloadIntervalMS, std::string delimiterRegex)
	{
		if (dataFile == NULL)
		{
			cout << "Open file error." << endl << "Press anykey to exit...";
			cin.get();
			exit(OPEN_FILE_ERROR);
		}

	}
	std::FILE FileDataModel::getDataFile() { return FILE(); }
	char FileDataModel::determineDelimiter(std::string line) { return '.'; }

	//#######################			protected member functions			#######################
	void FileDataModel::reload() { }
	//DataModel FileDataModel::buildModel() { return DataModel(); }
	void FileDataModel::processFile() { }//Insufficient params 
	void FileDataModel::processLine() { }//Insufficient params 
	void FileDataModel::processFileWithoutID() { }//Insufficient params 
	void FileDataModel::processLineWithoutID() { }//Insufficient params 
	long FileDataModel::readUserIDFromString(std::string value) { return 0; }
	long FileDataModel::readItemIDFromString(std::string value) { return 0; }
	long FileDataModel::readTimestampFromString(std::string value) { return 0; }






	//#######################			private assist functions			#######################
	void FileDataModel::getDateInfo(FILE *dataFile)
	{
		FILETIME creationTime, lastAccessTime, lastWriteTime;
		
		if (!GetFileTime(dataFile, &creationTime, &lastAccessTime, &lastWriteTime))
		{
			cout << "Get data file information failed." << endl << "Press anykey to exit...";
			cin.get();
			exit(READ_FILE_INFO_ERROR);
		}

		SYSTEMTIME sysTime;
		if (!FileTimeToSystemTime(&lastWriteTime, &sysTime))
		{
			cout << "Get time information failed." << endl << "Press anykey to exit...";
			cin.get();
			exit(READ_TIME_INFO_ERROR);
		}

		sysTime.
	}
}