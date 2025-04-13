#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

unordered_map<wstring, wstring> ConsonantMap;
unordered_map<wstring, wstring> VowelMap;
unordered_map<wstring, wstring> ReverseConsonantMap;
unordered_map<wstring, wstring> ReverseVowelMap;

void InitializeMappings() {
    ConsonantMap[L"B"] = L"Б";
    ConsonantMap[L"P"] = L"П";
    ConsonantMap[L"M"] = L"М";
    ConsonantMap[L"F"] = L"Ф";
    ConsonantMap[L"D"] = L"Д";
    ConsonantMap[L"T"] = L"Т";
    ConsonantMap[L"N"] = L"Н";
    ConsonantMap[L"L"] = L"Л";
    ConsonantMap[L"G"] = L"Г";
    ConsonantMap[L"K"] = L"К";
    ConsonantMap[L"H"] = L"Х";
    ConsonantMap[L"J"] = L"Й";
    ConsonantMap[L"Q"] = L"Ъ";
    ConsonantMap[L"X"] = L"Щ";
    ConsonantMap[L"Z"] = L"З";
    ConsonantMap[L"C"] = L"Ц";
    ConsonantMap[L"S"] = L"С";
    ConsonantMap[L"ZH"] = L"Ж";
    ConsonantMap[L"CH"] = L"Ч";
    ConsonantMap[L"SH"] = L"Ш";
    ConsonantMap[L"R"] = L"Р";
    ConsonantMap[L"Y"] = L"Я";
    ConsonantMap[L"W"] = L"В";
    ConsonantMap[L""] = L"О";
    VowelMap[L"A"] = L"А";
    VowelMap[L"AI"] = L"Б";
    VowelMap[L"AN"] = L"Н";
    VowelMap[L"ANG"] = L"Г";
    VowelMap[L"AO"] = L"У";
    VowelMap[L"E"] = L"Э";
    VowelMap[L"EI"] = L"Й";
    VowelMap[L"EN"] = L"Д";
    VowelMap[L"ENG"] = L"Ж";
    VowelMap[L"ER"] = L"Р";
    VowelMap[L"I"] = L"И";
    VowelMap[L"IA"] = L"Я";
    VowelMap[L"IAN"] = L"П";
    VowelMap[L"IANG"] = L"В";
    VowelMap[L"IAO"] = L"С";
    VowelMap[L"IE"] = L"З";
    VowelMap[L"IN"] = L"М";
    VowelMap[L"ING"] = L"Ы";
    VowelMap[L"IONG"] = L"Л";
    VowelMap[L"IU"] = L"Ю";
    VowelMap[L"O"] = L"О";
    VowelMap[L"ONG"] = L"К";
    VowelMap[L"OU"] = L"Ф";
    VowelMap[L"U"] = L"Е";
    VowelMap[L"UA"] = L"Ц";
    VowelMap[L"UAI"] = L"Ч";
    VowelMap[L"UAN"] = L"Щ";
    VowelMap[L"UANG"] = L"Ш";
    VowelMap[L"UE"] = L"Т";
    VowelMap[L"UI"] = L"Ъ";
    VowelMap[L"UN"] = L"Ь";
    VowelMap[L"UO"] = L"Х";
    VowelMap[L"V"] = L"Ё";

    for (const auto& pair : ConsonantMap) {
        ReverseConsonantMap[pair.second] = pair.first;
    }
    for (const auto& pair : VowelMap) {
        ReverseVowelMap[pair.second] = pair.first;
    }
}

// Custom functions for Cyrillic case conversion
bool IsCyrillicUpper(wchar_t ch) {
    return (ch >= L'А' && ch <= L'Я') || ch == L'Ё' || ch == L'Ъ' || ch == L'Ы' || ch == L'Ь';
}

bool IsCyrillicLower(wchar_t ch) {
    return (ch >= L'а' && ch <= L'я') || ch == L'ё' || ch == L'ъ' || ch == L'ы' || ch == L'ь';
}

wchar_t CyrillicToUpper(wchar_t ch) {
    if (IsCyrillicLower(ch)) {
        // Convert lowercase Cyrillic to uppercase
        if (ch == L'ё') return L'Ё';
        if (ch == L'ъ') return L'Ъ';
        if (ch == L'ы') return L'Ы';
        if (ch == L'ь') return L'Ь';
        return ch - (L'а' - L'А'); // Standard offset between lowercase and uppercase Cyrillic
    }
    return towupper(ch); // Use standard for non-Cyrillic
}

