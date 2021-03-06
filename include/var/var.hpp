#ifndef __CPP_VAR__
#define __CPP_VAR__

#include <string>
#include <map>
#include <vector>

class Var;
class Var
{
	public:
		enum Var_t
		{
			undefined,
			null,
			boolean,
			integer,
			real,
			symbol,
			string,
			map,
			map_iterator,
			vector,
			vector_iterator,
		};

		static int type(const Var& that);

	private:
		unsigned	internal_type;

		bool		internal_bool;
		long		internal_long;
		double		internal_double;
		std::string	internal_string;

		mutable std::string last_const_char_pointer;

		typedef std::map <std::string, Var*> internal_map_type;
		typedef std::vector <Var*> internal_vector_type;

		internal_map_type internal_map;
		internal_map_type::iterator internal_map_iterator;

		internal_vector_type internal_vector;
		internal_vector_type::iterator internal_vector_iterator;

		Var toNumber() const;
		std::string toString() const;

		static void decodeSub(const std::string& data, unsigned& i, Var& value);
		static void decodeNumber(const std::string& data, unsigned& i, double& value);
		static void decodeSymbol(const std::string& data, unsigned& i, std::string& value);
		static void decodeString(const std::string& data, unsigned& i, std::string& value);
		static void decodeVector(const std::string& data, unsigned& i, internal_vector_type& value);
		static void decodeMap(const std::string& data, unsigned& i, internal_map_type& value);

		static bool _sort(const Var*, const Var*);
		void _push(const Var&);
		template <typename... Args> void _push(const Var& c, Args... args) { this->_push(c); this->_push(args...); }
		Var _splice(const Var&, const Var&, const Var&);

	public:
		Var();
		Var(Var_t);
		Var(const Var&);

		Var(bool);
		Var(int);
		Var(unsigned int);
		Var(long);
		Var(unsigned long);
		Var(double);

		Var(const char*);
		Var(const std::string&);
		~Var();

		std::string encode(bool prettyPrint = false, int deep = 1) const;
		Var& decode(const Var&);

		Var& operator =(const Var&);

		Var operator +(const Var&) const;
		Var operator -(const Var&) const;
		Var operator *(const Var&) const;
		Var operator /(const Var&) const;

		Var& operator ++();
		Var& operator ++(int);
		Var& operator --(int);

		bool operator ==(const Var&) const;
		bool operator !=(const Var&) const;

		bool operator <(const Var&) const;
		bool operator >(const Var&) const;
		bool operator &&(const Var&) const;
		bool operator ||(const Var&) const;

		long operator &(const Var&);
		long operator |(const Var&);

		Var& operator [](const Var&);

		Var& operator <<(const Var&);

		Var concat(const Var&) const;
		template <typename... Args>
		Var concat(const Var& c, Args... args) const { return this->concat(c).concat(args...); }


		Var indexOf(const Var&, const Var& start = 0) const;
		Var lastIndexOf(const Var&) const;
		Var lastIndexOf(const Var&, const Var&) const;
		Var slice(const Var&) const;
		Var slice(const Var&, const Var&) const;

		Var charAt(const Var&) const;
		Var charCodeAt(const Var&) const;
		static Var fromCharCode(const Var&);
		Var localeCompare(const Var&) const;
		/* Var match(const Var&); */
		Var replace(const Var&, const Var&) const;
		/* Var search(const Var&); */
		Var split(const Var&) const;
		Var substr(const Var&) const;
		Var substr(const Var&, const Var&) const;
		Var substring(const Var&) const;
		Var substring(const Var&, const Var&) const;
		Var toLocaleLowerCase() const;
		Var toLocaleUpperCase() const;
		Var toLowerCase() const;
		Var toUpperCase() const;
		Var trim() const;

		Var join(const Var&);
		Var pop();

		template <typename... Args>
		Var push(Args... args) { this->_push(args...); return (long)this->size(); }
		Var reverse();
		Var shift();
		Var sort();
		template <typename... Args>
		Var splice(const Var& index, const Var& howmany, Args... args) { Var array; array.push(args...); return this->_splice(index, howmany, array); }

		bool compare(const Var& that) const;

		Var& operator *();
		Var begin();
		Var end();

		unsigned long size() const;
		void clear();

		operator bool() const;
		operator long() const;
		operator double() const;
		operator const char*() const;

		inline operator int()const {return (long)*this;}
		inline operator unsigned int()const {return (long)*this;}
		inline operator unsigned long()const {return (long)*this;}
		inline operator float()const {return (double)*this; }

		Var operator +(int) const;
		Var operator +(unsigned int) const;
		Var operator +(const char*) const;
		Var operator -(int) const;
		bool operator ==(bool) const;
		bool operator ==(int) const;
		bool operator ==(float) const;
		bool operator ==(double) const;
		bool operator ==(const char*) const;
		bool operator !=(int) const;
		bool operator !=(const char*) const;
		bool operator <(int) const;
		bool operator <(unsigned int) const;
		bool operator >(int) const;
		Var& operator [](int);
		Var& operator [](const char*);
		Var& operator <<(int);
};

inline Var operator+(char* a, const Var& b) {
	return Var((char*)a) + b;
}

inline Var operator+(const char* a, const Var& b) {
	return Var(a) + b;
}

inline Var operator*(const Var& a, float b) {
	return a * Var(b);
}

typedef Var var;
#define in :

#endif /* __CPP_VAR__ */
