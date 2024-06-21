#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <TradeRecord.h>
#include <StringConverter.h>

#define MAX_TRADE_RECORDS 1024
#define MAX_LINE_COUNT 1024


char **ReadTradeDataFromCsv(FILE *stream)
{
    char **lines = NULL;
    char line[MAX_LINE_LENGTH];
    int capacity = INITIAL_CAPACITY;
    int count = 0;

    // Allocate memory forarray of lines
    lines = (char **)malloc(capacity * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    while (fgets(line, sizeof(line), stream)) {
        // Allocate memory for the line
        lines[count] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        memcpy(lines[count] , line, strlen(line));
        count++;
    }

    return lines;
}

Trade_Record* mapCsvLineDataToTradeData(char **lineInFile)
{
    Trade_Record *tradeData;
    tradeData = (Trade_Record*) malloc (numoflines * sizeof(tradeData));
    char* fields[3];
    int fieldCount = 0;

    int index = 0;
    for (index = 0; index < MAX_LINE_COUNT ; index++)
    {
        fieldCount = 0;
        char* token = strtok( lineInFile[index] , ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }
        Records[currentRecord].Lots = tradeamount / LotSize;// Need to check this is required or not
       
        memcpy(tradeData[index].Source_Currency, fields[0] , strlen(fields[0]));
        memcpy(tradeData[index].Destibation_Currency, fields[0]+3 , strlen(fields[0]))
        memcpy(tradeData[index].tradeAmount, fields[1] , strlen(fields[0]));
        memcpy(tradeData[index].tradePrice, fields[2] , strlen(fields[0]));
    }

    return tradeData;
}

void validateTradeData(TradeRecord *records)
{
        char* fields[3];
        int fieldCount = 0;   
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
}

void WriteXML(TradeRecord *records) 
{
    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int i = 0; i < MAX_TRADE_RECORDS; i++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", records[i].SourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", records[i].DestinationCurrency);
        //fprintf(outFile, "\t\t<Lots>%d</Lots>\n", records[i].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", records[i].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
}
void ConvertDatafromCsvtoXML(FILE* stream) {
    
    Trade_Record *Records;
    int lineCount = 0;
    char * line[];
    line[] = readTradeDataFromCsv(stream);
    validateTradeData(Records);
    Records = mapCsvLineDataToTradeData(line[],);
    writeTradeDataToXML(Records);
           
}

