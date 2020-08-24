#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
#include "Piece.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <array>
#include <thread>
#include <chrono>

#define NAMEBOX1LEFT 0.05
#define NAMEBOX1TOP 0.8
#define NAMEBOX1WIDTH 0.2
#define NAMEBOX1HEIGHT 0.1
#define NAMEBOX2LEFT 0.75
#define NAMEBOX2TOP 0.1
#define NAMEBOX2WIDTH 0.2
#define NAMEBOX2HEIGHT 0.1
#define GAMEEXITBUTTONLEFT 0.01
#define GAMEEXITBUTTONTOP 0.01
#define GAMEEXITBUTTONWIDTH 0.1
#define GAMEEXITBUTTONHEIGHT 0.05
#define BOARDLEFT 0.3
#define BOARDRIGHT 0.75
#define BOARDTOP 0.1
#define BOARDBOTTOM 0.9
#define DESCRIPTIONBOXLEFT 0.4
#define DESCRIPTIONBOXTOP 0.25
#define DESCRIPTIONBOXWIDTH 0.2
#define DESCRIPTIONBOXHEIGHT 0.1

#define SQUARECODE 256

#define selectedPiece board.getPiece(currentState.selectedRow, currentState.selectedCol)

#define attackerRow selectedRow
#define attackerCol selectedCol

#define attacker board.getPiece(currentState.selectedRow, currentState.selectedCol)
#define defender board.getPiece(currentState.defenderRow, currentState.defenderCol)



enum class WindowCode
{
    singlePlayer,
    twoPlayers,
    createLoadouts,
    about, 
    startGame,
    nameTextbox1,
    nameTextbox2,
    exit,
    loadoutDropdown1,
    loadoutDropdown2,
    pieceDropdown,
    moveDropdown1,
    moveDropdown2,
    moveDropdown3,
    moveDropdown4,
    saveLoadout,
    promoteRook,
    promoteKnight,
    promoteBishop,
    promoteQueen,
    useSpecial,
    move,
    unfortify,
    move1,
    move2,
    move3,
    move4,
    flee,
    usingMove,
    finishingBattle,
    MAX_BUTTONS
};

enum class CurrentActivity
{
    mainMenu,
    board,
    battle,
    createLoadout,
    about, 
    selectLoadout,
    victoryScreen,
    MAX_ACTIVITIES,
};

enum class Winner
{
    player1,
    player2,
    draw,
    MAX_OUTCOMES
};

struct WindowState
{
   Grid board{};
   CurrentActivity currentActivity{ CurrentActivity::mainMenu };
   LONG leftEdge{};
   LONG rightEdge{};
   LONG topEdge{};
   LONG bottomEdge{};
   HWND mainWindow;
   HWND windows[20];
   HWND squares[8][8];
   bool blueSquares[8][8];
   std::string loadoutNames[11];
   std::wstring player1name{};
   std::wstring player2name{};
   Loadout loadouts[11];
   bool completedLoadouts[11];
   bool singlePlayer{ false };
   bool player1IsWhite{ false };
   bool loadoutChanged{ false };
   int player1Loadout{};
   int player2Loadout{};
   int selectedRow{-1};
   int selectedCol{-1};
   int defenderRow{ -1 };
   int defenderCol{ -1 };
   bool isWhiteTurn{ true };
   bool waitingForInput{ false };
   bool waiting{ false };
   bool attackerTurn{ true };
   bool handledStatus{ false };

   HBITMAP whitePawnWhiteBackground{};
   HBITMAP whitePawnBlackBackground{};
   HBITMAP whitePawnBlueBackground{};
   HBITMAP blackPawnWhiteBackground{};
   HBITMAP blackPawnBlackBackground{};
   HBITMAP blackPawnBlueBackground{};

   HBITMAP whiteRookWhiteBackground{};
   HBITMAP whiteRookBlackBackground{};
   HBITMAP whiteRookBlueBackground{};
   HBITMAP blackRookWhiteBackground{};
   HBITMAP blackRookBlackBackground{};
   HBITMAP blackRookBlueBackground{};

   HBITMAP whiteKnightWhiteBackground{};
   HBITMAP whiteKnightBlackBackground{};
   HBITMAP whiteKnightBlueBackground{};
   HBITMAP blackKnightWhiteBackground{};
   HBITMAP blackKnightBlackBackground{};
   HBITMAP blackKnightBlueBackground{};

   HBITMAP whiteBishopWhiteBackground{};
   HBITMAP whiteBishopBlackBackground{};
   HBITMAP whiteBishopBlueBackground{};
   HBITMAP blackBishopWhiteBackground{};
   HBITMAP blackBishopBlackBackground{};
   HBITMAP blackBishopBlueBackground{};

   HBITMAP whiteQueenWhiteBackground{};
   HBITMAP whiteQueenBlackBackground{};
   HBITMAP whiteQueenBlueBackground{};
   HBITMAP blackQueenWhiteBackground{};
   HBITMAP blackQueenBlackBackground{};
   HBITMAP blackQueenBlueBackground{};

   HBITMAP whiteKingWhiteBackground{};
   HBITMAP whiteKingBlackBackground{};
   HBITMAP whiteKingBlueBackground{};
   HBITMAP blackKingWhiteBackground{};
   HBITMAP blackKingBlackBackground{};
   HBITMAP blackKingBlueBackground{};

   HBITMAP whiteBackground{};
   HBITMAP blackBackground{};
   HBITMAP blueBackground{};

};

static WindowState currentState{};
static WNDCLASS wc = { };

void useMove(int move);
void destroyGameBoard();
void createBattle();
void useTurn();
void computerBattle();
void updateBoard(int row, int col);
void promotePawn(int row, int col);
void useSpecial(int row, int col);
void takeComputerTurn();
std::array<std::array<bool, 8>, 8> specialSquares();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();
    const wchar_t CLASS_NAME[] = L"ChessRPG";
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(50, 50, 50));
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(0,CLASS_NAME,L"ChessRPG",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL, NULL,hInstance, NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    currentState.mainWindow = hwnd;

    ShowWindow(hwnd, nCmdShow);
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

HWND createButton(HWND hwnd, const wchar_t* text, int code, double leftAsPercentOfScreen, double topAsPercentOfScreen, double widthAsPercentOfScreen, double heightAsPercentOfScreen)
{
    return CreateWindow(L"button", text, WS_VISIBLE | WS_CHILD | WS_BORDER,
        static_cast<int>((currentState.rightEdge - currentState.leftEdge) * leftAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * topAsPercentOfScreen)
        , static_cast<int>((currentState.rightEdge - currentState.leftEdge) * widthAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * heightAsPercentOfScreen)
        , hwnd, reinterpret_cast<HMENU>(code), NULL, NULL);
}

HWND createIcon(HWND hwnd, double leftAsPercentOfScreen, double topAsPercentOfScreen, double widthAsPercentOfScreen, double heightAsPercentOfScreen)
{
    return CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | SS_BITMAP,
        static_cast<int>((currentState.rightEdge - currentState.leftEdge) * leftAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * topAsPercentOfScreen)
        , static_cast<int>((currentState.rightEdge - currentState.leftEdge) * widthAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * heightAsPercentOfScreen)
        , hwnd, NULL, NULL, NULL);
}

void fillIcon(HWND hwnd, Piece& piece, int size)
{
    switch (piece.getType())
    {
    case Piece::Type::Pawn :
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whitepawnblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackpawnwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    case Piece::Type::Knight:
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whiteknightblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackknightwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    case Piece::Type::Bishop:
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whitebishopblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackbishopwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    case Piece::Type::Rook:
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whiterookblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackrookwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    case Piece::Type::Queen:
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whitequeenblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackqueenwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    case Piece::Type::King:
    {
        if (piece.isWhite())
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\whitekingblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        else
        {
            HBITMAP image{ (HBITMAP)LoadImage(NULL, L"Images\\blackkingwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE) };
            SendMessage(hwnd, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
        }
        break;
    }
    }
}

HWND createSquare(HWND hwnd,int code, int left, int top, int width, int height)
{
    return CreateWindow(L"button", L"", WS_VISIBLE | WS_CHILD | BS_BITMAP,left, top, width, height, hwnd, reinterpret_cast<HMENU>(code), NULL, NULL);
}

HWND createTextBox(HWND hwnd, const wchar_t* text, int code, double leftAsPercentOfScreen, double topAsPercentOfScreen, double widthAsPercentOfScreen, double heightAsPercentOfScreen)
{
    return CreateWindow(L"edit", text, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
        static_cast<int>((currentState.rightEdge - currentState.leftEdge) * leftAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * topAsPercentOfScreen)
        , static_cast<int>((currentState.rightEdge - currentState.leftEdge) * widthAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * heightAsPercentOfScreen)
        , hwnd, reinterpret_cast<HMENU>(code), NULL, NULL);
}

HWND createLabel(HWND hwnd, const wchar_t* text, double leftAsPercentOfScreen, double topAsPercentOfScreen, double widthAsPercentOfScreen, double heightAsPercentOfScreen)
{
    return CreateWindow(L"static", text, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
        static_cast<int>((currentState.rightEdge - currentState.leftEdge) * leftAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * topAsPercentOfScreen)
        , static_cast<int>((currentState.rightEdge - currentState.leftEdge) * widthAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * heightAsPercentOfScreen)
        , hwnd, NULL, NULL, NULL);
}

HWND createDropdown(HWND hwnd, int code, double leftAsPercentOfScreen, double topAsPercentOfScreen, double widthAsPercentOfScreen, double heightAsPercentOfScreen)
{
    return CreateWindow(L"Combobox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL,
        static_cast<int>((currentState.rightEdge - currentState.leftEdge) * leftAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * topAsPercentOfScreen)
        , static_cast<int>((currentState.rightEdge - currentState.leftEdge) * widthAsPercentOfScreen)
        , static_cast<int>((currentState.bottomEdge - currentState.topEdge) * heightAsPercentOfScreen)
        , hwnd, reinterpret_cast<HMENU>(code), NULL, NULL);
}

std::wstring StringToWString(const std::string& s)
{
    return std::wstring(s.begin(), s.end());
}

void waitBattle(int millis)
{
    SetTimer(currentState.mainWindow, static_cast<int>(WindowCode::usingMove), millis, (TIMERPROC)NULL);
    currentState.waiting = true;
}

void waitDone(int millis)
{
    SetTimer(currentState.mainWindow, static_cast<int>(WindowCode::finishingBattle), millis, (TIMERPROC)NULL);
    currentState.waiting = true;
}

void fillLoadoutDropdown(HWND hwnd)
{
    for (int i{ 0 }; i < 11; ++i)
    {
        SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)StringToWString(currentState.loadoutNames[i]).c_str());
    }
    SendMessage(hwnd, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

void fillChangeLoadoutDropdown(HWND hwnd)
{
    for (int i{ 1 }; i < 11; ++i)
    {
        SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)StringToWString(currentState.loadoutNames[i]).c_str());
    }
    SendMessage(hwnd, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

void fillPieceDropdown(HWND hwnd)
{
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM) L"Pawn");
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM) L"Rook");
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Knight");
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Bishop");
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Queen");
    SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"King");
    SendMessage(hwnd, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

int pieceShift(Piece::Type type)
{
    switch (type)
    {
    case Piece::Type::Pawn:
        return 0;
    case Piece::Type::Rook:
        return static_cast<int>(Piece::Move::PAWN_END) + 1;
    case Piece::Type::Knight:
        return static_cast<int>(Piece::Move::ROOK_END) + 1;
    case Piece::Type::Bishop:
        return static_cast<int>(Piece::Move::KNIGHT_END) + 1;
    case Piece::Type::Queen:
        return static_cast<int>(Piece::Move::BISHOP_END) + 1;
    case Piece::Type::King:
        return static_cast<int>(Piece::Move::QUEEN_END) + 1;
    }

    return 0;
}

void fillMoveDropdown(HWND hwnd, Piece::Type type)
{
    int start{};
    int end{};
    switch (type)
    {
    case Piece::Type::Pawn :
    {
        start = 0;
        end = static_cast<int>(Piece::Move::PAWN_END);
        break;
    }
    case Piece::Type::Rook:
    {
        start = static_cast<int>(Piece::Move::PAWN_END) + 1;
        end = static_cast<int>(Piece::Move::ROOK_END);
        break;
    }
    case Piece::Type::Knight:
    {
        start = static_cast<int>(Piece::Move::ROOK_END) + 1;
        end = static_cast<int>(Piece::Move::KNIGHT_END);
        break;
    }
    case Piece::Type::Bishop:
    {
        start = static_cast<int>(Piece::Move::KNIGHT_END) + 1;
        end = static_cast<int>(Piece::Move::BISHOP_END);
        break;
    }
    case Piece::Type::Queen:
    {
        start = static_cast<int>(Piece::Move::BISHOP_END) + 1;
        end = static_cast<int>(Piece::Move::QUEEN_END);
        break;
    }
    case Piece::Type::King:
    {
        start = static_cast<int>(Piece::Move::QUEEN_END) + 1;
        end = static_cast<int>(Piece::Move::KING_END);
        break;
    }
    }

    for (int i{ start }; i < end; ++i)
    {
        SendMessage(hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM) StringToWString(printMove(static_cast<Piece::Move>(i))).c_str());
    }
}