wchar_t CyrillicToLower(wchar_t ch) {
    if (IsCyrillicUpper(ch)) {
        // Convert uppercase Cyrillic to lowercase
        if (ch == L'Ё') return L'ё';
        if (ch == L'Ъ') return L'ъ';
        if (ch == L'Ы') return L'ы';
        if (ch == L'Ь') return L'ь';
        return ch + (L'а' - L'А'); // Standard offset between uppercase and lowercase Cyrillic
    }
    return towlower(ch); // Use standard for non-Cyrillic
}

// Improved function to check if character is uppercase (handles both Latin and Cyrillic)
bool IsUpperChar(wchar_t ch) {
    return iswupper(ch) || IsCyrillicUpper(ch);
}

// Improved function to check if character is lowercase (handles both Latin and Cyrillic)
bool IsLowerChar(wchar_t ch) {
    return iswlower(ch) || IsCyrillicLower(ch);
}

// Improved function to convert character to uppercase (handles both Latin and Cyrillic)
wchar_t ToUpperChar(wchar_t ch) {
    return IsCyrillicLower(ch) ? CyrillicToUpper(ch) : towupper(ch);
}

// Improved function to convert character to lowercase (handles both Latin and Cyrillic)
wchar_t ToLowerChar(wchar_t ch) {
    return IsCyrillicUpper(ch) ? CyrillicToLower(ch) : towlower(ch);
}

// Get uppercase version of a string
wstring ToUpper(const wstring& str) {
    wstring result = str;
    for (auto& c : result) {
        c = ToUpperChar(c);
    }
    return result;
}

// Check if a character is Cyrillic
bool IsCyrillic(wchar_t ch) {
    return IsCyrillicUpper(ch) || IsCyrillicLower(ch);
}

// Check if a word follows valid Pinyin syllable format
bool IsValidPinyinSyllable(const wstring& word) {
    // Must have at least 2 characters (at least one letter and one digit)
    if (word.length() < 2) return false;

    // Last character must be a digit (tone)
    if (!iswdigit(word.back())) return false;

    // All characters before the last must be letters
    for (size_t i = 0; i < word.length() - 1; i++) {
        if (!iswalpha(word[i])) return false;
    }

    // Check if the word has a valid structure (consonant + vowel)
    wstring syllable = word.substr(0, word.length() - 1);
    // Use our improved ToUpper function instead of manual conversion
    wstring upperSyllable = ToUpper(syllable);

    // Special case for vowel-only syllables like "A1"
    if (upperSyllable.length() == 1 &&
        (upperSyllable[0] == L'A' || upperSyllable[0] == L'E' ||
            upperSyllable[0] == L'I' || upperSyllable[0] == L'O' ||
            upperSyllable[0] == L'U' || upperSyllable[0] == L'V')) {
        return true;
    }

    // Try to identify a valid consonant at the beginning
    bool hasValidConsonant = false;

    // Try two-letter consonants first (ZH, CH, SH)
    if (upperSyllable.length() >= 2) {
        wstring twoLetters = upperSyllable.substr(0, 2);
        if (ConsonantMap.find(twoLetters) != ConsonantMap.end()) {
            hasValidConsonant = true;
        }
    }

    // If no two-letter match, try one-letter consonant
    if (!hasValidConsonant && !upperSyllable.empty()) {
        wstring oneLetter = upperSyllable.substr(0, 1);
        if (ConsonantMap.find(oneLetter) != ConsonantMap.end()) {
            hasValidConsonant = true;
        }
    }

    return hasValidConsonant;
}

// Check if a word follows valid Cyrillic syllable format
bool IsValidCyrillicSyllable(const wstring& word) {
    // Must have exactly 3 characters (consonant, vowel, and tone)
    if (word.length() != 3) return false;

    // Last character must be a digit (tone)
    if (!iswdigit(word.back())) return false;

    // First two characters must be Cyrillic letters
    if (!IsCyrillic(word[0]) || !IsCyrillic(word[1])) return false;

    return true;
}

