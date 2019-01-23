%USER SETTINGS________________________________________________________
%motor params
R = 1.15; % [Ohm] Motor armature Resistence
L = 1.5*10^(-3); % [Henry] Motor armature Inductance 
K = 0.383; % [V/rad/s] Back electromotive force coefficient 
I = 0.0021; % [Kg*m^2] Equivalent moment of inertia
B = 0.0088; % [N*m*s/rad] Equivalent viscous damping coefficient

%sensors (boolean: 1->measured, 0->not measured)
omega_meas = 1;
i_meas = 0;

%linsys matrices_____________________________________________________
%---| x = Ax + B1u |-------------------------------------------------
%---| y = Cx       |-------------------------------------------------
A = [-B/I K/I; -K/L -R/L];
B1 = [0; 1/L];
C = [omega_meas 0; 0 i_meas];

if(rank(ctrb(A,B1))~=2) % reachability check
    disp("system not fully reachable");
    %perform some actions (e.g. led blinking)
else disp("system fully reachable");    
end    
   