void changeMoveDropdown(HWND hwnd, Piece::Move move, Piece::Type type)
{
    SendMessage(hwnd, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
    fillMoveDropdown(hwnd, type);
    if (move != Piece::Move::MAX_MOVES)
    {
        int shift = pieceShift(type);
        SendMessage(hwnd, (UINT)CB_SETCURSEL, (WPARAM)(static_cast<int>(move) - shift), (LPARAM)0);
    }
    else
    {
        SendMessage(hwnd, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
    }
}

void loadImages(int size)
{
    currentState.whitePawnWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitepawnwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whitePawnBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitepawnblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whitePawnBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitepawnbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackPawnWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackpawnwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackPawnBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackpawnblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackPawnBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackpawnbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteRookWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiterookwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteRookBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiterookblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteRookBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiterookbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackRookWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackrookwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackRookBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackrookblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackRookBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackrookbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteKnightWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiteknightwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteKnightBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiteknightblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteKnightBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whiteknightbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKnightWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackknightwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKnightBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackknightblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKnightBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackknightbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteBishopWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitebishopwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteBishopBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitebishopblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteBishopBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitebishopbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackBishopWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackbishopwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackBishopBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackbishopblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackBishopBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackbishopbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteQueenWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitequeenwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteQueenBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitequeenblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteQueenBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitequeenbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackQueenWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackqueenwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackQueenBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackqueenblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackQueenBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackqueenbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteKingWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitekingwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteKingBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitekingblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.whiteKingBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitekingbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKingWhiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackkingwhitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKingBlackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackkingblackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackKingBlueBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackkingbluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);

    currentState.whiteBackground = (HBITMAP)LoadImage(NULL, L"Images\\whitebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blackBackground = (HBITMAP)LoadImage(NULL, L"Images\\blackbackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
    currentState.blueBackground = (HBITMAP)LoadImage(NULL, L"Images\\bluebackground.bmp", IMAGE_BITMAP, size, size, LR_LOADFROMFILE);
}

void selectSquare(int row, int col)
{
    Piece p{ currentState.board.getPiece(row, col) };
    if (p == Grid::noPiece)
    {
        SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blueBackground);
    }
    else
    {
        switch (p.getType())
        {
        case Piece::Type::Pawn :
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whitePawnBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackPawnBlueBackground);
            }
            break;
        case Piece::Type::Rook:
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteRookBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackRookBlueBackground);
            }
            break;
        case Piece::Type::Knight:
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKnightBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKnightBlueBackground);
            }
            break;
        case Piece::Type::Bishop:
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteBishopBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackBishopBlueBackground);
            }
            break;
        case Piece::Type::Queen:
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteQueenBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackQueenBlueBackground);
            }
            break;
        case Piece::Type::King:
            if (p.isWhite())
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKingBlueBackground);
            }
            else
            {
                SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKingBlueBackground);
            }
            break;
        }
    }
}

void deselectSquare(int row, int col)
{
    Piece p{ currentState.board.getPiece(row, col) };
    if (p == Grid::noPiece)
    {
        if (row % 2 != col % 2)
        {
            SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackBackground);
        }
        else
        {
            SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteBackground);
        }
    }
    else
    {
        switch (p.getType())
        {
        case Piece::Type::Pawn:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whitePawnBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whitePawnWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackPawnBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackPawnWhiteBackground);
                }
            }
            break;
        case Piece::Type::Rook:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteRookBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteRookWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackRookBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackRookWhiteBackground);
                }
            }
            break;
        case Piece::Type::Knight:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKnightBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKnightWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKnightBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKnightWhiteBackground);
                }
            }
            break;
        case Piece::Type::Bishop:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteBishopBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteBishopWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackBishopBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackBishopWhiteBackground);
                }
            }
            break;
        case Piece::Type::Queen:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteQueenBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteQueenWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackQueenBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackQueenWhiteBackground);
                }
            }
            break;
        case Piece::Type::King:
            if (p.isWhite())
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKingBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.whiteKingWhiteBackground);
                }
            }
            else
            {
                if (row % 2 != col % 2)
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKingBlackBackground);
                }
                else
                {
                    SendMessage(currentState.squares[row][col], (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)currentState.blackKingWhiteBackground);
                }
            }
            break;
        }
    }
}

void createMainMenu(HWND hwnd)
{
    currentState.windows[0] = createButton(hwnd, L"Single Player", static_cast<int>(WindowCode::singlePlayer), 0.4, 0.2, 0.2, 0.1);
    currentState.windows[1] = createButton(hwnd, L"Two Players", static_cast<int>(WindowCode::twoPlayers), 0.4, 0.31, 0.2, 0.1);
    currentState.windows[2] = createButton(hwnd, L"Create Loadouts", static_cast<int>(WindowCode::createLoadouts), 0.4, 0.42, 0.2, 0.1);
    currentState.windows[3] = createButton(hwnd, L"About", static_cast<int>(WindowCode::about), 0.4, 0.53, 0.2, 0.1);
    currentState.windows[4] = createButton(hwnd, L"Quit", static_cast<int>(WindowCode::exit), 0.4, 0.64, 0.2, 0.1);
}

void destroyMainMenu()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
    DestroyWindow(currentState.windows[2]);
    DestroyWindow(currentState.windows[3]);
    DestroyWindow(currentState.windows[4]);
}

void createVictoryScreen(Winner winner)
{
    std::wstring message{};
    switch (winner)
    {
    case Winner::player1 :
    {
        message = currentState.player1name + L" wins!";
        break;
    }
    case Winner::player2 :
    {
        message = currentState.player2name + L" wins!";
        break;
    }
    case Winner::draw :
    {
        message = L"Draw";
        break;
    }
    }

    currentState.windows[0] = createLabel(currentState.mainWindow, message.c_str(), 0.2, 0.3, 0.6, 0.2);
    currentState.windows[1] = createButton(currentState.mainWindow, L"OK", static_cast<int>(WindowCode::exit),
        0.4, 0.6, 0.2, 0.1);
}

void destroyVictoryScreen()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
}

void createSelectScreen(HWND hwnd)
{
    if (currentState.singlePlayer)
    {
        currentState.windows[0] = createButton(hwnd, L"Start Game", static_cast<int>(WindowCode::startGame), 0.4, 0.8, 0.2, 0.1);
        currentState.windows[1] = createTextBox(hwnd, L"Enter name here", static_cast<int>(WindowCode::nameTextbox1), 0.4, 0.4, 0.2, 0.1);
        currentState.windows[3] = createDropdown(hwnd, static_cast<int>(WindowCode::loadoutDropdown1), 0.4, 0.6, 0.2, 0.1);
        fillLoadoutDropdown(currentState.windows[3]);
    }
    else
    {
        currentState.windows[0] = createButton(hwnd, L"Start Game", static_cast<int>(WindowCode::startGame), 0.4, 0.8, 0.2, 0.1);
        currentState.windows[1] = createTextBox(hwnd, L"Enter name here", static_cast<int>(WindowCode::nameTextbox1), 0.2, 0.4, 0.2, 0.1);
        currentState.windows[2] = createTextBox(hwnd, L"Enter name here", static_cast<int>(WindowCode::nameTextbox2), 0.6, 0.4, 0.2, 0.1);
        currentState.windows[3] = createDropdown(hwnd, static_cast<int>(WindowCode::loadoutDropdown1), 0.2, 0.6, 0.2, 0.1);
        currentState.windows[4] = createDropdown(hwnd, static_cast<int>(WindowCode::loadoutDropdown2), 0.6, 0.6, 0.2, 0.1);
        fillLoadoutDropdown(currentState.windows[3]);
        fillLoadoutDropdown(currentState.windows[4]);
    }
    currentState.windows[19] = createButton(currentState.mainWindow, L"Back", static_cast<int>(WindowCode::exit), 0.01, 0.01, 0.1, 0.05);
}

void destroySelectScreen()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
    DestroyWindow(currentState.windows[2]);
    DestroyWindow(currentState.windows[3]);
    DestroyWindow(currentState.windows[4]);
    DestroyWindow(currentState.windows[10]);
    DestroyWindow(currentState.windows[19]);
}

