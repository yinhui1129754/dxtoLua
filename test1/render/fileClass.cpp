#include "../stdafx.h"
#include "fileClass.h"
fileClass::fileClass(char * filePath) {
	fileHandle = NULL;
	openFile(filePath);
}
BOOL fileClass::openFile(char * filePath) {
	//¹Ø±ÕÎÄ¼þ
	lines = 0;
	vector<long>().swap(lineIndex);
	if(fileHandle!=NULL){
		fclose(fileHandle);
		fileHandle = NULL;
	}
	path = filePath;
	errorCode = fopen_s(&fileHandle, filePath, "r+");
	if (errorCode != 0) {
		utils::DebugOut("error:code %d mode r+", errorCode);

		errorCode = fopen_s(&fileHandle, filePath, "w+");
		if (errorCode != 0) {
			utils::DebugOut("error:code %d mode w+", errorCode);
			errorCode = 0;
			return FALSE;
		}
	}
	getLines();
	return TRUE;
}
fileClass::~fileClass() {
	if (fileHandle != NULL) {
		fclose(fileHandle);
		fileHandle = NULL;
	}
}
//BOOL fileClass::write(char * s) {
//
//};
BOOL fileClass::write(const char * s) {
	size = fwrite(s, sizeof(char), strnlen_s(s, MAX_CHAR_BUFFER), fileHandle);
	return TRUE;
};
//BOOL fileClass::write(string s ) {
//	return write(s.c_str());
//};
string fileClass::readLine() {
	string s;
	char d = fgetc(fileHandle);
	int d2 = feof(fileHandle);
	while (!d2) {
		if (d == '\n' || d == '\r') {
			break;
		}
		s += d;
		d = fgetc(fileHandle);
		d2= feof(fileHandle);
		
	}
	return s;
}
string fileClass::readLine(int lines) {
	if (lines == 0) {
		toStart();
	}else
	if (lineIndex.size() > 0) {
		toIndex(lineIndex[lines - 1]);
	}
	return readLine();
}
BOOL fileClass::toStart() {
	rewind(fileHandle);
	return TRUE;
}
int fileClass::toIndex(long index) {
	return fseek(fileHandle, index, SEEK_SET);
}
long fileClass::getIndex() {
	return ftell(fileHandle);
}
int fileClass::getLines() {
	if (lines != 0) {
		return lines;
	}
	long nowIndex = getIndex();
	toStart();
	char d = fgetc(fileHandle);
	int d2 = feof(fileHandle);
	while (!d2) {
		d = fgetc(fileHandle);
		d2 = feof(fileHandle);
		if (d == '\n' || d == '\r') {
			lineIndex.push_back(getIndex());
			lines++;
		}
	}
	if (d != '\n'&&d != '\r') {
		lines++;
	}
	
	toIndex(nowIndex);
	return lines;
};