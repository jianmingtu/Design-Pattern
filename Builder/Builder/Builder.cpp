// Builder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;


class ITitle {
protected:
	string _title;
public:
	string getTitle() {return _title;}
};

class IBody {
protected:
	string _body;
public:
	string getBody() { return _body; }
};

class HtmlTitle : public ITitle {
public: 
	HtmlTitle(string str) 
	{
		_title = str;
	}
};

class HtmlBody : public IBody {
public:
	HtmlBody(string str)
	{
		_body = str;
	}

};

class IDocument
{
	unique_ptr<ITitle> _title;
	unique_ptr<IBody> _body;
	string _name;

public:
	IDocument(string name) : _name(name) {} 
	void setTitle(unique_ptr<ITitle>& title) {
		_title = std::move(title);
		title = nullptr;
	}

	void setBody(unique_ptr<IBody>& body) {
		_body = std::move(body);
		body = nullptr;
	}

	string getTitle() {return _title->getTitle();}
	string getBody() {return _body->getBody();}

	virtual string toString() = 0;
};

class HTMLDocument :  public IDocument
{
public:
	HTMLDocument(const string name) : IDocument(name) {}
	virtual string toString() override
	{
		return "<html><head><title>" + getTitle() + "< / title>< / head>" + getBody() + "<body>";
	}
};

class IBuilder
{
protected:
	IDocument * _doc;
public:
	virtual void makeTitle(string title) = 0;
	virtual void makeBody(string str) = 0;

	IDocument* getDocument()
	{
		return _doc;

	};
};


class HtmlBuilder : public IBuilder {

public:
	HtmlBuilder() {
		_doc = new HTMLDocument("HTML doc");
	}

	void makeTitle(string str) override {
		unique_ptr<ITitle> title = unique_ptr<ITitle>(new HtmlTitle(str));
		_doc->setTitle(title);
	}

	void makeBody(string str) override {
		unique_ptr<IBody>  body = unique_ptr<IBody>(new HtmlBody(str));
		_doc->setBody(body);
	}

};

int main()
{
	unique_ptr<IBuilder> builder = nullptr;
	IDocument* doc = nullptr;
	int choice;

	// Prompt user for their meal choice
	cout << "Select a document: " << endl;
	cout << "1: HTML" << endl;
	cout << "2: Text" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;


	// Instantiate the apporpriate builder based on user input
	switch (choice)
	{
	case 1:
		builder = make_unique<HtmlBuilder>();
		break;
	case 2:
		//builder = make_unique<TextBuilder>();
		break;
	default:
		cout << "Invalid Selection" << endl;
		builder = NULL;
		break;
	}


	// Build the complex object
	doc = builder->getDocument();
	builder->makeTitle("-- Builder ---")	;
	builder->makeBody("-- Builder Body ---")	;
	cout << doc->toString() << endl;

}