void createLoadoutScreen(HWND hwnd)
{
    currentState.windows[0] = createButton(hwnd, L"Back", static_cast<int>(WindowCode::exit), 0.01, 0.01, 0.1, 0.05);
    currentState.windows[1] = createButton(hwnd, L"Save Moves (Must be done for each piece)", static_cast<int>(WindowCode::saveLoadout), 0.4, 0.8, 0.2, 0.1);
    currentState.windows[2] = createDropdown(hwnd, static_cast<int>(WindowCode::loadoutDropdown1), 0.4, 0.1, 0.2, 0.1);
    currentState.windows[3] = createDropdown(hwnd, static_cast<int>(WindowCode::pieceDropdown), 0.45, 0.25, 0.1, 0.1);
    currentState.windows[4] = createDropdown(hwnd, static_cast<int>(WindowCode::moveDropdown1), 0.25, 0.35, 0.1, 0.2);
    currentState.windows[5] = createDropdown(hwnd, static_cast<int>(WindowCode::moveDropdown2), 0.65, 0.35, 0.1, 0.2);
    currentState.windows[6] = createDropdown(hwnd, static_cast<int>(WindowCode::moveDropdown3), 0.25, 0.65, 0.1, 0.2);
    currentState.windows[7] = createDropdown(hwnd, static_cast<int>(WindowCode::moveDropdown4), 0.65, 0.65, 0.1, 0.2);

    currentState.windows[8] = createLabel(hwnd, L"Choose a loadout to edit", 0.4, 0.01, 0.2, 0.03);
    currentState.windows[10] = createLabel(hwnd, L"Move1", 0.25, 0.3, 0.1, 0.03);
    currentState.windows[11] = createLabel(hwnd, L"Move2", 0.65, 0.3, 0.1, 0.03);
    currentState.windows[12] = createLabel(hwnd, L"Move3", 0.25, 0.6, 0.1, 0.03);
    currentState.windows[13] = createLabel(hwnd, L"Move4", 0.65, 0.6, 0.1, 0.03);
    currentState.windows[14] = createTextBox(hwnd, L"Change loadout name here (No spaces)", static_cast<int>(WindowCode::nameTextbox1), 0.4, 0.15, 0.2, 0.05);

    
    fillChangeLoadoutDropdown(currentState.windows[2]);
    fillPieceDropdown(currentState.windows[3]);
    changeMoveDropdown(currentState.windows[4], static_cast<Piece::Move>(currentState.loadouts[1].moves[0]), Piece::Type::Pawn);
    changeMoveDropdown(currentState.windows[5], static_cast<Piece::Move>(currentState.loadouts[1].moves[1]), Piece::Type::Pawn);
    changeMoveDropdown(currentState.windows[6], static_cast<Piece::Move>(currentState.loadouts[1].moves[2]), Piece::Type::Pawn);
    changeMoveDropdown(currentState.windows[7], static_cast<Piece::Move>(currentState.loadouts[1].moves[3]), Piece::Type::Pawn);

    currentState.windows[16] = createLabel(hwnd, StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str(),
        0.2, 0.4, 0.2, 0.08);
    currentState.windows[17] = createLabel(hwnd, StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[5], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str(),
        0.6, 0.4, 0.2, 0.08);
    currentState.windows[18] = createLabel(hwnd, StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[6], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str(),
        0.2, 0.7, 0.2, 0.08);
    currentState.windows[19] = createLabel(hwnd, StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[7], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str(),
        0.6, 0.7, 0.2, 0.08);
}

void destroyLoadoutScreen()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
    DestroyWindow(currentState.windows[2]);
    DestroyWindow(currentState.windows[3]);
    DestroyWindow(currentState.windows[4]);
    DestroyWindow(currentState.windows[5]);
    DestroyWindow(currentState.windows[6]);
    DestroyWindow(currentState.windows[7]);
    DestroyWindow(currentState.windows[8]);
    
    DestroyWindow(currentState.windows[10]);
    DestroyWindow(currentState.windows[11]);
    DestroyWindow(currentState.windows[12]);
    DestroyWindow(currentState.windows[13]);
    DestroyWindow(currentState.windows[14]);
    DestroyWindow(currentState.windows[15]);
    DestroyWindow(currentState.windows[16]);
    DestroyWindow(currentState.windows[17]);
    DestroyWindow(currentState.windows[18]);
    DestroyWindow(currentState.windows[19]);
}

void retrieveNewLoadoutSelection()
{
    DestroyWindow(currentState.windows[15]);
    int piece{ static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
    int shift{ pieceShift(static_cast<Piece::Type>(piece)) };

    int move1{ static_cast<int>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) + shift};
    int move2{ static_cast<int>(SendMessage(currentState.windows[5], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) + shift };
    int move3{ static_cast<int>(SendMessage(currentState.windows[6], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) + shift };
    int move4{ static_cast<int>(SendMessage(currentState.windows[7], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) + shift };

    if (move1 == move2 || move1 == move3 || move1 == move4 || move2 == move3 || move2 == move4 || move3 == move4)
    {
        currentState.windows[15] = createLabel(currentState.mainWindow, L"Please choose 4 different moves", 0.4, 0.55, 0.2, 0.05);
        return;
    }

    DestroyWindow(currentState.windows[15]);
    

    int loadout = static_cast<int>(SendMessage(currentState.windows[2], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) + 1;

    currentState.loadouts[loadout].moves[piece * 4] = static_cast<Piece::Move>(move1);
    currentState.loadouts[loadout].moves[piece * 4 + 1] = static_cast<Piece::Move>(move2);
    currentState.loadouts[loadout].moves[piece * 4 + 2] = static_cast<Piece::Move>(move3);
    currentState.loadouts[loadout].moves[piece * 4 + 3] = static_cast<Piece::Move>(move4);

    char name[50];
    GetWindowTextA(currentState.windows[14], name, 50);


    std::string str{ name };
    if (str.find(' ') != -1)
    {
        currentState.windows[15] = createLabel(currentState.mainWindow, L"Invalid name, no spaces allowed", 0.4, 0.7, 0.2, 0.05);
        return;
    }

    currentState.loadoutNames[loadout] = name;

    currentState.completedLoadouts[loadout] = true;
    for (int i{ 0 }; i < 24; ++i)
    {
        if (currentState.loadouts[loadout].moves[i] == Piece::Move::MAX_MOVES)
        {
            currentState.completedLoadouts[loadout] = false;
        }
    }

    DestroyWindow(currentState.windows[15]);
    currentState.loadoutChanged = true;
    currentState.windows[15] = createLabel(currentState.mainWindow, L"Saved!", 0.4, 0.7, 0.2, 0.05);
}

void readSavedLoadouts()
{
    std::ifstream loadoutFile{ "Loadout.dat" };

    for (int i{ 0 }; i < 4; ++i)
    {
        currentState.loadouts[0].moves[i] = static_cast<Piece::Move>(i);
        currentState.loadouts[0].moves[i + 4] = static_cast<Piece::Move>(i + static_cast<int>(Piece::Move::PAWN_END) + 1);
        currentState.loadouts[0].moves[i + 8] = static_cast<Piece::Move>(i + static_cast<int>(Piece::Move::ROOK_END) + 1);
        currentState.loadouts[0].moves[i + 12] = static_cast<Piece::Move>(i + static_cast<int>(Piece::Move::KNIGHT_END) + 1);
        currentState.loadouts[0].moves[i + 16] = static_cast<Piece::Move>(i + static_cast<int>(Piece::Move::BISHOP_END) + 1);
        currentState.loadouts[0].moves[i + 20] = static_cast<Piece::Move>(i + static_cast<int>(Piece::Move::QUEEN_END) + 1);
    }

    for (int i{ 0 }; i < 11; ++i)
    {
        currentState.completedLoadouts[i] = true;
    }

    for (int i{ 0 }; i < 10; ++i)
    {
        Loadout newLoadout{};
        for (int j{ 0 }; j < 24; ++j)
        {
            int data;
            loadoutFile >> data;
            newLoadout.moves[j] = static_cast<Piece::Move>(data);
            if (static_cast<Piece::Move>(data) == Piece::Move::MAX_MOVES)
            {
                currentState.completedLoadouts[i + 1] = false;
            }
        }
        currentState.loadouts[i + 1] = newLoadout;
    }

    
     currentState.loadoutNames[0] = "Default";
     int i{ 1 };
     while (loadoutFile && i < 11)
     {
         std::string input;
         loadoutFile >> input;
         currentState.loadoutNames[i] = input;
         ++i;
     }
}

void saveLoadoutChanges()
{
    std::ofstream outf{ "Loadout.dat" };

    std::remove("Loadout.dat");

    for (int i{ 1 }; i < 11; ++i)
    {
        for (int j{ 0 }; j < 23; ++j)
        {
            outf << static_cast<int>(currentState.loadouts[i].moves[j]) << ' ';
        }
        outf << static_cast<int>(currentState.loadouts[i].moves[23]) << '\n';
    }
    for (int i{ 1 }; i < 10; ++i)
    {
        outf << currentState.loadoutNames[i] << ' ';
    }
    outf << currentState.loadoutNames[10];
}

void createLoadoutFile()
{
    std::ofstream outf{ "Loadout.dat" };

    std::remove("Loadout.dat");

    for (int i{ 0 }; i < 10; ++i)
    {
        for (int j{ 0 }; j < 23; ++j)
        {
            outf << static_cast<int>(Piece::Move::MAX_MOVES) << ' ';
        }
        outf << static_cast<int>(Piece::Move::MAX_MOVES) << '\n';
    }
    for (int i{ 0 }; i < 9; ++i)
    {
        outf << "Loadout" << (i + 1) << ' ';
    }
    outf << "Loadout10";

}

void createGameBoard(HWND hwnd)
{
    if (currentState.player1IsWhite)
    {
        currentState.windows[5] = createLabel(hwnd, currentState.player1name.c_str(), NAMEBOX1LEFT, NAMEBOX1TOP, NAMEBOX1WIDTH, NAMEBOX1HEIGHT);
        currentState.windows[6] = createLabel(hwnd, currentState.player2name.c_str(), NAMEBOX2LEFT, NAMEBOX2TOP, NAMEBOX2WIDTH, NAMEBOX2HEIGHT);
    }
    else
    {
        currentState.windows[5] = createLabel(hwnd, currentState.player1name.c_str(), NAMEBOX2LEFT, NAMEBOX2TOP, NAMEBOX2WIDTH, NAMEBOX2HEIGHT);
        currentState.windows[6] = createLabel(hwnd, currentState.player2name.c_str(), NAMEBOX1LEFT, NAMEBOX1TOP, NAMEBOX1WIDTH, NAMEBOX1HEIGHT);
    }
    currentState.windows[7] = createButton(hwnd, L"Exit", static_cast<int>(WindowCode::exit), GAMEEXITBUTTONLEFT, GAMEEXITBUTTONTOP, GAMEEXITBUTTONWIDTH, GAMEEXITBUTTONHEIGHT);

    int size{ static_cast<int>((currentState.bottomEdge - currentState.topEdge) * (BOARDBOTTOM - BOARDTOP)) / 8 };
    loadImages(size);
    for (int row{ 0 }; row < 8; ++row)
    {
        for (int col{ 0 }; col < 8; ++col)
        {
            currentState.blueSquares[row][col] = false;
            currentState.squares[row][col] = createSquare(hwnd, SQUARECODE + row * 8 + col, static_cast<int>(static_cast<int>((currentState.rightEdge - currentState.leftEdge) * BOARDLEFT)) + col * size, static_cast<int>((currentState.bottomEdge - currentState.topEdge) * BOARDTOP) + row * size, size, size);
        }
    }

    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            deselectSquare(i, j);
        }
    }
    if (currentState.singlePlayer && !currentState.player1IsWhite)
    {
        takeComputerTurn();
    }
}

void computerUpdateBoard(int row, int col)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            if (currentState.blueSquares[i][j] || (i == currentState.selectedRow && j == currentState.selectedCol))
            {
                deselectSquare(i, j);
                currentState.blueSquares[i][j] = false;
            }

        }
    }

    if (currentState.board.getPiece(row, col).getType() == Piece::Type::King)
    {
        if (currentState.selectedCol - col == 2)
        {
            deselectSquare(row, 0);
        }
        else if (col - currentState.selectedCol == 2)
        {
            deselectSquare(row, 7);
        }
    }


    if (currentState.board.getPiece(row, col).getType() == Piece::Type::Pawn)
    {
        if ((currentState.board.getPiece(row, col).isWhite() && row == 0) || (!currentState.board.getPiece(row, col).isWhite() && row == 7))
        {
            currentState.selectedRow = row;
            currentState.selectedCol = col;
            int selection{ getRandomNumber(0, 3) };
            switch (selection)
            {
            case 0:
            {
                Piece rook = Piece(Piece::Type::Rook, currentState.loadouts[0].moves[4], currentState.loadouts[0].moves[5], 
                    currentState.loadouts[0].moves[6], currentState.loadouts[0].moves[7], currentState.selectedPiece.isWhite());
                currentState.board.addPiece(rook, row, col);
                deselectSquare(row, col);
                return;
            }
            case 1:
            {
                Piece knight = Piece(Piece::Type::Knight, currentState.loadouts[0].moves[8], currentState.loadouts[0].moves[9],
                    currentState.loadouts[0].moves[10], currentState.loadouts[0].moves[11], currentState.selectedPiece.isWhite());
                currentState.board.addPiece(knight, row, col);
                deselectSquare(row, col);
                return;
            }
            case 2:
            {
                Piece bishop = Piece(Piece::Type::Bishop, currentState.loadouts[0].moves[12], currentState.loadouts[0].moves[13],
                    currentState.loadouts[0].moves[14], currentState.loadouts[0].moves[15], currentState.selectedPiece.isWhite());
                currentState.board.addPiece(bishop, row, col);
                deselectSquare(row, col);
                return;
            }
            case 3:
            {
                Piece queen = Piece(Piece::Type::Queen, currentState.loadouts[0].moves[16], currentState.loadouts[0].moves[17],
                    currentState.loadouts[0].moves[18], currentState.loadouts[0].moves[19], currentState.selectedPiece.isWhite());
                currentState.board.addPiece(queen, row, col);
                deselectSquare(row, col);
                return;
            }
            default :
                return;
            }
        }
    }
}

