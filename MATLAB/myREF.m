function Kref = myREF(R, L, Km, Bm, I, omega_max, i_max, v_max)

%---System Matrices----------------------------------------------
%---| x = Ax + Bu |----------------------------------------------
%---| y = Cx      |----------------------------------------------
A = [-Bm/I Km/I; -Km/L -R/L];
B = [0; 1/L];
C = [1 0];

Kref = -2*inv(C*inv(A)*B);