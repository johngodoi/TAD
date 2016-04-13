//
// Created by john on 12/04/16.
//

#ifndef TAD_SPARSEMATRIX_H
#define TAD_SPARSEMATRIX_H

#include <stdlib.h>

typedef struct BucketStruct *BucketPointer;

typedef struct BucketStruct {
    int value;
    int columnIndex;
    int rowIndex;
    BucketPointer column;
    BucketPointer row;
} Bucket;

typedef struct SparseMatrixStruct *SparseMatrixPointer;

typedef struct SparseMatrixStruct {
    int columnQuantity;
    int rowQuantity;
    BucketPointer pivot;
} SparseMatrix;

BucketPointer findPreviousColumn(SparseMatrixPointer sparseMatrixPointer, BucketPointer bucket);

BucketPointer findPreviousRow(SparseMatrixPointer sparseMatrixPointer, BucketPointer bucket);

BucketPointer instantiateBucket(int value, int rowIndex, int columnIndex, BucketPointer previousRow,
                                BucketPointer previousColumn){
    BucketPointer pointer = (BucketPointer) malloc(sizeof(Bucket));
    if(previousColumn!=NULL) {
        pointer->column = previousColumn->column;
        previousColumn->column = pointer;
    } else pointer->column = pointer;
    if(previousRow!=NULL){
        pointer->row = previousRow->row;
        previousRow->row = pointer;
    } else pointer->row = pointer;
    pointer->columnIndex = columnIndex;
    pointer->rowIndex = rowIndex;
    pointer->value = value;
    return pointer;
}

SparseMatrixPointer instantiate(int rowQuantity, int columnQuantity){
    SparseMatrixPointer pointer = (SparseMatrixPointer) malloc(sizeof(SparseMatrix));
    pointer->columnQuantity=columnQuantity;
    pointer->rowQuantity=rowQuantity;
    return pointer;
}

BucketPointer initializeBuckets(int rowQuantity, int columnQuantity){
    BucketPointer pivot = instantiateBucket(-1, -1, -1, NULL, NULL);
    BucketPointer auxiliary = pivot;
    for (int j = 0; j < columnQuantity; ++j) {
        BucketPointer newBucket = instantiateBucket(-1, -1, j, NULL, auxiliary);
        newBucket->column = auxiliary->column;
        auxiliary=newBucket;
    }
    auxiliary->column = pivot;
    auxiliary = pivot;
    for (int i = 0; i < rowQuantity; ++i) {
        BucketPointer newBucket = instantiateBucket(-1, i, -1, auxiliary, NULL);
        newBucket->row = auxiliary->row;
        auxiliary=newBucket;
    }
    auxiliary->row = pivot;
    return pivot;
}

SparseMatrixPointer initialize(int rowQuantity, int columnQuantity){
    SparseMatrixPointer sparseMatrix = instantiate(rowQuantity, columnQuantity);
    sparseMatrix->pivot = initializeBuckets(rowQuantity,columnQuantity);
    return sparseMatrix;
}

BucketPointer findLastBucketByRows(SparseMatrixPointer sparseMatrixPointer, int rowIndex, int columnIndex) {
    BucketPointer bucketPointer = sparseMatrixPointer->pivot;
    while(bucketPointer->row!=sparseMatrixPointer->pivot){
        if(bucketPointer->rowIndex==rowIndex){
            BucketPointer actual = bucketPointer;
            while(bucketPointer->column != actual){
                bucketPointer=bucketPointer->column;
                if(bucketPointer->columnIndex==columnIndex){
                    break;
                }
            }
            return bucketPointer;
        }
        bucketPointer=bucketPointer->row;
    }
    return bucketPointer;
}

