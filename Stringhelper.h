char** SplitString(const char* inputstring, char delimiter) {
    int Delimiter_count = 0;
    const char* string = inputstring;
    while (*string != '\0') {
        if (*string++ == delimiter) {
            Delimiter_count++;
        }
    }

    char** tokens = (char**)malloc(sizeof(char*) * (String_count + 2));
    int tokenset = 0;
    string = inputstring;
    char* token = (char*)malloc(strlen(str) + 1);
    int tokeniterator = 0;
    while (*string != '\0') {
        if (*string == delimiter) {
            token[tokeniterator] = '\0';
            tokens[tokenset++] = strdup(token);
            tokeniterator = 0;
        } else {
            token[tokeniterator++] = *string;
        }
        string++;
    }
    token[tokeniterator] = '\0';
    tokens[tokenset++] = strdup(token);
    tokens[tokenset] = NULL;
    free(token);
    return tokens;
}
