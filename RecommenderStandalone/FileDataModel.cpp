#include "FileDataModel.h"
#include "Utils.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <atlstr.h>
#include <string>
#include <sstream>
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

	bool FileDataModel::hasPreferenceValues()
	{
		ifstream is(fileName);
		string line;
		while (getline(is, line))
		{
			if (line.empty() || line[0] == COMMENT_CHAR)
				continue;
		}

		vector<string> values;
		std::stringstream ss(line);
		string item;
		while (getline(ss, item, delimiter))
			values.push_back(item);

		return values.size() >= 3 && !values[2].empty();
	}

	float FileDataModel::getMaxPreference() { return 0; }
	float FileDataModel::getMinPreference() { return 0; }
	void FileDataModel::setMaxPreference(float maxPreferenceValue) { }
	void FileDataModel::setMinPreference(float minPreferenceValue) { }

	//#######################			public member functions			#######################
	FileDataModel::FileDataModel(HANDLE dataFile)
	{
		FileDataModel(dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS);
	}

	FileDataModel::FileDataModel(HANDLE dataFile, std::string delimiterRegex)
	{
		FileDataModel(dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, delimiterRegex);
	}

	FileDataModel::FileDataModel(HANDLE dataFile, bool transpose, long minReloadIntervalMS)
	{
		FileDataModel(dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, NULL);
	}
	
	FileDataModel::FileDataModel(HANDLE dataFile, bool transpose, long minReloadIntervalMS, string delimiterRegex)
	{
		if (dataFile == NULL)
		{
			cout << "Open file error." << endl << "Press anykey to exit...";
			cin.get();
			exit(OPEN_FILE_ERROR);
		}

		
		lastModified = getLastWriteTime(dataFile);
		lastUpdateFileModified = getLastWriteTime(dataFile);
		delimiter = getDelimieter(fileName, delimiterRegex);
		hasPrefValues = hasPreferenceValues();
	}
	std::FILE FileDataModel::getDataFile() { return FILE(); }
	char FileDataModel::determineDelimiter(std::string line) { return '.'; }

	//#######################			protected member functions			#######################
	void FileDataModel::reload()
	{
		buildModel();
	}

	DataModel FileDataModel::buildModel() { return DataModel(); }
	void FileDataModel::processFile() { }//Insufficient params 
	void FileDataModel::processLine() { }//Insufficient params 
	void FileDataModel::processFileWithoutID() { }//Insufficient params 
	void FileDataModel::processLineWithoutID() { }//Insufficient params 
	long FileDataModel::readUserIDFromString(std::string value) { return 0; }
	long FileDataModel::readItemIDFromString(std::string value) { return 0; }
	long FileDataModel::readTimestampFromString(std::string value) { return 0; }






	//#######################			private assist functions			#######################
	unsigned long long FileDataModel::getLastWriteTime(HANDLE file)
	{
		FILETIME creationTime, lastAccessTime, lastWriteTime;
		
		if (!GetFileTime(file, &creationTime, &lastAccessTime, &lastWriteTime))
		{
			cout << "Get data file information failed." << endl << "Press anykey to exit...";
			cin.get();
			exit(READ_FILE_INFO_ERROR);
		}

		ULARGE_INTEGER ularge;
		ularge.LowPart = lastWriteTime.dwLowDateTime;
		ularge.HighPart = lastWriteTime.dwHighDateTime;
		
		return ularge.QuadPart;
	}

	char FileDataModel::getDelimieter(string fileName, string delimiterRegex)
	{
		if (delimiterRegex.empty())
		{
			ifstream is(fileName);
			string line;
			while (getline(is, line))
			{
				if (line.empty() || line[0] == COMMENT_CHAR)
					continue;
			}

			for (int i = 0; i < strlen(DELIMIETERS); i++)
			{
				if (line.find(DELIMIETERS[i]) >= 0)
					return DELIMIETERS[i];
			}
			displayError("Delimieter not found.", DELIMIETER_NOT_FOUND_ERROR);
		}
		else
			displayError("DelimiterRegex is not support yet.", FEATURE_NOT_SUPPORT_ERROR);
	}
}