void takeComputerTurn()
{
    while (true)
    {
        int square = getRandomNumber(0, 63);
        int r = square / 8;
        int c = square % 8;
        if (currentState.board.getPiece(r, c) != Grid::noPiece && currentState.board.getPiece(r, c).isWhite() != currentState.player1IsWhite)
        {
            currentState.selectedRow = r;
            currentState.selectedCol = c;
            std::array<std::array<bool, 8>, 8> reachable{};
            if (getRandomNumber(0, 4) == 0)
            {
                if (currentState.selectedPiece.getType() == Piece::Type::Rook)
                {
                    if (currentState.selectedPiece.isUsingSpecial())
                    {
                        currentState.board.getPiece(r,c).allowMovement();
                    }
                    else
                    {
                        currentState.board.getPiece(r, c).useSpecial();
                    }
                    return;
                }
                else if (currentState.selectedPiece.getType() == Piece::Type::Knight
                    || currentState.selectedPiece.getType() == Piece::Type::Bishop)
                {
                    reachable = specialSquares();
                    currentState.board.getPiece(r, c).useSpecial();
                }
                else
                {
                    reachable = currentState.board.reachable(r, c);
                }
                
            }
            else
            {
                if (currentState.selectedPiece.getType() == Piece::Type::Rook && currentState.selectedPiece.isUsingSpecial())
                {
                    reachable = specialSquares();
                }
                else
                {
                    reachable = currentState.board.reachable(r, c);
                }
                
            }
            

            bool possible{ false };
            for (int i{ 0 }; i < 8; ++i)
            {
                for (int j{ 0 }; j < 8; ++j)
                {
                    if (reachable[i][j])
                    {
                        possible = true;
                        currentState.blueSquares[i][j] = true;
                    }
                }
            }
            if (possible)
            {
                while (true)
                {
                    int space = getRandomNumber(0, 63);
                    int ro = space / 8;
                    int co = space % 8;
                    if (reachable[ro][co])
                    {
                        if (currentState.board.getPiece(r, c).isUsingSpecial())
                        {
                            useSpecial(ro, co);
                            computerUpdateBoard(ro, co);
                        }
                        else
                        {
                            if (currentState.board.getPiece(ro, co) != Grid::noPiece)
                            {
                                currentState.defenderCol = co;
                                currentState.defenderRow = ro;
                                currentState.currentActivity = CurrentActivity::battle;
                                currentState.waitingForInput = true;
                                destroyGameBoard();
                                createBattle();
                            }
                            else
                            {
                                currentState.board.movePiece(r, c, ro, co);
                                computerUpdateBoard(ro, co);
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
}

void destroyGameBoard()
{
    DestroyWindow(currentState.windows[5]);
    DestroyWindow(currentState.windows[6]);
    DestroyWindow(currentState.windows[7]);
    DestroyWindow(currentState.windows[8]);
    DestroyWindow(currentState.windows[9]);
    DestroyWindow(currentState.windows[10]);
    DestroyWindow(currentState.windows[11]);
    DestroyWindow(currentState.windows[12]);
    DestroyWindow(currentState.windows[13]);
    DestroyWindow(currentState.windows[14]);
    DestroyWindow(currentState.windows[15]);
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            DestroyWindow(currentState.squares[i][j]);
        }
    }
}

void createAbout(HWND hwnd)
{
    currentState.windows[0] = createLabel(hwnd, L"Special Moves:\n\nPawn: Can move like a king in order to attack the enemy king\n\n"
        "Rook: Fortifying and unforifying immediately uses your turn when clicked. While fortified, the rook has a defensive bonus but cannot move, "
        "instead firing a cannon to hit a tile 3 away in a row or column\n\n"
        "Knight: The knight can joust through an adjacent piece, dealing damage as it passes through. Can only be performed next to a piece, and the other side must be empty\n\n"
        "Bishop: The bishop can use your turn to heal any of the 8 neighboring squares, except a king\n\n"
        "Status effects and stat changes do not persist between battles\n\n"
        "Created by Brandon Sommerfeld", 0.3, 0.1, 0.4, 0.4);
    currentState.windows[1] = createButton(hwnd, L"Back", static_cast<int>(WindowCode::exit), 0.4, 0.8, 0.2, 0.1);
}

void destroyAbout()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
}

void createBattle()
{
    currentState.attackerTurn = true;

    double iconPercent{ 0.2 };
    int side{ static_cast<int>(iconPercent * (currentState.bottomEdge - currentState.topEdge)) };

    int leftCenter{static_cast<int>(0.225 * (currentState.rightEdge - currentState.leftEdge))};
    int rightCenter{ static_cast<int>(0.775 * (currentState.rightEdge - currentState.leftEdge)) };

    currentState.windows[0] = createIcon(currentState.mainWindow, (leftCenter - side/2) / static_cast<double>(currentState.rightEdge - currentState.leftEdge), 0.15, iconPercent, iconPercent);
    fillIcon(currentState.windows[0], currentState.attacker, side);

    currentState.windows[1] = createIcon(currentState.mainWindow, (rightCenter - side / 2) / static_cast<double>(currentState.rightEdge - currentState.leftEdge), 0.15, iconPercent, iconPercent);
    fillIcon(currentState.windows[1], currentState.defender, side);

    std::string message{ "Health " + std::to_string(currentState.attacker.getCurrentHealth()) + '/' + std::to_string(currentState.attacker.getMaxHealth())};
    currentState.windows[2] = createLabel(currentState.mainWindow, StringToWString(message).c_str(), 0.125, 0.4, 0.2, 0.08);
    message = "Health " + std::to_string(currentState.defender.getCurrentHealth()) + '/' + std::to_string(currentState.defender.getMaxHealth());
    currentState.windows[3] = createLabel(currentState.mainWindow, StringToWString(message).c_str(), 0.675, 0.4, 0.2, 0.08);

    currentState.windows[9] = createButton(currentState.mainWindow, L"Exit Game", static_cast<int>(WindowCode::exit), 0.01, 0.01, 0.1, 0.05);

    if (currentState.singlePlayer && currentState.defender.isWhite() == currentState.player1IsWhite)
    {
        computerBattle();
    }
    else
    {
        currentState.windows[4] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(1))).c_str(), static_cast<int>(WindowCode::move1), 0.05, 0.5, 0.15, 0.1);
        currentState.windows[5] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(2))).c_str(), static_cast<int>(WindowCode::move2), 0.25, 0.5, 0.15, 0.1);
        currentState.windows[6] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(3))).c_str(), static_cast<int>(WindowCode::move3), 0.05, 0.7, 0.15, 0.1);
        currentState.windows[7] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(4))).c_str(), static_cast<int>(WindowCode::move4), 0.25, 0.7, 0.15, 0.1);
        currentState.windows[8] = createButton(currentState.mainWindow, L"Flee", static_cast<int>(WindowCode::flee), 0.175, 0.9, 0.1, 0.05);

        currentState.windows[11] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(1))).c_str(), 0.05, 0.61, 0.15, 0.05);
        currentState.windows[12] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(2))).c_str(), 0.25, 0.61, 0.15, 0.05);
        currentState.windows[13] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(3))).c_str(), 0.05, 0.81, 0.15, 0.05);
        currentState.windows[14] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(4))).c_str(), 0.25, 0.81, 0.15, 0.05);
    }
}

void updateBattle()
{
    std::string message{ "Health " + std::to_string(currentState.attacker.getCurrentHealth()) + '/' + std::to_string(currentState.attacker.getMaxHealth()) + "   " + printStatus(currentState.attacker.getStatus()) };
    if (currentState.attacker.getStatusTurns() != 0)
    {
        message += " (" + std::to_string(currentState.attacker.getStatusTurns()) + ")";
    }
    SetWindowText(currentState.windows[2], StringToWString(message).c_str());
    message = "Health " + std::to_string(currentState.defender.getCurrentHealth()) + '/' + std::to_string(currentState.defender.getMaxHealth()) + "   " + printStatus(currentState.defender.getStatus());
    if (currentState.defender.getStatusTurns() != 0)
    {
        message += " (" + std::to_string(currentState.defender.getStatusTurns()) + ")";
    }
    SetWindowText(currentState.windows[3], StringToWString(message).c_str());

}

