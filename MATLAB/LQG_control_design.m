%USER SETTINGS________________________________________________________
%motor params
R = 1.15; % [Ohm] Motor armature Resistence
L = 1.5*10^(-3); % [Henry] Motor armature Inductance 
K = 0.383; % [V/rad/s] Back electromotive force coefficient 
I = 0.0021; % [Kg*m^2] Equivalent moment of inertia
B = 0.0088; % [N*m*s/rad] Equivalent viscous damping coefficient

%sensors (boolean: 1->measured, 0->not measured)
%omega_meas = 1;
%i_meas = 1;

%LQR tuning
omega_max = 20; % [rad/sec] maximum admitted angular speed
i_max = 20; % [A] maximum admitted current
int_max = 2; % integral error maximum
v_max = 10; % [V] maximum admitted input voltage

%linsys matrices_____________________________________________________
%---| x = Ax + B1u |-------------------------------------------------
%---| y = Cx       |-------------------------------------------------
A = [-B/I K/I; -K/L -R/L];
B = [0; 1/L];
C = [1 0];

if(rank(ctrb(A,B))~=2) % reachability check
    disp("system not fully reachable");
    %perform some actions (e.g. led blinking)
else disp("system fully reachable");    
end    
   
%LQR controller______________________________________________________
Q = 1/2*inv([(omega_max)^2 0 0; 0 (i_max)^2 0; 0 0 (int_max)^2]); % state penalization
R = inv([(v_max)^2]); % input penalization
sys = ss(A,B,C,0);
[K,S,e] = lqi(sys,Q,R); % gain K computation
K = -K;
%G = 1/(C*inv(A+B*K)*B); % trajectory tracking gain
