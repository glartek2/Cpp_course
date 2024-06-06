#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <cctype>
#include <random>
#include <iterator>
#include <sstream>
#include <cstring>
#include <cassert>

class MyString {
public:
    // Constructors
    explicit MyString(const char *text = "");
    MyString(const MyString &text);

    MyString& operator=(const MyString &text);
    MyString& operator+=(char c);

    // Iterators
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::random_access_iterator_tag;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    // Capacity
    size_t capacity() const;
    size_t size() const;
    bool empty() const;

    // Element access
    char operator[](size_t i) const;
    char& operator[](size_t i);

    // Modifiers
    void push_back(char c);
    MyString& toLower();
    MyString& trim();
    MyString join(const std::vector<MyString> &texts) const;
    void clear();

    // Operations
    bool startsWith(const char *text) const;
    bool all_of(std::function<bool(char)> predicate) const;
    static MyString generateRandomWord(size_t length);
    std::set<MyString> getUniqueWords() const;
    std::map<MyString, size_t> countWordsUsageIgnoringCases() const;

    // Conversion operators
    explicit operator std::string() const;
    const char* asCharArray() const {
        return c_str();
    }

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);
    friend bool operator==(const MyString& lhs, const MyString& rhs);
    friend bool operator!=(const MyString& lhs, const MyString& rhs);

    // Other accessors
    const char* c_str() const;
    bool endsWith(const char* suffix) const;

    static size_t initialBufferSize_; // Member variable for initial buffer size

private:
    static constexpr size_t DEFAULT_INITIAL_BUFFER_SIZE = 20; // Default initial buffer size
    std::array<char, DEFAULT_INITIAL_BUFFER_SIZE> static_text;
    std::string dynamic_text;
    size_t text_length;

    void updateDynamicText();


    MyString(const char* text, size_t length) 
        : text_length(length) {
        // Copy the content of text into the internal buffer or dynamic text
        if (text_length <= initialBufferSize_) {
            std::copy(text, text + text_length, static_text.begin());
        } else {
            std::copy(text, text + initialBufferSize_, static_text.begin());
            dynamic_text = std::string(text + initialBufferSize_);
        }
    }

public:
    // Constructor for handling string literals
    template<size_t N>
    MyString(const char (&text)[N])
        : MyString(text, N - 1) {}

};

size_t MyString::initialBufferSize_ = MyString::DEFAULT_INITIAL_BUFFER_SIZE;

// Implementation

MyString::MyString(const char *text)
    : text_length(strlen(text)) {
    if (text_length <= initialBufferSize_) {
        std::copy(text, text + text_length, static_text.begin());
    } else {
        std::copy(text, text + initialBufferSize_, static_text.begin());
        dynamic_text = std::string(text + initialBufferSize_);
    }
}

MyString::MyString(const MyString &text)
    : static_text(text.static_text), dynamic_text(text.dynamic_text),
      text_length(text.text_length) {}


std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << static_cast<std::string>(str);
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    std::string temp;
    is >> temp;

    str = MyString(temp.c_str());

    return is;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    return (std::strcmp(lhs.c_str(), rhs.c_str()) == 0);
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
    return !(lhs == rhs);
}

MyString& MyString::operator+=(char c) {
    if (text_length < initialBufferSize_) {
        static_text[text_length] = c;
    } else {
        dynamic_text.push_back(c);
    }
    ++text_length;
    return *this;
}

bool MyString::endsWith(const char* suffix) const {
    size_t string_length = size();
    size_t suffix_length = strlen(suffix);
    
    if (string_length < suffix_length)
        return false;

    size_t static_end_index = std::min(string_length, initialBufferSize_);
    size_t dynamic_end_index = string_length - static_end_index;

    // Compare suffix with the end part of static_text and dynamic_text
    return std::strncmp(static_text.data() + static_end_index - suffix_length, suffix, suffix_length) == 0 ||
           (dynamic_end_index >= suffix_length &&
            std::strncmp(dynamic_text.c_str() + dynamic_end_index - suffix_length, suffix, suffix_length) == 0);
}



// Iterator classes
class MyString::iterator {
public:
    explicit iterator(MyString* myString, size_t position)
        : myString(myString), position(position) {}

    char& operator*() {
        return (*myString)[position];
    }

    iterator& operator++() {
        ++position;
        return *this;
    }

    bool operator!=(const iterator& other) const {
        return position != other.position;
    }

    iterator operator+(size_t pos) const {
        return iterator(myString, position + pos);
    }

    size_t operator-(const iterator& other) const {
        return position - other.position;
    }

    iterator& operator--() {
        --position;
        return *this;
    }

    bool operator==(const iterator& other) const {
        return position == other.position;
    }

    MyString* base() const {
        return myString;
    }

private:
    MyString* myString;
    size_t position;
};

class MyString::const_iterator {
public:
    explicit const_iterator(const MyString* myString, size_t position)
        : myString(myString), position(position) {}

    const char& operator*() const {
        return (*myString)[position];
    }

    const_iterator& operator++() {
        ++position;
        return *this;
    }

    bool operator!=(const const_iterator& other) const {
        return position != other.position;
    }

    const_iterator operator+(size_t pos) const {
        return const_iterator(myString, position + pos);
    }

    size_t operator-(const const_iterator& other) const {
        return position - other.position;
    }

    const_iterator& operator--() {
        --position;
        return *this;
    }

    bool operator==(const const_iterator& other) const {
        return position == other.position;
    }

    const MyString* base() const {
        return myString;
    }

private:
    const MyString* myString;
    size_t position;
};

