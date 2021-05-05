#include "Servo.h"
#include "DueTimer.h"

/* Default Tuning Variables */

#define MIN_I_TERM      (-250)  // Minimum Contribution of iTerm in PI controller
#define MAX_I_TERM      (250)   // Maximum Contribution of iTerm in PI controller
#define COMMAND         (-20)     // Commanded/Requested pitch (in degrees from horizontal)
#define FREQUENCY       (100)   // Refresh rate of controlller (in Hz)

/* Hardware Restrictions */
#define MIN_ANGLE       (-65)
#define MAX_ANGLE       (30)
#define MAX_FREQ        (1000) // Maximum refresh rate (in Hz)

/* Pin Numbers */
#define ESC_PIN         (6)   // PWM pin for signaling ESC
#define DRIVE_PIN       (10)  // Drive pin for power MOSFET
#define SENSOR_PIN      (A0)  // Pin for reading sensor values

/* Filter buffer size */
#define BUFFER_SIZE     (2)

/* Controller struct */
typedef struct PID_t {
  float   input;      // Input to controller (requested value)
  float   dt;         // Period between updates (in seconds)
  float   old_error;  // Last error value
  float   iState;     // Integrator state (accumulated error)
} PID;

volatile PID controller;  // PID controller for the system
volatile double pitch;     // Measured pitch
Servo ESC;                // ESC to drive motor
volatile int drive;       // Drive signal value fed to ESC

float newAngle;

// Initialize variables
float u[3]; // System error as input to controller
float y[3]; // System error as input from controller

double pitch_value;

volatile bool updatedPID; // Flag to indicate whenever controller is updated

float filterBuffer[BUFFER_SIZE];  // Array for moving average filter
float filteredVal;                // Current filtered valued
int idx;                        // Current idx of filterBuffer

double starttime;

// ================================================================
// ===                    HELPER FUNCTIONS                      ===
// ================================================================

/*
 * Reset the state of controller, filter, and pitch reading
 * Should be invoked whenever the system is stopped or paused
 */
void resetSystem() {
  // Reset drive signal
  drive = 0;

  // Reset updatedPID flag
  updatedPID = false;

  pitch=-20.0;

  // Reset the integrator state
  controller.iState = 0;

  // Re-initialize the derivative state to prevent derivative spikes
  controller.old_error = controller.input - pitch;
}

/*
 * Update PID output signal using current system state
 */
void ISR_controller_handler() {

//  Serial.println("in ISR");
  double uterms=0;
  double yterms = 0;
  double y_i = 0;

  // If potentiometer
  pitch_value = analogRead(SENSOR_PIN);
  pitch = ((975-pitch_value)*0.1875) - 55;
 
  // pitch_value = REG_TC0_CV0;
  // pitch = 120*(pitch_value*(360/2048))/1900;

  // Measure and filter rotary sensor value
 

 

  pitch = constrain(pitch, -40, 10);
 
  // Controller error is difference between input and current state
  float error = controller.input - pitch;
  u[2] = error;

//  Serial.print("error: ");
//  Serial.println(error);

  // 2ms
  uterms = 47.66*u[2] - 94.61 * u[0] + 46.96 * u[1];
  yterms = 1.538 * y[0] - 0.538 * y[1];

//  uterms = 50.48*u[2] - 100.4 * u[0] + 49.93 * u[1];
//  yterms = 1.633 * y[0] - 0.6327 * y[1];
 
  y_i = uterms + yterms;

  /**
   * y[0] = y[i-1] in DT terms
   * y[1] = y[i-2] in DT terms
   */
  y[1] = y[0];
  y[0] = uterms + yterms;
  y[2] = y_i;
 
  /**
   * u[0] = u[i-1] in DT terms
   * u[1] = u[i-2] in DT terms
   */
  u[1] = u[0];
  u[0] = error;

  double res= y_i + 52;
//  Serial.print("res: ");
//  Serial.println(res);
 
  drive = constrain(res, 44.2241, 73.31);
//  Serial.print("drive: ");
//  Serial.println(drive);
 
  // Send new drive signal to ESC
  drive = res;
  ESC.write(drive);

  // Set updatedPID flag
  updatedPID = true;

}

/*
 * Calibrate ESC's PWM range for first use
 */
void calibrate(Servo *ESC) {
  Serial.print("Calibrating ESC... ");
  digitalWrite(DRIVE_PIN, LOW);   // Disconnect ESC from power
  delay(500);                     // Wait 500ms
  ESC->write(141.2069);           // Request full speed
  digitalWrite(DRIVE_PIN, HIGH);  // Reconnect ESC to power
  delay(5000);                    // Wait 5 seconds
  ESC->write(44.2241);            // Request 0 speed
  delay(8000);                    // Wait 8 seconds
  Serial.println("Calibration complete");
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Attach ESC
  ESC.attach(ESC_PIN);

  // Configure I/O pins
  pinMode(DRIVE_PIN, OUTPUT);
  digitalWrite(DRIVE_PIN, LOW);

  // Setup initial PID controller values
  controller.input      = COMMAND;
  controller.dt         = 1.0 / FREQUENCY;
 
  /**
   *  Everytime you arm and then callibrate
   */
  calibrate(&ESC);
  /* End of arming and callibration */

//  // Reset system parameters before starting to avoid unpredictable behavior
//  resetSystem();
 
  newAngle = -20.0;

  u[0]=0;
  u[1]=0;
  u[2]=0;

  y[0]=0;
  y[1]=0;
  y[2]=0;

  pitch_value = 0;

//   Attach ISR for Due Timer interrupt
  Timer6.attachInterrupt(ISR_controller_handler);
  Timer6.start(2000); // Calls every 2ms

  analogReadResolution(12);

  REG_PMC_PCER0 = PMC_PCER0_PID27;
  REG_TC0_BMR = TC_BMR_QDEN;
  REG_TC0_CMR0 = TC_CMR_TCCLKS_XC0;
  REG_TC0_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA;
  REG_TC0_CCR0 = TC_CCR_CLKEN | TC_CCR_SWTRG;  

  starttime = millis();
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  pitch_value = REG_TC0_CV0;

  controller.input = -20.0;
  Serial.println(millis()-starttime);
  Serial.println(pitch);
 
}
