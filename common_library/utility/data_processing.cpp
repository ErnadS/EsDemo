/*
 * DataProcessing.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: ernad
 */

#include "data_processing.h"

#include <stdio.h>

#define SAMPLE_FILTER_COUNT 20
// !!! Must be same as in file "DataProcessing.cpp"
int rangeMaxValues[]={10, 50, 100, 500, 1000, 1600}; //the same values as max values in "Range.js"

DataProcessing::DataProcessing() {
	// TODO Auto-generated constructor stub

}

DataProcessing::~DataProcessing() {
	// TODO Auto-generated destructor stub
}

void DataProcessing::kalmanFilter(char* inArray, int dataLength, char* outArray) {
	//initial values for the kalman filter
	float previousValue = inArray[0];
	float P_last = 0;
	//the noise in the system
	float Qk = 0.042;//0.022;   // !!! Kan ikke brukes 0 (hvis Rk er også 0 => error)
	float Rk = 9.1;//0.917; //0.617; // bruk "0" for å disable

	float K;
	float P_temp;

	for (int i = 0; i < dataLength; i++) {
		P_temp = P_last + Qk;
		//calculate the Kalman gain
		K = P_temp * (1.0 / (P_temp + Rk));

		outArray[i] = previousValue + K * (inArray[i] - previousValue);
		P_last = (1 - K) * P_temp;
		previousValue = outArray[i];
	}
}

int DataProcessing::bottomDetection(char* inArray, int dataLength) {
	//int signalMaxIndex = getIndexOfSignalTop(inArray, dataLength);
    const int nSegmsCount = 16;
    const int nSegmentLength = dataLength / nSegmsCount;
    int nSegmArray[nSegmsCount];
    getSegmentsArray(inArray, nSegmsCount, nSegmentLength,
			nSegmArray); // 16* 25 = 400

	int bottom;/* = getBottomStartIndex((unsigned char*) inArray, dataLength,
			nMaxSegInd, nSegmentLength);*/
	//printf("MAX %d, depth: %d\n", nMaxSegInd, bottom);
    int nButtIndex = getMaxDiff(inArray, dataLength);
    bottom = 1000 * nButtIndex / 40; // *10/400
	/*bottom = rangeMaxValues[Data::getInstance()->getRange()] * bottom / 40;*/

	//printf("BOTTOM: %d\n", bottom);
	return bottom; // nMaxSegInd*nSegmentLength;
}

int DataProcessing::getMaxDiff(char *inArray, int arrayLenght) {
	int nMax = 0;
	int nTemp;
	int nInd = 0;

	for (int i = 0; i < arrayLenght - 10; i++) {
		int j;
		for (j=i; j<i+10;j++) {
			nTemp = inArray[j] - inArray[i];
			if (nMax < nTemp) {
				//printf("YES, %d\n",nMax);
				nMax = nTemp;
				nInd = i;
			}
		}
	}
	return nInd;
}

/*
 *
 */
void DataProcessing::getSegmentsArray(char *inArray,
        int segmentsCount, int segmLeng, int* segmArray) {
    for (int i = 0; i < segmentsCount; i++) {
        segmArray[i] = 0;

        for (int j = 0; j < segmLeng; j++)
        {
            segmArray[i] += (unsigned char) inArray[i * segmLeng + j];
        }
    }
}

int DataProcessing::getTopSegment(int* inArray, int arrayLenght) {
	int nMax = 0;
	int nIndex = 0;
	for (int i = 0; i < arrayLenght; i++) {
		//printf("%d %d, ", i, inArray[i]);
		if (nMax < inArray[i]) {
			//	printf("YES, ");
			nMax = inArray[i];
			nIndex = i;
		}
	}
	return nIndex;
}

int DataProcessing::getBottomStartIndex(char *inArray, int segmentIndex, int segmentLength) {
	int nSegmentTopIndex = segmentIndex * segmentLength + getTopInsideSegment(
			&inArray[segmentIndex * segmentLength], segmentLength);
    return getIncreasingStart(inArray, nSegmentTopIndex,
			2 * segmentLength);
}

int DataProcessing::getTopInsideSegment(char *inArray, int arrayLenght) {
	int nMax = 0;
	int nIndex = 0;
	for (int i = 0; i < arrayLenght; i++) {
		//printf("%d %d, ", i, inArray[i]);
		if (nMax < inArray[i]) {
			//	printf("YES, ");
			nMax = inArray[i];
			nIndex = i;
		}
	}
	return nIndex;
}

void DataProcessing::getMaxMinInsideSegment(char *inArray, int arrayLenght, int * nMinIndex, int * nMaxIndex) {
	unsigned char nMax = 0;
	unsigned char nMin = 255;

	for (int i = 0; i < arrayLenght; i++) {
		//printf("%d %d, ", i, inArray[i]);
		if (nMax < inArray[i]) {
			nMax = inArray[i];
			*nMaxIndex = i;
		}
		if (nMin > inArray[i]) {
			nMin = inArray[i];
			*nMinIndex = i;
		}
	}
}

int DataProcessing::getIncreasingStart(char *inArray, int topIndex, int maxSearchLength) {
    int nMinInd{0}, nMaxInd{0};
    int nMin{*inArray}, nMax{*inArray};

    getMaxMinInsideSegment(&inArray[topIndex - maxSearchLength], maxSearchLength, &nMinInd, &nMaxInd);
    nMin = inArray[nMinInd];
    nMax= inArray[nMaxInd];

    int nDiff = (nMax - nMin)*30/100;

    for (int i = 0; i < maxSearchLength; i++) {
        if (inArray[topIndex - i] < nMax - nDiff)
            return topIndex - i;
    }

    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WRONG BOTTOM DETECTION?????\n");
    return topIndex - maxSearchLength;
}
