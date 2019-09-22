#pragma once
extern class winClass;
class timmer
{
public:
	timmer();
	~timmer();
	string status = "timmer";

public:
	void loop(winClass *);
};