BucketPointer findLastBucketByColumns(SparseMatrixPointer sparseMatrixPointer, int rowIndex, int columnIndex) {
    BucketPointer bucketPointer = sparseMatrixPointer->pivot;
    while(bucketPointer->column!=sparseMatrixPointer->pivot){
        if(bucketPointer->columnIndex==columnIndex){
            BucketPointer actual = bucketPointer;
            while(bucketPointer->row != actual){
                bucketPointer=bucketPointer->row;
                if(bucketPointer->rowIndex==rowIndex) {
                    break;
                }
            }
            return bucketPointer;
        }
        bucketPointer=bucketPointer->column;
    }
    return bucketPointer;
}

BucketPointer findClosest(SparseMatrixPointer sparseMatrixPointer, int rowIndex, int columnIndex) {
    BucketPointer bucketPointer = sparseMatrixPointer->pivot;
    while(bucketPointer->column!=sparseMatrixPointer->pivot){
        bucketPointer=bucketPointer->column;
        if(bucketPointer->columnIndex==columnIndex){
            break;
        }
    }
    BucketPointer actual = bucketPointer;
    while(bucketPointer->row!=actual){
        bucketPointer=bucketPointer->row;
        if(bucketPointer->rowIndex==rowIndex){
            break;
        }
    }
    return bucketPointer;
}

SparseMatrixPointer insert(SparseMatrixPointer sparseMatrixPointer, int row, int column, int value){
    BucketPointer previousColumn = findLastBucketByColumns(sparseMatrixPointer, row, column);
    BucketPointer previousRow = findLastBucketByRows(sparseMatrixPointer, row, column);
    if(previousColumn->columnIndex==column && previousColumn->rowIndex==row){ //update
        previousColumn->value = value;
    } else if(previousRow->columnIndex==column && previousRow->rowIndex==row){
        previousRow->value=value;
    } else if(previousColumn !=  previousRow) {
        BucketPointer newBucket = instantiateBucket(value, row, column, NULL, NULL);
        newBucket->column = previousRow->column;
        previousRow->column = newBucket;
        newBucket->row = previousColumn->row;
        previousColumn->row = newBucket;
    }
    return sparseMatrixPointer;
}

void print(SparseMatrixPointer sparseMatrixPointer){
    for (int i = 0; i < sparseMatrixPointer->rowQuantity; ++i) {
        for (int j = 0; j < sparseMatrixPointer->columnQuantity; ++j) {
            BucketPointer bucket = findClosest(sparseMatrixPointer, i, j);
            if(bucket->rowIndex==i && bucket->columnIndex == j){
                printf("%d", bucket->value);
            } else {
                printf("0");
            }
            printf("\t");
        }
        printf("\n");
    }
}

BucketPointer removeOn(SparseMatrixPointer sparseMatrixPointer, int rowIndex, int columnIndex){
    BucketPointer bucket = findClosest(sparseMatrixPointer, rowIndex, columnIndex);
    if(bucket->columnIndex==columnIndex && bucket->rowIndex==rowIndex){
        BucketPointer previousRow = findPreviousRow(sparseMatrixPointer, bucket);
        BucketPointer previousColumn = findPreviousColumn(sparseMatrixPointer, bucket);
        previousRow->row=bucket->row;
        if(previousRow->column==bucket) previousRow->column=NULL;
        previousColumn->column=bucket->column;
        if(previousColumn->row==bucket) previousColumn->row=NULL;
        return bucket;
    }
    return bucket; 
}

BucketPointer findPreviousRow(SparseMatrixPointer sparseMatrixPointer, BucketPointer bucket) {
    BucketPointer previousRow = bucket->row;
    while(previousRow->rowIndex!=-1){
        previousRow=previousRow->row;
    }
    while(previousRow->row!=bucket){
        previousRow=previousRow->row;
    }
    return previousRow;
}
BucketPointer findPreviousColumn(SparseMatrixPointer sparseMatrixPointer, BucketPointer bucket) {
    BucketPointer previousColumn = bucket->column;
    while(previousColumn->columnIndex!=-1){
        previousColumn=previousColumn->column;
    }
    while(previousColumn->column!=bucket){
        previousColumn=previousColumn->column;
    }
    return previousColumn;
}

#endif //TAD_SPARSEMATRIX_H
