#include "dotlist.h"
#define M_SQRT_3_4 0.86602540378443864676372317
#define M_SQRT_3 1.73205080756887729352744634
#define M_SQRT_1_3 0.5773502691896257645091487805
#define M_1PHI 0.6180339887498948482046
#define M_SQRTCUBE_1PHI 0.48586827175664567817745
#define KIND_COMPOSITE -1
#define KIND_PRIME -2
#define KIND_FIBONACCI -3
#define KIND_SQUARE -4
#define KIND_PRONIC -5
#define KIND_TRIANGLE -6
#define KIND_HEXAGON -7
#define NUM_KINDS 7

DotList asterPattern(int n);
DotList basePattern(int n,int base);
DotList compositePattern(int n);
DotList fibonacciPattern(int n);
DotList squarePronicPattern(int n);
DotList trianglePattern(int n);
DotList hexagonPattern(int n);

bool isComposite(int n);
bool isPrime(int n);
bool isFibonacci(int n);
bool isSquare(int n);
bool isPronic(int n);
bool isTriangle(int n);
bool isHexagon(int n);

DotList kindPattern(int n,int kind);
bool isKind(int n,int kind);
