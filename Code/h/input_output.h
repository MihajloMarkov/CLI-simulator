#ifndef _INPOTP__
#define _INPOTP__
#include <string>

using namespace std;

class InputStream {// Base input stream interface
public:
    virtual ~InputStream() = default;
    virtual string read() = 0;
    virtual string getType() const = 0;
};

class OutputStream {// Base output stream interface
public:
    virtual ~OutputStream() = default;
    virtual void write(const string& content) = 0;
    virtual string getContent() const { return ""; };
    virtual string getType() const = 0;
};

class StringInputStream : public InputStream {// String input stream - reads from string
public:
    StringInputStream(const string& data);
    string read();
    string getType() const override;
private:
    string data;
};

class ConsoleInputStream : public InputStream {// Console input stream - reads from console
public:
    string read();
    string getType() const override;
};

class FileInputStream : public InputStream {// File input stream - reads from file
public:
    FileInputStream(const string& filename);
    string read();
    string getType() const override;
private:
    string filename;
};

class StringOutputStream : public OutputStream {// String output stream - writes to string
public:
    void write(const string& content);
    string getContent() const override;
    string getType() const override;
private:
    string outString;
};

class ConsoleOutputStream : public OutputStream {// Console output stream - writes to console
public:
    void write(const string& content);
    string getType() const override;
};

class FileOutputStream : public OutputStream {// File output stream - writes to file
public:
    FileOutputStream(const string& filename, bool append = false);
    void write(const string& content);
    string getType() const override;
private:
    string filename;
    bool append;
};

#endif 