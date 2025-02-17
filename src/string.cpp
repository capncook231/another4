#include "string.hpp"
#include <utility>
#include <iostream>

String::String(const char *s){
	buf = s;
}


String::String(const String &s){
	buf = strdup(s.buf);
}

String::String(String &&s) {
	buf = s.buf;
	s.buf = nullptr;
}

void String::swap(String &s){
	std::swap(buf, s.buf);
}

//COPY ASSIGNMENT
String& String::operator=(String s){
	int s_len = strlen(s.buf);
	if (&s == this) return *this;
	delete[] buf;
	buf = new char[s_len+1];
	buf = strcpy(buf, s.buf);
	return *this;
}

//MOVE ASSIGNMENT
String& String::operator=(String &&s){
	if(&s == this) return *this;
	delete[] buf;
	swap(s);
	s.buf = nullptr;
	return *this;
}

char& String::operator[](int index){
	int lim = strlen(buf);
	if (index < lim && index>= 0) {
		return buf[index];
	}else if (index < 0 && lim != 0){
		return buf[lim+index-1];
	}else if (index >= lim && lim!=0){
		return buf[index%lim];
	}else throw("Out of bounds!");
}

const char& String::operator[](int index) const{
	int lim = strlen(buf);
	if (index < lim && index>= 0) {
		return buf[index];
	}else if (index < 0 && lim != 0){
		return buf[lim+index-1];
	}else if (index >= lim && lim!=0){
		return buf[index%lim];
	}else throw("Out of bounds!");
}

int String::size() const{
	return strlen(buf);
}

String String::reverse() const{
	int buf_len = strlen(buf);
	String temp = String(buf_len + 1);
	reverse_cpy(temp.buf, buf);
	return temp;
}

int String::indexOf(char c) const{
	const char* temp = strchr(buf, c);
	if (temp != nullptr) return temp - buf; else throw("Out of bounds!");

}

int String::indexOf(String s) const{
	const char* temp = strstr(buf, s.buf);
	if (temp != nullptr) return temp - buf; else throw("Out of bounds!");

}

bool String::operator==(String s) const{
	if(strcmp(buf, s.buf) == 0) return true; else return false;	
}

bool String::operator!=(String s) const{
	if(strcmp(buf, s.buf) != 0) return true; else return false;
}

bool String::operator>(String s) const{
	if(strcmp(buf, s.buf) > 0) return true; else return false;
}

bool String::operator<(String s) const{
	if(strcmp(buf, s.buf) < 0) return true; else return false;
}

bool String::operator<=(String s) const{
	if(strcmp(buf, s.buf) <= 0) return true; else return false;
}

bool String::operator>=(String s) const{
	if(strcmp(buf, s.buf) >= 0) return true; else return false;
}

String String::operator+(String s) const{
	String sup = String(strlen(buf) + strlen(s.buf) + 1);
	sup.buf = strcpy(sup.buf, buf);
	sup.buf = strcat(sup.buf, s.buf);
	return sup;

}

String& String::operator+=(String s){
	String sup = String(strlen(buf) + strlen(s.buf) + 1);
	sup.buf = strcpy(sup.buf, buf);
	sup.buf = strcat(sup.buf, s.buf);
	buf = strcpy(buf, sup.buf);
	//delete[] sup.buf;
	return *this;
}



void String::print(std::ostream &out) const{
	out << buf;
}

void String::read(std::istream &in){
	const int maxSize = 1024;
	char temp[maxSize];
	in.getline(temp, maxSize);
	delete[] buf;
	buf = strdup(temp);
}

String::~String(){
	delete[] buf;
}


int String::strlen(const char *s){
	int counter{0};
	for(; s[counter] != '\0'; ++counter){}
	return counter;
}

char* String::strcpy(char *dest, const char *src){
	
	int counter = 0;

	for (; src[counter] != '\0'; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';
	return dest;

}

//STR DUP STR DUP STR DUP STR DUP STR DUP STRDUP

char* String::strdup(const char *src){
	int src_len = strlen(src);
	String temp = String(src_len + 1);
	return strcpy(temp.buf, src);
}

char* String::strncpy(char *dest, const char *src, int n){
	
	int counter = 0;

	for (; src[counter] != '\0' && counter < n; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';

	return dest;
}



char* String::strcat(char *dest, const char *src){
	int counter{0};
	int dest_counter = strlen(dest);

	for(; src[counter] != '\0'; ++counter, ++dest_counter) dest[dest_counter] = src[counter];
		
	dest[dest_counter] = '\0';

	return dest;

}




char* String::strncat(char *dest, const char *src, int n){
	
	int counter{0};
	int dest_counter = strlen(dest);

	for (; src[counter] != '\0' && counter < n; ++counter, ++dest_counter) dest[dest_counter] = src[counter];
	dest[dest_counter] = '\0';

	return dest;
}




int String::strcmp(const char *left, const char *right){
	int counter = 0;
	int src_len = strlen(right);
	for (; counter < src_len && left[counter] == right[counter]; ++counter){}
	return left[counter] - right[counter];
}

int String::strncmp(const char *left, const char *right, int n){
	int counter = 0;
	int src_len = strlen(right);
	if (n == 0) return 0;
	for (; counter<src_len && counter < n && left[counter] == right[counter]; ++counter){}
	if (counter == n) return 0; else return left[counter] - right[counter] - 0;
}

//HAVE NOT DOUBLE CHECKED BELOW
void String::reverse_cpy(char *dest, const char *src){
	int src_len{strlen(src)};
	for (int counter = 0; counter < src_len; ++counter){
		dest[counter] = src[src_len-1-counter];
	}
	dest[src_len] = '\0';
}

const char* String::strchr(const char *str, char c){
	//int str_len{strlen(str)};
	int counter{0};
	for (; str[counter] != '\0' && str[counter] != c; ++counter) {}
	if (str[counter] == c) return &str[counter]; else return nullptr;
}

const char* String::strstr(const char *haystack, const char *needle){
	int ned_size = strlen(needle);
	int hay_size = strlen(haystack);
	if (ned_size > hay_size || ned_size == 0) return nullptr;
	for (int counter = 0; haystack[counter] != '\0' && counter < hay_size - ned_size + 1; ++counter){
		if (strcmp(&haystack[counter], needle) == 0) return &haystack[counter];
	} return nullptr;
}

String::String(int length){
	buf = new char[length];
}

std::ostream &operator<<(std::ostream &out, String s){
	s.print(out);
	return out;
}

std::istream &operator>>(std::istream &in, String &s){
	s.read(in);
	return in;
}
