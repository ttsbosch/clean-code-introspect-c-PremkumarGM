char** SplitString(const char* inputstring, char delimiter) {
    int delimiter_count = 0;
    const char* string = inputstring;

    // Count the number of delimiters to determine the number of tokens
    while (*string != '\0') {
        if (*string == delimiter) {
            delimiter_count++;
        }
        string++;
    }

    // Allocate memory for an array of string pointers (tokens)
    char** tokens = (char**)malloc(sizeof(char*) * (delimiter_count + 2));
    if (tokens == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Parse the input string and split into tokens
    int token_index = 0;
    const char* token_start = inputstring;

    while (*inputstring != '\0') {
        if (*inputstring == delimiter) {
            // Calculate length of token
            int token_length = inputstring - token_start;
            // Allocate memory for token and copy it
            tokens[token_index] = (char*)malloc(token_length + 1);
            if (tokens[token_index] == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strncpy(tokens[token_index], token_start, token_length);
            tokens[token_index][token_length] = '\0';
            // Move to next token
            token_start = inputstring + 1;
            token_index++;
        }
        inputstring++;
    }

    // Handle the last token
    int last_token_length = inputstring - token_start;
    tokens[token_index] = (char*)malloc(last_token_length + 1);
    if (tokens[token_index] == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(tokens[token_index], token_start, last_token_length);
    tokens[token_index][last_token_length] = '\0';
    token_index++;

    // Set the last element of tokens array to NULL to indicate end of tokens
    tokens[token_index] = NULL;

    return tokens;
}

