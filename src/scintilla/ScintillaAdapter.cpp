#include "ScintillaAdapter.h"

#include <cassert>
#include <memory>
#include <utility>

ScintillaAdapter::ScintillaAdapter(const NppData& nppData) : m_nppData(nppData)
{
	int which = -1;
	::SendMessage(m_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, reinterpret_cast<LPARAM>(&which));
	assert(which != -1);
	if (which != -1)
		m_hScintilla = (which == 0) ? m_nppData._scintillaMainHandle : m_nppData._scintillaSecondHandle;
}

std::string ScintillaAdapter::GetSelectedText() const
{
	if (!m_hScintilla)
		return std::string();

	// Get the required length
	auto length = Execute(SCI_GETLENGTH);

	auto pData = std::make_unique<char[]>(length + 1);
	GetSelectedText(pData.get(), static_cast<int>(length + 1), false);

	return pData ? pData.get() : "";
}

bool ScintillaAdapter::ReplaceSelectedText(const std::string& replaceText) const
{
	return Execute(SCI_REPLACESEL, 0, reinterpret_cast<LPARAM>(replaceText.c_str())) == 0;
}

LRESULT ScintillaAdapter::Execute(UINT Msg, WPARAM wParam, LPARAM lParam) const
{
	if (!m_hScintilla)
		return -1;

	try
	{
		return ::SendMessage(m_hScintilla, Msg, wParam, lParam);
	}
	catch (...)
	{
		return -1;
	}
}

char* ScintillaAdapter::GetSelectedText(char* txt, int size, bool expand) const {
	if (!size)
		return NULL;
	auto range = GetSelection();
	if (range.cpMax == range.cpMin && expand)
	{
		ExpandWordSelection();
		range = GetSelection();
	}
	if (!(static_cast<Sci_Position>(size) > (range.cpMax - range.cpMin)))	//there must be atleast 1 byte left for zero terminator
	{
		range.cpMax = range.cpMin + size - 1;	//keep room for zero terminator
	}

	return GetWordFromRange(txt, size, range.cpMin, range.cpMax);
}


auto ScintillaAdapter::GetWordFromRange(char* txt, size_t size, size_t pos1, size_t pos2) const-> char*
{
	if (!size)
		return NULL;
	if (pos1 > pos2)
	{
		auto tmp = pos1;
		pos1 = pos2;
		pos2 = tmp;
	}

	if (size < pos2 - pos1)
		return NULL;

	GetText(txt, pos1, pos2);
	return txt;
}

bool ScintillaAdapter::ExpandWordSelection() const
{
	std::pair<int, int> wordRange = GetWordRange();
	if (wordRange.first != wordRange.second)
	{
		Execute(SCI_SETSELECTIONSTART, wordRange.first);
		Execute(SCI_SETSELECTIONEND, wordRange.second);
		return true;
	}
	return false;
}

std::pair<int, int> ScintillaAdapter::GetWordRange() const
{
	auto caretPos = Execute(SCI_GETCURRENTPOS, 0, 0);
	int startPos = static_cast<int>(Execute(SCI_WORDSTARTPOSITION, caretPos, true));
	int endPos = static_cast<int>(Execute(SCI_WORDENDPOSITION, caretPos, true));
	return std::pair<int, int>(startPos, endPos);
}

void ScintillaAdapter::GetText(char* dest, size_t start, size_t end) const
{
	Sci_TextRangeFull tr;
	tr.chrg.cpMin = static_cast<long>(start);
	tr.chrg.cpMax = static_cast<long>(end);
	tr.lpstrText = dest;
	Execute(SCI_GETTEXTRANGEFULL, 0, reinterpret_cast<LPARAM>(&tr));
}

Sci_CharacterRangeFull ScintillaAdapter::GetSelection() const
{
	Sci_CharacterRangeFull charRange;
	charRange.cpMin = static_cast<long>(Execute(SCI_GETSELECTIONSTART));
	charRange.cpMax = static_cast<long>(Execute(SCI_GETSELECTIONEND));
	return charRange;
}

LRESULT ScintillaAdapter::SendMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	return ::SendMessage(m_hScintilla, msg, wParam, lParam);
}

int ScintillaAdapter::MessageBox(LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
	return ::MessageBox(m_hScintilla, lpText, lpCaption, uType);
}