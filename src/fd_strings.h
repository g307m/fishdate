#ifndef FD_STRINGS_H
#define FD_STRINGS_H

#define STRENT(s) {(sizeof(s)/sizeof(s[0])-1), s}

struct strent_s {
	const unsigned int len;
	const char* content;
};

static const struct strent_s strings[] = {
	STRENT("0"),
	STRENT("1"),
	STRENT("2"),
	STRENT("3"),
	STRENT("4"),
	STRENT("5"),
	STRENT("6"),
	STRENT("7"),
	STRENT("8")
};

#endif