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
		return false;
	}

	float FileDataModel::getMaxPreference() { return 0; }
	float FileDataModel::getMinPreference() { return 0; }
	void FileDataModel::setMaxPreference(float maxPreferenceValue) { }
	void FileDataModel::setMinPreference(float minPreferenceValue) { }
	string FileDataModel::toString(){ return ""; }

	//#######################			public member functions			#######################
	FileDataModel::FileDataModel(std::string _fileName, HANDLE dataFile)
	{
		FileDataModel(_fileName,dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS);
	}

	FileDataModel::FileDataModel(std::string _fileName, HANDLE dataFile, std::string delimiterRegex)
	{
		FileDataModel(_fileName,dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, delimiterRegex);
	}

	FileDataModel::FileDataModel(std::string _fileName, HANDLE dataFile, bool transpose, long minReloadIntervalMS)
	{
		FileDataModel(_fileName,dataFile, false, DEFAULT_MIN_RELOAD_INTERVAL_MS, "");
	}
	
	FileDataModel::FileDataModel(std::string _fileName, HANDLE dataFile, bool transpose, long minReloadIntervalMS, string delimiterRegex) :fileName(_fileName)
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
		hasPrefValues = isDataContainsPrefVals();
		this->transpose = transpose;
		this->minReloadIntervalMS = minReloadIntervalMS;

		reload();
	}
	std::FILE FileDataModel::getDataFile() { return FILE(); }
	char FileDataModel::determineDelimiter(std::string line) { return '.'; }

	//#######################			protected member functions			#######################
	void FileDataModel::reload()
	{
		delegate = buildModel();
	}

	DataModel* FileDataModel::buildModel()
	{
		if (hasPrefValues)
		{
			processFile(false);
		}
		else
			displayError("Un-preferenceValues is not support yet.", FEATURE_NOT_SUPPORT_ERROR);

		return new DataModel();
	}
	void FileDataModel::processFile(boolean fromPriorData) //Insufficient params 
	{
		ifstream is(fileName);
		string line;

		while (getline(is, line))
		{
			if (line.empty() || line[0] == COMMENT_CHAR)
				continue;
			else
				processLine(line, fromPriorData);
		}
	}
	void FileDataModel::processLine(string line, boolean fromPriorData) //Insufficient params 
	{
		

		vector<string> values;
		std::stringstream ss(line);
		string element;
		while (getline(ss, element, delimiter))
			values.push_back(element);

		long userID = readUserIDFromString(values[0]);
		long itemID = readItemIDFromString(values[1]);
		float preferenceValue = atof(values[2].c_str());

		if (!fromPriorData)
		{

		}
		else
			displayError("fromPriorData is not supported yet.", FEATURE_NOT_SUPPORT_ERROR);
	}
	void FileDataModel::processFileWithoutID() { }//Insufficient params 
	void FileDataModel::processLineWithoutID() { }//Insufficient params 
	long FileDataModel::readUserIDFromString(std::string value) { return atol(value.c_str()); }
	long FileDataModel::readItemIDFromString(std::string value) { return atol(value.c_str()); }
	long FileDataModel::readTimestampFromString(std::string value) { return atol(value.c_str()); }






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
				else
					break;
			}

			for (int i = 0; i < strlen(DELIMIETERS); i++)
			{
				if (line.find(DELIMIETERS[i]) != string::npos)
					return DELIMIETERS[i];
			}
			displayError("Delimieter not found.", DELIMIETER_NOT_FOUND_ERROR);
		}
		else
			displayError("DelimiterRegex is not support yet.", FEATURE_NOT_SUPPORT_ERROR);
	}

	bool FileDataModel::isDataContainsPrefVals()
	{
		ifstream is(fileName);
		string line;
		while (getline(is, line))
		{
			if (line.empty() || line[0] == COMMENT_CHAR)
				continue;
			else
				break;
		}

		vector<string> values;
		std::stringstream ss(line);
		string item;
		while (getline(ss, item, delimiter))
			values.push_back(item);

		return values.size() >= 3 && !values[2].empty();
	}
}