void destroyBattle()
{
    DestroyWindow(currentState.windows[0]);
    DestroyWindow(currentState.windows[1]);
    DestroyWindow(currentState.windows[2]);
    DestroyWindow(currentState.windows[3]);
    DestroyWindow(currentState.windows[4]);
    DestroyWindow(currentState.windows[5]);
    DestroyWindow(currentState.windows[6]);
    DestroyWindow(currentState.windows[7]);
    DestroyWindow(currentState.windows[8]);
    DestroyWindow(currentState.windows[9]);
    DestroyWindow(currentState.windows[10]);
    DestroyWindow(currentState.windows[11]);
    DestroyWindow(currentState.windows[12]);
    DestroyWindow(currentState.windows[13]);
    DestroyWindow(currentState.windows[14]);
}

void computerBattle()
{
    int move{ getRandomNumber(1,4) };
    useMove(move);
}

void changeTurns()
{
    DestroyWindow(currentState.windows[4]);
    DestroyWindow(currentState.windows[5]);
    DestroyWindow(currentState.windows[6]);
    DestroyWindow(currentState.windows[7]);
    DestroyWindow(currentState.windows[8]);
    DestroyWindow(currentState.windows[11]);
    DestroyWindow(currentState.windows[12]);
    DestroyWindow(currentState.windows[13]);
    DestroyWindow(currentState.windows[14]);
    if (!currentState.attackerTurn)
    {
        currentState.windows[4] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(1))).c_str(), static_cast<int>(WindowCode::move1), 0.05, 0.5, 0.15, 0.1);
        currentState.windows[5] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(2))).c_str(), static_cast<int>(WindowCode::move2), 0.25, 0.5, 0.15, 0.1);
        currentState.windows[6] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(3))).c_str(), static_cast<int>(WindowCode::move3), 0.05, 0.7, 0.15, 0.1);
        currentState.windows[7] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.attacker.getMove(4))).c_str(), static_cast<int>(WindowCode::move4), 0.25, 0.7, 0.15, 0.1);
        currentState.windows[8] = createButton(currentState.mainWindow, L"Flee", static_cast<int>(WindowCode::flee), 0.175, 0.9, 0.1, 0.05);

        currentState.windows[11] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(1))).c_str(), 0.05, 0.61, 0.15, 0.05);
        currentState.windows[12] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(2))).c_str(), 0.25, 0.61, 0.15, 0.05);
        currentState.windows[13] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(3))).c_str(), 0.05, 0.81, 0.15, 0.05);
        currentState.windows[14] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.attacker.getMove(4))).c_str(), 0.25, 0.81, 0.15, 0.05);
    }
    else
    {
        currentState.windows[4] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.defender.getMove(1))).c_str(), static_cast<int>(WindowCode::move1), 0.6, 0.5, 0.15, 0.1);
        currentState.windows[5] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.defender.getMove(2))).c_str(), static_cast<int>(WindowCode::move2), 0.8, 0.5, 0.15, 0.1);
        currentState.windows[6] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.defender.getMove(3))).c_str(), static_cast<int>(WindowCode::move3), 0.6, 0.7, 0.15, 0.1);
        currentState.windows[7] = createButton(currentState.mainWindow, StringToWString(printMove(currentState.defender.getMove(4))).c_str(), static_cast<int>(WindowCode::move4), 0.8, 0.7, 0.15, 0.1);

        currentState.windows[11] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.defender.getMove(1))).c_str(), 0.6, 0.61, 0.15, 0.05);
        currentState.windows[12] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.defender.getMove(2))).c_str(), 0.8, 0.61, 0.15, 0.05);
        currentState.windows[13] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.defender.getMove(3))).c_str(), 0.6, 0.81, 0.15, 0.05);
        currentState.windows[14] = createLabel(currentState.mainWindow, StringToWString(getDescription(currentState.defender.getMove(4))).c_str(), 0.8, 0.81, 0.15, 0.05);
    }
    currentState.attackerTurn = !currentState.attackerTurn;
}

void useMove(int move)
{
    if (!currentState.waiting)
    {
        currentState.handledStatus = false;
        if (currentState.attackerTurn)
        {
            int startingHealth{ currentState.defender.getCurrentHealth() };
            Piece::Status startingStatus{ currentState.defender.getStatus() };
            int startingTurns{ currentState.defender.getStatusTurns() };
            Piece::AttackOutcome result{ currentState.attacker.useMove(currentState.defender, currentState.attacker.getMove(move)) };

            std::string message{};
            if (result == Piece::AttackOutcome::Miss)
            {
                message = printMove(currentState.attacker.getMove(move)) + " missed!";
            }
            else
            {
                if (result == Piece::AttackOutcome::Super_Effective)
                {
                    message += "Critical hit! ";
                }
                message += printMove(currentState.attacker.getMove(move)) + " dealt "
                + std::to_string(startingHealth - currentState.defender.getCurrentHealth()) + " damage.\n";

                if (currentState.defender.getStatus() != startingStatus || currentState.defender.getStatusTurns() != startingTurns)
                {
                    message += "Inflicted " + printStatus(currentState.defender.getStatus());
                }
            }
            
            currentState.windows[10] = createLabel(currentState.mainWindow, StringToWString(message).c_str(),
                DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
            waitBattle(3000);
        }
        else
        {
            int startingHealth{ currentState.attacker.getCurrentHealth() };
            Piece::Status startingStatus{ currentState.attacker.getStatus() };
            int startingTurns{ currentState.attacker.getStatusTurns() };
            Piece::AttackOutcome result{ currentState.defender.useMove(currentState.attacker, currentState.defender.getMove(move)) };

            std::string message{};
            if (result == Piece::AttackOutcome::Miss)
            {
                message = printMove(currentState.defender.getMove(move)) + " missed!";
            }
            else
            {
                if (result == Piece::AttackOutcome::Super_Effective)
                {
                    message += "Critical hit! ";
                }
                message += printMove(currentState.defender.getMove(move)) + " dealt "
                    + std::to_string(startingHealth - currentState.attacker.getCurrentHealth()) + " damage.\n";

                if (currentState.attacker.getStatus() != startingStatus || currentState.attacker.getStatusTurns() != startingTurns)
                {
                    message += "Inflicted " + printStatus(currentState.attacker.getStatus());
                }
            }
            currentState.windows[10] = createLabel(currentState.mainWindow, StringToWString(message).c_str(),
                DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
            waitBattle(3000);
        }
    }
}

void handleStatus()
{
    currentState.handledStatus = true;
    std::string message{};
    if (currentState.attackerTurn)
    {
        message = currentState.defender.getName() + " is " + printStatus(currentState.defender.getStatus());
        if (currentState.defender.getStatus() != Piece::Status::Cursed)
        {
            currentState.defender.dealDamage(1);
        }
        currentState.defender.decrementStatusTurns();
    }
    else
    {
        message = currentState.attacker.getName() + " is " + printStatus(currentState.attacker.getStatus());
        if (currentState.attacker.getStatus() != Piece::Status::Cursed)
        {
            currentState.attacker.dealDamage(1);
        }
        currentState.attacker.decrementStatusTurns();
    }

    currentState.windows[10] = createLabel(currentState.mainWindow, StringToWString(message).c_str(),
        DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
    waitBattle(3000);
}

void exitCases(HWND hwnd)
{
    switch (currentState.currentActivity)
    {
    case CurrentActivity::mainMenu :
         DestroyWindow(hwnd);
         break;
    case CurrentActivity::about :
        destroyAbout();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    case CurrentActivity::board :
        destroyGameBoard();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    case CurrentActivity::selectLoadout :
        destroySelectScreen();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    case CurrentActivity::createLoadout :
        destroyLoadoutScreen();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    case CurrentActivity::battle :
        destroyBattle();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    case CurrentActivity::victoryScreen :
        destroyVictoryScreen();
        createMainMenu(hwnd);
        currentState.currentActivity = CurrentActivity::mainMenu;
        break;
    }
}

void adjustButtons(HWND hwnd)
{
    switch (currentState.currentActivity)
    {
    case CurrentActivity::mainMenu :
        destroyMainMenu();
        createMainMenu(hwnd);
        break;
    case CurrentActivity::selectLoadout:
        destroySelectScreen();
        createSelectScreen(hwnd);
        break;
    case CurrentActivity::about:
        destroyAbout();
        createAbout(hwnd);
        break;
    }
}

void promotePawn(int row, int col)
{
    currentState.waitingForInput = true;

    currentState.windows[8] = createLabel(currentState.mainWindow, L"Promote your pawn:", BOARDRIGHT, 0.4, 0.2, 0.1);
    currentState.windows[9] = createButton(currentState.mainWindow, L"Rook", static_cast<int>(WindowCode::promoteRook), BOARDRIGHT, 0.55, 0.1, 0.05);
    currentState.windows[10] = createButton(currentState.mainWindow, L"Knight", static_cast<int>(WindowCode::promoteKnight), BOARDRIGHT + 0.15, 0.55, 0.1, 0.05);
    currentState.windows[11] = createButton(currentState.mainWindow, L"Bishop", static_cast<int>(WindowCode::promoteBishop), BOARDRIGHT, 0.75, 0.1, 0.05);
    currentState.windows[12] = createButton(currentState.mainWindow, L"Queen", static_cast<int>(WindowCode::promoteQueen), BOARDRIGHT + 0.15, 0.75, 0.1, 0.05);
    currentState.selectedCol = col;
    currentState.selectedRow = row;
}

void useSpecial(int row, int col)
{
    switch (currentState.selectedPiece.getType())
    {
    case Piece::Type::Rook:
    {
        currentState.board.getPiece(row, col).dealDamage(10);
        if (currentState.board.getPiece(row, col).isDead())
        {
            currentState.board.removePiece(row, col);
        }
        break;
    }
    case Piece::Type::Knight:
    {
        if (currentState.selectedRow > row)
        {
            currentState.board.getPiece(row + 1, col).dealDamage(7);
            if (currentState.board.getPiece(row + 1, col).isDead())
            {
                currentState.board.removePiece(row + 1, col);
                deselectSquare(row + 1, col);
            }
        }
        else if (row > currentState.selectedRow)
        {
            currentState.board.getPiece(row - 1, col).dealDamage(7);
            if (currentState.board.getPiece(row - 1, col).isDead())
            {
                currentState.board.removePiece(row - 1, col);
                deselectSquare(row - 1, col);
            }
        }
        else if (currentState.selectedCol > col)
        {
            currentState.board.getPiece(row, col + 1).dealDamage(7);
            if (currentState.board.getPiece(row, col + 1).isDead())
            {
                currentState.board.removePiece(row, col + 1);
                deselectSquare(row, col + 1);
            }
        }
        else
        {
            currentState.board.getPiece(row, col - 1).dealDamage(7);
            if (currentState.board.getPiece(row, col - 1).isDead())
            {
                currentState.board.removePiece(row, col - 1);
                deselectSquare(row, col - 1);
            }
        }
        currentState.board.movePiece(currentState.selectedRow, currentState.selectedCol, row, col);
        currentState.board.getPiece(row, col).allowMovement();
        break;
    }
    case Piece::Type::Bishop:
    {
        currentState.board.getPiece(row, col).dealDamage(-5);
        currentState.selectedPiece.allowMovement();
        break;
    }
    }
}

void updateBoard(int row, int col)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            if (currentState.blueSquares[i][j] || (i == currentState.selectedRow && j == currentState.selectedCol))
            {
                deselectSquare(i, j);
                currentState.blueSquares[i][j] = false;
            }

        }
    }
    if (currentState.board.getPiece(row, col).getType() == Piece::Type::King)
    {
        if (currentState.selectedCol - col == 2)
        {
            deselectSquare(row, 0);
        }
        else if (col - currentState.selectedCol == 2)
        {
            deselectSquare(row, 7);
        }
    }
}

