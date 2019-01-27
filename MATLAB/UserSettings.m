import Parameters.*; 
%% USER SETTINGS-------------------------------------------------
%--Plant Timing--------------------------------------------------
ESTIMATION_SAMPLES = 50;
SAMPLE_TIME = 5e-5;
DATA_SAMPLING_FREQUENCY = 500;

%--Parameter Estimation------------------------------------------
motorParameters = Parameters(); 
motorParameters.range('R', [1e-1 1e2]) ...
               .range('L', [1e-5 1e-2]) ...
               .range('K', [1e-3 1]) ...
               .range('f', [1e-7 1e-4]) ...
               .range('Jm', [1e-8 1e-4]); 

%--Motor Parameters (SIL)----------------------------------------
R = 65; % [Ohm] Motor armature Resistence
L = 1.41e-3; % [Henry] Motor armature Inductance 
Km = 2.55e-2; % [V/rad/s] Back electromotive force coefficient 
I = 7.2e-8; % [Kg*m^2] Equivalent moment of inertia
Bm = 1.11e-7; % [N*m*s/rad] Equivalent viscous damping coefficient

%--Sensors Acquisition Parameters--------------------------------
PPR = 1000; % ENCODER pulses per revolution
ADC_Vref = 3.3; % [V] reference voltage of the ADC
ADC_bits = 12; % resolution (number of bits) of the adc
current_gain = 0.5; % current sensor conversion gain
current_offset = 1; % current sesnsor conversion offset
omega_gain = 0.5; % omega ref sensor conversion gain
omega_offset = 1; % omega sensor conversion offset

%--Actuation-----------------------------------------------------
V_ACT = 12; % [V] amplitude af actuation PWM applied to the motor

%--LQR tuning----------------------------------------------------
omega_max = 20; % [rad/sec] maximum admitted angular speed
i_max = 20; % [A] maximum admitted current
int_max = 2; % integral error maximum
v_max = 10; % [V] maximum admitted input voltage

%--State and Output Penalization---------------------------------
%Q = 1/2*inv([(omega_max)^2 0; 0 (i_max)^2; 0 0 (int_max)^2]);
Q = 1/2*inv([(omega_max)^2 0; 0 (i_max)^2]);
R = inv([(v_max)^2]);

A = [-Bm/I Km/I; -Km/L -R/L];
B = [0; 1/L];
C = [1 0];