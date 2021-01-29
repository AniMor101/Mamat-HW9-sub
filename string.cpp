
#include <iostream>
#include <vector>
#include <cstring>
#include <cctype>
#include "string.h"

using namespace std;

// Default constructor
String::String() : length(0) {
    data = new char[1];
    *data = '\0';
}

// Constructor
String::String(const char* str) {
    if (str == NULL)
    {
        length = 0;
        data = new char[1];
        *data = '\0';
        return;
    }
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}


// Copy constructor
String::String(const String& str) {
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
}

// Destructor
String::~String() {
    if (data != NULL) {
        delete[] data;
    }
}

// Operator =, according to rhs
String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        delete[] data;
        length = rhs.length;
        data = new char[length + 1];
        strcpy(data, rhs.data);
    }
    return *this;
}

// Operator =, according to str
String& String::operator=(const char* str) {
    delete[] data;
    if (str == NULL) {
        length = 0;
        data = new char[1];
        *data = '\0';
        return *this;
    }
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
    return *this;
}

// Returns true if the contents of this equals to the contents of rhs
bool String::equals(const String& rhs) const {
    if (strcmp(data, rhs.data) == 0) {
        return true;
    }
    return false;
}

// Returns true if the contents of this equals to rhs
bool String::equals(const char* rhs) const {
    if (rhs == NULL) {
        return false;
    }
    if (strcmp(data, rhs) == 0) {
        return true;
    }
    return false;
}

// Splits this to several sub-strings according to delimiters
void String::split(const char* delimiters, String** output,
    size_t* size) const {
    if (size != NULL) {
        *size = 0;
    }
    if ((delimiters == NULL) || (size == NULL) || (length == 0)) {
        return;
    }
    // vector of sub-strings
    vector<String> tokens;
    char* str_copy = new char[length + 1];
    strcpy(str_copy, data);

    char* ch_p;
    // strtok modify the string to truncate so we give him a copy
    ch_p = strtok(str_copy, delimiters);
    while (ch_p != NULL)
    {
        tokens.push_back(String(ch_p));
        ch_p = strtok(NULL, delimiters);
    }
    delete[] str_copy;

    String* str_array = new String[(int)tokens.size()];
    for (int i = 0; i < (int)tokens.size(); i++) {
        str_array[i] = (tokens.data())[i].trim();
    }
    // str_array (includes each sub-string) into the output
    *size = (size_t)tokens.size();
    if (output != NULL) {
        *output = str_array;
    }else {
    	delete[] str_array;
    }
}

// Convert data to an integer
int String::to_integer() const
{
    int integer;
    integer = atoi(data);
    return integer;
}

// Remove white-spaces
String String::trim() const
{
    if (length == 0) {
        return *this;
    }
    int first = 0;
    while (isspace(data[first]))
    {
        first++;
    }
    // first = index of the first relevant position (no white space)

    if (data[first] == '\0') {
        char tmp_str[] = "";
        return String(tmp_str);
    }

    int last = (int)length - 1; ;
    while (isspace(data[last]))
    {
        last--;
    }
    // last = index of the last relevant position (no white space)

    int new_length = last - first + 1;
    char* new_string = new char[new_length + 1];
    strncpy(new_string, &data[first], new_length);
    // add end of string
    new_string[new_length] = '\0';
    String str = String(new_string);
    delete[] new_string;
    return str;
}
