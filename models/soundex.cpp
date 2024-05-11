#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include <ctype.h>

char *soundex(char *);


char * utf8_replace(char * needle, char * replace, char * haystack) {
	size_t
		len_replace = strlen(replace),
		len_needle = strlen(needle),
		len = strlen(haystack);

	__int32 diff = (__int32)(len_replace - len_needle);

	char * new_string = (char *)calloc(1, (len + diff + 1));

	char * pos = strstr(haystack, needle);

	if (pos == NULL) {
		strcpy((char *) new_string, (char *)haystack);
		return new_string;
	}

	size_t num_shifts = pos - haystack;

	// Add begining of the string
	memcpy(new_string, haystack, num_shifts);

	// Copy the replacement in place of the needle
	memcpy(new_string + num_shifts, replace, len_replace);

	// Copy the remainder of the initial string
	memcpy(new_string + num_shifts + len_replace, pos + len_needle, len - num_shifts - len_needle);

	return new_string;
}

char * utf8_replace_all(char * needle, char * replace, char * haystack) {
	char
		* new_string = utf8_replace(needle, replace, haystack),
		*old_new_string = NULL;

	while (strstr(new_string, needle) != NULL) {
		old_new_string = new_string;
		new_string = utf8_replace(needle, replace, new_string);
		free(old_new_string);
	}

	return new_string;
}

/* for ASCII only */
static char code[128] = { 0 };
void add_code(const char *s, int c)
{
	while (*s) {
		code[(int)*s] = code[0x20 ^ (int)*s] = c;
		s++;
	}
}

void init()
{
	static const char *cls[] =
	{ "AEIOU", "", "BFPV", "CGJKQSXZ", "DT", "L", "MN", "R", 0 };
	int i;
	for (i = 0; cls[i]; i++)
		add_code(cls[i], i - 1);
}

/* returns a static buffer; user must copy if want to save
result across calls */
char *soundex(char *s)
{
	static char out[5];
	int c, prev, i;
	char *s1, *s2;

	s1 = utf8_replace_all("┼ş", "s", s);
	s2 = utf8_replace_all("┼Ş", "S", s1);
	s1 = utf8_replace_all("├Â", "ö", s2);
	s2 = utf8_replace_all("├û", "O", s1);
	s1 = utf8_replace_all("ü", "u", s2);
	s2 = utf8_replace_all("─▒", "ı", s1);
	s1 = utf8_replace_all("├ğ", "c", s2);

	out[0] = out[4] = 0;
	if (!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for (i = 1; *s && i < 4; s++) {
		if ((c = code[(int)*s1]) == prev) continue;

		if (c == -1) prev = 0;	/* vowel as separator */
		else if (c > 0) {
			out[i++] = c + '0';
			prev = c;
		}
	}
	while (i < 4) out[i++] = '0';
	return out;
}