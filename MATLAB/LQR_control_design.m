%USER SETTINGS________________________________________________________
%motor params
R = 1.15; % [Ohm] Motor armature Resistence
L = 1.5*10^(-3); % [Henry] Motor armature Inductance 
K = 0.383; % [V/rad/s] Back electromotive force coefficient 
I = 0.0021; % [Kg*m^2] Equivalent moment of inertia
B = 0.0088; % [N*m*s/rad] Equivalent viscous damping coefficient

%sensors acquisition params
PPR = 1000; % ENCODER pulses per revolution
ADC_Vref = 3.3; % [V] reference voltage of the ADC
ADC_bits = 12; % resolution (number of bits) of the adc
current_gain = 0.5; % current sensor conversion gain
current_offset = 1; % current sesnsor conversion offset
omega_gain = 0.5; % omega ref sensor conversion gain
omega_offset = 1; % omega sensor conversion offset

%actuation
Vact = 12; % [V] amplitude af actuation PWM applied to the motor

%LQR tuning
omega_max = 20; % [rad/sec] maximum admitted angular speed
i_max = 20; % [A] maximum admitted current
int_max = 2; % integral error maximum
v_max = 10; % [V] maximum admitted input voltage

%linsys matrices_____________________________________________________
%---| x = Ax + Bu |--------------------------------------------------
%---| y = Cx      |--------------------------------------------------
A = [-B/I K/I; -K/L -R/L];
B = [0; 1/L];
C = [1 0];

if(rank(ctrb(A,B))~=2) % reachability check
    disp("system not fully reachable");
    %perform some actions (e.g. led blinking)
else disp("system fully reachable");    
end    
   
%LQR controller______________________________________________________
Q = 1/2*inv([(omega_max)^2 0 ; 0 (i_max)^2]); % state penalization
R = inv([(v_max)^2]); % input penalization
%sys = ss(A,B,C,0);
%[K_m,S,e] = lqr(sys,Q,R) % gain K computation
%K = -K;
%RICCATI  Solves an algebraic Riccati equation
%   X = Riccati(A,G,Q) solves the algebraic Riccati equation of the form:
%       A'*X + X*A' - X*G*X + Q = 0, where X is symmetric.

   n=size(A,1);
   G = (1/R).*B*B';

   H = [A -G; -Q -A'];

   [U1,S1] = schur(H);
   %[U,S]=ordschur(U1,S1,'lhp');

   X = U(n+1:end,1:n)*U(1:n,1:n)^-1;
%end RICCATI
%[Sc,L,J] = care(A,B,Q,R);
Sinf = X;
   
K = -(1/R).*B'*Sinf
%Kc = -(1/R).*B'*Sc