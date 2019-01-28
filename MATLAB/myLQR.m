function S = myLQR(R, L, Km, Bm, I, omega_max, i_max, v_max)

%---System Matrices----------------------------------------------
%---| x = Ax + Bu |----------------------------------------------
%---| y = Cx      |----------------------------------------------
A = [-Bm/I Km/I; -Km/L -R/L];
B = [0; 1/L];
C = [1 0];

%--State and Output Penalization---------------------------------
%Q = 1/2*inv([(omega_max)^2 0; 0 (i_max)^2; 0 0 (int_max)^2]);
Q = 1/2*inv([(omega_max)^2 0; 0 (i_max)^2]);
R = inv([(v_max)^2]);

%RICCATI
n=size(A,1);
G=(1/R).*B*B';
H=[A -G; -Q -A'];
[U,~]=schur(H);
Sinf=U(n+1:end,1:n)*U(1:n,1:n)^-1;

K=-(1/R).*B'*Sinf;
Kw=K(1);
Ki=K(2);

S = [R, L, Km, Bm, I, Kw, Ki];