void deselectAll()
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            if (currentState.blueSquares[i][j])
            {
                currentState.blueSquares[i][j] = false;
                deselectSquare(i, j);
            }
        }
    }
}

void createPieceDescription(int row, int col)
{
    Piece p{ currentState.board.getPiece(row,col) };
    
    std::string message{};
    message = p.getName() + "\nHealth: " + std::to_string(p.getCurrentHealth()) + '/'+ std::to_string(p.getMaxHealth())
        + "\nMove 1: " + printMove(p.getMove(1)) + "\nMove 2: " + printMove(p.getMove(2))
        + "\nMove 3: "+ printMove(p.getMove(3)) + "\nMove 4: " + printMove(p.getMove(4));
    if (p.getType() == Piece::Type::Rook && p.isUsingSpecial())
    {
        message += "\nFortified";
    }
    currentState.windows[13] = createLabel(currentState.mainWindow, StringToWString(message).c_str(), BOARDRIGHT, 0.4, 0.2, 0.4);

    if ((currentState.singlePlayer && (currentState.player1IsWhite == p.isWhite())) || (!currentState.singlePlayer && (currentState.isWhiteTurn == p.isWhite())))
    {
        switch (p.getType())
        {
        case Piece::Type::Rook:
        {
            if (p.isUsingSpecial())
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Unfortify", static_cast<int>(WindowCode::useSpecial), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            else
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Fortify", static_cast<int>(WindowCode::useSpecial), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            break;
        }
        case Piece::Type::Knight:
        {
            if (!p.isUsingSpecial())
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Joust", static_cast<int>(WindowCode::useSpecial), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            else
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Move", static_cast<int>(WindowCode::move), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            break;
        }
        case Piece::Type::Bishop:
        {
            if (!p.isUsingSpecial())
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Heal", static_cast<int>(WindowCode::useSpecial), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            else
            {
                currentState.windows[14] = createButton(currentState.mainWindow, L"Move", static_cast<int>(WindowCode::move), BOARDRIGHT + 0.025, 0.55, 0.15, 0.1);
            }
            break;
        }
        }
    }
    
}

void destroyPieceDescription()
{
    DestroyWindow(currentState.windows[13]);
    DestroyWindow(currentState.windows[14]);
    DestroyWindow(currentState.windows[15]);
}

void setBlue(const std::array<std::array<bool, 8>, 8>& valid)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            currentState.blueSquares[i][j] = valid[i][j];
            if (valid[i][j])
            {
                selectSquare(i, j);
            }
        }
    }
}

std::array<std::array<bool, 8>, 8> specialSquares()
{
    std::array<std::array<bool, 8>, 8> reachable{};
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            reachable[i][j] = false;
        }
    }

    switch (currentState.selectedPiece.getType())
    {
    case Piece::Type::Rook :
    {
        if (currentState.selectedRow > 2 && currentState.board.getPiece(currentState.selectedRow-3, currentState.selectedCol) != Grid::noPiece)
        {
            reachable[currentState.selectedRow - 3][currentState.selectedCol] = true;
        }
        if (currentState.selectedRow < 5 && currentState.board.getPiece(currentState.selectedRow + 3, currentState.selectedCol) != Grid::noPiece)
        {
            reachable[currentState.selectedRow + 3][currentState.selectedCol] = true;
        }
        if (currentState.selectedCol > 2 && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol - 3) != Grid::noPiece)
        {
            reachable[currentState.selectedRow][currentState.selectedCol - 3] = true;
        }
        if (currentState.selectedCol < 5 && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol + 3) != Grid::noPiece)
        {
            reachable[currentState.selectedRow][currentState.selectedCol + 3] = true;
        }
        break;
    }
    case Piece::Type::Knight:
    {
        if (currentState.selectedRow > 1 && currentState.board.getPiece(currentState.selectedRow - 2, currentState.selectedCol) == Grid::noPiece && currentState.board.getPiece(currentState.selectedRow - 1, currentState.selectedCol) != Grid::noPiece)
        {
            reachable[currentState.selectedRow - 2][currentState.selectedCol] = true;
        }
        if (currentState.selectedRow < 6 && currentState.board.getPiece(currentState.selectedRow + 2, currentState.selectedCol) == Grid::noPiece && currentState.board.getPiece(currentState.selectedRow + 1, currentState.selectedCol) != Grid::noPiece)
        {
            reachable[currentState.selectedRow + 2][currentState.selectedCol] = true;
        }
        if (currentState.selectedCol > 1 && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol - 2) == Grid::noPiece && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol - 1) != Grid::noPiece)
        {
            reachable[currentState.selectedRow][currentState.selectedCol - 2] = true;
        }
        if (currentState.selectedCol < 6 && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol + 2) == Grid::noPiece && currentState.board.getPiece(currentState.selectedRow, currentState.selectedCol + 1) != Grid::noPiece)
        {
            reachable[currentState.selectedRow][currentState.selectedCol + 2] = true;
        }
        break;
    }
    case Piece::Type::Bishop:
    {
        for (int i{ -1 }; i < 2; ++i)
        {
            if (currentState.selectedRow + i >= 0 && currentState.selectedRow + i < 8 && currentState.selectedCol - 1 >= 0 && currentState.board.getPiece(currentState.selectedRow + i, currentState.selectedCol - 1) != Grid::noPiece
                && currentState.board.getPiece(currentState.selectedRow + i, currentState.selectedCol - 1).getType() != Piece::Type::King)
            {
                reachable[currentState.selectedRow + i][currentState.selectedCol - 1] = true;
            }
            if (currentState.selectedRow + i >= 0 && currentState.selectedRow + i < 8 && currentState.selectedCol + 1 < 8 && currentState.board.getPiece(currentState.selectedRow + i, currentState.selectedCol + 1) != Grid::noPiece
                && currentState.board.getPiece(currentState.selectedRow + i, currentState.selectedCol + 1).getType() != Piece::Type::King)
            {
                reachable[currentState.selectedRow + i][currentState.selectedCol + 1] = true;
            }
        }
        if (currentState.selectedRow + 1 < 8 && currentState.board.getPiece(currentState.selectedRow + 1, currentState.selectedCol) != Grid::noPiece
            && currentState.board.getPiece(currentState.selectedRow + 1, currentState.selectedCol).getType() != Piece::Type::King)
        {
            reachable[currentState.selectedRow + 1][currentState.selectedCol] = true;
        }
        if (currentState.selectedRow - 1 >= 0 && currentState.board.getPiece(currentState.selectedRow - 1, currentState.selectedCol) != Grid::noPiece
            && currentState.board.getPiece(currentState.selectedRow - 1, currentState.selectedCol).getType() != Piece::Type::King)
        {
            reachable[currentState.selectedRow - 1][currentState.selectedCol] = true;
        }
        break;
    }
    }
    return reachable;
}

void useTurn()
{
    currentState.selectedRow = -1;
    currentState.selectedCol = -1;
    destroyPieceDescription();
    if (currentState.singlePlayer)
    {
        takeComputerTurn();
    }
    else
    {
        currentState.isWhiteTurn = !currentState.isWhiteTurn;
    }
}

void squarePressed(int row, int col)
{
    
    if (!currentState.waitingForInput)
    {
        destroyPieceDescription();
        if (!currentState.blueSquares[row][col] && currentState.board.getPiece(row, col) != Grid::noPiece)
        {
            currentState.selectedCol = col;
            currentState.selectedRow = row;

            deselectAll();

            if ((!currentState.singlePlayer && currentState.selectedPiece.isWhite() == currentState.isWhiteTurn) ||
                (currentState.singlePlayer && currentState.selectedPiece.isWhite() == currentState.player1IsWhite))
            {
                if (currentState.selectedPiece.isUsingSpecial() && currentState.selectedPiece.getType() == Piece::Type::Rook)
                {
                    setBlue(specialSquares());
                }
                else
                {
                    currentState.selectedPiece.allowMovement();
                    setBlue(currentState.board.reachable(row, col));
                }
            }
            createPieceDescription(row, col);
        }
        else if (currentState.selectedPiece != Grid::noPiece)
        {
            if (currentState.blueSquares[row][col])
            {
                if (currentState.selectedPiece.isUsingSpecial())
                {
                    useSpecial(row, col);
                    updateBoard(row, col);
                }
                else
                {
                    if (currentState.board.getPiece(row, col) != Grid::noPiece)
                    {
                        currentState.defenderCol = col;
                        currentState.defenderRow = row;
                        currentState.currentActivity = CurrentActivity::battle;
                        currentState.waitingForInput = true;
                        destroyGameBoard();
                        createBattle();
                    }
                    else
                    {
                        currentState.board.movePiece(currentState.selectedRow, currentState.selectedCol, row, col);
                        updateBoard(row, col);
                        if (currentState.board.getPiece(row, col).getType() == Piece::Type::Pawn)
                        {
                            if ((currentState.board.getPiece(row, col).isWhite() && row == 0)
                                || (!currentState.board.getPiece(row, col).isWhite() && row == 7))
                            {
                                promotePawn(row, col);
                            }
                        }
                    }
                    
                }
                if (currentState.singlePlayer && !currentState.waitingForInput)
                {
                    takeComputerTurn();
                }
                else
                {
                    currentState.isWhiteTurn = !currentState.isWhiteTurn;
                }

            }
            else
            {
                deselectAll();
            }
            if (!currentState.waitingForInput)
            {
                currentState.selectedRow = -1;
                currentState.selectedCol = -1;
            }
             
        }
    }
}

