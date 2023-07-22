#pragma once

#include <string>
#include <windows.h>
#include "scintilla/Scintilla.h"
#include "plugin/PluginDefinition.h"

class ScintillaAdapter
{
public:
	explicit ScintillaAdapter(const NppData& nppData);
	virtual ~ScintillaAdapter() = default;

	ScintillaAdapter() = delete;
	ScintillaAdapter(ScintillaAdapter const&) = delete;
	ScintillaAdapter& operator=(ScintillaAdapter const&) = delete;

	std::string GetSelectedText() const;
	bool ReplaceSelectedText(const std::string& replaceText) const;

	LRESULT Execute(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0) const;
	LRESULT SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	int MessageBox(LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);

private:
	Sci_CharacterRangeFull GetSelection() const;
	char* GetSelectedText(char* txt, int size, bool expand = true) const;
	char* GetWordFromRange(char* txt, size_t size, size_t pos1, size_t pos2) const;
	bool ExpandWordSelection() const;
	std::pair<int, int> GetWordRange() const;
	void GetText(char* dest, size_t start, size_t end) const;

private:
	NppData m_nppData = {};
	HWND m_hScintilla = nullptr;
};

