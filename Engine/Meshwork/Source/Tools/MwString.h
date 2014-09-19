#pragma once

#include "..\MwGlobals.h"

// TODO Consider moving the member variables to private

class MWDLLCLASS MwString
{
private:
	void Initialize();

public:
	wchar_t &operator [] (int index);

	// MwString operators
	void operator = (const MwString &argument);
	void operator += (const MwString &argument);
	MwString operator + (const MwString &argument);
	bool operator == (const MwString &argument);
	bool operator != (const MwString &argument);
	bool operator > (const MwString &argument);
	bool operator >= (const MwString &argument);
	bool operator < (const MwString &argument);
	bool operator <= (const MwString &argument);

	// WChar operators
	void operator = (const wchar_t *argument);
	void operator += (const wchar_t *argument);
	MwString operator + (const wchar_t *argument);
	bool operator == (const wchar_t *argument);
	bool operator != (const wchar_t *argument);
	bool operator > (const wchar_t *argument);
	bool operator >= (const wchar_t *argument);
	bool operator < (const wchar_t *argument);
	bool operator <= (const wchar_t *argument);

	// Char operators
	void operator = (const char *argument);
	void operator += (const char *argument);
	MwString operator + (const char *argument);
	bool operator == (const char *argument);
	bool operator != (const char *argument);
	bool operator > (const char *argument);
	bool operator >= (const char *argument);
	bool operator < (const char *argument);
	bool operator <= (const char *argument);

	int length, capacity;
	wchar_t *contents;
	
	int charContentsCapacity;
	bool charContentsChanged;
	char *charContents;

	MwString(void);
	MwString(MwString &str);
	MwString(const char *str);
	MwString(const wchar_t *str);
	MwString(const char *str, int length);
	MwString(const wchar_t *str, int length);
	MwString(char str);
	MwString(wchar_t str);
	MwString(int value, int radix = 10);
	MwString(unsigned int value, int radix = 10);
	MwString(long long value, int radix = 10);
	MwString(unsigned long long value, int radix = 10);
	MwString(double value);
	~MwString(void);

	// Sets capacity exactly to the desired amount	
	void ResizeCapacity(int newCapacity, bool keepContents = true);
	// Makes sure there is the amount of capacity deisred. If the desired capacity already fits in the current one, no change is made
	void EnsureCapacity(int length);
	// Sets the length of the string. If the new length is greater than the current one, the added characters are undefined
	void SetLength(int length);
	int GetLength();

	bool IsEmpty();
	
	const wchar_t *GetContents();
	const char *GetCharContents();

	void InsertCharacters(int position, int count);

	void CopyCharacters(int offset, const MwString &source, int sourceOffset, int count);
	void CopyCharacters(int offset, const char *source, int sourceOffset, int count);
	void CopyCharacters(int offset, const wchar_t *source, int sourceOffset, int count);

	void FillCharacters(int offset, const char fillChar, int count);
	void FillCharacters(int offset, const wchar_t fillChar, int count);

	int Compare(const MwString &str);
	int Compare(const char *str);
	int Compare(const wchar_t *str);

	bool Equals(const MwString &str);
	bool Equals(const char *str);
	bool Equals(const wchar_t *str);

	void Copy(const MwString &source);
	void Copy(const char *source);
	void Copy(const wchar_t *source);

	void Insert(const MwString &source, int position = -1, int count = -1);
	void Insert(const char *source, int position = -1, int count = -1);
	void Insert(const wchar_t *source, int position = -1, int count = -1);

	int IndexOf(const MwString &substr, int start = 0);
	int IndexOf(const char *substr, int start = 0);
	int IndexOf(const wchar_t *substr, int start = 0);

	int LastIndexOf(const MwString &substr, int start = -1);
	int LastIndexOf(const char *substr, int start = -1);
	int LastIndexOf(const wchar_t *substr, int start = -1);

	MwString SubString(int start, int count);
	MwString Remove(int start, int count);

	MwString Remove(const MwString &str);
	MwString Remove(const char *str);
	MwString Remove(const wchar_t *str);

	MwString Replace(const MwString &str, const MwString &substitute);
	MwString Replace(const char *str, const char *substitute);
	MwString Replace(const wchar_t *str, const wchar_t *substitute);

	MwString PadLeft(int minLength, const char fillChar);
	MwString PadLeft(int minLength, const wchar_t fillChar);

	MwString PadRight(int minLength, const char fillChar);
	MwString PadRight(int minLength, const wchar_t fillChar);

	bool StartsWith(const MwString &str);
	bool StartsWith(const char *str);
	bool StartsWith(const wchar_t *str);
	bool StartsWith(const char chr);
	bool StartsWith(const wchar_t chr);
	
	bool EndsWith(const MwString &str);
	bool EndsWith(const char *str);
	bool EndsWith(const wchar_t *str);
	bool EndsWith(const char chr);
	bool EndsWith(const wchar_t chr);
	
	MwString Trim(const char chr, bool left = true, bool right = true);
	MwString Trim(const wchar_t chr, bool left = true, bool right = true);
	
	bool ToInt(int &value, int radix = 10);
	bool ToUInt(unsigned int &value, int radix = 10);
	bool ToFloat(float &value);
	bool ToDouble(double &value);

	MwString ToLower();
	MwString ToUpper();

	MwString ToBase64();
	MwString FromBase64();

	static char *CopyNew(const char *source);
	static wchar_t *CopyNew(const wchar_t *source);
	static void Dispose(char **str);
	static void Dispose(wchar_t **str);

	static int GetLength(const wchar_t *str);
	static int GetLength(const char *str);

	static int ToInt(char *str, char **end, int radix = 10);
	static int ToInt(wchar_t *str, wchar_t **end, int radix = 10);
	static unsigned int ToUInt(char *str, char **end, int radix = 10);
	static unsigned int ToUInt(wchar_t *str, wchar_t **end, int radix = 10);
	static double ToDouble(char *str, char **end);
	static double ToDouble(wchar_t *str, wchar_t **end);

	static MwString ToBase64(const void *data, unsigned int dataSize);
	static bool FromBase64(MwString &base64String, void **data, unsigned int &dataSize);

	//static MwString Format(const wchar_t *formatString, ...);
};

