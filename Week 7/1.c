#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
    float amount_taken;
}item;

void swap (item *a, item *b){
    item temp = *a;
    *a=*b;
    *b=temp;
}

void heapify(){

}

void heapSort(){
    
}