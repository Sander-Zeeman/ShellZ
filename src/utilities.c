#include "utilities.h"
#include <stdio.h>
char *copy(char *str) {
	int len;

	for (len = 1; *str != '\0'; len++) {
		str++;
	}
	str -= (len - 1);

	char *newStr = malloc(len * sizeof(char));
	for (int i = 0; i < len; i++) {
		newStr[i] = str[i];
	}
	newStr[len - 1] = '\0';

	return newStr;
}

bool compare(char *str1, char *str2) {
    int i;
    if (!(str1 && str2)) {
		return FALSE;
    }

    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
		if (str1[i] != str2[i])
		    return FALSE;
    }

    return str1[i] == str2[i];
}