// Translate Pinyin to Cyrillic
wstring TranslatePinyinToCyrillic(const wstring& word) {
    // If not a valid Pinyin syllable format, return as is
    if (!IsValidPinyinSyllable(word)) {
        return word;
    }

    // Extract the tone (last character)
    wstring tone = word.substr(word.length() - 1);
    wstring syllable = word.substr(0, word.length() - 1);

    // Store the original case pattern
    bool isAllUpper = true;
    for (auto c : syllable) {
        if (IsLowerChar(c)) {
            isAllUpper = false;
            break;
        }
    }

    // Convert to uppercase for mapping
    wstring upperSyllable = ToUpper(syllable);

    // Find the longest matching consonant
    wstring consonant;
    wstring remainingVowel = upperSyllable;

    // Special case for words starting with vowels - use empty consonant
    if (!upperSyllable.empty() && (
        upperSyllable[0] == L'A' || upperSyllable[0] == L'E' ||
        upperSyllable[0] == L'I' || upperSyllable[0] == L'O' ||
        upperSyllable[0] == L'U' || upperSyllable[0] == L'V')) {
        consonant = L"";
    }
    else {
        // Try two-letter consonants first (ZH, CH, SH)
        if (upperSyllable.length() >= 2) {
            wstring twoLetters = upperSyllable.substr(0, 2);
            if (ConsonantMap.find(twoLetters) != ConsonantMap.end()) {
                consonant = twoLetters;
                remainingVowel = upperSyllable.substr(2);
            }
        }

        // If no two-letter match, try one-letter consonant
        if (consonant.empty() && !upperSyllable.empty()) {
            wstring oneLetter = upperSyllable.substr(0, 1);
            if (ConsonantMap.find(oneLetter) != ConsonantMap.end()) {
                consonant = oneLetter;
                remainingVowel = upperSyllable.substr(1);
            }
        }
    }

    // The remaining part should be the vowel
    wstring vowel = remainingVowel;

    // Only translate if both parts have valid mappings
    wstring translatedConsonant;
    wstring translatedVowel;

    if (ConsonantMap.count(consonant) && VowelMap.count(vowel)) {
        translatedConsonant = ConsonantMap[consonant];
        translatedVowel = VowelMap[vowel];
    }
    else {
        // If no valid mapping, return original word
        return word;
    }

    // Combine translated parts
    wstring result = translatedConsonant + translatedVowel + tone;

    // Apply the original case pattern
    if (!isAllUpper) {
        for (auto& c : result) {
            if (iswalpha(c) || IsCyrillic(c)) {
                c = ToLowerChar(c);
            }
        }
    }

    return result;
}

// Translate Cyrillic to Pinyin
wstring TranslateCyrillicToPinyin(const wstring& word) {
    // If not a valid Cyrillic syllable format, return as is
    if (!IsValidCyrillicSyllable(word)) {
        return word;
    }

    // Extract the tone (last character)
    wstring tone = word.substr(word.length() - 1);
    wstring consonant = word.substr(0, 1);
    wstring vowel = word.substr(1, 1);

    // Store the original case pattern
    bool isAllUpper = IsUpperChar(consonant[0]) && IsUpperChar(vowel[0]);

    // Convert to uppercase for mapping
    wstring upperConsonant = ToUpper(consonant);
    wstring upperVowel = ToUpper(vowel);

    // Only translate if both parts have valid mappings
    wstring translatedConsonant;
    wstring translatedVowel;

    if (ReverseConsonantMap.count(upperConsonant) && ReverseVowelMap.count(upperVowel)) {
        translatedConsonant = ReverseConsonantMap[upperConsonant];
        translatedVowel = ReverseVowelMap[upperVowel];
    }
    else {
        // If no valid mapping, return original word
        return word;
    }

    // Combine translated parts
    wstring result = translatedConsonant + translatedVowel + tone;

    // Apply the original case pattern
    if (!isAllUpper) {
        for (auto& c : result) {
            if (iswalpha(c) || IsCyrillic(c)) {
                c = ToLowerChar(c);
            }
        }
    }

    return result;
}

// Custom function to check if a character is alphanumeric (including Cyrillic)
bool IsAlphaNumericChar(wchar_t ch) {
    return iswalpha(ch) || IsCyrillic(ch) || iswdigit(ch);
}

