#pragma once

//https://jansson.readthedocs.org/en/2.5/tutorial.html

#include <jansson/jansson.h>

typedef long long long_long;

class JSONObject {

private:
	json_t * root;

public:
	JSONObject(json_t * json);
	JSONObject(const char * jsonString, size_t flags);
	JSONObject(const char * jsonString);
	
	~JSONObject();

	JSONObject* getJSONObject(char * key);
	void putJSONObject(char * key, JSONObject * value);

	const char* getString(char * key);
	void putString(char * key, const char * value);

	long_long getLong(char * key);
	void putLong(char * key, long_long value);

	double getDouble(char * key);
	void putDouble(char * key, double value);

	char* toJSONString();
	char* toJSONString(size_t flags);
	
	
};