void buttonPressed(HWND hwnd, WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
        case static_cast<int>(WindowCode::startGame) :
        {
            DestroyWindow(currentState.windows[10]);
            currentState.isWhiteTurn = true;
            if (getRandomNumber(0, 1) == 0)
            {
                currentState.player1IsWhite = true;
            }
            else
            {
                currentState.player1IsWhite = false;
            }
            
            if (currentState.singlePlayer)
            {
                wchar_t name[30];
                GetWindowText(currentState.windows[1], name, 30);
                currentState.player1name = std::wstring{ name };

                currentState.player2name = L"Computer";

                currentState.player1Loadout = static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
                currentState.player2Loadout = 0;
            }
            else
            {
                wchar_t name[30];
                GetWindowText(currentState.windows[1], name, 30);
                currentState.player1name = std::wstring{ name };
                GetWindowText(currentState.windows[2], name, 30);
                currentState.player2name = std::wstring{ name };
                
                currentState.player1Loadout = static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
                currentState.player2Loadout = static_cast<int>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
            }

            if (!currentState.completedLoadouts[currentState.player1Loadout] || !currentState.completedLoadouts[currentState.player2Loadout])
            {
                currentState.windows[10] = createLabel(hwnd, L"One of the loadouts selected is not complete", 0.4, 0.7, 0.2, 0.1);
                break;
            }

            if (currentState.player1IsWhite)
            {
                currentState.board = Grid{currentState.loadouts[currentState.player1Loadout], currentState.loadouts[currentState.player2Loadout] };
            }
            else
            {
                currentState.board = Grid{ currentState.loadouts[currentState.player2Loadout], currentState.loadouts[currentState.player1Loadout] };
            }

            createGameBoard(hwnd);
            
            destroySelectScreen();
            currentState.currentActivity = CurrentActivity::board;
            currentState.selectedCol = -1;
            currentState.selectedRow = -1;
            currentState.defenderCol = -1;
            currentState.defenderRow = -1;
            currentState.waitingForInput = false;
            currentState.waiting = false;
            currentState.attackerTurn = true;
            currentState.handledStatus = false;
            break;
        }
        case static_cast<int>(WindowCode::singlePlayer) :
        {
            destroyMainMenu();
            currentState.singlePlayer = true;
            createSelectScreen(hwnd);
            currentState.currentActivity = CurrentActivity::selectLoadout;
            break;
        }
        case static_cast<int>(WindowCode::twoPlayers) :
        {
            destroyMainMenu();
            currentState.singlePlayer = false;
            createSelectScreen(hwnd);
            currentState.currentActivity = CurrentActivity::selectLoadout;
            break;
        }
        case static_cast<int>(WindowCode::createLoadouts) :
        {
            destroyMainMenu();
            createLoadoutScreen(hwnd);
            currentState.currentActivity = CurrentActivity::createLoadout;
            break;
        }
        case static_cast<int>(WindowCode::about) :
        {
            destroyMainMenu();
            createAbout(hwnd);
            currentState.currentActivity = CurrentActivity::about;
            break;
        }
        
        case static_cast<int>(WindowCode::exit) :
        {
            exitCases(hwnd);
            break;
        }
        case static_cast<int>(WindowCode::saveLoadout) :
        {
            retrieveNewLoadoutSelection();
            break;
        }
        case static_cast<int>(WindowCode::useSpecial) :
        {
            deselectAll();
            if (currentState.selectedPiece.getType() == Piece::Type::Rook)
            {
                if (currentState.selectedPiece.isUsingSpecial())
                {
                    currentState.selectedPiece.allowMovement();
                }
                else
                {
                    currentState.selectedPiece.useSpecial();
                }
                useTurn();
                break;
            }

            currentState.selectedPiece.useSpecial();
            setBlue(specialSquares());
            destroyPieceDescription();
            createPieceDescription(currentState.selectedRow, currentState.selectedCol);
            
            break;
        }
        case static_cast<int>(WindowCode::move) :
        {
            currentState.selectedPiece.allowMovement();
            currentState.selectedPiece.allowMovement();
            destroyPieceDescription();
            createPieceDescription(currentState.selectedRow, currentState.selectedCol);
            deselectAll();
            setBlue(currentState.board.reachable(currentState.selectedRow, currentState.selectedCol));
            break;
        }
        case static_cast<int>(WindowCode::promoteRook) :
        {
            Piece rook{};
            if (currentState.singlePlayer || (currentState.player1IsWhite == currentState.selectedPiece.isWhite()))
            {
                rook = Piece(Piece::Type::Rook, currentState.loadouts[currentState.player1Loadout].moves[4],
                    currentState.loadouts[currentState.player1Loadout].moves[5], currentState.loadouts[currentState.player1Loadout].moves[6],
                    currentState.loadouts[currentState.player1Loadout].moves[7], currentState.selectedPiece.isWhite());
            }
            else
            {
                rook = Piece(Piece::Type::Rook, currentState.loadouts[currentState.player2Loadout].moves[4],
                    currentState.loadouts[currentState.player2Loadout].moves[5], currentState.loadouts[currentState.player2Loadout].moves[6],
                    currentState.loadouts[currentState.player2Loadout].moves[7], currentState.selectedPiece.isWhite());
            }
            currentState.board.addPiece(rook, currentState.selectedRow, currentState.selectedCol);
            deselectSquare(currentState.selectedRow, currentState.selectedCol);
            currentState.waitingForInput = false;
            if (currentState.singlePlayer)
            {
                takeComputerTurn();
            }
            currentState.selectedRow = -1;
            currentState.selectedCol = -1;
            
            DestroyWindow(currentState.windows[8]);
            DestroyWindow(currentState.windows[9]);
            DestroyWindow(currentState.windows[10]);
            DestroyWindow(currentState.windows[11]);
            DestroyWindow(currentState.windows[12]);
            break;
        }
        case static_cast<int>(WindowCode::promoteKnight) :
        {
            Piece knight{};
            if (currentState.singlePlayer || (currentState.player1IsWhite == currentState.selectedPiece.isWhite()))
            {
                knight = Piece(Piece::Type::Knight, currentState.loadouts[currentState.player1Loadout].moves[8],
                    currentState.loadouts[currentState.player1Loadout].moves[9], currentState.loadouts[currentState.player1Loadout].moves[10],
                    currentState.loadouts[currentState.player1Loadout].moves[11], currentState.selectedPiece.isWhite());
            }
            else
            {
                knight = Piece(Piece::Type::Knight, currentState.loadouts[currentState.player2Loadout].moves[8],
                    currentState.loadouts[currentState.player2Loadout].moves[9], currentState.loadouts[currentState.player2Loadout].moves[10],
                    currentState.loadouts[currentState.player2Loadout].moves[11], currentState.selectedPiece.isWhite());
            }
            currentState.board.addPiece(knight, currentState.selectedRow, currentState.selectedCol);
            deselectSquare(currentState.selectedRow, currentState.selectedCol);
            currentState.waitingForInput = false;
            if (currentState.singlePlayer)
            {
                takeComputerTurn();
            }
            currentState.selectedRow = -1;
            currentState.selectedCol = -1;

            DestroyWindow(currentState.windows[8]);
            DestroyWindow(currentState.windows[9]);
            DestroyWindow(currentState.windows[10]);
            DestroyWindow(currentState.windows[11]);
            DestroyWindow(currentState.windows[12]);
            break;
        }
        case static_cast<int>(WindowCode::promoteBishop) :
        {
            Piece bishop{};
            if (currentState.singlePlayer || (currentState.player1IsWhite == currentState.selectedPiece.isWhite()))
            {
                bishop = Piece(Piece::Type::Bishop, currentState.loadouts[currentState.player1Loadout].moves[12],
                    currentState.loadouts[currentState.player1Loadout].moves[13], currentState.loadouts[currentState.player1Loadout].moves[14],
                    currentState.loadouts[currentState.player1Loadout].moves[15], currentState.selectedPiece.isWhite());
            }
            else
            {
                bishop = Piece(Piece::Type::Bishop, currentState.loadouts[currentState.player2Loadout].moves[12],
                    currentState.loadouts[currentState.player2Loadout].moves[13], currentState.loadouts[currentState.player2Loadout].moves[14],
                    currentState.loadouts[currentState.player2Loadout].moves[15], currentState.selectedPiece.isWhite());
            }
            currentState.board.addPiece(bishop, currentState.selectedRow, currentState.selectedCol);
            deselectSquare(currentState.selectedRow, currentState.selectedCol);
            currentState.waitingForInput = false;
            if (currentState.singlePlayer)
            {
                takeComputerTurn();
            }
            currentState.selectedRow = -1;
            currentState.selectedCol = -1;

            DestroyWindow(currentState.windows[8]);
            DestroyWindow(currentState.windows[9]);
            DestroyWindow(currentState.windows[10]);
            DestroyWindow(currentState.windows[11]);
            DestroyWindow(currentState.windows[12]);
            break;
        }
        case static_cast<int>(WindowCode::promoteQueen) :
        {
            Piece queen{};
            if (currentState.singlePlayer || (currentState.player1IsWhite == currentState.selectedPiece.isWhite()))
            {
                queen = Piece(Piece::Type::Queen, currentState.loadouts[currentState.player1Loadout].moves[16],
                    currentState.loadouts[currentState.player1Loadout].moves[17], currentState.loadouts[currentState.player1Loadout].moves[18],
                    currentState.loadouts[currentState.player1Loadout].moves[19], currentState.selectedPiece.isWhite());
            }
            else
            {
                queen = Piece(Piece::Type::Queen, currentState.loadouts[currentState.player2Loadout].moves[16],
                    currentState.loadouts[currentState.player2Loadout].moves[17], currentState.loadouts[currentState.player2Loadout].moves[18],
                    currentState.loadouts[currentState.player2Loadout].moves[19], currentState.selectedPiece.isWhite());
            }
            currentState.board.addPiece(queen, currentState.selectedRow, currentState.selectedCol);
            deselectSquare(currentState.selectedRow, currentState.selectedCol);
            currentState.waitingForInput = false;
            if (currentState.singlePlayer)
            {
                takeComputerTurn();
            }
            currentState.selectedRow = -1;
            currentState.selectedCol = -1;

            DestroyWindow(currentState.windows[8]);
            DestroyWindow(currentState.windows[9]);
            DestroyWindow(currentState.windows[10]);
            DestroyWindow(currentState.windows[11]);
            DestroyWindow(currentState.windows[12]);
            break;
        }
        case static_cast<int>(WindowCode::loadoutDropdown1) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE && currentState.currentActivity == CurrentActivity::createLoadout)
            {
                int newLoadout = static_cast<int>(SendMessage(currentState.windows[2], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
                SendMessage(currentState.windows[3], (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

                changeMoveDropdown(currentState.windows[4], currentState.loadouts[newLoadout + 1].moves[0], Piece::Type::Pawn);
                changeMoveDropdown(currentState.windows[5], currentState.loadouts[newLoadout + 1].moves[1], Piece::Type::Pawn);
                changeMoveDropdown(currentState.windows[6], currentState.loadouts[newLoadout + 1].moves[2], Piece::Type::Pawn);
                changeMoveDropdown(currentState.windows[7], currentState.loadouts[newLoadout + 1].moves[3], Piece::Type::Pawn);
                SetWindowText(currentState.windows[16], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str());
                SetWindowText(currentState.windows[17], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[5], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str());
                SetWindowText(currentState.windows[18], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[6], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str());
                SetWindowText(currentState.windows[19], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[7], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::pieceDropdown) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int newLoadout = static_cast<int>(SendMessage(currentState.windows[2], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
                int piece = static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
                changeMoveDropdown(currentState.windows[4], currentState.loadouts[newLoadout + 1].moves[piece * 4], static_cast<Piece::Type>(piece));
                changeMoveDropdown(currentState.windows[5], currentState.loadouts[newLoadout + 1].moves[piece * 4 + 1], static_cast<Piece::Type>(piece));
                changeMoveDropdown(currentState.windows[6], currentState.loadouts[newLoadout + 1].moves[piece * 4 + 2], static_cast<Piece::Type>(piece));
                changeMoveDropdown(currentState.windows[7], currentState.loadouts[newLoadout + 1].moves[piece * 4 + 3], static_cast<Piece::Type>(piece));
                int shift = pieceShift(static_cast<Piece::Type>(piece));
                SetWindowText(currentState.windows[16], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) + shift))).c_str());
                SetWindowText(currentState.windows[17], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[5], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) + shift))).c_str());
                SetWindowText(currentState.windows[18], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[6], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) + shift))).c_str());
                SetWindowText(currentState.windows[19], StringToWString(getDescription(static_cast<Piece::Move>(SendMessage(currentState.windows[7], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) + shift))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::moveDropdown1) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int piece{ static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                int shift{ pieceShift(static_cast<Piece::Type>(piece)) };
                int newMove{ static_cast<int>(SendMessage(currentState.windows[4], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                SetWindowText(currentState.windows[16], StringToWString(getDescription(static_cast<Piece::Move>(newMove + shift))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::moveDropdown2) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int piece{ static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                int shift{ pieceShift(static_cast<Piece::Type>(piece)) };
                int newMove{ static_cast<int>(SendMessage(currentState.windows[5], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                SetWindowText(currentState.windows[17], StringToWString(getDescription(static_cast<Piece::Move>(newMove + shift))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::moveDropdown3) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int piece{ static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                int shift{ pieceShift(static_cast<Piece::Type>(piece)) };
                int newMove{ static_cast<int>(SendMessage(currentState.windows[6], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                SetWindowText(currentState.windows[18], StringToWString(getDescription(static_cast<Piece::Move>(newMove + shift))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::moveDropdown4) :
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int piece{ static_cast<int>(SendMessage(currentState.windows[3], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                int shift{ pieceShift(static_cast<Piece::Type>(piece)) };
                int newMove{ static_cast<int>(SendMessage(currentState.windows[7], (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0)) };
                SetWindowText(currentState.windows[19], StringToWString(getDescription(static_cast<Piece::Move>(newMove + shift))).c_str());
            }
            break;
        }
        case static_cast<int>(WindowCode::move1) :
        {
            useMove(1);
            break;
        }
        case static_cast<int>(WindowCode::move2) :
        {
            useMove(2);
            break;
        }
        case static_cast<int>(WindowCode::move3) :
        {
            useMove(3);
            break;
        }
        case static_cast<int>(WindowCode::move4) :
        {
            useMove(4);
            break;
        }
        case static_cast<int>(WindowCode::flee) :
        {
            int success{ getRandomNumber(0,1) };
            if (success == 0)
            {
                std::string message{};
                if (currentState.attackerTurn)
                {
                    message = currentState.attacker.getName();
                }
                else
                {
                    message = currentState.defender.getName();
                }
                message += " failed to flee";
                currentState.windows[10] = createLabel(hwnd, StringToWString(message).c_str(), DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);

                waitBattle(3000);
            }
            else
            {
                std::string message{};
                if (currentState.attackerTurn)
                {
                    message = currentState.attacker.getName();
                }
                else
                {
                    message = currentState.defender.getName();
                }
                message += " fled";
                currentState.windows[10] = createLabel(hwnd, StringToWString(message).c_str(), DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);

                currentState.attacker.reset();
                currentState.defender.reset();
                waitDone(3000);
            }
            break;
        }
        case static_cast<int>(WindowCode::usingMove) :
        {
            DestroyWindow(currentState.windows[10]);
            KillTimer(currentState.mainWindow, static_cast<int>(WindowCode::usingMove));
            currentState.waiting = false;
            updateBattle();
            if (currentState.attacker.isDead() && currentState.defender.isDead())
            {
                if (currentState.defender.getType() == Piece::Type::King)
                {
                    if (currentState.defender.isWhite() == currentState.player1IsWhite)
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player2);
                    }
                    else
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player1);
                    }
                    break;
                }
                if (currentState.attacker.getType() == Piece::Type::King)
                {
                    if (currentState.attacker.isWhite() == currentState.player1IsWhite)
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player2);
                    }
                    else
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player1);
                    }
                    break;
                }
                currentState.board.removePiece(currentState.attackerRow, currentState.attackerCol);
                currentState.board.removePiece(currentState.defenderRow, currentState.defenderCol);
                currentState.windows[10] = currentState.windows[10] = createLabel(currentState.mainWindow, L"Both pieces died",
                    DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
                waitDone(3000);
            }
            else if (currentState.attacker.isDead())
            {
                if (currentState.attacker.getType() == Piece::Type::King)
                {
                    if (currentState.attacker.isWhite() == currentState.player1IsWhite)
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player2);
                    }
                    else
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player1);
                    }
                    break;
                }

                std::string message{};
                if (currentState.attacker.isWhite())
                {
                    message += "White ";
                }
                else
                {
                    message += "Black ";
                }
                message += printType(currentState.attacker.getType()) + " died";
                currentState.windows[10] = currentState.windows[10] = createLabel(currentState.mainWindow, StringToWString(message).c_str(),
                    DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
                currentState.defender.reset();
                currentState.board.removePiece(currentState.attackerRow, currentState.attackerCol);
                waitDone(3000);
            }
            else if (currentState.defender.isDead())
            {
                if (currentState.defender.getType() == Piece::Type::King)
                {
                    if (currentState.defender.isWhite() == currentState.player1IsWhite)
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player2);
                    }
                    else
                    {
                        destroyBattle();
                        createVictoryScreen(Winner::player1);
                    }
                    break;
                }
                std::string message{};
                if (currentState.defender.isWhite())
                {
                    message += "White ";
                }
                else
                {
                    message += "Black ";
                }
                message += printType(currentState.defender.getType()) + " died";
                currentState.windows[10] = currentState.windows[10] = createLabel(currentState.mainWindow, StringToWString(message).c_str(),
                    DESCRIPTIONBOXLEFT, DESCRIPTIONBOXTOP, DESCRIPTIONBOXWIDTH, DESCRIPTIONBOXHEIGHT);
                currentState.attacker.reset();
                currentState.board.movePiece(currentState.attackerRow, currentState.attackerCol, currentState.defenderRow, currentState.defenderCol);
                waitDone(3000);
            }
            else if (!currentState.handledStatus && 
                ((currentState.attackerTurn && currentState.defender.getStatus() != Piece::Status::MAX_STATUSES) || 
                    (!currentState.attackerTurn && currentState.attacker.getStatus() != Piece::Status::MAX_STATUSES)))
            {
                handleStatus();
            }
            else
            {
                if (currentState.singlePlayer)
                {
                    if ((currentState.attackerTurn && (currentState.attacker.isWhite() != currentState.player1IsWhite))
                        || (!currentState.attackerTurn && (currentState.defender.isWhite() != currentState.player1IsWhite)))
                    {
                        changeTurns();
                    }
                    else
                    {
                        currentState.attackerTurn = !currentState.attackerTurn;
                        DestroyWindow(currentState.windows[4]);
                        DestroyWindow(currentState.windows[5]);
                        DestroyWindow(currentState.windows[6]);
                        DestroyWindow(currentState.windows[7]);
                        DestroyWindow(currentState.windows[8]);
                        DestroyWindow(currentState.windows[11]);
                        DestroyWindow(currentState.windows[12]);
                        DestroyWindow(currentState.windows[13]);
                        DestroyWindow(currentState.windows[14]);
                        computerBattle();
                    }
                }
                else
                {
                    changeTurns();
                }
            }
            break;
        }
        case static_cast<int>(WindowCode::finishingBattle) :
        {
            destroyBattle();
            
            if (currentState.singlePlayer && currentState.attacker.isWhite() != currentState.player1IsWhite)
            {
                computerUpdateBoard(currentState.defenderRow, currentState.defenderCol);
            }
            else
            {
                updateBoard(currentState.defenderRow, currentState.defenderCol);
                if (currentState.board.getPiece(currentState.defenderRow, currentState.defenderCol).getType() == Piece::Type::Pawn)
                {
                    if ((currentState.board.getPiece(currentState.defenderRow, currentState.defenderCol).isWhite() && currentState.defenderRow == 0)
                        || (!currentState.board.getPiece(currentState.defenderRow, currentState.defenderCol).isWhite() && currentState.defenderRow == 7))
                    {
                        promotePawn(currentState.defenderRow, currentState.defenderCol);
                    }
                }
            }
            createGameBoard(hwnd);
            
            


            currentState.waitingForInput = false;
            currentState.waiting = false;
            currentState.currentActivity = CurrentActivity::board;

            if (currentState.singlePlayer)
            {
                if (currentState.defender.isWhite() != currentState.player1IsWhite)
                {
                    takeComputerTurn();
                }
            }
            
            KillTimer(currentState.mainWindow, static_cast<int>(WindowCode::finishingBattle));
            break;
        }
        default :
            if (LOWORD(wParam) > SQUARECODE-1 && LOWORD(wParam) < SQUARECODE+64)
            {
                squarePressed((LOWORD(wParam) - SQUARECODE) / 8, (LOWORD(wParam) - SQUARECODE) % 8);
            }
            break;
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        RECT temp{};
        LPRECT coordinates{ &temp };
        GetWindowRect(hwnd, coordinates);
        
        currentState.leftEdge = coordinates->left;
        currentState.rightEdge = coordinates->right;
        currentState.topEdge = coordinates->top;
        currentState.bottomEdge = coordinates->bottom;

        //createLoadoutFile();

        readSavedLoadouts();
        createMainMenu(hwnd);
        break;
    }
    case WM_TIMER :
    case WM_COMMAND:
        buttonPressed(hwnd, wParam);
        break;
    case WM_CLOSE:
        if (currentState.currentActivity == CurrentActivity::mainMenu  || currentState.currentActivity == CurrentActivity::about
            || MessageBox(hwnd, L"Are you sure you want to quit? Game will not be saved.", L"Confirm", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:
        if (currentState.loadoutChanged)
        {
            saveLoadoutChanges();
        }
        PostQuitMessage(0);
        return 0;
        break;
    case WM_PAINT:
    {
        RECT temp{};
        LPRECT coordinates{ &temp };
        GetWindowRect(hwnd, coordinates);
        currentState.leftEdge = coordinates->left;
        currentState.rightEdge = coordinates->right;
        currentState.topEdge = coordinates->top;
        currentState.bottomEdge = coordinates->bottom;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_SIZE :
        adjustButtons(hwnd);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
    return 0;

    
}