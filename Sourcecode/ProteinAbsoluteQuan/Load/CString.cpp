// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Stephan Aiche$
// $Authors: Marc Sturm $
// --------------------------------------------------------------------------
#include "stdafx.h"
#include "CString.h"



const String String::EMPTY;

String::String() :
string()
{
}

String::String(const string& s) :
string(s)
{
}

String::String(const char* s) :
string(s)
{
}

String::String(const char* s, SizeType length)
{
	SizeType count = 0;
	while (count < length && *(s + count) != 0)
	{
		*this += *(s + count);
		++count;
	}
}

String::String(const char c) :
string(1, c)
{
}

String::String(size_t len, char c) :
string(len, c)
{
}

String::String(int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(unsigned int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(short int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(short unsigned int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(long int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(long unsigned int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(long long unsigned int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(long long signed int i) :
string()
{
	stringstream s;
	s << i;
	string::operator=(s.str());
}

String::String(float f) :
string()
{
	stringstream s;
	s << f;
	string::operator=(s.str());
}

String::String(double d) :
string()
{
	stringstream s;
	s << d;
	string::operator=(s.str());
}

String::String(long double ld) :
string()
{
	stringstream s;
	//s.precision(writtenDigits(ld));
	s << ld;
	string::operator=(s.str());
}

String String::numberLength(double d, int n)
{
	stringstream s;
	//reserve one space for the minus sign
	int sign = 0;
	if (d < 0)
		sign = 1;
	d = fabs(d);

	if (d < pow(10.0, int(n - sign - 2)))
	{
		//s.precision(writtenDigits(d));
		if (sign == 1)
			s << "-";
		s << d;
	}
	else
	{
		int exp = 0;
		while (d > pow(10.0, int(n - sign - 4)))
		{
			d /= 10;
			++exp;
		}
		d = int(d) / 10.0;
		exp += 1;
		if (sign == 1)
			s << "-";
		s << d << "e";
		if (exp < 10)
			s << "0";
		s << exp;
	}
	return s.str().substr(0, n);
}

String& String::fillLeft(char c, int size)
{
	if (string::size() < size)
	{
		string::operator=(String(size - string::size(), c) + *this);
	}
	return *this;
}

String& String::fillRight(char c, int size)
{
	if (string::size() < size)
	{
		string::operator=(*this + String(size - string::size(), c));
	}
	return *this;
}

bool String::hasPrefix(const String& string) const
{
	if (string.size() > size())
	{
		return false;
	}
	if (string.empty())
	{
		return true;
	}
	return compare(0, string.size(), string) == 0;
}

bool String::hasSuffix(const String& string) const
{
	if (string.size() > size())
	{
		return false;
	}
	if (string.empty())
	{
		return true;
	}
	return compare(size() - string.size(), string.size(), string) == 0;
}

bool String::hasSubstring(const String& string) const
{
	return string::find(string) != string::npos;
}

bool String::has(unsigned char byte) const
{
	return string::find(char(byte)) != string::npos;
}

String String::prefix(SizeType length) const
{
	if (length > size())
	{
		//throw Exception::IndexOverflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, size());
	}
	return substr(0, length);
}

String String::suffix(SizeType length) const
{
	if (length > size())
	{
		//throw Exception::IndexOverflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, size());
	}
	return substr(size() - length, length);
}

String String::prefix(int length) const
{
	if (length < 0)
	{
		//throw Exception::IndexUnderflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, 0);
	}
	if (length > int(size()))
	{
		//throw Exception::IndexOverflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, size());
	}
	return substr(0, length);
}

String String::suffix(int length) const
{
	if (length < 0)
	{
		//throw Exception::IndexUnderflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, 0);
	}
	if (length > int(size()))
	{
		//throw Exception::IndexOverflow(__FILE__, __LINE__, __PRETTY_FUNCTION__, length, size());
	}
	return substr(size() - length, length);
}

String String::prefix(char delim) const
{
	size_t pos = string::find(delim);
	if (pos == string::npos) //char not found
	{
		//throw Exception::ElementNotFound(__FILE__, __LINE__, __PRETTY_FUNCTION__,
		//String(delim));
	}
	return string::substr(0, pos);
}

String String::suffix(char delim) const
{
	size_t pos = string::rfind(delim);
	if (pos == string::npos) //char not found
	{
		//throw Exception::ElementNotFound(__FILE__, __LINE__, __PRETTY_FUNCTION__,
		//	String(delim));
	}
	return string::substr(++pos);
}

String String::substr(size_t pos, size_t n) const
{
	size_t begin = std::min(pos, this->size());
	return (String)string::substr(begin, n);
}

String String::chop(size_t n) const
{
	size_t end = 0;
	if (n < this->size())
	{
		end = this->size() - n;
	}

	return String(this->begin(), this->begin() + end);
}

String& String::trim()
{
	//search for the begin of truncated string
	iterator begin = this->begin();
	while (begin != end() && (*begin == ' ' || *begin == '\t' || *begin == '\n' || *begin == '\r'))
	{
		++begin;
	}

	//all characters are whitespaces
	if (begin == end())
	{
		string::clear();
		return *this;
	}

	//search for the end of truncated string
	Iterator end = this->end();
	end--;
	while (end != begin && (*end == ' ' || *end == '\n' || *end == '\t' || *end == '\r'))
	{
		--end;
	}
	++end;

	//no characters are whitespaces
	if (begin == this->begin() && end == this->end())
	{
		return *this;
	}

	string::operator=(string(begin, end));

	return *this;
}

String& String::quote(char q, QuotingMethod method)
{
	if (method == ESCAPE)
	{
		substitute(String("\\"), String("\\\\"));
		substitute(String(q), "\\" + String(q));
	}
	else if (method == DOUBLE)
		substitute(String(q), String(q) + String(q));
	string::operator=(q + *this + q);
	return *this;
}

String& String::unquote(char q, QuotingMethod method)
{
	// check if input string matches output format of the "quote" method:
	if ((size() < 2) || ((*this)[0] != q) || ((*this)[size() - 1] != q))
	{
		//throw Exception::ConversionError(
		////	__FILE__, __LINE__, __PRETTY_FUNCTION__,
		//	"'" + *this + "' does not have the expected format of a quoted string");
	}
	string::operator=(string::substr(1, size() - 2)); // remove quotation marks
	if (method == ESCAPE)
	{
		substitute("\\" + String(q), String(q));
		substitute(String("\\\\"), String("\\"));
	}
	else if (method == DOUBLE)
		substitute(String(q) + String(q), String(q));
	return *this;
}

String& String::simplify()
{
	String simple;

	bool last_was_whitespace = false;
	for (iterator it = this->begin(); it != end(); ++it)
	{
		if (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
		{
			if (!last_was_whitespace)
			{
				simple += ' ';
			}
			last_was_whitespace = true;
		}
		else
		{
			simple += *it;
			last_was_whitespace = false;
		}
	}

	this->swap(simple);

	return *this;
}

String String::random(int length)
{
	srand(time(0));
	String tmp(length, '.');
	SizeType random;
	for (size_t i = 0; i < length; ++i)
	{
		random = (SizeType)floor(((double)rand() / (double(RAND_MAX) + 1)) * 62.0);
		if (random < 10)
		{
			tmp[i] = (char)(random + 48);
		}
		else if (random < 36)
		{
			tmp[i] = (char)(random + 55);
		}
		else
		{
			tmp[i] = (char)(random + 61);
		}
	}
	return tmp;
}

String& String::reverse()
{
	String tmp = *this;
	for (size_t i = 0; i != size(); ++i)
	{
		(*this)[i] = tmp[size() - 1 - i];
	}
	return *this;
}

bool String::split(const char splitter, vector<String>& substrings,
	bool quote_protect) const
{
	substrings.clear();
	if (empty())
		return false;

	size_t nsplits = count(begin(), end(), splitter);

	if (!quote_protect && (nsplits == 0))
	{
		substrings.push_back(*this);
		return false;
	}

	substrings.reserve(nsplits + 1);
	ConstIterator begin = this->begin();
	ConstIterator end = this->begin();

	if (quote_protect)
	{
		int quote_count(0);
		for (; end != this->end(); ++end)
		{
			if (*end == '"')
			{
				++quote_count;
			}
			if ((quote_count % 2 == 0) && (*end == splitter))
			{
				String block = String(begin, end);
				block.trim();
				if ((block.size() >= 2) && ((block.prefix(1) == String("\"")) ^
					(block.suffix(1) == String("\""))))
				{ // block has start or end quote, but not both
					// (one quote is somewhere in the middle)
					//throw Exception::ConversionError(
					//	__FILE__, __LINE__, __PRETTY_FUNCTION__,
					//	String("Could not dequote string '") + block +
					//	"' due to wrongly placed '\"'.");
				}
				else if ((block.size() >= 2) && (block.prefix(1) == String("\"")) &&
					(block.suffix(1) == String("\"")))
				{ // block has start and end quotes --> remove them
					block = block.substr(1, block.size() - 2);
				}
				substrings.push_back(block);
				begin = end + 1;
			}
		}
		// no valid splitter found - return empty list
		if (substrings.empty())
		{
			substrings.push_back(*this);
			return false;
		}

		String block = String(begin, end);
		block.trim();
		if ((block.size() >= 2) && ((block.prefix(1) == String("\"")) ^
			(block.suffix(1) == String("\""))))
		{ // block has start or end quote but not both
			// (one quote is somewhere in the middle)
			//throw Exception::ConversionError(
			//	__FILE__, __LINE__, __PRETTY_FUNCTION__,
			//	String("Could not dequote string '") + block +
			//	"' due to wrongly placed '\"'.");
		}
		else if ((block.size() >= 2) && (block.prefix(1) == String("\"")) &&
			(block.suffix(1) == String("\"")))
		{ // block has start and end quotes --> remove them
			block = block.substr(1, block.size() - 2);
		}
		substrings.push_back(block);
	}
	else // do not honor quotes
	{
		for (; end != this->end(); ++end)
		{
			if (*end == splitter)
			{
				substrings.push_back(String(begin, end));
				begin = end + 1;
			}
		}
		substrings.push_back(String(begin, end));
	}

	return true;
}

bool String::split(const String& splitter, std::vector<String>& substrings)
const
{
	substrings.clear();
	if (empty())
		return false;

	if (splitter.empty()) // split after every character:
	{
		substrings.resize(size());
		for (size_t i = 0; i < size(); ++i)
			substrings[i] = (*this)[i];
		return true;
	}

	size_t len = splitter.size(), start = 0, pos = string::find(splitter);
	if (len == 0)
		len = 1;
	while (pos != string::npos)
	{
		substrings.push_back(string::substr(start, pos - start));
		start = pos + len;
		pos = string::find(splitter, start);
	}
	substrings.push_back(string::substr(start, size() - start));
	return substrings.size() > 1;
}

bool String::split_quoted(const String& splitter, vector<String>& substrings,
	char q, QuotingMethod method) const
{
	substrings.clear();
	if (empty() || splitter.empty())
		return false;

	bool in_quote = false;
	char targets[2] = { q, splitter[0] }; // targets for "find_first_of"
	std::string rest = splitter.substr(1, splitter.size() - 1);
	size_t start = 0;
	for (size_t i = 0; i < size(); ++i)
	{
		if (in_quote) // skip to closing quotation mark
		{
			bool embedded = false;
			if (method == ESCAPE)
			{
				for (; i < size(); ++i)
				{
					if ((*this)[i] == '\\')
						embedded = !embedded;
					else if (((*this)[i] == q) && !embedded)
						break;
					else
						embedded = false;
				}
			}
			else // method: NONE or DOUBLE
			{
				for (; i < size(); ++i)
				{
					if ((*this)[i] == q)
					{
						if (method == NONE)
							break; // found
						// next character is also closing quotation mark:
						if ((i < size() - 1) && ((*this)[i + 1] == q))
							embedded = !embedded;
						// even number of subsequent quotes (doubled) => found
						else if (!embedded)
							break;
						// odd number of subsequent quotes => belongs to a pair
						else
							embedded = false;
					}
				}
			}
			in_quote = false; // end of quote reached
		}
		else
		{
			i = string::find_first_of(targets, i, 2);
			if (i == string::npos)
				break; // nothing found
			if ((*this)[i] == q)
				in_quote = true;
			else if (string::compare(i + 1, rest.size(), rest) == 0) // splitter found
			{
				substrings.push_back(string::substr(start, i - start));
				start = i + splitter.size();
				i = start - 1; // increased by loop
			}
		}
	}
	if (in_quote) // reached end without finding closing quotation mark
	{
		//throw Exception::ConversionError(
		//	__FILE__, __LINE__, __PRETTY_FUNCTION__,
		//	"unbalanced quotation marks in string '" + *this + "'");
	}
	substrings.push_back(string::substr(start, size() - start));
	return substrings.size() > 1;
}



int String::toInt() const
{
	std::stringstream ss(c_str());
	int ret = 0;
	ss >> ret;
	return ret;
}

float String::toFloat() const
{
	float ret = 0.0;
	try
	{
		ret = boost::lexical_cast<float>(boost::trim_copy(*this));
	}
	catch (boost::bad_lexical_cast&)
	{
		//throw Exception::ConversionError(__FILE__, __LINE__, __PRETTY_FUNCTION__, String("Could not convert string '") + *this + "' to a float value");
	}
	return ret;
}

double String::toDouble() const
{
	double ret = 0.0;
	if (*this == "")
		return 0.0;
	try
	{
		ret = boost::lexical_cast<double>(boost::trim_copy(*this));
	}
	catch (boost::bad_lexical_cast&)
	{
		//throw Exception::ConversionError(__FILE__, __LINE__, __PRETTY_FUNCTION__, String("Could not convert string \'") + *this + "\' to a double value");
	}
	return ret;
}

String& String::toUpper()
{
	std::transform(begin(), end(), begin(), (int(*)(int))toupper);
	return *this;
}

String& String::firstToUpper()
{
	if (size() != 0)
	{
		(*this)[0] = toupper((*this)[0]);
	}
	return *this;
}

String& String::toLower()
{
	std::transform(begin(), end(), begin(), (int(*)(int))tolower);
	return *this;
}

String& String::substitute(char from, char to)
{
	std::replace(this->begin(), this->end(), from, to);
	return *this;
}

String& String::substitute(const String& from, const String& to)
{
	if (!from.empty())
	{
		vector<String> parts;
		split(from, parts);
		concatenate(parts.begin(), parts.end(), to);
	}
	return *this;
}

String& String::remove(char what)
{
	this->erase(std::remove(this->begin(), this->end(), what), this->end());
	return *this;
}

String& String::ensureLastChar(char end)
{
	if (!this->hasSuffix(end))
		this->append(1, end);
	return *this;
}

String& String::removeWhitespaces()
{
	bool contains_ws = false;
	for (ConstIterator it = this->begin(); it != this->end(); ++it)
	{
		char c = *it;
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		{
			contains_ws = true;
			break;
		}
	}

	if (contains_ws)
	{
		string tmp;
		tmp.reserve(this->size());
		for (ConstIterator it = this->begin(); it != this->end(); ++it)
		{
			char c = *it;
			if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
				tmp += c;
		}
		this->swap(tmp);
	}

	return *this;
}

String String::operator+(int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(unsigned int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(short int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(short unsigned int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(long int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(long unsigned int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(long long unsigned int i) const
{
	stringstream s;
	s << *this << i;
	return s.str();
}

String String::operator+(float f) const
{
	stringstream s;
	//s.precision(writtenDigits(f));
	s << *this << f;
	return s.str();
}

String String::operator+(double d) const
{
	stringstream s;
	//s.precision(writtenDigits(d));
	s << *this << d;
	return s.str();
}

String String::operator+(long double ld) const
{
	stringstream s;
	//s.precision(writtenDigits(ld));
	s << *this << ld;
	return s.str();
}

String String::operator+(char c) const
{
	String tmp(*this);
	tmp.push_back(c);
	return tmp;
}

String String::operator+(const char* s) const
{
	String tmp(*this);
	tmp.append(s);
	return tmp;
}

String String::operator+(const String& s) const
{
	String tmp(*this);
	tmp.insert(tmp.end(), s.begin(), s.end());
	return tmp;
}

String String::operator+(const std::string& s) const
{
	String tmp(*this);
	tmp.insert(tmp.end(), s.begin(), s.end());
	return tmp;
}

String& String::operator+=(int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(unsigned int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(short int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(short unsigned int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(long int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(long unsigned int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(long long unsigned int i)
{
	this->append(String(i));
	return *this;
}

String& String::operator+=(float f)
{
	this->append(String(f));
	return *this;
}

String& String::operator+=(double d)
{
	this->append(String(d));
	return *this;
}

String& String::operator+=(long double d)
{
	this->append(String(d));
	return *this;
}

String& String::operator+=(char c)
{
	this->append(String(c));
	return *this;
}

String& String::operator+=(const char* s)
{
	this->append(s);
	return *this;
}

String& String::operator+=(const String& s)
{
	this->append(s);
	return *this;
}

String& String::operator+=(const std::string& s)
{
	this->append(s);
	return *this;
}

