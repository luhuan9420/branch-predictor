//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "predictor.h"

//
// TODO:Student Information
//
const char *studentName1 = "Huan Ho";
const char *studentID1   = "A59012210";
const char *email1       = "h4ho@ucsd.edu";

const char *studentName2 = "NAME";
const char *studentID2   = "PID";
const char *email2       = "EMAIL";

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

int ghistoryBits; // Number of bits used for Global History
int lhistoryBits; // Number of bits used for Local History
int pcIndexBits;  // Number of bits used for PC index
int bpType;       // Branch Prediction Type
int verbose;

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

//
//TODO: Add your own Branch Predictor data structures here
//
int global_hist;
uint8_t *gshare_BHT;
int gmask;


//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void
init_predictor()
{
  switch (bpType) {
    case STATIC:
      break;
    case GSHARE:
      init_GSHARE();
      break;
    case TOURNAMENT:
      init_TOURNAMENT();
      break;
    case CUSTOM:
      init_CUSTOM();
      break;
    default:
      break;
  }
}

// Helper method for initializing 3 types of predictors
void init_GSHARE(){
  gmask = (1 << ghistoryBits) -1;
  global_hist = 0;
  int size = (1 << ghistoryBits);
  gshare_BHT = malloc(size * sizeof(uint8_t));
  for(int i = 0; i < size; i++){
    gshare_BHT[i] = WN; // weak not taken (n)
  }
}

void init_TOURNAMENT(){

}

void init_CUSTOM(){

}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
make_prediction(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //

  // Make a prediction based on the bpType
  switch (bpType) {
    case STATIC:
      return TAKEN;
    case GSHARE:
      return pred_GSHARE(pc);
    case TOURNAMENT:
      return pred_TOURNAMENT(pc);
    case CUSTOM:
      return pred_CUSTOM(pc);
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}

// Helper methods to make prediction for each of the 3 types of predictors
uint8_t pred_GSHARE(uint32_t pc){
  //int mask = (1 << ghistoryBits) -1;
  uint32_t index = (pc^global_hist) & gmask;
  if(gshare_BHT[index] <= 1){
    return NOTTAKEN;
  }
  else{
    return TAKEN;
  }
}

uint8_t pred_TOURNAMENT(uint32_t pc){
  
}

uint8_t pred_CUSTOM(uint32_t pc){
  
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
train_predictor(uint32_t pc, uint8_t outcome)
{
  switch (bpType) {
    case STATIC:
      break;
    case GSHARE:
      train_GSHARE(pc, outcome);
      break;
    case TOURNAMENT:
      train_TOURNAMENT(pc, outcome);
      break;
    case CUSTOM:
      train_CUSTOM(pc, outcome);
      break;
    default:
      break;
  }
}

// Helper methods to train predictor for each of the 3 types of predictors
void train_GSHARE(uint32_t pc, uint8_t outcome){
  uint32_t index = (pc ^ global_hist) & gmask;
  updateBHT(gshare_BHT, index, outcome); 
  global_hist = (global_hist << 1) | outcome;
}

void train_TOURNAMENT(uint32_t pc, uint8_t outcome){
  
}

void train_CUSTOM(uint32_t pc, uint8_t outcome){
  
}

void updateBHT(uint8_t *BHT, uint32_t index, uint8_t outcome){
  if(outcome == NOTTAKEN && BHT[index] != SN){
    BHT[index]--;
  }
  else if (outcome == TAKEN && BHT[index] != ST){
    BHT[index]++;
  }
}
