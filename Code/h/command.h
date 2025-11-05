#ifndef _KOMANDA__
#define _KOMANDA__
#include <string>
#include <vector>
#include "input_output.h" 

using namespace std;

// Base command class
class Command {
public:
    Command();
    virtual ~Command();

    virtual void execute() = 0;  // Execute command
    virtual string getName() const = 0;  // Get command name

    virtual void setInputStream(InputStream* in);  // Set input stream
    virtual void setOutputStream(OutputStream* out);  // Set output stream
    InputStream* getInputStream() const;  // Get input stream
    OutputStream* getOutputStream() const;  // Get output stream

protected:
    InputStream* m_input = nullptr;  // Input stream
    OutputStream* m_output = nullptr;  // Output stream
};

class EchoCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class TimeCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class DateCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class TouchCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class WCCommand : public Command {
public:
    explicit WCCommand(const string& option);
    void setOption(const string& option);
    void execute() override;
    string getName() const override;

private:
    void executew(const string& data);  // Execute word count
    void executec(const string& data);  // Execute character count

    string option;
};

class ExitCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class PromptCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class TruncateCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class RmCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class TrCommand : public Command {
public:
    TrCommand(const string& what, const string& with);
    void execute() override;
    string getName() const override;
private:
    string m_what;  // Text to replace
    string m_with;  // Replacement text
};

class HeadCommand : public Command {
public:
    HeadCommand(int count);
    void execute() override;
    string getName() const override;
private:
    int m_count;  // Number of lines to display
};

class BatchCommand : public Command {
public:
    void execute() override;
    string getName() const override;
};

class Pipe : public Command {
public:
    ~Pipe();
    void addCommand(Command* cmd);// Add command to pipe
    void execute() override;
    string getName() const override;
    void setInputStream(InputStream* in) override; // Set input for first command
    void setOutputStream(OutputStream* out) override;// Set output for last command
    
private:
    vector<Command*> m_commands;// Commands in pipe
};
#endif