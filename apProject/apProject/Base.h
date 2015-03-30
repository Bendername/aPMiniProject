#pragma once
class Base
{
public:
	Base();

	virtual void Increment();
	Base(Base&&);

	virtual ~Base();

protected:
	int counter = 0;

};

