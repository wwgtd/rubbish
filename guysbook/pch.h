#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstddef>


struct Record;

char * field(Record & rcrd, const char* Id); 

// operators

int add(const char * filename, char * args[]);

int count(const char * filename);

bool edit(const char * filename, char * args[]);

//bool del(const char * filename, char * args[]);

struct Record
{
	char firstname[50];
	char lastname[50];
	char patronomic[50];
	char birthday[50];
	char adress[50];
	char phone[20];
	char note[4096];
};




struct FieldMap
{
	char   Id[20];
	size_t offset;
} fields[] = {
#define RegField(FIELD) {#FIELD, offsetof(Record,  FIELD)}
	RegField(firstname),
	RegField(lastname),
	RegField(patronomic),
	RegField(birthday),
	RegField(adress),
	RegField(phone),
	RegField(note)
#undef RegField
};

class RecordIterator : public std::iterator<std::random_access_iterator_tag, Record>
{
public:
	enum { END, NORMAL };
	RecordIterator() {}
	RecordIterator(FILE * pf,  const char * filename = nullptr, int mode = NORMAL);
	explicit RecordIterator(Record * rcrd) : _pr(rcrd) {}
	//RecordIterator(const RecordIterator &it); // default is ok I suppose

	bool operator!=(RecordIterator const& other) const { return _pr != other._pr; }
	bool operator==(RecordIterator const& other) const { return _pr == other._pr; }
	typename RecordIterator::reference operator*() { return *_pr; }
	RecordIterator & operator++() { _pr + sizeof(Record); return *this; }
	RecordIterator & operator++(int) { return ++*this; }
	Record * operator->() {	return _pr; }
	RecordIterator & operator+(int);
	Record & operator[](int);
private:
	Record *	  _pr;
	const char *  _filename;
	Record *	  _begin;
};


// ./prog edit ...
/*
	add F I O Db Adr Ph Notes -> N
	edit n fieldId -> OK/error
	del n -> OK/error
	find HeldId regexp -> n |...| or NULL
	list //n1 n2 -> n |...| or NULL
	count -> n
*/

#endif 
