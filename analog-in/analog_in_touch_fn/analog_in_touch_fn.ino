const int PinI = 0; //input
const int ValuesSize = 10;
const float ErrorThreshold = 70.0;
int Values[ValuesSize];
int Frame;

void setup() {
  pinMode(PinI, INPUT);
  Serial.begin(9200);
  for(int i=0; i<ValuesSize; i++){
    Values[i] = 0;
  }
  Frame = 0;
}

void loop() {
  Frame++;
  int val = analogRead(PinI);

  update_values(Values, sizeof(Values)/sizeof(int), val);

  float total = calc_total(Values, sizeof(Values)/sizeof(int));
  float mean = calc_mean(Values, sizeof(Values)/sizeof(int));
  float rootMeanSquareError = calc_rootMeanSquareError(Values, ValuesSize, mean);

  bool isTouch = check_touch(rootMeanSquareError, ErrorThreshold);
  
  print_bool("", isTouch, " ");
  print_int("", val, " ");
  print_float("total=", total, " ");
  print_float("mean=", mean, " ");
  print_float("rootMeanSquareError=", rootMeanSquareError, " ");
  print_ints("values=[", Values, sizeof(Values)/sizeof(int), "] ");  
  Serial.println("");
}

//######################################################################
//######################################################################
//######################################################################

void update_values(int _values[], int _valuesSize, int _val){
  if(Frame < _valuesSize){
    _values[Frame] = _val;
  } else {
    for(int i=0; i<_valuesSize-1; i++){
      _values[i] = _values[i+1];
    }
    _values[_valuesSize-1] = _val;
  }
}

//----------------------------------------------------------------------

float calc_total(int _values[], int _valuesSize){
  float _total = 0;
  for(int i=0; i<_valuesSize; i++){
    _total+=_values[i];
  }
  return _total;
}

//----------------------------------------------------------------------

float calc_mean(int _values[], int _valuesSize){
  float _total = 0;
  float _mean = 0;
  _total = calc_total(_values, _valuesSize);
  _mean = _total/float(_valuesSize);
  return _mean;
}

//----------------------------------------------------------------------

float calc_rootMeanSquareError(int _values[], int _valuesSize, float _trueValue){
  float _totalSquareError = 0;
  float _meanSquareError = 0;
  float _rootMeanSquareError = 0;
  for(int i=0; i<_valuesSize; i++){
    float _error = _values[i]-_trueValue;
    _totalSquareError+=_error*_error;
  }
  _meanSquareError = _totalSquareError/float(_valuesSize);
  _rootMeanSquareError = sqrt(_meanSquareError);
  return _rootMeanSquareError;
}

//----------------------------------------------------------------------

bool check_touch(float _rootMeanSquareError, float _errorThreshold){
  bool _isTouch = false;
  if (_rootMeanSquareError <= _errorThreshold){
    Serial.print("[touch!!] ");
    _isTouch = true;
  }else{
    Serial.print("[release] ");
  }
  return _isTouch;
}

//----------------------------------------------------------------------

void print_int(char* _c1, int _x, char* _c2){
  Serial.print(_c1);
  Serial.print(_x);
  Serial.print(_c2);
}

//----------------------------------------------------------------------

void print_float(char* _c1, float _x, char* _c2){
  Serial.print(_c1);
  Serial.print(_x);
  Serial.print(_c2);
}

//----------------------------------------------------------------------

void print_bool(char* _c1, bool _x, char* _c2){
  Serial.print(_c1);
  Serial.print(_x);
  Serial.print(_c2);
}
//----------------------------------------------------------------------

void print_ints(char* _c1, int _x[], int _xSize, char* _c2){
  Serial.print(_c1);
  for(int i=0; i<_xSize-1; i++){
    print_int("", _x[i], " ");
  }
  print_int("", _x[_xSize-1], "");
  Serial.print(_c2);
}


