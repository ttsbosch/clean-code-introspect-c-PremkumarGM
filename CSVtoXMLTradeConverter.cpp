#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <TradeRecord.h>
#include <StringConverter.h>

#define MAX_TRADE_RECORDS 1024
#define MAX_LINE_LENGTH 1024

void readTradeDataFromCsv(FILE* stream)
{
while (fgets(line, sizeof(line), stream)) {
        
        int fieldCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }
}
}
void validateTradeData(void)
{
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
void   mapCsvLineDataToTradeData(void)
{
        strncpy(Records[currentRecord].Source_Currency, fields[0], 3);
        strncpy(Records[currentRecord].Destibation_Currency, fields[0] + 3, 3);
        Records[currentRecord].Lots = tradeamount / LotSize;
        Records[currentRecord].Price = tradeprice;
        currentRecord++;
        lineCount++;
}
void writeTradeDataToXML(void)
{
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
void ConvertDatafromCsvtoXML(FILE* stream) {
    char line[MAX_LINE_LENGTH];
    Trade_Record Records[MAX_TRADE_RECORDS];
    int lineCount = 0;
    int currentRecord = 0;
    char* fields[3];
    readTradeDataFromCsv(stream);
    validateTradeData();
    mapCsvLineDataToTradeData();
    writeTradeDataToXML();
           
}