class MyString::reverse_iterator {
public:
    explicit reverse_iterator(iterator it) : it(it) {}

    char& operator*() {
        iterator temp = it;
        return *--temp;
    }

    reverse_iterator& operator++() {
        --it;
        return *this;
    }

    reverse_iterator& operator--() {
        ++it;
        return *this;
    }

    bool operator!=(const reverse_iterator& other) const {
        return it != other.it;
    }

    iterator base() const {
        iterator temp = it;
        return ++temp;
    }

private:
    iterator it;
};

class MyString::const_reverse_iterator {
public:
    explicit const_reverse_iterator(const_iterator it) : it(it) {}

    const char& operator*() const {
        const_iterator temp = it;
        return *--temp;
    }

    const_reverse_iterator& operator++() {
        --it;
        return *this;
    }

    const_reverse_iterator& operator--() {
        ++it;
        return *this;
    }

    bool operator!=(const const_reverse_iterator& other) const {
        return it != other.it;
    }

    const_iterator base() const {
        const_iterator temp = it;
        return ++temp;
    }

private:
    const_iterator it;
};

inline MyString::iterator MyString::begin() {
    return iterator(this, 0);
}

inline MyString::const_iterator MyString::begin() const {
    return const_iterator(this, 0);
}

inline MyString::const_iterator MyString::cbegin() const {
    return const_iterator(this, 0);
}

inline MyString::iterator MyString::end() {
    return iterator(this, text_length);
}

inline MyString::const_iterator MyString::end() const {
    return const_iterator(this, text_length);
}

inline MyString::const_iterator MyString::cend() const {
    return const_iterator(this, text_length);
}

inline MyString::reverse_iterator MyString::rbegin() {
    return reverse_iterator(end());
}

inline MyString::const_reverse_iterator MyString::rbegin() const {
    return const_reverse_iterator(end());
}

inline MyString::const_reverse_iterator MyString::crbegin() const {
    return const_reverse_iterator(end());
}

inline MyString::reverse_iterator MyString::rend() {
    return reverse_iterator(begin());
}

inline MyString::const_reverse_iterator MyString::rend() const {
    return const_reverse_iterator(begin());
}

inline MyString::const_reverse_iterator MyString::crend() const {
    return const_reverse_iterator(begin());
}

inline size_t MyString::capacity() const {
    return 20 + dynamic_text.capacity();
}

inline size_t MyString::size() const {
    return text_length;
}

inline bool MyString::empty() const {
    return text_length == 0;
}

inline char MyString::operator[](size_t i) const {
    assert(i < text_length);
    if (i < 20) {
        return static_text[i];
    }
    return dynamic_text[i - 20];
}

inline char& MyString::operator[](size_t i) {
    assert(i < text_length);
    if (i < 20) {
        return static_text[i];
    }
    return dynamic_text[i - 20];
}

void MyString::push_back(char c) {
    if (text_length < initialBufferSize_) {
        static_text[text_length] = c;
    } else {
        if (text_length == initialBufferSize_) {
            updateDynamicText();
        }
        dynamic_text.push_back(c);
    }
    ++text_length; // Increment text_length after adding the character
}

inline MyString& MyString::toLower() {
    std::transform(begin(), end(), begin(), ::tolower);
    return *this;
}

inline MyString& MyString::trim() {
    auto is_not_space = [](char c) { return !std::isspace(static_cast<unsigned char>(c)); };
    auto start = std::find_if(begin(), end(), is_not_space);
    auto end_it = std::find_if(rbegin(), rend(), is_not_space).base();
    if (start != end_it) {
        std::string trimmed(start.base(), end_it.base());
        *this = MyString(trimmed.c_str());
    }
    return *this;
}

inline MyString MyString::join(const std::vector<MyString> &texts) const {
    std::string result = static_cast<std::string>(*this);
    for (const auto& text : texts) {
        result += " " + static_cast<std::string>(text);
    }
    return MyString(result.c_str());
}

inline bool MyString::startsWith(const char *text) const {
    size_t length = strlen(text);
    if (length > text_length) return false;
    return std::equal(text, text + length, static_text.begin());
}

inline bool MyString::all_of(std::function<bool(char)> predicate) const {
    return std::all_of(begin(), end(), predicate);
}

inline MyString MyString::generateRandomWord(size_t length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string result;
    result.reserve(length);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);
    std::generate_n(std::back_inserter(result), length, [&]() {
        return alphanum[dis(gen)];
    });
    return MyString(result.c_str());
}

inline std::set<MyString> MyString::getUniqueWords() const {
    std::set<MyString> unique_words;
    std::string str = static_cast<std::string>(*this);
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        unique_words.insert(MyString(word.c_str()));
    }
    return unique_words;
}

inline std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
    std::map<MyString, size_t> word_count;
    std::string str = static_cast<std::string>(*this);
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        MyString word_lower(word.c_str());
        word_lower.toLower();
        ++word_count[word_lower];
    }
    return word_count;
}

inline MyString::operator std::string() const {
    return std::string(static_text.begin(), static_text.begin() + std::min(text_length, static_text.size())) + dynamic_text;
}

inline void MyString::updateDynamicText() {
    dynamic_text = std::string(static_text.begin() + 20, static_text.begin() + text_length);
}

inline void MyString::clear() {
    static_text.fill('\0');
    dynamic_text.clear();
    text_length = 0;
}

inline const char* MyString::c_str() const {
    return static_cast<std::string>(*this).c_str();
}

#endif // MYSTRING_H
