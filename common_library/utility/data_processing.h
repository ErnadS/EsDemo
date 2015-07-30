/*
 * DataProcessing.h
 *
 *  Created on: Aug 3, 2011
 *      Author: ernad
 */

#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

class DataProcessing {
public:
	DataProcessing();
	virtual ~DataProcessing();

    static void kalmanFilter(char *inArray, int dataLength, char *outArray);
    static int bottomDetection(char *inArray, int dataLength);

private:
    static int getMaxDiff(char* inArray, int arrayLenght);
    static void getSegmentsArray(char *inArray, int segmentsCount, int segmLeng, int* segmArray);
	static int getTopSegment(int* inArray, int dataLength);

    static int getBottomStartIndex(char* inArray, int segmentIndex, int segmentLength);
    static int getTopInsideSegment(char* inArray, int arrayLenght);
    static int getIncreasingStart(char* inArray, int topIndex, int maxSearchLength);
    static void getMaxMinInsideSegment(char* inArray, int arrayLenght, int * nMinIndex, int * nMaxIndex);
};

#endif
