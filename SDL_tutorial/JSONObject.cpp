#include "JSONObject.h"

//https://jansson.readthedocs.org/en/2.5/tutorial.html

JSONObject::JSONObject(json_t * json) {

	root = json;
}

JSONObject::JSONObject( const char * jsonString ) {
	
	json_error_t jsonError;
	root = json_loads(jsonString, 0, &jsonError);
}

JSONObject::JSONObject( const char * jsonString, size_t flags ) {

	json_error_t jsonError;
	root = json_loads(jsonString, flags, &jsonError);
}

JSONObject::~JSONObject(void) {

	json_decref(root);
	root = NULL;
}

const char* JSONObject::getString(char * key) {

	return json_string_value(json_object_get(root, key));
}

void JSONObject::putString(char * key, const char * value) {

	json_t * obj = json_string(value);

	json_object_set(root, key, obj);
	
	json_decref(obj);
}

long_long JSONObject::getLong(char * key) {

	return json_integer_value(json_object_get(root, key));
}

void JSONObject::putLong(char * key, long_long value) {

	json_t * obj = json_integer(value);
	
	json_object_set(root, key, obj);

	json_decref(obj);
}

double JSONObject::getDouble(char * key) {

	return json_real_value(json_object_get(root, key));
}

void JSONObject::putDouble(char * key, double value) {

	json_t * obj = json_real(value);
	
	json_object_set(root, key, obj);

	json_decref(obj);
}

JSONObject* JSONObject::getJSONObject( char * key ) {
	
	return new JSONObject(json_object_get(root, key));
}

void JSONObject::putJSONObject( char * key, JSONObject * value ) {

	json_object_set(root, key, value->root);
}

char* JSONObject::toJSONString() {

	return toJSONString(0);
}

char* JSONObject::toJSONString( size_t flags ) {

	return json_dumps(root, flags);
}
