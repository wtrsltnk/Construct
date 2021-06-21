#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <glad/glad.h>

#include "../GL/Font.h"
#include "../GL/UserInput.h"
#include "../GL/keys.h"

#define MAX_ENRTY_TEXT 256

class Console
{
protected:
    static Console *pInstance;
    static UserInput *pUserInput;

public:
    static Console *Instance();
    static void UserInputKey(eKeys e, eKeyState state, UserInput *pUI);

private:
    class Entry
    {
    public:
        Entry() : cursor(0), iscommand(true), next(0) {}
        virtual ~Entry() {}

    public:
        char text[MAX_ENRTY_TEXT];
        int cursor;
        bool iscommand;
        Entry *next;
    };

protected:
    Console();

    Entry *pFirstEntry;
    Entry *pInputEntry;
    Font *pFont;
    bool focus;

    void SubmitInputEntry();
    void InputNumber(eKeys key);
    void InputLetter(eKeys key);
    void InputSpecialLetter(eKeys key);
    void InputKeyPad(eKeys key);
    void AddCharacter(char c);
    void RemoveCharacter();

public:
    virtual ~Console();

    void SetFont(Font *font) { this->pFont = font; }

    void Render(int width, int height);

    void AddEntry(const char *entry);
    void OnUserInput(eKeys key, eKeyState state);
};

#endif /*CONSOLE_H_*/
