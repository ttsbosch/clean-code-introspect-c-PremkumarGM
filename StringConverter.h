bool TrytoConvertintoint(const char* inputstring, int* output_Integervalue) {
    char* Convertion;
    *output_Integervalue = strtol(inputstring, &Convertion, 10);
    if (Convertion == inputstring) {
        return 0;
    }
    return 1;
}

bool TrytoConvertintoDouble(const char* inputstring, double* output_doublevalue) {
    char* Convertion;
    *output_doublevalue = strtod(inputstring, &Convertion);
    if (Convertion == inputstring) {
        return 0;
    }
    return 1;
}
