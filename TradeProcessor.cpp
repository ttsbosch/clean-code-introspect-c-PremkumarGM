#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <TradeRecord.h>

#define MAX_TRADE_RECORDS 1024
#define MAX_LINE_LENGTH 1024
#define CURRENCY_LENGTH 3



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

void ConvertDatafromCsvtoXML(FILE* stream) {
    char line[MAX_LINE_LENGTH];
    Trade_Record Records[MAX_TRADE_RECORDS];
    int lineCount = 0;
    int currentRecord = 0;

    while (fgets(line, sizeof(line), stream)) {
        char* fields[3];
        int fieldCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        if (fieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, fieldCount);
            continue;
        }

        if (strlen(fields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, fields[0]);
            continue;
        }

        int tradeamount;
        if (!TrytoConvertintoint(fields[1], &tradeamount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, fields[1]);
        }

        double tradeprice;
        if (!TrytoConvertintoDouble(fields[2], &tradeprice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, fields[2]);
        }

        strncpy(Records[currentRecord].Source_Currency, fields[0], 3);
        strncpy(Records[currentRecord].Destibation_Currency, fields[0] + 3, 3);
        Records[currentRecord].Lots = tradeamount / LotSize;
        Records[currentRecord].Price = tradeprice;
        currentRecord++;
        lineCount++;
    }

    FILE* outFile = fopen("outradepriceut.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int TradeRecord_index = 0; TradeRecord_index < currentRecord; TradeRecord_index++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", Records[TradeRecord_index].Source_Currency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", Records[TradeRecord_index].Destibation_Currency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", Records[TradeRecord_index].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", Records[TradeRecord_index].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades ConvertDatafromCsvtoXMLed\n", currentRecord);
}

