// Local variables
double error = 0;
//int outMax = 255;
//int outMin = -255;
int outMax = 155;
int outMin = -155;
float lastInput = 0;
double Integral_Term = 0;
double dInput = 0;


// Calculates the PID output
double Compute(double input)
{

  error = Setpoint - input;

  Integral_Term = (ki * error) + Integral_Term;

  dInput = (input - lastInput);

  // Compute PID Output
//  output = kp * error +  Integral_Term + kd * dInput;
  output = kp * error +  Integral_Term + kd * dInput;

  if (output > outMax) 
  {
    output = outMax;
//    Integral_Term = 0;
  }
  else if (output < outMin) 
  {
    output = outMin;
//    Integral_Term = 0;
  }

  // Remember some variables for next time
  lastInput = input;
  return output;
}