// Main translation function
wstring TranslateText(const wstring& input) {
    // Initialize the mapping tables
    InitializeMappings();

    wstring result;
    wstring currentWord;
    bool inWord = false;

    // Process each character in the input
    for (size_t i = 0; i < input.length(); i++) {
        wchar_t ch = input[i];

        // If we're in a word and encounter a non-alphanumeric character, process the word
        if (inWord && !IsAlphaNumericChar(ch)) {
            // Translate the word if it's in valid format
            if (!currentWord.empty()) {
                if (IsCyrillic(currentWord[0])) {
                    result += TranslateCyrillicToPinyin(currentWord);
                }
                else {
                    result += TranslatePinyinToCyrillic(currentWord);
                }
            }

            // Add the non-alphanumeric character
            result += ch;

            currentWord.clear();
            inWord = false;
        }
        // If we're in a word and encounter an alphanumeric character, add to current word
        else if (inWord) {
            currentWord += ch;
        }
        // If we're not in a word and encounter an alphanumeric character, start a new word
        else if (IsAlphaNumericChar(ch)) {
            currentWord += ch;
            inWord = true;
        }
        // If we're not in a word and encounter a non-alphanumeric character, add it directly
        else {
            result += ch;
        }
    }

    // Process any remaining word
    if (inWord && !currentWord.empty()) {
        if (IsCyrillic(currentWord[0])) {
            result += TranslateCyrillicToPinyin(currentWord);
        }
        else {
            result += TranslatePinyinToCyrillic(currentWord);
        }
    }

    return result;
}

// Control IDs
#define IDC_STATIC_INPUT       999
#define IDC_STATIC_OUTPUT      998
#define IDC_EDIT_INPUT         997
#define IDC_EDIT_OUTPUT        996

// Global handles to our controls
HWND hStaticInput, hStaticOutput, hEditInput, hEditOutput;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hStaticInput = CreateWindow(
            L"STATIC",
            L"SHU1 RU4 / ШЕ1 РЕ4:",
            WS_CHILD | WS_VISIBLE,
            0, 0, 0, 0,
            hWnd,
            (HMENU)IDC_STATIC_INPUT,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        hStaticOutput = CreateWindow(
            L"STATIC",
            L"SHU1 CHU1 / ШЕ1 ЧЕ1:",
            WS_CHILD | WS_VISIBLE,
            0, 0, 0, 0,
            hWnd,
            (HMENU)IDC_STATIC_OUTPUT,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        hEditInput = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            L"EDIT",
            L"",
            WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            0, 0, 0, 0,
            hWnd,
            (HMENU)IDC_EDIT_INPUT,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        hEditOutput = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            L"EDIT",
            L"",
            WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
            0, 0, 0, 0,
            hWnd,
            (HMENU)IDC_EDIT_OUTPUT,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
    }
    break;

    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        int margin = 10;
        int labelHeight = 20;
        int spacing = 5;
        int columnWidth = (width - 3 * margin) / 2;
        int editHeight = height - (margin + labelHeight + spacing + margin);
        MoveWindow(hStaticInput, margin, margin, columnWidth, labelHeight, TRUE);
        MoveWindow(hEditInput, margin, margin + labelHeight + spacing, columnWidth, editHeight, TRUE);
        int secondColumnX = margin * 2 + columnWidth;
        MoveWindow(hStaticOutput, secondColumnX, margin, columnWidth, labelHeight, TRUE);
        MoveWindow(hEditOutput, secondColumnX, margin + labelHeight + spacing, columnWidth, editHeight, TRUE);
    }
    break;

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDC_EDIT_INPUT && HIWORD(wParam) == EN_CHANGE)
        {
            int length = GetWindowTextLength(hEditInput);
            wstring inputText(length + 1, L'\0');
            GetWindowText(hEditInput, &inputText[0], length + 1);
            wstring outputText = TranslateText(inputText);
            SetWindowText(hEditOutput, outputText.c_str());
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"DoubleArinoglishTranslator";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    HWND hWnd = CreateWindowEx(
        NULL,
        CLASS_NAME,
        L"ARINOGLISH+ ШШ1 ПМ1 ФБ1 ЯИ4 ЪИ4",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}